#include "keyboard.h"

void KeyAction(unsigned char keycode);

unsigned char code Key_Map[4][4] = {
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'+','0','-','D'},
};

unsigned char Key_Sta[4][4] = {
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
};


void KeyDriver()
{
	unsigned char i,j;
	static unsigned char backup[4][4] = {
		{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
	};
	
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(backup[i][j] != Key_Sta[i][j])
			{
				if(backup[i][j] != 0)
				{
					KeyAction(Key_Map[i][j]);
				}
				backup[i][j] = Key_Sta[i][j];
			}
		}
	}
}

void KeyScan()
{
	unsigned char i;
	static unsigned char keyout = 0;
	static unsigned char KeyBuff[4][4] = {
		{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
		{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF}
	};
	
	KeyBuff[keyout][0] = KeyBuff[keyout][0] << 1 | KEY_IN_1;
	KeyBuff[keyout][1] = KeyBuff[keyout][1] << 1 | KEY_IN_2;
	KeyBuff[keyout][2] = KeyBuff[keyout][2] << 1 | KEY_IN_3;
	KeyBuff[keyout][3] = KeyBuff[keyout][3] << 1 | KEY_IN_4;
	
	for(i = 0; i < 4; i++)
	{
		if((KeyBuff[keyout][i] & 0x0F) == 0x00)
		{
			Key_Sta[keyout][i] = 0;
		}
		else if((KeyBuff[keyout][i] & 0x0F) == 0x0F)
		{
			Key_Sta[keyout][i] = 1;
		}
	}
	
	keyout++;
	keyout &= 0x03;	
	
	switch(keyout)
	{
		case 0: KEY_OUT_4 = 1; KEY_OUT_1 = 0; break;
		case 1: KEY_OUT_1 = 1; KEY_OUT_2 = 0; break;
		case 2: KEY_OUT_2 = 1; KEY_OUT_3 = 0; break;
		case 3: KEY_OUT_3 = 1; KEY_OUT_4 = 0; break;
		default: break;
	}	
}
