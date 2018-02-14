#include "LevelManager.h"
#include "Character.h"

Character::Character(LevelManager& manager, float posx, float posy, char* texpath, float size):
	Manager(manager),
	PosX(posx),
	PosY(posy),
	TexRect(sf::Vector2f(size, size)) //wymiary tekstury postaci
{
	//Wczytaj obrazek z pliku i stwórz teksturê do wyświetlenia
	TexRect.setPosition(PosX, PosY);
	Texture.loadFromFile(texpath);
	TexRect.setTexture(&Texture);

	TexRect.setOrigin(size / 2.0f, size / 2.0f); //ustaw środek transformacji na środek obrazka
}
Character::~Character()
{
}
void Character::Draw()
{
	Manager.GetWindow().draw(TexRect);
	return;
}
