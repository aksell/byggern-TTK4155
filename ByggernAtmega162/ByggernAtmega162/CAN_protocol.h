/*
 * CAN_adresses.h
 *
 * Created: 24.10.2018 15:19:56
 *  Author: torbjfug
 */ 


#ifndef CAN_ADRESSES_H_
#define CAN_ADRESSES_H_


//CAN Message Addresses


//State messages
#define CAN_GAME_OVER 1 //Message sendt to force other node out of game mode
#define CAN_GAME_OVER_ACK 2 //Acknowledge that other node has changed out of game mode

#define CAN_START_GAME 3 //Message sent from node 1 indicating that a game is stating
#define CAN_START_GAME_ACK 4 //Acknowledge that node 2 has reacted to START_GAME

//IO messages
#define CAN_JOYSTICK_Y	10 //Send 1 signed byte from joystick Y with senter at 0
#define CAN_JOYSTICK_X	11 //Send 1 signed byte from joystick X with senter at 0

#define CAN_SLIDER_1 12 //Send 1 unsigned byte from Slider 1
#define CAN_SLIDER_2 13 //Send 1 undigned byte from Slider 2


#define CAN_SOLANOIDE_TRIGGER_MS 14 //Request node 2 to activate solenoid together with two bytes of data indicating the ms of activation

#define CAN_SOLANOIDE_TRIGGER_AND_HOLD 15 //Request node 2 to activate solenoid
#define CAN_SOLANOIDE_RELIASE 16 //Request node 2 to reliase solenoid


//Music messages
#define CAN_START_MUSIC 20 //Request a start of music in node 2 with value of 1 byte of music_t from "music.h"
	
#define CAN_STOP_MUSIC 21 //Stops music on node 2


#endif /* CAN_ADRESSES_H_ */