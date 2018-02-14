#include "LevelManager.h"
#include "Enemy.h"

Enemy::Enemy(LevelManager& manager, float posx, float posy, char* texpath, float walkdist, float walkspeed, bool walkdir):
	Character(manager, posx, posy, texpath, 80.0f),
	WalkDistance(walkdist),
	WalkSpeed(walkspeed),
	WalkDir(walkdir),
	DistanceMoved(0.0f)
{
}
Enemy::~Enemy()
{
}
void Enemy::Update()
{
	//Zrzuc przeciwnika na ziemie
	auto pos = TexRect.getPosition() + sf::Vector2f(0.0f, 40.0f);
	auto col = Manager.GetCurrentLevel()->GetImage().getPixel((unsigned int)pos.x, (unsigned int)pos.y);
	if (col.r < 10) TexRect.move(0.0f, 0.3f);

	//Poruszanie
	if (DistanceMoved < WalkDistance) //poruszaj sie tylko w podanym dystansie
	{
		//ustal kierunek ruchu
		if (WalkDir) TexRect.move(WalkSpeed, 0.0f);
		else TexRect.move(-WalkSpeed, 0.0f); 

		DistanceMoved += WalkSpeed;
	}
	else
	{
		//Po dojściu do koñca zmieñ kierunek ruchu
		WalkDir = !WalkDir;
		DistanceMoved = 0.0f;
	}

	//Sprawdz czy nie zaszła kolizja z graczem
	auto PlayerPos = Manager.GetPlayer().GetPosition();
	auto ThisPos = TexRect.getPosition();
	if (PlayerPos.x > ThisPos.x - 32.0f && PlayerPos.x < ThisPos.x + 32.0f)
		if (PlayerPos.y > ThisPos.y - 0.0f && PlayerPos.y < ThisPos.y + 64.0f)
			Manager.GetPlayer().OnCollisionWithEnemy();

	return;
}