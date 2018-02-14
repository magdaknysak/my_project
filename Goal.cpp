#include <SFML\Graphics.hpp>
#include "Goal.h"
#include "LevelManager.h"

Goal::Goal(LevelManager& manager, float posx, float posy, char* texpath):
	Character(manager, posx, posy, texpath, 88.0f)
{
}
Goal::~Goal()
{
}
void Goal::Update()
{
	//Sprawdz czy nie zaszła kolizja z graczem
	auto PlayerPos = Manager.GetPlayer().GetPosition();
	auto ThisPos = TexRect.getPosition();
	if (PlayerPos.x > ThisPos.x - 32.0f && PlayerPos.x < ThisPos.x + 32.0f)
		if (PlayerPos.y > ThisPos.y - 0.0f && PlayerPos.y < ThisPos.y + 64.0f)
			Manager.GetPlayer().OnGoalAchieved();
	return;
}