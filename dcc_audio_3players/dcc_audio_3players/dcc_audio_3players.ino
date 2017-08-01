/*
 Name:		dcc_audio_3players.ino
 Created:	4/9/2017 7:01:30 PM
 Author:	PBY
*/

// ******** UNLESS YOU WANT ALL CV'S RESET UPON EVERY POWER UP
// ******** AFTER THE INITIAL DECODER LOAD REMOVE THE "//" IN THE FOOLOWING LINE!!
#define DECODER_LOADED

// ******** REMOVE THE "//" IN THE FOOLOWING LINE TO SEND DEBUGGING
// ******** INFO TO THE SERIAL MONITOR
#define DEBUG
//#define _DEBUG


// the setup function runs once when you press reset or power the board
#include <SoftwareSerial.h>
#include <NmraDcc.h>
#include <DFRobotDFPlayerMini.h>


NmraDcc Dcc;
DCC_MSG Packet;
uint8_t CV_DECODER_MASTER_RESET = 120;
int t; // temp
#define This_Decoder_Address 3

#define CV_SND_MUTE_VOL  135
#define CV_SND_PLAYER1_VOL  141
#define CV_SND_PLAYER2_VOL  142
#define CV_SND_PLAYER3_VOL  143

struct QUEUE
{
	int inuse;
	int current_position;
	int increment;
	int stop_value;
	int start_value;
};

QUEUE* ftn_queue = new QUEUE[17];

extern uint8_t Decoder_Address = This_Decoder_Address;

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

	// ONLY uncomment 1 CV_29_CONFIG line below as approprate
	//  {CV_29_CONFIG,                                      0}, // Short Address 14 Speed Steps
	{CV_29_CONFIG, CV29_F0_LOCATION}, // Short Address 28/128 Speed Steps
	//  {CV_29_CONFIG, CV29_EXT_ADDRESSING | CV29_F0_LOCATION}, // Long  Address 28/128 Speed Steps  
	{CV_SND_MUTE_VOL, 1},
	{CV_SND_PLAYER1_VOL, 15},
	{CV_SND_PLAYER2_VOL, 15},
	{CV_SND_PLAYER3_VOL, 15},
};

uint8_t FactoryDefaultCVIndex = 150;

void notifyCVResetFactoryDefault()
{
	// Make FactoryDefaultCVIndex non-zero and equal to num CV's to be reset 
	// to flag to the loop() function that a reset to Factory Defaults needs to be done
	FactoryDefaultCVIndex = sizeof(FactoryDefaultCVs) / sizeof(CVPair);
}

SoftwareSerial softSerialPlayer1(10, 11); // RX, TX
SoftwareSerial softSerialPlayer2(9, 8); // RX, TX
SoftwareSerial softSerialPlayer3(12, 13); // RX, TX
//SoftwareSerial softSerialPlayer3(7,6); // RX, TX
DFRobotDFPlayerMini DfPlayer1;
DFRobotDFPlayerMini DfPlayer2;
DFRobotDFPlayerMini DfPlayer3;


bool _isNight = false;

bool _isPlayer1Playing = false;
bool _isPlayer2Playing = false;
bool _isPlayer3Playing = false;

bool _player1NeedRestart = false;
bool _player2NeedRestart = false;
bool _player3NeedRestart = false;

void Player1Loop()
{
	if (!_isPlayer1Playing)
	{
		_isPlayer1Playing = true;
		if (_isNight)
			DfPlayer1.loop(2);
		else
			DfPlayer1.loop(1);
	}
}

void Player1Stop()
{
	if (_isPlayer1Playing)
	{
		_isPlayer1Playing = false;
		DfPlayer1.stop();
	}
}

void Player2Loop()
{
	if (!_isPlayer2Playing)
	{
		_isPlayer2Playing = true;
		if (_isNight)
			DfPlayer2.loop(2);
		else
			DfPlayer2.loop(1);
	}
}

void Player2Stop()
{
	if (_isPlayer2Playing)
	{
		_isPlayer2Playing = false;
		DfPlayer2.stop();
	}
}

void Player3Loop()
{
	if (!_isPlayer3Playing)
	{
		_isPlayer3Playing = true;
		if (_isNight)
			DfPlayer3.loop(2);
		else
			DfPlayer3.loop(1);
	}
}

void Player3Stop()
{
	if (_isPlayer3Playing)
	{
		_isPlayer3Playing = false;
		DfPlayer3.stop();
	}
}

void setup()
{
	softSerialPlayer1.begin(9600);
	softSerialPlayer2.begin(9600);
	softSerialPlayer3.begin(9600);
#ifdef DEBUG
	Serial.begin(115200);
	Serial.println();
	Serial.println(F("dcc_audio_3players"));
	Serial.println(F("Initializing DFPlayers ... (May take 3~5 seconds)"));
#endif

	softSerialPlayer1.listen();
	if (!DfPlayer1.begin(softSerialPlayer1))
	{ //Use softwareSerial to communicate with mp3.
#ifdef DEBUG
		Serial.println(F("Unable to begin (DFPlayer 1):"));
		Serial.println(F("1.Please recheck the connection! (DFPlayer 1)"));
		Serial.println(F("2.Please insert the SD card! (DFPlayer 1)"));
#endif // DEBUG

		while (true);
	}

	softSerialPlayer2.listen();
	if (!DfPlayer2.begin(softSerialPlayer2))
	{ //Use softwareSerial to communicate with mp3.
#ifdef DEBUG
		Serial.println(F("Unable to begin (DFPlayer 2):"));
		Serial.println(F("1.Please recheck the connection! (DFPlayer 2)"));
		Serial.println(F("2.Please insert the SD card! (DFPlayer 2)"));
#endif // DEBUG

		while (true);
	}

	softSerialPlayer3.listen();
	if (!DfPlayer3.begin(softSerialPlayer3))
	{ //Use softwareSerial to communicate with mp3.
#ifdef DEBUG
		Serial.println(F("Unable to begin (DFPlayer 3):"));
		Serial.println(F("1.Please recheck the connection! (DFPlayer 3)"));
		Serial.println(F("2.Please insert the SD card! (DFPlayer 3)"));
#endif // DEBUG

		while (true);
	}
#ifdef DEBUG
	Serial.println(F("All DFPlayers Mini are online."));
#endif // DEBUG


	DfPlayer1.volume(15); //Set volume value. From 0 to 30
	Player1Loop(); //Play the first mp3

	DfPlayer2.volume(15); //Set volume value. From 0 to 30
	Player2Loop(); //Play the first mp3

	DfPlayer3.volume(15); //Set volume value. From 0 to 30
	Player3Loop(); //Play the first mp3


	// Setup which External Interrupt, the Pin it's associated with that we're using 
	Dcc.pin(0, 2, 0);
	// Call the main DCC Init function to enable the DCC Receiver
	Dcc.init(MAN_ID_DIY, 100, FLAGS_MY_ADDRESS_ONLY, 0);
	delay(800);
#ifdef DEBUG
	Serial.print(F("Address="));
	Serial.println(Dcc.getAddr());
#endif
	
}


void printDetail(uint8_t type, int value) {
	switch (type) {
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
		switch (value) {
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

int _playerCount = 0;


void Func1(bool state)
{
	if (_isNight != state)
	{
		_isNight = state;
#ifdef DEBUG
		Serial.print(F("Change night state to: "));
		Serial.println(_isNight);
#endif
		_player1NeedRestart = true;
		DfPlayer1.disableLoop();
		_player2NeedRestart = true;
		DfPlayer2.disableLoop();
	}
}

static unsigned long timer = millis();

void loop() //**********************************************************************
{
	//MUST call the NmraDcc.process() method frequently 
	// from the Arduino loop() function for correct library operation
	Dcc.process();

	

	if (millis() - timer > 10000) {
		timer = millis();
		Serial.print("setting isNight to:");		
		Serial.println(!_isNight);
		Func1(!_isNight);

	}

#ifndef  DECODER_LOADED
	if (FactoryDefaultCVIndex && Dcc.isSetCVReady())
	{
#ifdef DEBUG
		Serial.print(F("Reset CV"));
		Serial.print(FactoryDefaultCVs[FactoryDefaultCVIndex].CV);
		Serial.print("=");
		Serial.println(FactoryDefaultCVs[FactoryDefaultCVIndex].Value);
#endif
		FactoryDefaultCVIndex--; // Decrement first as initially it is the size of the array 
		Dcc.setCV(FactoryDefaultCVs[FactoryDefaultCVIndex].CV, FactoryDefaultCVs[FactoryDefaultCVIndex].Value);
	}
#endif

	if (_playerCount == 0)
	{

		
		//DfPlayer1.waitAvailable();
		if (DfPlayer1.available())
		{
			/*Serial.print(F("Player 1:"));
			Serial.println(DfPlayer1.readState());*/
			//printDetail(DfPlayer1.readType(), DfPlayer1.read());*/
			if (DfPlayer1.readType() == DFPlayerPlayFinished)
			{
#ifdef DEBUG
				Serial.print(F("Number:"));
				Serial.print(DfPlayer1.read());
				Serial.println(F(" Play Finished! (Player 1)"));
#endif
				if (_player1NeedRestart)
				{
					_player1NeedRestart = false;
					_isPlayer1Playing = false;
					Player1Loop();
				}
			}
			_playerCount++;
		}
		softSerialPlayer2.listen();
	}
	if (_playerCount == 1)
	{
		
		//DfPlayer2.waitAvailable();
		if (DfPlayer2.available())
		{
			/*Serial.print(F("Player 2:"));
			Serial.println(DfPlayer2.readState());*/
			//printDetail(DfPlayer2.readType(), DfPlayer2.read());
			if (DfPlayer2.readType() == DFPlayerPlayFinished)
			{
#ifdef DEBUG
				Serial.print(F("Number:"));
				Serial.print(DfPlayer2.read());
				Serial.println(F(" Play Finished! (Player 2)"));
#endif
				if (_player2NeedRestart)
				{
					_player2NeedRestart = false;
					_isPlayer2Playing = false;
					Player2Loop();
				}
			}
			_playerCount++;
		}
		softSerialPlayer1.listen();
	}

	
	if (_playerCount >= 2)
		_playerCount = 0;
}





void Func4(bool state)
{
	//softSerialPlayer1.listen();
	if (state)	
		Player1Stop();
	else
		Player1Loop();
}

void Func5(bool state)
{
	//softSerialPlayer2.listen();
	if (state)
		Player2Stop();
	else
		Player2Loop();
}


void Func7(bool state)
{
	if (state)
	{
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
#endif // DEBUG
	}
}

void Func8(bool state)
{
#ifdef DEBUG
	/*Serial.print(F("Function 8 state="));
	Serial.println(state ? "1  " : "0  ");*/	
#endif // DEBUG

	DfPlayer1.volume(state ? Dcc.getCV(CV_SND_MUTE_VOL) : Dcc.getCV(CV_SND_PLAYER1_VOL));
	DfPlayer2.volume(state ? Dcc.getCV(CV_SND_MUTE_VOL) : Dcc.getCV(CV_SND_PLAYER2_VOL));
	DfPlayer3.volume(state ? Dcc.getCV(CV_SND_MUTE_VOL) : Dcc.getCV(CV_SND_PLAYER2_VOL));
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
