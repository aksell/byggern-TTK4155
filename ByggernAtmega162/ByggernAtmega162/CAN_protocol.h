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
#define CAN_GAME_OVER 2 //Message sendt to force node 2 out of game mode
#define CAN_GAME_OVER_ACK 1 //Acknowledge that node 2 has changed out of game mode

#define CAN_START_GAME 4 //Message sent from node 1 indicating that a game is stating
#define CAN_START_GAME_ACK 3 //Acknowledge that node 2 has reacted to START_GAME

//IO messages
#define CAN_MOTOR_POS	10 //Send 1 signed byte of desired position of main motor

#define CAN_MOTOR_CALIBRATE 11 //Request node 2 to calibrate motor

#define CAN_SERVO_POS 12 //Send 1 signed byte to set servo position. 

#define CAN_SOLANOIDE_TRIGGER_MS 14 //Request node 2 to activate solenoid together with two bytes of data indicating the ms of activation

#define CAN_SOLANOIDE_TRIGGER_AND_HOLD 15 //Request node 2 to activate solenoid
#define CAN_SOLANOIDE_RELIASE 16 //Request node 2 to release solenoid

#define CAN_BALL_SENSOR_TRIGGERED 17 //Node 2 has detected ball

//Music messages
#define CAN_START_MUSIC 20 //Request a start of music in node 2 with value of 1 byte of music_t from "music.h"
#define CAN_START_MUSIC_LOOP 21	 //Request a start of music played in loop in node 2 with value of 1 byte of music_t from "music.h"
#define CAN_STOP_MUSIC 22 //Stops music on node 2

#define CAN_TEST 0
#endif /* CAN_ADRESSES_H_ */