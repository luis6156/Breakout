Copyright Micu Florian-Luis, 2020

Breakout Clone

Made using C++ and OpenGL.

Tutorial provided by learnopengl.com

Implementation and changes to the game made by Micu Florian-Luis.

Instructions:

SELECTING A LEVEL:
Use the W or S keys to select a level or the UP and DOWN arrows, then press 
ENTER.

MAIN MENU:
You can access the main menu by pressing ESCAPE if you are already playing a
game.

ENABLE/DISABLE VSYNC:
If you want to test your computer power, you can disable VSYNC bumping the 
framerate higher than the screen refresh rate (eg. 60hz, 144hz, 300hz). To 
DISABLE VSYNC press "0" and to ENABLE VSYNC press "9".

ENABLE/DISABLE FPS COUNTER:
To ENABLE/DISABLE the framerate, press "8". The counter will display the
frames per second (FPS) and the miliseconds per frames.

QUIT:
To quit press ESCAPE on the main menu.

MOVING:
Use WASD or the ARROW keys.

LAUNCHING THE BALL:
When you choose a level or when a certain power up occurs, you have to press 
SPACEBAR to launch the ball.

POWER UPS:
SPEED: increases the velocity of the ball by 20%

STICKY: make the ball stick to the paddle, until SPACEBAR is pressed

PASS-THROUGH: collisions for non-solid blocks is disabled, making the ball hit 
			more bricks in one go

PAD-SIZE-INCREASE: increases the paddle by 50 pixels

CONFUSE: activates the confuse postprocessing effect for a short period of 
			time, confusing the user

CHAOS: activates the chaos postprocessing effect for a short period of time,
			heavily disorienting the user

CHEAT CODE:
In order to change the RNG of the POWER UPS, type in the MAIN MENU "GOD".
This will ensure that good buffs will have a 1/5 chance to spawn and the
bad bufs will a 1/12 chance to spawn. The original values are 1/20 and 1/15.

CHANGE MUSIC:
If you want to change the main music, go in the application folder and move
the music file from audio/default_bg to a safe place (to put it back if you 
want) and place your music file in that folder. Rename the file to 
"breakout.mp3" and make sure you have an MP3 file.

CUSTOM LEVELS:
If you want to change a level, all you have to do is go in the application
folder and open the "levels" folder. From there open any file with a text
editor and make a matrix with values from 0-5 (0 - empty block, 1 - stone
block, 2-5 different color blocks). The matrix can be any size, it is scalled
to fit on the width of the screen and half the height of it, thus if you have
more elements the blocks will shrink to fit.

HAVE FUN AND THANK YOU FOR PLAYING!!!
