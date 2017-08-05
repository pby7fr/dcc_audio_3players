// 
// 
// 

#include "AudioPlayer.h"




AudioPlayerClass::AudioPlayerClass(uint8_t receivePin, uint8_t transmitPin)
{

	_softSerialPlayer = new SoftwareSerial(receivePin, transmitPin); // RX, TX

}

void AudioPlayerClass::Init()
{
	_softSerialPlayer->begin(9600);


	_softSerialPlayer->listen();
	if (!_dfPlayer.begin(*_softSerialPlayer))
	{ //Use softwareSerial to communicate with mp3.
#ifdef DEBUG
		Serial.println(F("Unable to begin (DFPlayer 1):"));
		Serial.println(F("1.Please recheck the connection! (DFPlayer 1)"));
		Serial.println(F("2.Please insert the SD card! (DFPlayer 1)"));
#endif // DEBUG

		while (true);
	}
}

void AudioPlayerClass::SetVolume(uint8_t volume)
{
	_dfPlayer.volume(volume); //Set volume value. From 0 to 30
}

void AudioPlayerClass::SetIsNight(bool isNight)
{
	_isNight = isNight;
	//_player1NeedRestart = true;
	_softSerialPlayer->listen();
	_dfPlayer.disableLoop();
	_isPlayerPlaying = false;
	Loop();
}

void AudioPlayerClass::Loop()
{
	if (!_isPlayerPlaying)
	{
		_isPlayerPlaying = true;
		if (_isNight)
			_dfPlayer.loop(2);
		else
			_dfPlayer.loop(1);
	}
}

void AudioPlayerClass::Stop()
{
	if (_isPlayerPlaying)
	{
		_isPlayerPlaying = false;
		_dfPlayer.stop();
	}
}
