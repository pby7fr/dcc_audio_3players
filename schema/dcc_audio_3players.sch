EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ardupromini-6
LIBS:6N137-TTL-Serial-Optoisolator-cache
LIBS:rur
LIBS:dcc_audio_3players-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ARDUPROMINI-6 uP4
U 1 1 598EEF91
P 5800 4300
F 0 "uP4" H 5500 4200 60  0000 C CNN
F 1 "ARDUPROMINI-6" H 5800 4300 60  0000 C CNN
F 2 "" H 5800 4300 60  0000 C CNN
F 3 "" H 5800 4300 60  0000 C CNN
	1    5800 4300
	1    0    0    -1  
$EndComp
$Comp
L 6N137 IC4
U 1 1 598EF1FC
P 3650 5200
F 0 "IC4" H 3436 5429 40  0000 C CNN
F 1 "6N137" H 3800 4960 40  0000 C CNN
F 2 "DIP8" H 3485 4965 29  0000 C CNN
F 3 "" H 3650 5200 60  0000 C CNN
	1    3650 5200
	1    0    0    -1  
$EndComp
$Comp
L DFPLAYER_MINI U1
U 1 1 598EF3C2
P 9150 2850
F 0 "U1" H 9150 2600 60  0000 C CNN
F 1 "DFPLAYER_MINI" H 9150 3300 60  0000 C CNN
F 2 "" H 9150 2850 60  0000 C CNN
F 3 "" H 9150 2850 60  0000 C CNN
	1    9150 2850
	1    0    0    -1  
$EndComp
$Comp
L DFPLAYER_MINI U2
U 1 1 598EF46A
P 9150 4050
F 0 "U2" H 9150 3800 60  0000 C CNN
F 1 "DFPLAYER_MINI" H 9150 4500 60  0000 C CNN
F 2 "" H 9150 4050 60  0000 C CNN
F 3 "" H 9150 4050 60  0000 C CNN
	1    9150 4050
	1    0    0    -1  
$EndComp
$Comp
L DFPLAYER_MINI U3
U 1 1 598EF4F9
P 9150 5300
F 0 "U3" H 9150 5050 60  0000 C CNN
F 1 "DFPLAYER_MINI" H 9150 5750 60  0000 C CNN
F 2 "" H 9150 5300 60  0000 C CNN
F 3 "" H 9150 5300 60  0000 C CNN
	1    9150 5300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 598EF763
P 1350 2700
F 0 "#PWR?" H 1350 2550 50  0001 C CNN
F 1 "+5V" H 1350 2840 50  0000 C CNN
F 2 "" H 1350 2700 50  0001 C CNN
F 3 "" H 1350 2700 50  0001 C CNN
	1    1350 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 598EF79A
P 1350 3000
F 0 "#PWR?" H 1350 2750 50  0001 C CNN
F 1 "GND" H 1350 2850 50  0000 C CNN
F 2 "" H 1350 3000 50  0001 C CNN
F 3 "" H 1350 3000 50  0001 C CNN
	1    1350 3000
	1    0    0    -1  
$EndComp
Text GLabel 1500 5000 0    60   Input ~ 0
DCC1
Text GLabel 1500 5300 0    60   Input ~ 0
DCC2
$Comp
L Speaker LS1
U 1 1 598EF8D2
P 10750 2800
F 0 "LS1" H 10800 3025 50  0000 R CNN
F 1 "Speaker" H 10800 2950 50  0000 R CNN
F 2 "" H 10750 2600 50  0001 C CNN
F 3 "" H 10740 2750 50  0001 C CNN
	1    10750 2800
	1    0    0    -1  
$EndComp
$Comp
L Speaker LS2
U 1 1 598EF96B
P 10800 4100
F 0 "LS2" H 10850 4325 50  0000 R CNN
F 1 "Speaker" H 10850 4250 50  0000 R CNN
F 2 "" H 10800 3900 50  0001 C CNN
F 3 "" H 10790 4050 50  0001 C CNN
	1    10800 4100
	1    0    0    -1  
$EndComp
$Comp
L Speaker LS3
U 1 1 598EF9FC
P 10750 5150
F 0 "LS3" H 10800 5375 50  0000 R CNN
F 1 "Speaker" H 10800 5300 50  0000 R CNN
F 2 "" H 10750 4950 50  0001 C CNN
F 3 "" H 10740 5100 50  0001 C CNN
	1    10750 5150
	1    0    0    -1  
$EndComp
Wire Bus Line
	6300 4850 8000 4850
Wire Bus Line
	8000 2500 8000 4950
Wire Bus Line
	8000 2500 8550 2500
Wire Bus Line
	8550 3700 8000 3700
Wire Bus Line
	8000 4950 8550 4950
Wire Bus Line
	4000 5350 4500 5350
Wire Bus Line
	4500 3000 4500 6000
Wire Bus Line
	4500 4850 5100 4850
Wire Bus Line
	5950 6000 8150 6000
Wire Bus Line
	8150 6000 8150 3100
Wire Bus Line
	8150 5550 8550 5550
Wire Bus Line
	8150 4300 8550 4300
Wire Bus Line
	8150 3100 8550 3100
Connection ~ 8000 4850
Connection ~ 8000 3700
Connection ~ 8150 4300
Connection ~ 8150 5550
Connection ~ 4500 5350
Wire Wire Line
	8550 5650 8550 5850
Wire Wire Line
	8550 5850 10450 5850
Wire Wire Line
	10450 5850 10450 5250
Wire Wire Line
	10450 5250 10550 5250
Wire Wire Line
	10550 5150 10550 5100
Wire Wire Line
	10550 5100 10350 5100
Wire Wire Line
	10350 5100 10350 6000
Wire Wire Line
	10350 6000 8450 6000
Wire Wire Line
	8450 6000 8450 5450
Wire Wire Line
	8450 5450 8550 5450
Wire Wire Line
	8550 4400 8500 4400
Wire Wire Line
	8500 4400 8500 4600
Wire Wire Line
	8500 4600 10450 4600
Wire Wire Line
	10450 4600 10450 4200
Wire Wire Line
	10450 4200 10600 4200
Wire Wire Line
	10600 4100 10350 4100
Wire Wire Line
	10350 4100 10350 4700
Wire Wire Line
	10350 4700 8450 4700
Wire Wire Line
	8450 4700 8450 4200
Wire Wire Line
	8450 4200 8550 4200
Wire Wire Line
	8550 3200 8550 3400
Wire Wire Line
	8550 3400 10450 3400
Wire Wire Line
	10450 3400 10450 2900
Wire Wire Line
	10450 2900 10550 2900
Wire Wire Line
	8550 3000 8450 3000
Wire Wire Line
	8450 3000 8450 3500
Wire Wire Line
	8450 3500 10350 3500
Wire Wire Line
	10350 3500 10350 2800
Wire Wire Line
	10350 2800 10550 2800
Wire Bus Line
	6000 6000 4550 6000
Wire Bus Line
	4500 6000 4600 6000
$Comp
L R R3
U 1 1 598F036D
P 7350 5050
F 0 "R3" V 7430 5050 50  0000 C CNN
F 1 "1K" V 7350 5050 50  0000 C CNN
F 2 "" V 7280 5050 50  0001 C CNN
F 3 "" H 7350 5050 50  0001 C CNN
	1    7350 5050
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 598F0452
P 7350 3800
F 0 "R2" V 7430 3800 50  0000 C CNN
F 1 "1K" V 7350 3800 50  0000 C CNN
F 2 "" V 7280 3800 50  0001 C CNN
F 3 "" H 7350 3800 50  0001 C CNN
	1    7350 3800
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 598F04F3
P 7350 2600
F 0 "R1" V 7430 2600 50  0000 C CNN
F 1 "1K" V 7350 2600 50  0000 C CNN
F 2 "" V 7280 2600 50  0001 C CNN
F 3 "" H 7350 2600 50  0001 C CNN
	1    7350 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	8550 5050 7500 5050
Wire Wire Line
	8550 3800 7500 3800
Wire Wire Line
	8550 2600 7500 2600
Wire Wire Line
	7200 2600 6650 2600
Wire Wire Line
	6650 2600 6650 5550
Wire Wire Line
	6650 5550 6300 5550
Wire Wire Line
	8550 2700 6800 2700
Wire Wire Line
	6800 2700 6800 5650
Wire Wire Line
	6800 5650 6300 5650
Wire Wire Line
	5100 5650 5100 5800
Wire Wire Line
	5100 5800 6950 5800
Wire Wire Line
	6950 5800 6950 3900
Wire Wire Line
	6950 3900 8550 3900
Wire Wire Line
	5100 5550 5000 5550
Wire Wire Line
	5000 5550 5000 5900
Wire Wire Line
	5000 5900 7050 5900
Wire Wire Line
	7050 5900 7050 3800
Wire Wire Line
	7050 3800 7200 3800
Wire Wire Line
	6300 5350 7200 5350
Wire Wire Line
	7200 5350 7200 5050
Wire Wire Line
	8600 5150 7550 5150
Wire Wire Line
	7550 5150 7550 5450
Wire Wire Line
	7550 5450 6300 5450
Wire Wire Line
	3300 5300 1500 5300
$Comp
L R R4
U 1 1 598F1600
P 1900 5000
F 0 "R4" V 1980 5000 50  0000 C CNN
F 1 "1.3K" V 1900 5000 50  0000 C CNN
F 2 "" V 1830 5000 50  0001 C CNN
F 3 "" H 1900 5000 50  0001 C CNN
	1    1900 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 5000 2050 5000
Wire Wire Line
	1750 5000 1500 5000
$Comp
L C C1
U 1 1 598F176A
P 2250 5150
F 0 "C1" H 2275 5250 50  0000 L CNN
F 1 "270pF" H 2275 5050 50  0000 L CNN
F 2 "" H 2288 5000 50  0001 C CNN
F 3 "" H 2250 5150 50  0001 C CNN
	1    2250 5150
	1    0    0    -1  
$EndComp
$Comp
L D D1
U 1 1 598F17F1
P 2650 5150
F 0 "D1" H 2650 5250 50  0000 C CNN
F 1 "1N4148" H 2650 5050 50  0000 C CNN
F 2 "" H 2650 5150 50  0001 C CNN
F 3 "" H 2650 5150 50  0001 C CNN
	1    2650 5150
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 5100 3300 5000
Connection ~ 2650 5000
Connection ~ 2250 5000
Connection ~ 2250 5300
Connection ~ 2650 5300
$Comp
L CP C2
U 1 1 598F1DC1
P 2000 2850
F 0 "C2" H 2025 2950 50  0000 L CNN
F 1 "470uF 25V" H 2025 2750 50  0000 L CNN
F 2 "" H 2038 2700 50  0001 C CNN
F 3 "" H 2000 2850 50  0001 C CNN
	1    2000 2850
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 598F1EBE
P 2700 2850
F 0 "C3" H 2725 2950 50  0000 L CNN
F 1 "0.1uF 25V" H 2725 2750 50  0000 L CNN
F 2 "" H 2738 2700 50  0001 C CNN
F 3 "" H 2700 2850 50  0001 C CNN
	1    2700 2850
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 598F1F0D
P 4150 3700
F 0 "R5" V 4230 3700 50  0000 C CNN
F 1 "10K" V 4150 3700 50  0000 C CNN
F 2 "" V 4080 3700 50  0001 C CNN
F 3 "" H 4150 3700 50  0001 C CNN
	1    4150 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3850 4150 5150
Wire Wire Line
	4150 5150 4000 5150
Wire Bus Line
	1350 3000 4500 3000
Wire Bus Line
	1350 2700 6550 2700
Wire Bus Line
	6550 2700 6550 4850
Connection ~ 6550 4850
Connection ~ 4500 4850
Connection ~ 2000 3000
Connection ~ 2000 2700
Wire Wire Line
	4150 2700 4150 3550
Connection ~ 4150 2700
$Comp
L R R6
U 1 1 598F26F5
P 4300 4200
F 0 "R6" V 4380 4200 50  0000 C CNN
F 1 "5K" V 4300 4200 50  0000 C CNN
F 2 "" V 4230 4200 50  0001 C CNN
F 3 "" H 4300 4200 50  0001 C CNN
	1    4300 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 4350 4300 5250
Wire Wire Line
	4300 5250 4000 5250
Wire Wire Line
	5100 4950 4300 4950
Connection ~ 4300 4950
Wire Wire Line
	4300 4050 4300 2700
Connection ~ 4300 2700
Connection ~ 2150 2950
Connection ~ 2700 2700
Connection ~ 2700 3000
Wire Wire Line
	4500 4850 4000 4850
Wire Wire Line
	4000 4850 4000 5050
$EndSCHEMATC