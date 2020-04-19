#include "Screen.h"
int Screen::Width = 512;
int Screen::Height = 512;

Int2 Screen::Center()
{
	return Int2(Width / 2, Height / 2);
}
