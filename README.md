Deathclock from Futurama Season 1- Episode 8 A Big Piece of Garbage

******************************
** Main files for Deathclock alone **
******************************

Parts required:
==============

-	Arduino Nano or Arduino ESP8266 
(I recommend the nano if you are simply making this as a stand-alone)
-	MAX7219 Dot Matrix 4-In-1 Display Module

- DeathClockESP.ino (for ESP8266 boards)
- DeathClockNano.ino (for Arduino Nano)

Print the following files:

-	button.stl
-	rear.stl
-	FrontLCD.stl
- leg.stl (x4)

See NanoDeathClockWiring.png or ESP8266DeathClockWiring.png for connections
==================================================================================

******************************
******** The Finger Mech *******
******************************

DeathClock_KCESPFinger.ino
** updated, new ESP option which currently uses Kruiz-Control to monitor channel points and we simply monitor chat on the Arduino to activate
The code to enter into Kruiz-Control is :

In triggers.txt located in the main directory
_____________________________________________

OnChannelPoint "DeathClock"
Chat Send "{user} is about to reveal their future"
Delay 25

In the root fileTriggers.txt
_____________________________________________

Make sure you have the line
Mycommands.txt

In the Mycommands.txt file located in the triggers directory 
_____________________________________________________________

#********* Death Clock **********************

OnCommand b 0 !deathshow
OBS Source DCSound on
Delay 6
OBS Source DCSound off



https://github.com/Kruiser8/Kruiz-Control

The Finger button push mechanism is designed to use channel points with Twitch integration.
As such it uses an ESP8266 board. You could merge DeathClockESP.ino and ESPDeathClockFinger.ino into one, however
I have kept them separate so you have the choice of being able to run manually (which I figure most people would like to do.)

Parts required:
==============

-	Mg90s Servo (you could probably get away with a cheap SG90)
-	Arduino ESP8266
-	https://github.com/jacob1421/Twitch-IRC-API
-	Check out Noycebru’s Tutorial here for setup https://www.youtube.com/watch?v=WV1r6HaXaPY


Print the following files:

-	toothmountfinal.3mf
-	finger.3mf 
(This is an edited version of https://www.thingiverse.com/thing:171234 by Spfaff1994)
-	MG90S Servo Mount.3mf
-	Rackandpinion.3mf
(This is an edited version of https://www.thingiverse.com/thing:944471 by dreyfusduke)

See ESP8266DeathClockFingerWiring.png for connections

Any questions feel free to come chat http://twitch.tv/disasterofpuppets
Tutorial available on Disaster of Puppets Youtube channel http://www.disasterofpuppets.com
Twitch @dofpuppets

Special thanks to:
**The BruCrew**
