#pragma once
#include <SFML\Graphics.hpp>

#include "Enemy.h"
#include "Player.h"
#include "Level.h"
#include "Goal.h"

#define MAX_ENEMIES 8

class LevelManager
{
private: 

	int ResX, ResY; //rozdzielczość okna

	sf::RenderWindow Window; //główne okno programu

	Level* Level1; //mapa poziomu 1
	Player* Gracz; //obiekt gracza
	Enemy* Enemy1[MAX_ENEMIES]; //przeciwnik na planszy
	Goal* Goal1; //cel do przechwycenia przez gracza do wygrania planszy

public:

	inline sf::RenderWindow& GetWindow() { return Window; }

	//Pobierz wskaźnik na aktualny poziom
	Level* GetCurrentLevel();

	//aktualizuj stan managera
	void Update();

	//rysuj aktualny poziom
	void DrawCurrentLevel();

	//rozdzielczość okna x, rozdz. y, nazwa okna
	LevelManager(int resx, int resy, char* windowname);
	~LevelManager();

	Player& GetPlayer(); //Pobierz referencję gracza (dla przeciwników do sprawdzania kolizji)
};