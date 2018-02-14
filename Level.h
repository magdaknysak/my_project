#pragma once

#include <SFML\Graphics.hpp>

class Level
{
private:
	
	class LevelManager& Manager; //referencja managera plansz

	sf::Image MapImage; //obraz mapy (do czytania pojedynczych pikseli)
	sf::Texture MapTex; //tekstura mapy
	sf::RectangleShape MapRect; //prostokąt mapy

public:

	inline sf::Image& GetImage() { return MapImage; } //pobierz obrazek (do czytania pojedynczych pikseli)

	//rysuj mapę
	void Draw();

	//rozdzielczość poziomu, ścieżka do obrazka poziomu
	Level(LevelManager& manager, int resx, int resy, char* path);
	~Level();

};