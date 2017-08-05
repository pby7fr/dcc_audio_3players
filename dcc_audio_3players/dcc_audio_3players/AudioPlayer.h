// AudioPlayer.h

#ifndef _AUDIOPLAYER_h
#define _AUDIOPLAYER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

class AudioPlayerClass
{
 protected:
	 SoftwareSerial* _softSerialPlayer;
	 DFRobotDFPlayerMini _dfPlayer;

	 bool _isPlayerPlaying = false;
	 bool _isNight = false;

 public:
	 AudioPlayerClass(uint8_t receivePin, uint8_t transmitPin);
	 void Loop();
	 void Stop();
	 void Init();
	 void SetVolume(uint8_t volume);
	 void SetIsNight(bool isNight);
};

extern AudioPlayerClass AudioPlayer;

#endif

