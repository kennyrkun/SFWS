#include <SFWS/SFWS.hpp>

#include <SFUI/Theme.hpp>

#include <SFML/Graphics.hpp>

int main()
{
//	SFUI::Theme::loadFont(GBL::DIR::fonts + "tahoma.ttf");
//	SFUI::Theme::loadTexture(GBL::DIR::textures + "interface/window/vgui.png");
	SFUI::Theme::textCharacterSize = 11;
	SFUI::Theme::click.textColor = sf::Color::White;
	SFUI::Theme::click.textColorHover = sf::Color::White;
	SFUI::Theme::click.textColorFocus = sf::Color::White;
	SFUI::Theme::input.textColor = sf::Color::White;
	SFUI::Theme::input.textColorHover = sf::Color::White;
	SFUI::Theme::input.textColorFocus = sf::Color::White;
	SFUI::Theme::label.textColor = sf::Color::White;
	SFUI::Theme::label.textColorHover = sf::Color::White;
	SFUI::Theme::label.textColorFocus = sf::Color::White;
	SFUI::Theme::PADDING = 2.f;

	SFWSUtil::ResourceSettings settings;
	settings.minimise = "./resources/minimise.png";

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFWS-Test", sf::Style::None);

	SFWS windowSystem;
	windowSystem.bindToWindow(&window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			windowSystem.HandleEvents(event);

		window.clear();
		windowSystem.Draw();
		window.display();
	}

	return EXIT_SUCCESS;
}
