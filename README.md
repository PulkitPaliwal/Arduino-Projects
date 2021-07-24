# Automating Dino Game using Arduino Uno
#### This repository contains the idea, code as well as the layout behind an Arduino Uno based project aimed at automating the classic dino game (in dark mode) on the chrome browser.
## Components needed-
* 1x Arduino Uno R3
* 1x Servo Motor
* 1x Photoresistor
* 1x LED
* 1x Breadboard
* Several Wires

## Idea of the project-
A photoresistor can be attached to the screen, and the brightness should be increased to maximum. The photoresistor should be positioned such that when the game is being played, the cactuses would pass in front of the photoresistor. The whole screen being dark and only the cactuses being white, there would a momentary small change in voltage in one of the pins of the photoresistor. The idea is to observe and take down values of the voltages observed in dark and light screens and calculate a threshold value such that if the voltage measured by the photoresistor crosses this threshold, the arduino board signals the servo motor to move and hit the spacebar.

## Parameters on which the 'accuracy' of the project will depend upon-
* Internal (code related):
  * Time delays within the code
  * Number of previous iterations we check for (whether the servo moved in the previous iteration or not)
  * Factor with which the dtime variable is modified
  * Score gaps with which the dtime variable modification happens
  * The threshold which is decided after which the arduino gives signal for the motor to rotate
* External
  * General lighting conditions (works better in a dark room, nevertheless, don't let any light directly onto your screen)
  * Brightness of the screen and color contrast settings
  * Position of the photoresistor

## Demo-
[Watch it here](https://drive.google.com/file/d/1Fy28mR4CiQMVbj5SsDaxedmWMT5nz-VY/view?usp=sharing)
#### The setup achieved a high of 378 in the video and a record high of 488.
