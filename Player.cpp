#include "LevelManager.h"
#include "Player.h"
#include <iostream>
#include <fstream>

Player::Player(LevelManager& manager, float posx, float posy, char* texpath):
	Character(manager, posx, posy, texpath),
	Gravity(0.3f),
	IsJumping(false),
	JumpSpeed(0.0f),
	StartX(posx),
	StartY(posy)
{
}
Player::~Player()
{
}
void Player::CheckInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		TexRect.move(-0.5f, 0.0f);
		TexRect.setScale(-1.0f, 1.0f); //obróć gracza w prawo
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		TexRect.move(0.5f, 0.0f);
		TexRect.setScale(1.0f, 1.0f); //obróć gracza w lewo
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		if (!IsJumping) //jeśli gracz nie jest w trakcie skoku, to może podskoczyć
		{
			IsJumping = true;
			JumpSpeed = 2.0f;
		}
	}


	return;
}
void Player::RunPhysics()
{
	//pobierz pozycję gracza i kolor piksela pod spodem, korekta z ustawionym originem (setOrigin)
	auto pos = TexRect.getPosition() + sf::Vector2f(0.0f, 64.0f);
	auto col = Manager.GetCurrentLevel()->GetImage().getPixel((unsigned int)pos.x, (unsigned int)pos.y);

	if (!IsJumping)
	{
		//kolor czarny - nic nie ma i gracz spada przechodząc do trybu skoku
		//inny kolor - gracz jest wypchnięty i ląduje na powierzchni
		if (col.r < 10)
		{
			IsJumping = true;
			JumpSpeed = 0.0f;
		}
		else TexRect.move(0.0f, -Gravity * 2.0f); //prędkość zasysania do góry, jeśli gracz znalazł się w ziemi
	}
	else
	{
		//obsługa skoku
		TexRect.move(0.0f, -JumpSpeed); //przesuwaj do góry w skoku
		JumpSpeed -= 0.015f; //zmniejszaj prędkość w skoku

		if (JumpSpeed < -1.0f) JumpSpeed = -1.0f; //ograniczenie prędkości opadania

		//Czy gracz już na ziemi
		if (col.r >= 10)
		{
			TexRect.move(0.0f, -Gravity * 2.0f); //prędkość zasysania do góry, jeśli gracz znalazł się w ziemi
			IsJumping = false;
		}
	}

	try //sprawdź czy wystąpił wyjątek
	{
		auto PlayerPos = TexRect.getPosition() + sf::Vector2f(0.0f, 64.0f);

		//Sprawdź czy gracz wyszedł poza mapę
		if (PlayerPos.x < 0.0f) throw 1;
		if (PlayerPos.x > 1024.0f) throw 2;
		if (PlayerPos.y > 768.0f) throw 3;
		if (PlayerPos.y < 0.0f) throw 4;
	}
	catch (int e) //przechwyć numer błędu
	{
		auto PlayerPos = TexRect.getPosition();

		//jeśli gracz jest poza mapą
		switch (e)
		{
		case 1:
			std::cout << "Gracz poza mapa! Pozycja x mniejsza od 0!" << std::endl;
			TexRect.setPosition(50.0f, PlayerPos.y);
			break;
		case 2:
			std::cout << "Gracz poza mapa! Pozycja x wieksza od 1024!" << std::endl;
			TexRect.setPosition(960.0f, PlayerPos.y);
			break;
		case 3:
			std::cout << "Gracz poza mapa! Pozycja y wieksza od 768!" << std::endl;
			TexRect.setPosition(PlayerPos.x, 690.0f);
			break;
		case 4:
			std::cout << "Gracz poza mapa! Pozycja y mniejsza od 0!" << std::endl;
			TexRect.setPosition(PlayerPos.x, 50.0f);
			break;
		default:
			std::cout << "Nieznany kod bledu!" << std::endl;
			break;
		}
	}
	catch (...) //jeśli wystąpił nieznany wyjątek
	{
		std::cout << "Nieznany wyjatek!" << std::endl;
	}
	
}
void Player::OnCollisionWithEnemy()
{
	TexRect.setPosition(StartX, StartY); //zresetuj pozycję
	return;
}
void Player::OnGoalAchieved()
{
	//zwycięstwo
	TexRect.setPosition(StartX, StartY);
	std::cout << std::endl << std::endl << "*** Uratowales Fluttershy! Wygrales! ***" << std::endl << std::endl;

	//Odczytaj i wyświetl liczbę punktów
	std::fstream File("points.bin", std::ios::binary | std::ios::in);

	try
	{
		if (!File.is_open()) throw 1;
	}
	catch(int e)
	{
		switch (e) //jeśli plik z punktami nie istnieje
		{
		case 1:
			//stwórz taki plik i zapisz jeden punkt
			std::cout << "Brak pliku z punktami! Tworzenie nowego..." << std::endl;
			std::fstream File("points.bin", std::ios::binary | std::ios::out);

			int p = 1;
			File.write((const char*)&p, sizeof(int)); //zapisz jeden punkt do pliku
			std::cout << "Masz 1 punkt!" << std::endl;

			File.close();
			return;
			break;
		}
	}

	//To się wykona tylko jeśli plik z punktami istnieje
	int p = 0;
	File.read((char*)&p, sizeof(int)); //wczytaj punkty z pliku

	++p; //dodaj punkt
	std::cout << "Punkty gracza: " << p << std::endl;

	File.close();

	//zapisz nową wartość punktów
	File.open("points.bin", std::ios::binary | std::ios::trunc | std::ios::out); //otwórz plik do zapisu i nadpisz dane
	File.write((const char*)&p, sizeof(int));
	File.close();

	return;
}
sf::Vector2f Player::GetPosition()
{
	return TexRect.getPosition() + sf::Vector2f(0.0f, 64.0f);
}