/*
 * custom project.c
 *
 * Created: 11/24/2019 3:13:26 PM
 * Author : jc434
 */ 

/*
 * proj using buttons.c
 *
 * Created: 11/27/2019 2:18:56 AM
 * Author : jc434
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "nokia5110.h"
#include "nokia5110.c"
#include "timer.h"
#include "io.h"
#include "io.c"

enum Menu_States {M_Init, M_Main, M_MainWait, M_MainWait2, M_Diff, M_DiffWait, M_MainUp, M_MainDown, M_DiffUp, M_DiffDown, M_Button, M_Time, M_Clear} Menu_state;
enum Player_States {P_Init, P_MenuWait, P_Wait, P_Up, P_Down, P_Left, P_Right} Player_state;
enum Room_States {R_Init, R_MenuWait, RoomStart, RoomStart2, RoomEnd, RoomEnd2, Room3B, Room3T, Room4W, RoomTL, RoomML, RoomBL, RoomTR, RoomMR, RoomBR, Finish} Room_state;


unsigned char difficulty = 0;
//MAP SCREENSHOTS
unsigned char i = 0;
void startRoom() {
	nokia_lcd_set_cursor(28, 35);
	nokia_lcd_write_string("START", 1);
	//vertical lines
	for (i = 0; i < 16; i++) {
		nokia_lcd_set_pixel(28, i, 1);
		nokia_lcd_set_pixel(56, i, 1);
	}
	//horizontal lines
	for (i = 0; i < 29; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
	}
	for (i = 56; i < 84; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
	}
	for (i = 0; i < 84; i++) {
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

void endRoom() {
	//door
	for (i = 0; i < 16; i++) {
		nokia_lcd_set_pixel(42, i, 1);
	}
	for (i = 7; i < 10; i++) {
		nokia_lcd_set_pixel(40, i, 1);
		nokia_lcd_set_pixel(44, i, 1);
	}
	//vertical lines
	for (i = 0; i < 16; i++) {
		nokia_lcd_set_pixel(28, i, 1);
		nokia_lcd_set_pixel(56, i, 1);
	}
	//horizontal lines
	for (i = 0; i < 84; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
	}
	for (i = 0; i < 84; i++) {
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

void startRoom2() {
	nokia_lcd_set_cursor(28, 8);
	nokia_lcd_write_string("START", 1);
	//vertical lines
	for (i = 32; i < 48; i++) {
		nokia_lcd_set_pixel(28, i, 1);
		nokia_lcd_set_pixel(56, i, 1);
	}
	//horizontal lines
	for (i = 0; i < 84; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
	}
	for (i = 0; i < 28; i++) {
		nokia_lcd_set_pixel(i, 32, 1);
	}
	for (i = 56; i < 84; i++) {
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

void endRoom2() {
	//door
	for (i = 56; i < 84; i++) {
		nokia_lcd_set_pixel(i, 24, 1);
	}
	for (i = 69; i < 72; i++) {
		nokia_lcd_set_pixel(i, 22, 1);
		nokia_lcd_set_pixel(i, 26, 1);
	}
	//vertical lines
	for (i = 0; i < 48; i++) {
		nokia_lcd_set_pixel(56, i, 1);
	}
	for (i = 0; i < 16; i++) {
		nokia_lcd_set_pixel(28, i, 1);
	}
	for (i = 32; i < 48; i++) {
		nokia_lcd_set_pixel(28, i, 1);
	}
	//horizontal lines
	for (i = 0; i < 28; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
		nokia_lcd_set_pixel(i, 32, 1);
	}
	for (i = 56; i < 84; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

void fourWay() {
	//vertical lines
	for (i = 0; i < 16; i++) {
		nokia_lcd_set_pixel(28, i, 1);
		nokia_lcd_set_pixel(56, i, 1);
	}
	for (i = 32; i < 48; i++) {
		nokia_lcd_set_pixel(28, i, 1);
		nokia_lcd_set_pixel(56, i, 1);
	}
	//horizontal lines
	for (i = 0; i < 28; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
		nokia_lcd_set_pixel(i, 32, 1);
	}
	for (i = 56; i < 84; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

void threeTop() {
	//vertical lines
	for (i = 32; i < 48; i++) {
		nokia_lcd_set_pixel(28, i, 1);
		nokia_lcd_set_pixel(56, i, 1);
	}
	//horizontal lines
	for (i = 0; i < 84; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
	}
	for (i = 0; i < 28; i++) {
		nokia_lcd_set_pixel(i, 32, 1);
	}
	for (i = 56; i < 84; i++) {
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

void threeBottom() {
	//vertical lines
	for (i = 0; i < 16; i++) {
		nokia_lcd_set_pixel(28, i, 1);
		nokia_lcd_set_pixel(56, i, 1);
	}
	//horizontal lines
	for (i = 0; i < 29; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
	}
	for (i = 56; i < 84; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
	}
	for (i = 0; i < 84; i++) {
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

//LEFT SIDE
//top left
void topLeft() {
	//vertical lines
	for (i = 16; i < 48; i++) {
		nokia_lcd_set_pixel(28, i, 1);
	}
	for (i = 32; i < 48; i++) {
		nokia_lcd_set_pixel(56, i, 1);
	}
	//horizontal lines
	for (i = 28; i < 84; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
	}
	for (i = 56; i < 84; i++) {
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

//middle left
void middleLeft() {
	//vertical lines
	for (i = 0; i < 48; i++) {
		nokia_lcd_set_pixel(28, i, 1);
	}
	for (i = 0; i < 16; i++) {
		nokia_lcd_set_pixel(56, i, 1);
	}
	for (i = 32; i < 48; i++) {
		nokia_lcd_set_pixel(56, i, 1);
	}
	//horizontal lines
	for (i = 56; i < 84; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

//bottom left
void bottomLeft() {
	//vertical lines
	for (i = 0; i < 32; i++) {
		nokia_lcd_set_pixel(28, i, 1);
	}
	for (i = 0; i < 16; i++) {
		nokia_lcd_set_pixel(56, i, 1);
	}
	//horizontal lines
	for (i = 56; i < 84; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
	}
	for (i = 28; i < 84; i++) {
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

//RIGHT SIDE
//top right
void topRight() {
	//vertical lines
	for (i = 16; i < 48; i++) {
		nokia_lcd_set_pixel(56, i, 1);
	}
	for (i = 32; i < 48; i++) {
		nokia_lcd_set_pixel(28, i, 1);
	}
	//horizontal lines
	for (i = 0; i < 56; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
	}
	for (i = 0; i < 28; i++) {
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

//middle right
void middleRight() {
	//vertical lines
	for (i = 0; i < 48; i++) {
		nokia_lcd_set_pixel(56, i, 1);
	}
	for (i = 0; i < 16; i++) {
		nokia_lcd_set_pixel(28, i, 1);
	}
	for (i = 32; i < 48; i++) {
		nokia_lcd_set_pixel(28, i, 1);
	}
	//horizontal lines
	for (i = 0; i < 28; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

//bottom right
void bottomRight() {
	//vertical lines
	for (i = 0; i < 32; i++) {
		nokia_lcd_set_pixel(56, i, 1);
	}
	for (i = 0; i < 16; i++) {
		nokia_lcd_set_pixel(28, i, 1);
	}
	//horizontal lines
	for (i = 0; i < 28; i++) {
		nokia_lcd_set_pixel(i, 16, 1);
	}
	for (i = 0; i < 56; i++) {
		nokia_lcd_set_pixel(i, 32, 1);
	}
}

//PLAYER POSITION AND RESTRICTIONS
//player current position
unsigned char currRoom = 18;
unsigned char currRoom2 = 3;
unsigned char posX = 41; //very left of 3x3
unsigned char posY = 23; //very top of 3x3
void generatePlayer() {
	for (i = posY; i < posY + 3; i++) {
		nokia_lcd_set_pixel(posX, i, 1);
		nokia_lcd_set_pixel(posX + 1, i, 1);
		nokia_lcd_set_pixel(posX + 2, i, 1);
	}
}

void clearPlayer() {
	for (i = posY; i < posY + 3; i++) {
		nokia_lcd_set_pixel(posX, i, 0);
		nokia_lcd_set_pixel(posX + 1, i, 0);
		nokia_lcd_set_pixel(posX + 2, i, 0);
	}
}

void playerUp() {
	//START, THREE BOTTOM
	if (Room_state == RoomStart || Room_state == Room3B) {
		if (posY > 16) {
			if (posX > 28 && posX < 56) {
				posY -= 3;
			}
			else if (posX < 28 || posX > 55) {
				if (posY > 19) {
					posY -= 3;
				}
				else {
					posY = posY;
				}
			}
		}
		else if (posY < 16) {
			if (posY > 2) {
				posY -= 3;
			}
			else {
				posY = 44;
				nokia_lcd_clear();
				//currRoom -= 5;
				if (difficulty == 0) {
					currRoom -= 5;
				}
				else if (difficulty == 1) {
					currRoom2 -= 5;
				}
			}
		}
	}
	//FOUR WAY, MIDDLE LEFT, BOTTOM LEFT, MIDDLE RIGHT, BOTTOM RIGHT; END2
	else if (Room_state == Room4W || Room_state == RoomML|| Room_state == RoomBL || Room_state == RoomMR || Room_state == RoomBR || Room_state == RoomEnd2) {
		if (posX < 28 || posX > 55) {
			if (posY > 19) {
				posY -= 3;
			}
			else {
				posY = posY;
			}
		}
		else if (posX > 28 && posX < 56) {
			if (posY > 2) {
				posY -= 3;
			}
			else {
				posY = 44;
				nokia_lcd_clear();
				//currRoom -= 5;
				if (difficulty == 0) {
					currRoom -= 5;
				}
				else if (difficulty == 1) {
					currRoom2 -= 5;
				}
			}
		}
	}
	//TOP LEFT, TOP RIGHT, THREE TOP; START2
	else if (Room_state == RoomTL || Room_state == RoomTR || Room_state == Room3T || Room_state == RoomStart2) {
		if (posY > 19) {
			posY -= 3;
		}
		else {
			posY = posY;
		}
	}
	//END
	else if (Room_state == RoomEnd) {
		if (posX < 28 || posX > 55) {
			if (posY > 19) {
				posY -= 3;
			}
			else {
				posY = posY;
			}
		}
		else if (posX > 28 && posX < 56) {
			if (posY > 19) {
				posY -= 3;
			}
			else {
				currRoom = 0;
				posX = 100;
				posY = 100;
			}
		}
	}
	//test
	else {
		posY = posY;
	}
}

void playerDown() {
	//START, END, THREE BOTTOM, BOTTOM LEFT, BOTTOM RIGHT
	if (Room_state == RoomStart || Room_state == RoomEnd || Room_state == Room3B || Room_state == RoomBL || Room_state == RoomBR) {
		if (posY < 29) {
			posY += 3;
		}
		else {
			posY = posY;
		}
	}
	//FOUR WAY, TOP LEFT, MIDDLE LEFT, TOP RIGHT, MIDDLE RIGHT, THREE TOP; START2, END2
	else if (Room_state == Room4W || Room_state == RoomTL || Room_state == RoomML || Room_state == RoomTR || Room_state == RoomMR || Room_state == Room3T || Room_state == RoomStart2 || Room_state == RoomEnd2) {
		if (posX < 28 || posX > 55) {
			if (posY < 29) {
				posY += 3;
			}
			else {
				posY = posY;
			}
		}
		else if (posX > 28 && posX < 56) {
			if (posY < 44) {
				posY += 3;
			}
			else {
				posY = 2;
				nokia_lcd_clear();
				//currRoom += 5;
				if (difficulty == 0) {
					currRoom += 5;
				}
				else if (difficulty == 1) {
					currRoom2 += 5;
				}
			}
		}
	}
	//test
	else {
		posY = posY;
	}
}

void playerLeft() {
	//START, END, THREE BOTTOM, THREE TOP, FOUR WAY, TOP RIGHT, MIDDLE RIGHT, BOTTOM RIGHT; START2, END2
	if (Room_state == RoomStart || Room_state == RoomEnd || Room_state == Room3B || Room_state == Room3T || Room_state == Room4W || Room_state == RoomTR || Room_state == RoomMR || Room_state == RoomBR || Room_state == RoomStart2 || Room_state == RoomEnd2) {
		if (posY < 16 || posY > 30) {
			if (posX > 30) {
				posX -= 3;
			}
			else {
				posX = posX;
			}
		}
		else if (posY > 16 && posY < 32) {
			if (posX > 2) {
				posX -= 3;
			}
			else {
				posX = 80;
				nokia_lcd_clear();
				//currRoom--;
				if (difficulty == 0) {
					currRoom--;
				}
				else if (difficulty == 1) {
					currRoom2--;
				}
			}
		}
	}
	//TOP LEFT, MIDDLE LEFT, BOTTOM LEFT
	else if (Room_state == RoomTL || Room_state == RoomML || Room_state == RoomBL) {
		if (posX > 30) {
			posX -= 3;
		}
		else {
			posX = posX;
		}
	}
	//test
	else {
		posX = posX;
	}
}

void playerRight() {
	//START, END, THREE BOTTOM, THREE TOP, FOUR WAY, TOP LEFT, MIDDLE LEFT, BOTTOM LEFT; START2
	if (Room_state == RoomStart || Room_state == RoomEnd || Room_state == Room3B || Room_state == Room3T || Room_state == Room4W || Room_state == RoomTL || Room_state == RoomML || Room_state == RoomBL || Room_state == RoomStart2) {
		if (posY < 16 || posY > 31) {//changed 30 to 31
			if (posX < 53) {
				posX += 3;
			}
			else {
				posX = posX;
			}
		}
		else if (posY > 16 && posY < 32) {
			if (posX < 80) {
				posX += 3;
			}
			else {
				posX = 2;
				nokia_lcd_clear();
				//currRoom++;
				if (difficulty == 0) {
					currRoom++;
				}
				else if (difficulty == 1) {
					currRoom2++;
				}
			}
		}
	}
	//TOP RIGHT, MIDDLE RIGHT, BOTTOM RIGHT; END2
	else if (Room_state == RoomTR || Room_state == RoomMR || Room_state == RoomBR) {
		if (posX < 53) {
			posX += 3;
		}
		else {
			posX = posX;
		}
	}
	//END2
	else if (Room_state == RoomEnd2) {
		if (posY < 16 || posY > 31) {
			if (posX < 53) {
				posX += 3;
			}
			else {
				posX = posX;
			}
		}
		else if (posY > 16 && posY < 32) {
			if (posX < 53) {
				posX += 3;
			}
			else {
				currRoom2 = 0;
				posX = 100;
				posY = 100;
			}
		}
	}
	//test
	else {
		posX = posX;
	}
}

//RUN TIME
unsigned short runTime= 0;
unsigned short a, b = 0;
void upTime() {	
	b = runTime / 1000;
	LCD_Cursor(6);
	LCD_WriteData(b + '0');
	a = runTime % 1000;
	
	b = a / 100;
	LCD_Cursor(7);
	LCD_WriteData(b + '0');
	a = a % 100;
	
	b = a / 10;
	LCD_Cursor(8);
	LCD_WriteData(b + '0');
	a = a % 10;
	LCD_Cursor(0);
	
	if (currRoom != 0) {
		runTime++;
	}
	else {
		runTime = runTime;
	}
}

//JOYSTICK
void ADC_init() {
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t ADC_read(uint8_t ch){
	ch &= 0b00000111;
	ADMUX = (ADMUX & 0xF8)|ch;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);
}

int16_t AD_LR = 0;
int16_t AD_UD = 0;

unsigned char D1 = 0x00; //RESET BUTON
//MENU SCREEN LCD
unsigned char D0 = 0x00;
unsigned char cursorPos = 0;
void menu() {
	D0 = ~PIND & 0x01;
	D1 = ~PIND & 0X02;
	switch(Menu_state) {
		case M_Init:
		case M_Main:
			break;
		case M_MainWait:
			AD_UD = ADC_read(0);
			if (AD_UD < 150) {
				Menu_state = M_MainUp;
			}
			else if (AD_UD > 750) {
				Menu_state = M_MainDown;
			}
			else if (D0) {
				Menu_state = M_MainWait2;
			}
			else if (D1) {
				Menu_state = M_Main;
			}
			else {
				Menu_state = M_MainWait;
			}
			break;
		case M_MainWait2:
			if (D0) {
				Menu_state = M_MainWait2;
			}
			else {
				if (cursorPos == 6) {
					currRoom = 18;
					currRoom2 = 3;
					if (difficulty == 0) {
						currRoom2 = -1;
						Room_state = RoomStart;
					}
					else if (difficulty == 1) {
						currRoom = -1;
						Room_state = RoomStart2;
					}
					else if (difficulty == 2) {
						
					}
					else {
						Room_state = RoomStart;
					}
					Player_state = P_Wait;
					Menu_state = M_Time;
					LCD_ClearScreen();
					LCD_DisplayString(1, "Time:");
				}
				else if (cursorPos == 27) {
					Menu_state = M_Diff;
				}
				else {
					Menu_state = M_MainWait2;
				}
			}
			break;
		case M_Diff:
			break;
		case M_DiffWait:
			AD_UD = ADC_read(0);
			if (AD_UD < 150) {
				Menu_state = M_DiffUp;
			}
			else if (AD_UD > 750) {
				Menu_state = M_DiffDown;
			}
			else if (D0) {
				Menu_state = M_Button;
			}
			else if (D1) {
				Menu_state = M_Main;
			}
			else {
				Menu_state = M_DiffWait;
			}
			break;
		case M_Button:
			if (D0) {
				Menu_state = M_Button;
			}
			else {
				Menu_state = M_Main;
			}
			if (D1) {
				Menu_state = M_MainWait;
			}
			break;
		case M_MainUp:
		case M_MainDown:
		case M_DiffUp:
		case M_DiffDown:
		case M_Time:
		case M_Clear:
			if (D1) {
				Menu_state = M_Clear;
			}
			break;
		default:
			Menu_state = M_Init;
			break;
	}
	switch(Menu_state) {
		case M_Init:
		case M_Main:
			cursorPos = 6;
			LCD_DisplayString(1, "Start           Difficulty");
			LCD_Cursor(cursorPos);
			Menu_state = M_MainWait;
			break;
		case M_MainWait:
			break;
		case M_Diff:
			if (difficulty == 0) {
				cursorPos = 5;
			}
			else if (difficulty == 1) {
				cursorPos = 14;
			}
			else if (difficulty == 2) {
				cursorPos = 21;
			}
			else {
				cursorPos = 5;
			}
			LCD_DisplayString(1, "Easy   Medium   Hard");
			LCD_Cursor(cursorPos);
			Menu_state = M_DiffWait;
			break;
		case M_DiffWait:
			break;
		case M_MainUp:
			cursorPos = 6;
			LCD_Cursor(cursorPos);
			Menu_state = M_MainWait;
			break;
		case M_MainDown:
			cursorPos = 27;
			LCD_Cursor(cursorPos);
			Menu_state = M_MainWait;
			break;
		case M_DiffUp:
			if (difficulty > 0) {
				difficulty--;
			}
			Menu_state = M_Diff;
			break;
		case M_DiffDown:
			if (difficulty < 2) {
				difficulty++;
			}
			Menu_state = M_Diff;
			break;
		case M_Button:
			break;
		case M_Time:
			upTime();
			break;
		case M_Clear:
			runTime = 0;
			LCD_ClearScreen();
			Menu_state = M_Main;
			break;
	}
}

//PLAYER GENERATOR
void player() {
	D1 = ~PIND & 0x02;
	switch(Player_state) { //transitions
		case P_Init:
		case P_MenuWait:
			break;
		case P_Wait:
			AD_UD = ADC_read(0);
			AD_LR = ADC_read(1);
			if (AD_UD < 150) {
				Player_state = P_Up;
			}
			else if (AD_UD > 750) {
				Player_state = P_Down;
			}
			else if (AD_LR > 750) {
				Player_state = P_Right;
			}
			else if (AD_LR < 150) {
				Player_state = P_Left;
			}
			else if (D1) {
				Player_state = P_MenuWait;
			}
			else {
				Player_state = P_Wait;
			}
		case P_Up:
			break;
		case P_Down:
			break;
		case P_Left:
			break;
		case P_Right:
			break;
		default:
			Player_state = P_Init;
			break;
	}
	switch(Player_state) { //actions
		case P_Init:
			Player_state = P_MenuWait;
			break;
		case P_MenuWait:
			clearPlayer();
			posX = 41;
			posY = 23;
			break;
		case P_Wait:
			generatePlayer();
			break;
		case P_Up:
			clearPlayer();
			playerUp();
			generatePlayer();
			Player_state = P_Wait;
			break;
		case P_Down:
			clearPlayer();
			playerDown();
			generatePlayer();
			Player_state = P_Wait;
			break;
		case P_Left:
			clearPlayer();
			playerLeft();
			generatePlayer();
			Player_state = P_Wait;
			break;
		case P_Right:
			clearPlayer();
			playerRight();
			generatePlayer();
			Player_state = P_Wait;
			break;
	}
}

//ROOM GENERATOR
void room() {
	D1 = ~PIND & 0x02;
	switch(Room_state) {
		case R_Init:
			Room_state = R_MenuWait;
			break;
		case R_MenuWait:
			break;
		case RoomStart:
		case RoomStart2:
		case RoomEnd:
		case RoomEnd2:
		case Room3B:
		case Room3T:
		case Room4W:
		case RoomTL:
		case RoomML:
		case RoomBL:
		case RoomTR:
		case RoomMR:
		case RoomBR:
		case Finish:
			if (D1) {
				currRoom = 21;
				currRoom2 = 21;
			}
			else if (currRoom == 0 || currRoom2 == 0) {
				Room_state = Finish;
			}
			else if (currRoom == 1 || currRoom2 == 1 || currRoom2 == 5) {
				Room_state = RoomTL;
			}
			else if (currRoom == 2 || currRoom == 4 || currRoom == 8 || currRoom2 == 2 || currRoom2 == 11 || currRoom2 == 12) {
				Room_state = Room3T;
			}
			else if (currRoom == 3) {
				Room_state = RoomEnd;
			}
			else if (currRoom == 5 || currRoom2 == 4 || currRoom2 == 13) {
				Room_state = RoomTR;
			}
			else if (currRoom == 6 || currRoom == 11 || currRoom2 == 10) {
				Room_state = RoomML;
			}
			else if (currRoom == 10 || currRoom == 15) {
				Room_state = RoomMR;
			}
			else if (currRoom == 16 || currRoom2 == 7 || currRoom2 == 15 || currRoom2 == 22) {
				Room_state = RoomBL;
			}
			else if (currRoom == 17 || currRoom == 19 || currRoom2 == 8 || currRoom2 == 16) {
				Room_state = Room3B;
			}
			else if (currRoom == 18) {
				Room_state = RoomStart;
			}
			else if (currRoom == 20 || currRoom2 == 6 || currRoom2 == 9 || currRoom2 == 23) {
				Room_state = RoomBR;
			}
			else if (currRoom == 21 && currRoom2 == 21) {
				Room_state = R_MenuWait;
			}
			else if (currRoom2 == 3) {
				Room_state = RoomStart2;
			}
			else if (currRoom2 == 18) {
				Room_state = RoomEnd2;
			}
			else {
				Room_state = Room4W;
			}
			break;
		default:
			Room_state = R_Init;
	}
	switch(Room_state) {
		case R_Init:
		case R_MenuWait:
			nokia_lcd_clear();
			break;
		case RoomStart:
			startRoom();
			break;
		case RoomStart2:
			startRoom2();
			break;
		case RoomEnd:
			endRoom();
			break;
		case RoomEnd2:
			endRoom2();
			break;
		case Room3B:
			threeBottom();
			break;
		case Room3T:
			threeTop();
			break;
		case Room4W:
			fourWay();
			break;
		case RoomTL:
			topLeft();
			break;
		case RoomML:
			middleLeft();
			break;
		case RoomBL:
			bottomLeft();
			break;
		case RoomTR:
			topRight();
			break;
		case RoomMR:
			middleRight();
			break;
		case RoomBR:
			bottomRight();
			break;
		case Finish:
			nokia_lcd_clear();
			nokia_lcd_set_cursor(24, 21);
			nokia_lcd_write_string("FINISH!", 1);
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xC0; PORTD = 0x3F;
	
	TimerSet(100);
	TimerOn();
	nokia_lcd_init();
	nokia_lcd_clear();
	LCD_init();
	LCD_ClearScreen();
	ADC_init();
	
	Menu_state = -1;
	Room_state = -1;
	Player_state = -1;
	
	while (1) {
		menu();
		room();
		player();
		nokia_lcd_render();
		while (!TimerFlag) {}
		TimerFlag = 0;
	}
}