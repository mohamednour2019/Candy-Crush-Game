#include "Menu.h"


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("CANDY.TTF"))
	{
		// handle error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color(205, 92, 92));
	menu[0].setCharacterSize(90);
	menu[0].setString("Play");
	menu[0].setPosition(670, 350);

	menu[1].setFont(font);
	menu[1].setCharacterSize(90);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Description");
	menu[1].setPosition(550, 550);

	menu[2].setFont(font);
	menu[2].setCharacterSize(90);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(670, 750);

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color(205, 92, 92));
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color(205, 92, 92));
	}
}