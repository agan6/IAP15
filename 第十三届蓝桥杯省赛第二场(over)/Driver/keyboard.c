#include "keyboard.h"

unsigned char code Key_Map[4] = {'1','2','3','4'};
unsigned char Key_Sta[4] = {1,1,1,1};

extern void KeyAction(unsigned char keycode);

void KeyDriver()
{
    unsigned char i = 0;
    static unsigned char backup[4] = {1,1,1,1};
    for(i = 0; i < 4; i++)
    {
        if(backup[i] != Key_Sta[i])
        {
            if(backup[i] != 0)
            {
                KeyAction(Key_Map[i]);
            }
            backup[i] = Key_Sta[i];
        }
    }
}

void KeyScan()
{
    static unsigned char keyout = 0;
    static unsigned char Key_Buff[4] = {0xFF,0xFF,0xFF,0xFF};

    switch(keyout)
    {
        case 0: Key_Buff[0] = Key_Buff[0] << 1 | KEY_IN_1; break;
        case 1: Key_Buff[1] = Key_Buff[1] << 1 | KEY_IN_2; break;
        case 2: Key_Buff[2] = Key_Buff[2] << 1 | KEY_IN_3; break;
        case 3: Key_Buff[3] = Key_Buff[3] << 1 | KEY_IN_4; break;
        default: break;
    }

	if((Key_Buff[keyout] & 0x0F) == 0x00)
	{
		Key_Sta[keyout] = 0;
	}
	else if((Key_Buff[keyout] & 0x0F) == 0x0F)
	{
		Key_Sta[keyout] = 1;
	}

    keyout++;
    keyout &= 0x03;
}
