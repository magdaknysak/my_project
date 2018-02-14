#include <iostream>

#include "LevelManager.h"

LevelManager::LevelManager(int resx, int resy, char* windowname):
	Window(sf::VideoMode(resx, resy), windowname, sf::Style::Close | sf::Style::Resize),
	ResX(resx),
	ResY(resy),
	Level1(nullptr),
	Gracz(nullptr),
	Goal1(nullptr)
{
	//Zeruj tablicę
	for (int i = 0; i < MAX_ENEMIES; ++i)
		Enemy1[i] = nullptr;

	//Stwórz poziom
	Level1 = new Level(*this, resx, resy, "mapa.jpg");

	//Stwórz gracza
	Gracz = new Player(*this, 70.0f, 70.0f, "rd.png");

	//Stwórz przeciwników
	int num = 0;
	Enemy1[num++] = new Enemy(*this, 500.0f, 300.0f, "enemy.png", 300.0f, 0.3f, false);
	Enemy1[num++] = new Enemy(*this, 200.0f, 450.0f, "enemy.png", 500.0f, 0.4f, true);
	Enemy1[num++] = new Enemy(*this, 900.0f, 100.0f, "enemy.png", 200.0f, 0.15f, false);

	//stwórz cel dla gracza
	Goal1 = new Goal(*this, 70.0f, 698.0f, "goal.png");
}
LevelManager::~LevelManager()
{
	delete Gracz;
	delete Level1;

	for (int i = 0; i < MAX_ENEMIES; ++i)
		if (Enemy1[i]) { delete Enemy1[i]; Enemy1[i] = nullptr; }

	delete Goal1;
}
Level* LevelManager::GetCurrentLevel()
{
	return Level1;
}
void LevelManager::Update()
{
	//przechwyć zdarzenia dla okna
	sf::Event evnt;
	while (Window.pollEvent(evnt))
	{

		switch (evnt.type)
		{
		case sf::Event::Closed:
			Window.close();
			break;
		case sf::Event::Resized:
			std::cout << "new window width: " << evnt.size.width << " and height: " << evnt.size.height << std::endl;
			break;
		case sf::Event::TextEntered:
			if (evnt.text.unicode < 128)
				std::cout << (char)evnt.text.unicode;
		}
	}

	//Gracz
	Gracz->CheckInput(); //check input from keyboard
	Gracz->RunPhysics(); //calculate physics

	//Przeciwnik
	for (int i = 0; i < MAX_ENEMIES; ++i)
		if(Enemy1[i]) Enemy1[i]->Update();

	//cel dla gracza
	Goal1->Update();

	return;
}
void LevelManager::DrawCurrentLevel()
{
	Level1->Draw(); //narysuj aktualną mapę
	Gracz->Draw(); //narysuj gracza
	for (int i = 0; i < MAX_ENEMIES; ++i)
		if (Enemy1[i]) Enemy1[i]->Draw(); //narysuj przeciwnika

	Goal1->Draw(); //narysuj cel gracza

	return;
}
Player& LevelManager::GetPlayer()
{
	return *Gracz;
}