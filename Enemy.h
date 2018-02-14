#pragma once
#include"Character.h"


class Enemy : public Character
{
private:

	float WalkDistance; //Odległość na jaką porusza siê przeciwnik
	float WalkSpeed; //szybkość poruszania
	bool WalkDir; //kierunek ruchu
	float DistanceMoved; //dystans pokonany (do obliczenia punktu zawrócenia)

public:
	Enemy(LevelManager& manager, float posx, float posy, char* texpath, float walkdist, float walkspeed, bool walkdir);
	~Enemy();

	void Update(); //aktualizacja stanu, do wywołania co klatke
};