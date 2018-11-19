/*
 * music.c
 *
 * Created: 05.11.2018 16:17:29
 *  Author: EdvardOlaf
 */ 
#include "music.h"


#define	C0	16
#define	C_x0	17
#define	D0	18
#define	D_x0	19
#define	E0	21
#define	F0	22
#define	F_x0	23
#define	G0	25
#define	G_x0	26
#define	A0	28
#define	A_x0	29
#define	B0	31
#define	C1	33
#define	C_x1	35
#define	D1	37
#define	D_x1	39
#define	E1	41
#define	F1	44
#define	F_x1	46
#define	G1	49
#define	G_x1	52
#define	A1	55
#define	A_x1	58
#define	B1	62
#define	C2	65
#define	C_x2	69
#define	D2	73
#define	D_x2	78
#define	E2	82
#define	F2	87
#define	F_x2	93
#define	G2	98
#define	G_x2	104
#define	A2	110
#define	A_x2	117
#define	B2	123
#define	C3	131
#define	C_x3	139
#define	D3	147
#define	D_x3	156
#define	E3	165
#define	F3	175
#define	F_x3	185
#define	G3	196
#define	G_x3	208
#define	A3	220
#define	A_x3	233
#define	B3	247
#define	C4	262
#define	C_x4	277
#define	D4	294
#define	D_x4	311
#define	E4	330
#define	F4	349
#define	F_x4	370
#define	G4	392
#define	G_x4	415
#define	A4	440
#define	A_x4	466
#define	B4	494
#define	C5	523
#define	C_x5	554
#define	D5	587
#define	D_x5	622
#define	E5	659
#define	F5	698
#define	F_x5	740
#define	G5	784
#define	G_x5	831
#define	A5	880
#define	A_x5	932
#define	B5	988
#define	C6	1047
#define	C_x6	1109
#define	D6	1175
#define	D_x6	1245
#define	E6	1319
#define	F6	1397
#define	F_x6	1480
#define	G6	1568
#define	G_x6	1661
#define	A6	1760
#define	A_x6	1865
#define	B6	1976
#define	C7	2093
#define	C_x7	2217
#define	D7	2349
#define	D_x7	2489
#define	E7	2637
#define	F7	2794
#define	F_x7	2960
#define	G7	3136
#define	G_x7	3322
#define	A7	3520
#define	A_x7	3729
#define	B7	3951
#define	C8	4186
#define	C_x8	4435
#define	D8	4699
#define	D_x8	4978
#define	E8	5274
#define	F8	5588
#define	F_x8	5920
#define	G8	6272
#define	G_x8	6645
#define	A8	7040
#define	A_x8	7459
#define	B8	7902

#define STOP_NOTE 0
#define PAUSE_NOTE 1

#define PWM_PRESCALER 1024UL
#define PWM_PRESCALER_BITMAP 0b101

uint16_t bpm_to_timer_top(uint16_t bpm);
void music_timer_start();
void music_timer_stop();
void music_reset();
void music_play_next_note();

Note GoT[] =  {		
{G5, 4}, {C5, 4}, {E6, 2}, {F5, 2},
{G5, 4}, {C5, 4}, {E6, 2}, {F5, 2},
{G5, 4}, {C5, 4}, {E6, 2}, {F5, 2},
{G5, 4}, {C5, 4}, {E6, 2}, {F5, 2},
{G5, 12},
{C5, 12},
{C5, 2}, {F5,2}, {G5, 8},
{C5, 8}, {D_x5, 2}, {F5, 2},
{D5, 4}, {G4, 4}, {A_x4, 2}, {C5, 2},
{D5, 4}, {G4, 4}, {A_x4, 2}, {C5, 2},
{D5, 4}, {G4, 4}, {A_x4, 2}, {C5, 2},
{D5, 4}, {G4, 4}, {A_x4, 4},
{F5,12},
{A_x4,12},
{D_x5, 2}, {D5, 2}, {F5,8},
{A_x4, 8}, {C5, 2}, {D5, 2},
{C5, 4}, {F4, 4}, {G_x4, 2}, {A_x4, 2},
{C5, 4}, {F4, 4}, {G_x4, 2}, {A_x4, 2},
{C5, 4}, {F4, 4}, {G_x4, 2}, {A_x4, 2},
{C5, 4}, {F4, 4}, {G_x4, 4}, 
{STOP_NOTE, 0}};
						
Note game_over_music[] = {
{G4, 4}, {D5, 4}, {PAUSE_NOTE, 4}, {D5, 4},
{D5, 4},  {PAUSE_NOTE, 1} ,{C5, 4}, {PAUSE_NOTE, 1}, {B4, 4}, {PAUSE_NOTE, 2},
{G4, 4}, {E4, 4}, {PAUSE_NOTE, 4}, {E4, 4},
{C4, 4}, 
{STOP_NOTE, 0}};
	
Note one_music[] = {
{B3, 2}, {F_x4, 2}, {B3, 2}, {D4, 10},
{G3, 2}, {F_x4, 2}, {G3, 2}, {D4, 10},
{B3, 2}, {F_x4, 2}, {B3, 2}, {D4, 10},
{G3, 2}, {F_x4, 2}, {G3, 2}, {D4, 4}, {G4, 6},
{B3, 2}, {F_x4, 2}, {B3, 2}, {D4, 10},
{A3, 2}, {F_x4, 2}, {A3, 2}, {D4, 10},
{G3, 2}, {F_x4, 2}, {G3, 2}, {D4, 10},
{E4, 2}, {B3, 2}, {E4, 2}, {B3, 2}, 
{PAUSE_NOTE, 2}, {E4, 1}, {F_x4, 1}, {A4, 2}, {C_x5, 2}, {B4, 8},
{PAUSE_NOTE, 2}, {D5, 1}, {C_x5, 1}, {B4, 2}, {PAUSE_NOTE, 2}, {D5, 1}, {C_x5, 1}, {A4, 2}, {PAUSE_NOTE, 2}, {D5, 2},
{D5, 1}, {C_x5, 1}, {B4, 14},
{PAUSE_NOTE, 2}, {F_x5, 1}, {E5, 1}, {D5, 1}, {E5, 1}, {D5, 2}, {C_x5,1}, {G4, 1}, {A4,1}, {C_x5, 1}, {B4, 1}, {G4, 1}, {A4, 2},
{B4, 10}, {A4, 2}, {B4, 2}, {C_x5, 1}, {D5, 1},
{C_x5, 6}, {A4, 2}, {B4, 2}, {C_x5, 2}, {D5, 1}, {C_x5, 1}, {A4, 2},
{B4, 12}, {PAUSE_NOTE, 4},
{STOP_NOTE, 0}};

Note wallace_and_gromit[] = {
{D5, 4}, {C5, 2}, {B4, 2}, {D5, 4}, {C5, 2}, {B4, 2},
{D5, 4}, {A4, 8}, {PAUSE_NOTE, 4},
{E5, 2}, {D5, 2}, {E5, 2}, {F_x5, 4}, {E5, 2}, {D5, 2}, {C5, 2},
{B4, 8},
{D5, 4}, {C5, 2}, {B4, 2}, {D5, 4}, {C5, 2}, {B4, 2},
{D5, 4}, {A4, 8}, {PAUSE_NOTE, 4},
{E5, 2}, {D5, 2}, {E5, 2}, {F_x5, 4}, {E5, 4}, {F5, 2},
{G5, 2}, {PAUSE_NOTE, 2},{D5, 2}, {PAUSE_NOTE, 2},{G5, 2}, {PAUSE_NOTE, 6},
{STOP_NOTE, 0}};


Note *current_song;
uint8_t note_index;
uint16_t music_bar;
uint16_t note_pause;
bool looping;
void music_init() {
		music_timer_init();
		speaker_init();
		looping = false;
		current_song = game_over_music;
		note_index = 0;
}


void music_timer_init() {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		TCCR4A = (0b00 << COM4A0) | (0b00 << COM5B0) |  (0b00 << WGM40);	//Toggle OC1A on Compare Match, OC1B and OC1C disconnected
		//Set Wave gen to 15 (Fast PWM) and
		TCCR4B = (0b000 << CS40) | (0b01 << WGM42);		//Prescaler to 0
		music_set_bpm(120);
		OCR4A = 20;
		OCR4B = 20;
		TIMSK4 |= (1 << OCIE4A) | (1 << OCIE4B);
	}
}

bool music_is_playing() {
	return (TCCR4B & (0b111 << CS40)) != 0;
}

void music_test() {
	music_set_bpm(80);
	music_play(3);
}
void music_play_loop(music_t music) {
	looping = true;
	music_play(music);	
}

void music_play(music_t music) {
	bool defined_song = true;
	switch(music){
		case GOT_MUSIC:
			music_set_bpm(80);
			current_song = GoT;
		break;
		case WALLACE_AND_GROMMIT_MUSIC:
			music_set_bpm(80);
			current_song = wallace_and_gromit;
		break;
		case GAME_OVER_MUSIC:
			music_set_bpm(90);
			current_song = game_over_music;
		break;
		case ONE_MUSIC:
			music_set_bpm(65);
			current_song = one_music;
			break;
		default:
			
			music_reset();
			defined_song = false;
			break;
	}
	if (defined_song){
		note_index = 0;
		music_timer_start();
		music_play_next_note();
	}
}

void music_set_bpm(uint16_t bpm) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		music_bar = bpm_to_timer_top(bpm);
		note_pause = music_bar/4;
	}
}

uint16_t bpm_to_timer_top(uint16_t bpm) {
	return ((F_CPU*60)/PWM_PRESCALER)/(bpm*8)-1;
}
void music_timer_stop() {
	TCCR4B = TCCR4B & ~(0b111 << CS40);//Set prescalar to 0
}

void music_timer_start() {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		OCR4A = 0;
		TCCR4B = (TCCR4B & ~(0b111 << CS40)) | (PWM_PRESCALER_BITMAP << CS40); //Set prescalar to 1
	}
}

void music_reset() {
	looping = false;
	note_index = 0;
	music_timer_stop();
	speaker_off();
}
void music_play_next_note() {
	if(current_song[note_index][0] == STOP_NOTE) {
		note_index = 0;
	}
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		OCR4A = music_bar*current_song[note_index][1];
		OCR4B = OCR4A - note_pause;
	}
	if(current_song[note_index][0] != PAUSE_NOTE) {
		speaker_set_hz(current_song[note_index][0]);
		speaker_on();
	}
	note_index += 1;
}
	

ISR(TIMER4_COMPA_vect) {
	if(!looping && current_song[note_index][0] == STOP_NOTE) {
		if(looping) {
			note_index = 0;	
		} else {
			music_reset();
		}
	} else {
		music_play_next_note();
	}
}

ISR(TIMER4_COMPB_vect) { 
	speaker_off();
}