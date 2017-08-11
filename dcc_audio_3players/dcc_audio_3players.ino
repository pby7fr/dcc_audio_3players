//  dcc_audio_3players - dcc_audio_3players.ino
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

// ******** UNLESS YOU WANT ALL CV'S RESET UPON EVERY POWER UP
// ******** AFTER THE INITIAL DECODER LOAD REMOVE THE "//" IN THE FOOLOWING LINE!!

#define DECODER_LOADED

// ******** REMOVE THE "//" IN THE FOOLOWING LINE TO SEND DEBUGGING
// ******** INFO TO THE SERIAL MONITOR
//#define DEBUG
//#define _DEBUG


// the setup function runs once when you press reset or power the board

#include <NmraDcc.h>


NmraDcc Dcc;
DCC_MSG Packet;
uint8_t CV_DECODER_MASTER_RESET = 120;
int t; // temp
#define This_Decoder_Address 3

#define CV_FACTORY_RESET 8

#define CV_SND_MUTE_VOL  135

#define CV_SND_PLAYER1_VOL  141
#define CV_SND_PLAYER2_VOL  142
#define CV_SND_PLAYER3_VOL  143

#define CV_AUTO_TRANSITION  145
#define CV_TRANSITION_DURATION  146

#define CV_ALL_USE_TRANSITION  150
#define CV_PLAYER1_USE_TRANSITION  151
#define CV_PLAYER2_USE_TRANSITION  152
#define CV_PLAYER3_USE_TRANSITION  153

struct QUEUE
{
	int inuse;
	int current_position;
	int increment;
	int stop_value;
	int start_value;
};

QUEUE* ftn_queue = new QUEUE[17];

uint8_t Decoder_Address = This_Decoder_Address;

struct CVPair
{
	uint16_t CV;
	uint8_t Value;
};

CVPair FactoryDefaultCVs[] =
{
	// The CV Below defines the Short DCC Address
	{CV_MULTIFUNCTION_PRIMARY_ADDRESS, This_Decoder_Address},

	// These two CVs define the Long DCC Address
	{CV_MULTIFUNCTION_EXTENDED_ADDRESS_MSB, 0},
	{CV_MULTIFUNCTION_EXTENDED_ADDRESS_LSB, This_Decoder_Address},

	{CV_FACTORY_RESET, 0}, // set to 8 to reset all CVs to factory default

	// ONLY uncomment 1 CV_29_CONFIG line below as approprate
	//  {CV_29_CONFIG,                                      0}, // Short Address 14 Speed Steps
	{CV_29_CONFIG, CV29_F0_LOCATION}, // Short Address 28/128 Speed Steps
	//  {CV_29_CONFIG, CV29_EXT_ADDRESSING | CV29_F0_LOCATION}, // Long  Address 28/128 Speed Steps  
	{CV_SND_MUTE_VOL, 1},
	{CV_SND_PLAYER1_VOL, 15},
	{CV_SND_PLAYER2_VOL, 15},
	{CV_SND_PLAYER3_VOL, 15},

	{CV_AUTO_TRANSITION, 0}, // auto transition time in milliseconds, 0 for no auto transition
	{CV_TRANSITION_DURATION, 10}, // transition sound duration in seconds

	{CV_ALL_USE_TRANSITION, 1}, // 0 for false, true otherwise
	{CV_PLAYER1_USE_TRANSITION, 1}, // 0 for false, true otherwise
	{CV_PLAYER2_USE_TRANSITION, 1}, // 0 for false, true otherwise
	{CV_PLAYER3_USE_TRANSITION, 1}, // 0 for false, true otherwise
};

uint8_t FactoryDefaultCVIndex = 160;

AudioPlayerClass AudioPlayer1(10, 11); // RX, TX
AudioPlayerClass AudioPlayer2(9, 8); // RX, TX
AudioPlayerClass AudioPlayer3(12, 13); // RX, TX


bool _isNight = false;
bool _isFunc7Done = false;
int _playerCount = 0;


static unsigned long timer = millis();


void Func1(bool state);
void Func4(bool state);
void Func5(bool state);
void Func6(bool state);
void Func7(bool state);
void Func8(bool state);

void notifyCVResetFactoryDefault()
{
	// Make FactoryDefaultCVIndex non-zero and equal to num CV's to be reset 
	// to flag to the loop() function that a reset to Factory Defaults needs to be done
	FactoryDefaultCVIndex = sizeof(FactoryDefaultCVs) / sizeof(CVPair);
}

void setup()
{
	// Setup which External Interrupt, the Pin it's associated with that we're using 
	Dcc.pin(0, 2, 0);
	// Call the main DCC Init function to enable the DCC Receiver
	Dcc.init(MAN_ID_DIY, 100, FLAGS_MY_ADDRESS_ONLY, 0);
	delay(800);
#ifdef DEBUG
	Serial.print(F("Address="));
	Serial.println(Dcc.getAddr());
#endif
	uint8_t transitionDuration = Dcc.getCV(CV_TRANSITION_DURATION);

	AudioPlayer1.Init(transitionDuration);
	AudioPlayer2.Init(transitionDuration);
	AudioPlayer3.Init(transitionDuration);

#ifdef DEBUG
	Serial.begin(115200);
	Serial.println();
	Serial.println(F("dcc_audio_3players"));
	Serial.println(F("Initializing DFPlayers ... (May take 3~5 seconds)"));

	Serial.println(F("All DFPlayers Mini are online."));
#endif // DEBUG


	AudioPlayer1.SetVolume(15); //Set volume value. From 0 to 30
	AudioPlayer1.Loop(); //Play the first mp3

	AudioPlayer2.SetVolume(15); //Set volume value. From 0 to 30
	AudioPlayer2.Loop(); //Play the first mp3

	AudioPlayer3.SetVolume(15); //Set volume value. From 0 to 30
	AudioPlayer3.Loop(); //Play the first mp3	
}

void printDetail(uint8_t type, int value)
{
	switch (type)
	{
	case TimeOut:
		Serial.println(F("Time Out!"));
		break;
	case WrongStack:
		Serial.println(F("Stack Wrong!"));
		break;
	case DFPlayerCardInserted:
		Serial.println(F("Card Inserted!"));
		break;
	case DFPlayerCardRemoved:
		Serial.println(F("Card Removed!"));
		break;
	case DFPlayerCardOnline:
		Serial.println(F("Card Online!"));
		break;
	case DFPlayerPlayFinished:
		Serial.print(F("Number:"));
		Serial.print(value);
		Serial.println(F(" Play Finished!"));
		break;
	case DFPlayerError:
		Serial.print(F("DFPlayerError:"));
		switch (value)
		{
		case Busy:
			Serial.println(F("Card not found"));
			break;
		case Sleeping:
			Serial.println(F("Sleeping"));
			break;
		case SerialWrongStack:
			Serial.println(F("Get Wrong Stack"));
			break;
		case CheckSumNotMatch:
			Serial.println(F("Check Sum Not Match"));
			break;
		case FileIndexOut:
			Serial.println(F("File Index Out of Bound"));
			break;
		case FileMismatch:
			Serial.println(F("Cannot Find File"));
			break;
		case Advertise:
			Serial.println(F("In Advertise"));
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void loop() //**********************************************************************
{
	//MUST call the NmraDcc.process() method frequently 
	// from the Arduino loop() function for correct library operation
	Dcc.process();

	AudioPlayer1.ArduinoLoop();
	AudioPlayer2.ArduinoLoop();
	AudioPlayer3.ArduinoLoop();

	uint8_t autoTransition = Dcc.getCV(CV_AUTO_TRANSITION);
	if (autoTransition > 0 && millis() - timer > autoTransition)
	{
		
		timer = millis();
#ifdef DEBUG
		Serial.print("autoTransition:");
		Serial.println(autoTransition);
		Serial.print("setting isNight to:");
		Serial.println(!_isNight);
#endif
		Func1(!_isNight);
	}

#ifdef  DECODER_LOADED
	if (Dcc.getCV(CV_FACTORY_RESET) == 8)
	{
#endif
	if (Dcc.isSetCVReady())
	{
		while (FactoryDefaultCVIndex > 0)
		{
#ifdef DEBUG
			Serial.print(F("Reset CV "));
			Serial.print(FactoryDefaultCVs[FactoryDefaultCVIndex].CV);
			Serial.print("=");
			Serial.println(FactoryDefaultCVs[FactoryDefaultCVIndex].Value);
#endif
			FactoryDefaultCVIndex--; // Decrement first as initially it is the size of the array 
			Dcc.setCV(FactoryDefaultCVs[FactoryDefaultCVIndex].CV, FactoryDefaultCVs[FactoryDefaultCVIndex].Value);
		}
	}
#ifdef  DECODER_LOADED
	}
#endif
}

void Func1(bool state)
{
	if (_isNight != state)
	{
		_isNight = state;
#ifdef DEBUG
		Serial.print(F("Change night state to: "));
		Serial.println(_isNight);
#endif
		if (Dcc.getCV(CV_ALL_USE_TRANSITION) > 0)
		{
			if (Dcc.getCV(CV_PLAYER1_USE_TRANSITION) > 0)
				AudioPlayer1.SetIsNight(_isNight);
			if (Dcc.getCV(CV_PLAYER2_USE_TRANSITION) > 0)
				AudioPlayer2.SetIsNight(_isNight);
			if (Dcc.getCV(CV_PLAYER3_USE_TRANSITION) > 0)
				AudioPlayer3.SetIsNight(_isNight);
		}
	}
}

void Func4(bool state)
{
	if (state)
		AudioPlayer1.Stop();
	else
		AudioPlayer1.Loop();
}

void Func5(bool state)
{
	if (state)
		AudioPlayer2.Stop();
	else
		AudioPlayer2.Loop();
}

void Func6(bool state)
{
	if (state)
		AudioPlayer3.Stop();
	else
		AudioPlayer3.Loop();
}


void Func7(bool state)
{
	if (state)
	{
		if (_isFunc7Done)
			return;
		_isFunc7Done = true;
#ifdef DEBUG
		Serial.print(F("Address="));
		Serial.println(Dcc.getAddr());
		Serial.print(F("Mute Volume CV "));
		Serial.print(CV_SND_MUTE_VOL);
		Serial.print("=");
		Serial.println(Dcc.getCV(CV_SND_MUTE_VOL));
		Serial.print(F("Player 1 Volume CV "));
		Serial.print(CV_SND_PLAYER1_VOL);
		Serial.print("=");
		Serial.println(Dcc.getCV(CV_SND_PLAYER1_VOL));
		Serial.print(F("Player 2 Volume CV "));
		Serial.print(CV_SND_PLAYER2_VOL);
		Serial.print("=");
		Serial.println(Dcc.getCV(CV_SND_PLAYER2_VOL));
		Serial.print(F("Player 3 Volume CV "));
		Serial.print(CV_SND_PLAYER3_VOL);
		Serial.print("=");
		Serial.println(Dcc.getCV(CV_SND_PLAYER3_VOL));

		Serial.print(F("Auto transition CV "));
		Serial.print(CV_AUTO_TRANSITION);
		Serial.print("=");
		Serial.println(Dcc.getCV(CV_AUTO_TRANSITION));
		Serial.print(F("Transition duration CV "));
		Serial.print(CV_TRANSITION_DURATION);
		Serial.print("=");
		Serial.println(Dcc.getCV(CV_TRANSITION_DURATION));

		Serial.print(F("All players use transition CV "));
		Serial.print(CV_ALL_USE_TRANSITION);
		Serial.print("=");
		Serial.println(Dcc.getCV(CV_ALL_USE_TRANSITION));
		Serial.print(F("Player 1 use transition CV "));
		Serial.print(CV_PLAYER1_USE_TRANSITION);
		Serial.print("=");
		Serial.println(Dcc.getCV(CV_PLAYER1_USE_TRANSITION));
		Serial.print(F("Player 2 use transition CV "));
		Serial.print(CV_PLAYER2_USE_TRANSITION);
		Serial.print("=");
		Serial.println(Dcc.getCV(CV_PLAYER2_USE_TRANSITION));
		Serial.print(F("Player 3 use transition CV "));
		Serial.print(CV_PLAYER3_USE_TRANSITION);
		Serial.print("=");
		Serial.println(Dcc.getCV(CV_PLAYER3_USE_TRANSITION));

#endif // DEBUG
	}
	else
		_isFunc7Done = false;
}

void Func8(bool state)
{
	AudioPlayer1.SetVolume(state ? Dcc.getCV(CV_SND_MUTE_VOL) : Dcc.getCV(CV_SND_PLAYER1_VOL));
	AudioPlayer2.SetVolume(state ? Dcc.getCV(CV_SND_MUTE_VOL) : Dcc.getCV(CV_SND_PLAYER2_VOL));
	AudioPlayer3.SetVolume(state ? Dcc.getCV(CV_SND_MUTE_VOL) : Dcc.getCV(CV_SND_PLAYER2_VOL));
}

void    notifyCVChange(uint16_t CV, uint8_t Value)
{
#ifdef DEBUG
	Serial.print(F("Change CV "));
	Serial.print(CV);
	Serial.print("=");
	Serial.println(Value);
#endif // DEBUG
}

void notifyDccFunc(uint16_t Addr, DCC_ADDR_TYPE AddrType, FN_GROUP FuncGrp, uint8_t FuncState)
{
	switch (FuncGrp)
	{
	case FN_0_4: //Function Group 1 F0 F4 F3 F2 F1
		//exec_function(0, FunctionPin0, (FuncState & FN_BIT_00) >> 4);
		Func1(FuncState & FN_BIT_01);
		Func4(FuncState & FN_BIT_04);

		break;

	case FN_5_8: //Function Group 1 S FFFF == 1 F8 F7 F6 F5  &  == 0  F12 F11 F10 F9 F8
		Func5(FuncState & FN_BIT_05);
		Func6(FuncState & FN_BIT_06);
		Func7(FuncState & FN_BIT_07);
		Func8(FuncState & FN_BIT_08);
		break;

	case FN_9_12:

		break;

	case FN_13_20: //Function Group 2 FuncState == F20-F13 Function Control

		break;

	case FN_21_28:
		break;
	}
}
