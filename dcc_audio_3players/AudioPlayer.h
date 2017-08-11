//  dcc_audio_3players - AudioPlayer.h
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
	 bool _isTransition = false;
	 unsigned long _timer = 0;
	 unsigned long _transitionDuration;

	 void Transition();

 public:
	 AudioPlayerClass(uint8_t receivePin, uint8_t transmitPin);
	 void Loop();
	 void Stop();
	 void Init(uint8_t transitionDuration);
	 void SetVolume(uint8_t volume);
	 void SetIsNight(bool isNight);
	 void ArduinoLoop();
};

extern AudioPlayerClass AudioPlayer;

#endif

