#pragma once
#include <SFML\Graphics.hpp>

#include"Character.h"

class Player : public Character 
{
private:

	const float StartX, StartY; //pozycja początkowa
	const float Gravity; //przyspieszenie grawitacyjne

	bool IsJumping; //czy gracz jest w trakcie skoku?
	float JumpSpeed; //prędkość poruszania do góry w skoku

public:

	void CheckInput(); //odczytaj wejścia z klawiatury
	void RunPhysics(); //obliczenia związane z grawitacją i kolizjami

	//referencja okna, referencja mapy, pozycja x, pozycja y, ścieżka do pliku z obrazkiem
	Player(LevelManager& manager, float posx, float posy, char* texpath);
	~Player();

	void OnCollisionWithEnemy(); //Zdarzenie kolizji z przeciwnikiem
	void OnGoalAchieved(); //Zdarzenie zebrania celu
	sf::Vector2f GetPosition(); //Pobierz pozycję punktu styku gracza z ziemią
};