#pragma once
#include "Gui_Elements.h"
class Gui_Buttons : public Gui_Elements
{
public:
	Gui_Buttons();
	~Gui_Buttons();
	void AddGuiButtons2(float posx, float posy, SDL_Rect* name = {}, const char* string = nullptr, int tab = -1, float scale = 0.5f);

public:
	SDL_Texture*		buttons;
	_TTF_Font*			font24;

};

