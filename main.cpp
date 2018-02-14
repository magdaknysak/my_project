#include <SFML\Graphics.hpp>
#include <iostream>
#include "LevelManager.h"
#include "Level.h"
#include "Character.h" 
#include "Player.h"
#include "Enemy.h"

int main()
{
	
	//stwórz obiekt managera plansz
	LevelManager Manager(1024, 768, "My awesome game"); //manager level ze wszystkimi obsługiwanymi poziomami w środku + manager okna programu

	//rozpocznij pętlę główną
	while (Manager.GetWindow().isOpen()) //wykonuj pętlę aż do zamknięcia okna programu
	{
		Manager.Update(); //zaktualizuj stan okna obsługiwanego przez manager

		Manager.GetWindow().clear(); //wyczyść ekran
		Manager.DrawCurrentLevel(); //narysuj aktualną mapę
		Manager.GetWindow().display(); //wyświetl to co narysowano
	}

	return 0;
}
