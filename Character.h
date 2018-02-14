#pragma once

class Character
{
protected:

	class LevelManager& Manager; //referencja managera plansz
	sf::RectangleShape TexRect; //prtostokąt mieszczący postac

	sf::Texture Texture; //tekstura postaci

	float PosX, PosY; //pozycja
public:
	Character(LevelManager& manager, float posx, float posy, char* texpath, float size = 128.0f);
	~Character();

	void Draw(); //narysuj teksturę
};