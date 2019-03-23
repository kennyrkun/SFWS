#ifndef WINDOW_DECORATIONS_HPP
#define WINDOW_DECORATIONS_HPP

#include <SFUI/Menu.hpp>

#include <string>
#include <SFML/Graphics.hpp>

class WindowDecorations
{
public:
	WindowDecorations();
	~WindowDecorations();

	sf::RenderWindow& createWindow(sf::Vector2f size = { 310, 500 }, std::string title_ = "Source SDK");

	sf::Text title;
	sf::Vector2f windowSize;
	sf::Vector2f useableWindowSize;

	sf::Vector2i grabbedOffset;
	bool grabbedWindow = false;
	bool resizingXLeft = false;
	bool resizingXRight = false;
	bool resizingYTop = false;
	bool resizingYBottom = false;
	bool resizing = false;

	sf::Vector2u lastWindowSize;
	sf::Vector2u lastWindowSize2;
	sf::Vector2i lastWindowPosition;
	int dragOffsetY;
	int dragOffsetX;

	sf::RectangleShape titlebar;
	sf::RectangleShape top;
	sf::RectangleShape topUpper;
	sf::RectangleShape topLower;
	sf::RectangleShape left;
	sf::RectangleShape leftLeftBorder;
	sf::RectangleShape leftRightBorder;
	sf::RectangleShape right;
	sf::RectangleShape rightLeftBorder;
	sf::RectangleShape rightRightBorder;
	sf::RectangleShape bottom;
	sf::RectangleShape bottomUpperBorder;
	sf::RectangleShape bottomLowerBorder;

	SFUI::Menu* closeMenu;

	SFUI::SpriteButton* minimiseButton;
	SFUI::SpriteButton* maximiseButton;
	SFUI::SpriteButton* closeButton;

	sf::Color WHITE_BORDER = sf::Color(136, 145, 128);
	sf::Color BLACK_BORDER = sf::Color(40, 46, 34);

	sf::Color WINDOW_BACKGROUND = sf::Color(62, 70, 55);
	sf::Color BORDER = sf::Color(76, 88, 68);

	sf::Texture minimiseButtonTexture;
	sf::Texture maximiseButtonTexture;
	sf::Texture closeButtonTexture;

	bool isMaximised = false;

	void HandleEvents(sf::Event& event);
	void Draw();

	void updateWindowDecorations();

private:
	sf::RenderWindow window;

	enum CALLBACK
	{
		CLOSED,
		MINIMISED,
		MAXIMISED
	};
};

#endif // !WINDOW_DECORATIONS_HPP
