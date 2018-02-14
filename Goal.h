#pragma once

#include "Character.h"

//Cel do zdobycia przez gracza w celu zakoñczenia poziomu
class Goal : public Character
{
private:

public:

	Goal(LevelManager& manager, float posx, float posy, char* texpath);
	~Goal();

	void Update(); //aktualizacja co klatkê
};