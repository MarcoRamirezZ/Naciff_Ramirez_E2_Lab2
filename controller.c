/*
 * controler.c
 *
 *  Created on: 3 may 2020
 *      Author: Chencho
 */

#include "controller.h"

//Control for state machines in the code
static substate_t currentSubState = STATE0;

state_flag_t MSPaint(uint8_t* bufferMouseOrKey)
{
	//Checks if open paint has been completed
	static state_flag_t openPaint_flag = INCOMPLETE;

	switch(currentSubState)
	{
	case STATE0:
	{
		//Windows + R
		bufferMouseOrKey[3] = KEY_LEFT_GUI;
		bufferMouseOrKey[4] = KEY_R;
	}
	break;
	//Next states meant to write "mspaint + ENTER"
	case STATE1:
	{
		bufferMouseOrKey[3] = KEY_M;
	}
	break;
	case STATE2:
	{
		bufferMouseOrKey[3] = KEY_S;
	}
	break;
	case STATE3:
	{
		bufferMouseOrKey[3] = KEY_P;
	}
	break;
	case STATE4:
	{
		bufferMouseOrKey[3] = KEY_A;
	}
	break;
	case STATE5:
	{
		bufferMouseOrKey[3] = KEY_I;
	}
	break;
	case STATE6:
	{
		bufferMouseOrKey[3] = KEY_N;
	}
	break;
	case STATE7:
	{
		bufferMouseOrKey[3] = KEY_T;
	}
	break;
	case STATE8:
	{
		bufferMouseOrKey[3] = KEY_ENTER;
		openPaint_flag = COMPLETE;
	}
	break;
	default:
		break;
	}

	//is substate = 8? if true send to 0, else send next state
	currentSubState = (STATE8 == currentSubState) ? STATE0 : ( currentSubState + 1 );

	return openPaint_flag;
}

state_flag_t Square(uint8_t* bufferMouseOrKey)
{
	//Checks is figure has been drawn
	static state_flag_t drawFigure_flag = INCOMPLETE;

	//To draw a line in certain direction
	static uint8_t counter = 0;

	static uint8_t currentSubState = STATE0;

	switch (currentSubState)
	{
	case STATE0:
	{
		//Move ->
		bufferMouseOrKey[1] = 1U;//click pressed
		bufferMouseOrKey[2] = 1U;//x
		bufferMouseOrKey[3] = 0U;//y
	}
		break;
	case STATE1:
	{
		//Move down
		bufferMouseOrKey[1] = 1U;
		bufferMouseOrKey[2] = 0U;
		bufferMouseOrKey[3] = 1U;
	}
		break;
	case STATE2:
	{
		//Move <-
		bufferMouseOrKey[1] = 1U;
		bufferMouseOrKey[2] = (uint8_t)(0xFFU);
		bufferMouseOrKey[3] = 0U;
	}
		break;
	case STATE3:
	{
		//Move up
		bufferMouseOrKey[1] = 1U;
		bufferMouseOrKey[2] = 0U;
		bufferMouseOrKey[3] = (uint8_t)(0xFFU);
	}
		break;
	case STATE4:
		drawFigure_flag = COMPLETE;
		break;
	default:
		break;
	}

	//Draw a line in certain direction
	if(counter < SIZE_OF_SQUARE)
		{
			counter++;
			currentSubState = currentSubState;
		}
		else
		{
			counter = 0;
			currentSubState++;
		}

	return drawFigure_flag;
}

state_flag_t Notepad(uint8_t* bufferMouseOrKey)
{
	//Checks is notepad actions have been completed
	static state_flag_t openNotepad_flag = INCOMPLETE;

	static moveWindow_t moveWindow = LEFT;

	switch(currentSubState)
	{
	case STATE0:
		//Write "Windows + R"
		bufferMouseOrKey[3] = KEY_LEFT_GUI;
		bufferMouseOrKey[4] = KEY_R;
		break;
	case STATE1:
		//Next lines write "notepad + ENTER"
		bufferMouseOrKey[3] = KEY_N;
		break;
	case STATE2:
		bufferMouseOrKey[3] = KEY_O;
		break;
	case STATE3:
		bufferMouseOrKey[3] = KEY_T;
		break;
	case STATE4:
		bufferMouseOrKey[3] = KEY_E;
		break;
	case STATE5:
		bufferMouseOrKey[3] = KEY_P;
		break;
	case STATE6:
		bufferMouseOrKey[3] = KEY_A;
		break;
	case STATE7:
		bufferMouseOrKey[3] = KEY_D;
		break;
	case STATE8:
		bufferMouseOrKey[3] = KEY_ENTER;
		break;
	case STATE9:
		// Execute either "CTRL + <-" or "CTRL + ->"
		bufferMouseOrKey[3] = KEY_LEFT_GUI;
		if(LEFT == moveWindow)
		{
			bufferMouseOrKey[4] = KEY_LEFTARROW;
			moveWindow = RIGHT;
		}else
		{
			bufferMouseOrKey[4] = KEY_RIGHTARROW;
			openNotepad_flag = COMPLETE;
		}
		break;
	default:
		break;
	}

	//If state = 9, send to 0, else, send to next state
	currentSubState = (STATE9 == currentSubState) ? STATE0 : currentSubState + 1;

	return openNotepad_flag;
}

state_flag_t moveLeft(uint8_t* bufferMouseOrKey)
{
	//Move cursor to the left
	static state_flag_t moveLeft_flag = INCOMPLETE;
	static uint8_t currentSubState = STATE0;
	static uint8_t counter = 0;

	switch (currentSubState)
	{
	case STATE0:
	{
		//Move ->
		bufferMouseOrKey[1] = 0U;
		bufferMouseOrKey[2] = (uint8_t)(0xFBU);
		bufferMouseOrKey[3] = 0U;
	}
		break;
	case STATE1:
	{
		//Click
		bufferMouseOrKey[1] = 1U;
		bufferMouseOrKey[2] = 0U;
		bufferMouseOrKey[3] = 0U;
		moveLeft_flag = COMPLETE;
	}
		break;
	default:
		break;
	}

	//Needs to be donde lots of times since its moving pixelwise
	if( counter < 100 )
	{
		counter++;
		currentSubState = currentSubState;
	}
	else
	{
		counter = 0;
		currentSubState++;
	}

	return moveLeft_flag;
}

state_flag_t write_notepad(uint8_t* bufferMouseOrKey)
{
	//Writes "hola mundo" in recently opened notepad
	static state_flag_t writeText_flag = INCOMPLETE;

	switch(currentSubState)
	{
	case STATE0:
		bufferMouseOrKey[3] = KEY_H;
		break;
	case STATE1:
		bufferMouseOrKey[3] = KEY_O;
		break;
	case STATE2:
		bufferMouseOrKey[3] = KEY_L;
		break;
	case STATE3:
		bufferMouseOrKey[3] = KEY_A;
		break;
	case STATE4:
		bufferMouseOrKey[3] = KEY_SPACEBAR;
		break;
	case STATE5:
		bufferMouseOrKey[3] = KEY_M;
		break;
	case STATE6:
		bufferMouseOrKey[3] = KEY_U;
		break;
	case STATE7:
		bufferMouseOrKey[3] = KEY_N;
		break;
	case STATE8:
		bufferMouseOrKey[3] = KEY_D;
		break;
	case STATE9:
		bufferMouseOrKey[3] = KEY_O;
		break;
	case STATE10:
		//Selects everything in notepad
		bufferMouseOrKey[3] = KEY_LEFTCONTROL;
		bufferMouseOrKey[4] = KEY_E;
		break;
	case STATE11:
		//Copy "hola mundo" text just written
		bufferMouseOrKey[3] = KEY_LEFTCONTROL;
		bufferMouseOrKey[4] = KEY_C;
		writeText_flag = COMPLETE;
		break;
	default:
		break;
	}

	//Reset or increase value of state machine
	currentSubState = (STATE11 == currentSubState) ? STATE0 : currentSubState + 1;

	return writeText_flag;
}

state_flag_t moveRight(uint8_t* bufferMouseOrKey)
{
	//Move cursor to the right
	static state_flag_t moveRight_flag = INCOMPLETE;
	static uint8_t currentSubState = STATE0;
	static uint8_t counter;

	switch (currentSubState)
	{
	case STATE0:
	{
		// Move ->
		bufferMouseOrKey[1] = 0U;
		bufferMouseOrKey[2] = 10U;
		bufferMouseOrKey[3] = 0U;
	}
		break;
	case STATE1:
	{
		//Click
		bufferMouseOrKey[1] = 1U;
		bufferMouseOrKey[2] = 0U;
		bufferMouseOrKey[3] = 0U;
		moveRight_flag = COMPLETE;
	}
		break;
	default:
		break;
	}

	//Same as Moveleft function
	if(counter < 100)
	{
		counter++;
		currentSubState = currentSubState;
	}
	else
	{
		counter = 0;
		currentSubState++;
	}

	return moveRight_flag;
}

state_flag_t paste_notepad(uint8_t* bufferMouseOrKey){

	//Pastes copied text in second notepad
	static state_flag_t pasteText_flag = INCOMPLETE;

	//Writes "CTRL + V"
	bufferMouseOrKey[3] = KEY_LEFTCONTROL;
	bufferMouseOrKey[4] = KEY_V;
	pasteText_flag = COMPLETE;

	return pasteText_flag;
}


