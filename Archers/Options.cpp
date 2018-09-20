#include "stdafx.h"
#include "Options.h"

Options::Options(sf::RenderWindow& myWindow)
{
	std::cout << "OPT const" << std::endl;
	selectedItemIndex = 0;
	dificultyLevelIndex = 1;
	if (!myFont.loadFromFile("snap.ttf"))
	{
		std::cout << "Font error" << std::endl;
	}
	for (int i = 0; i < NUMBER_OF_OPTIONS_ITEMS; i++)
	{
		optionsTexts[i].setFont(myFont);
		optionsTexts[i].setPosition(sf::Vector2f(myWindow.getSize().x*0.2, myWindow.getSize().y / (NUMBER_OF_OPTIONS_ITEMS + 1)*(i + 1)));
		optionsTexts[i].setCharacterSize(50);
		optionsTexts[i].setOutlineColor(sf::Color::Black);
		optionsTexts[i].setOutlineThickness(5);
	}

	optionsTexts[0].setFillColor(sf::Color::Red);
	optionsTexts[0].setString("Muzyka");

	optionsTexts[1].setFillColor(sf::Color::White);
	optionsTexts[1].setString("Wiatr");

	optionsTexts[2].setFillColor(sf::Color::White);
	optionsTexts[2].setString("Poziom trudnosci");

	optionsTexts[3].setFillColor(sf::Color::White);
	optionsTexts[3].setString("Powrot");

	optionsTexts[4].setFillColor(sf::Color::White);
	optionsTexts[4].setString("ON");
	optionsTexts[4].setPosition(sf::Vector2f(myWindow.getSize().x*0.6, myWindow.getSize().y / (NUMBER_OF_OPTIONS_ITEMS + 1)*(0 + 1)));
	

	optionsTexts[5].setFillColor(sf::Color::White);
	optionsTexts[5].setString("ON");
	optionsTexts[5].setPosition(sf::Vector2f(myWindow.getSize().x*0.6, myWindow.getSize().y / (NUMBER_OF_OPTIONS_ITEMS + 1)*(1 + 1)));
	//nowe znaczniki 3 stopniowego poziomu trudnosci
	optionsTexts[6].setFillColor(sf::Color::White);
	optionsTexts[6].setString("1");
	optionsTexts[6].setCharacterSize(50);
	optionsTexts[6].setPosition(sf::Vector2f(myWindow.getSize().x*0.6, myWindow.getSize().y / (NUMBER_OF_OPTIONS_ITEMS + 1)*(2 + 1)));

	optionsTexts[7].setFillColor(sf::Color::Red);
	optionsTexts[7].setString("2");
	optionsTexts[7].setCharacterSize(65);
	optionsTexts[7].setPosition(sf::Vector2f(myWindow.getSize().x*0.64, myWindow.getSize().y / (NUMBER_OF_OPTIONS_ITEMS + 1)*(2 + 1)));

	optionsTexts[8].setFillColor(sf::Color::White);
	optionsTexts[8].setString("3");
	optionsTexts[8].setCharacterSize(80);
	optionsTexts[8].setPosition(sf::Vector2f(myWindow.getSize().x*0.69, myWindow.getSize().y / (NUMBER_OF_OPTIONS_ITEMS + 1)*(2 + 1)));
}

void Options::Display(sf::RenderWindow& myWindow)
{
	for (int i = 0; i < NUMBER_OF_OPTIONS_ITEMS; i++)
	{
		myWindow.draw(optionsTexts[i]);
	}
}

void Options::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		optionsTexts[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		optionsTexts[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Options::MoveDown()
{
	if (selectedItemIndex + 1 < NUMBER_OF_OPTIONS_ITEMS - 5)
	{
		optionsTexts[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		optionsTexts[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Options::Listening(sf::Event event, sf::RenderWindow& myWindow, Menu*& ptrPresent, Menu*&ptrAlternative, GameMode*&ptrGameMode, DataOfOptions & doo, Camera & myCamera)
{
	Menu* wskTemporary; //wskaznik pomocniczy do zamiany wartosci Present i Alter ze soba
	switch (event.type)
	{
	case sf::Event::Closed:
		myWindow.close();
		break;
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			this->MoveUp();
			break;
		case sf::Keyboard::Down:
			this->MoveDown();
			break;
		case sf::Keyboard::Return:
			switch (GetPressedItem())
			{
			case 0:
				std::cout << "Muzyka" << std::endl;
				if (optionsTexts[4].getString() == "ON") {
					optionsTexts[4].setString("OFF");
					doo.changeMusic();
				}
				else {
					optionsTexts[4].setString("ON");
					doo.changeMusic();
				}
				break;
			case 1:
			{
				std::cout << "Wiatr" << std::endl;
				if (optionsTexts[5].getString() == "ON") {
					optionsTexts[5].setString("OFF");
					doo.changeWind();
				}
				else {
					optionsTexts[5].setString("ON");
					doo.changeWind();
				}
				break;
			}
			case 2:
			{
				std::cout << "Poziom trudnosci" << std::endl;
				if (dificultyLevelIndex < 2) {
					optionsTexts[6 + dificultyLevelIndex].setFillColor(sf::Color::White);
					dificultyLevelIndex++;
					optionsTexts[6 + dificultyLevelIndex].setFillColor(sf::Color::Red);
				}
				else {
					optionsTexts[6 + dificultyLevelIndex].setFillColor(sf::Color::White);
					dificultyLevelIndex = 0;
					optionsTexts[6 + dificultyLevelIndex].setFillColor(sf::Color::Red);
				}
				if (dificultyLevelIndex == 0)
					doo.changeDificultyLevel(1.1, 0.9);
				if (dificultyLevelIndex == 1)
					doo.changeDificultyLevel(1.5, 0.5);
				if (dificultyLevelIndex == 2)
					doo.changeDificultyLevel(2.0, 0.4);
				break;
			}//dodane graficzne wyswietlenie poziomu trudnosci
			
			case 3:
			{
				std::cout << "Powrot" << std::endl;
				wskTemporary = ptrPresent;//zamiana wartosci wskaznikow, return juz nie jest potrzebny
				ptrPresent = ptrAlternative;
				ptrAlternative = wskTemporary;
				break;
			}
			}
			break;
		}
		break;
	default:
		break;
	}
}
