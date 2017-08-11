//  dcc_audio_3players - AudioPlayer.cpp
//
//  Copyright(C) 2017 Pierre-Yann Bridé
//  
//  This file is part of dcc_audio_3players.
//  
//  dcc_audio_3players is free software : you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  dcc_audio_3players is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with Foobar.If not, see <http://www.gnu.org/licenses/>.

#include "AudioPlayer.h"




AudioPlayerClass::AudioPlayerClass(uint8_t receivePin, uint8_t transmitPin)
{
	_transitionDuration = 10000;
	_softSerialPlayer = new SoftwareSerial(receivePin, transmitPin); // RX, TX
}

void AudioPlayerClass::Init(uint8_t transitionDuration)
{
	_transitionDuration = transitionDuration * 1000;
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
	_timer = millis();
	Transition();
}

void AudioPlayerClass::ArduinoLoop()
{
	if (!_isTransition)
		return;	
	if (millis() - _timer > _transitionDuration)
	{
		_isTransition = false;
		Serial.print("AudioPlayerClass transition end:");
		Serial.println(!_isNight);
		_softSerialPlayer->listen();
		_dfPlayer.disableLoop();
		_isPlayerPlaying = false;		
		Loop();
	}
	
}

void AudioPlayerClass::Transition()
{
	_isTransition = true;
	if (!_isPlayerPlaying)
	{
		_isPlayerPlaying = true;
		if (_isNight)
			_dfPlayer.loop(2);
		else
			_dfPlayer.loop(4);
	}
}

void AudioPlayerClass::Loop()
{
	if (!_isPlayerPlaying)
	{
		_isPlayerPlaying = true;
		if (_isNight)
			_dfPlayer.loop(3);
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
