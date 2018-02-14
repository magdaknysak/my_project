
#include "LevelManager.h"

Level::Level(LevelManager& manager, int resx, int resy, char* path):
	Manager(manager),
	MapRect(sf::Vector2f((float)resx, (float)resy))
{
	MapImage.loadFromFile(path);
	MapTex.loadFromImage(MapImage);
	MapRect.setTexture(&MapTex);
}
Level::~Level()
{
}
void Level::Draw()
{
	Manager.GetWindow().draw(MapRect);

	return;
}