#include "WindowDecorations.hpp"

WindowDecorations::WindowDecorations()
{
	// nothing
}

WindowDecorations::~WindowDecorations()
{
	delete closeMenu;
}

sf::RenderWindow& WindowDecorations::createWindow(sf::Vector2f size = { 310, 500 }, std::string title_ = "Source SDK")
{
	windowSize = size;
	useableWindowSize = { windowSize.x - (borderWidth * 2), windowSize.y - (borderWidth * 2) - titlebarHeight };

	window.create(sf::VideoMode(windowSize.x, windowSize.y), title.getString(), sf::Style::None);
	window.setVerticalSyncEnabled(true);

	closeMenu = new SFUI::Menu(window);

	SFUI::HorizontalBoxLayout* closehbox = closeMenu->addHorizontalBoxLayout();

	minimiseButtonTexture.loadFromFile("resources/interface/minimise.png");
	minimiseButton = new SFUI::SpriteButton(minimiseButtonTexture);
	closehbox->add(minimiseButton, DECO_CALLBACK::MINIMISED);

	maximiseButtonTexture.loadFromFile("resources/interface/maximise.png");
	maximiseButton = new SFUI::SpriteButton(maximiseButtonTexture);
	closehbox->add(maximiseButton, DECO_CALLBACK::MAXIMISED);

	closeButtonTexture.loadFromFile("resources/interface/close.png");
	closeButton = new SFUI::SpriteButton(closeButtonTexture);
	closehbox->add(closeButton, DECO_CALLBACK::CLOSED);

	closeMenu->setPosition(sf::Vector2f(windowSize.x - closeMenu->getSize().x - borderWidth, borderWidth - 2));

	titlebar.setFillColor(BORDER);
	top.setFillColor(BORDER);
	topUpper.setFillColor(WHITE_BORDER);
	topLower.setFillColor(BLACK_BORDER);
	left.setFillColor(BORDER);
	leftLeftBorder.setFillColor(WHITE_BORDER);
	leftRightBorder.setFillColor(BLACK_BORDER);
	right.setFillColor(BORDER);
	rightLeftBorder.setFillColor(WHITE_BORDER);
	rightRightBorder.setFillColor(BLACK_BORDER);
	bottom.setFillColor(BORDER);
	bottomUpperBorder.setFillColor(WHITE_BORDER);
	bottomLowerBorder.setFillColor(BLACK_BORDER);

	updateWindowDecorations();

	return window;
}

void WindowDecorations::HandleEvents(sf::Event& event)
{
	if (event.type == sf::Event::EventType::Resized)
	{
		sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
		window.setView(sf::View(visibleArea));

		updateWindowDecorations();

		closeMenu->setPosition(sf::Vector2f(windowSize.x - closeMenu->getSize().x - borderWidth, borderWidth - 2));
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			// TODO: don't drag if over closeMenu
			if (titlebar.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				grabbedWindow = true;

			if (top.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				resizingYTop = true;
				resizing = true;
			}
			if (left.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				resizingXLeft = true;
				resizing = true;
			}
			if (right.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				resizingXRight = true;
				resizing = true;
			}
			if (bottom.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				resizingYBottom = true;
				resizing = true;
			}

			grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
			dragOffsetX = sf::Mouse::getPosition().x;
			dragOffsetY = sf::Mouse::getPosition().y;

			lastWindowSize = window.getSize();
			lastWindowPosition = window.getPosition();
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			// FIXME: fix this horseshit
			// only run this here so it only triggers if the mouse is released
			if (!grabbedWindow)
			{
				int id = closeMenu->onEvent(event);
				switch (id)
				{
				case DECO_CALLBACK::CLOSED:
				{
					window.close();
					break;
				}
				};
			}

			grabbedWindow = false;
			resizingXLeft = false;
			resizingXRight = false;
			resizingYTop = false;
			resizingYBottom = false;
			resizing = false;
		}
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		// TODO: optimise this so it's not dog shit
		// TODO: check if mouse is in regular bounds first

		// FIXME: SFML cursor is invisible through discord screenshare.
		// perhaps this is due to the usage of CopyCursor rather than SetCursor in the SFML source.

		if (top.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			sf::Cursor cursor;

			if (left.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				cursor.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
			else if (right.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				cursor.loadFromSystem(sf::Cursor::SizeBottomLeftTopRight);
			else
				cursor.loadFromSystem(sf::Cursor::SizeVertical);

			window.setMouseCursor(cursor);
		}
		else if (left.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			sf::Cursor cursor;

			if (top.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				cursor.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
			else if (bottom.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				cursor.loadFromSystem(sf::Cursor::SizeBottomLeftTopRight);
			else
				cursor.loadFromSystem(sf::Cursor::SizeHorizontal);

			window.setMouseCursor(cursor);
		}
		else if (right.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			sf::Cursor cursor;

			if (bottom.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				cursor.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
			else if (top.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				cursor.loadFromSystem(sf::Cursor::SizeBottomLeftTopRight);
			else
				cursor.loadFromSystem(sf::Cursor::SizeHorizontal);

			window.setMouseCursor(cursor);
		}
		else if (bottom.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			sf::Cursor cursor;

			if (left.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				cursor.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
			else if (right.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
				cursor.loadFromSystem(sf::Cursor::SizeBottomLeftTopRight);
			else
				cursor.loadFromSystem(sf::Cursor::SizeVertical);

			window.setMouseCursor(cursor);
		}
		else
		{
			sf::Cursor cursor;
			if (cursor.loadFromSystem(sf::Cursor::Arrow))
				window.setMouseCursor(cursor);
		}

		if (resizing)
		{
			sf::Vector2u newWindowSize(lastWindowSize);
			sf::Vector2i newWindowPosition(lastWindowPosition);

			if (resizingXRight)
				newWindowSize.x = lastWindowSize.x + sf::Mouse::getPosition().x - dragOffsetX;

			if (resizingYBottom)
				newWindowSize.y = sf::Mouse::getPosition().y + lastWindowSize.y - dragOffsetY;

			if (resizingYTop)
			{
				newWindowSize.y = lastWindowSize.y - sf::Mouse::getPosition().y + dragOffsetY;
				newWindowPosition.y = lastWindowPosition.y - (window.getSize().y - lastWindowSize.y);
			}

			if (resizingXLeft)
			{
				newWindowSize.x = lastWindowSize.x - sf::Mouse::getPosition().x + dragOffsetX;
				newWindowPosition.x = lastWindowPosition.x - (window.getSize().x - lastWindowSize.x);
			}

			window.setSize(newWindowSize);
			windowSize = sf::Vector2f(window.getSize());

			window.setPosition(newWindowPosition);
		}
	}

	int id = closeMenu->onEvent(event);
	switch (id)
	{
	case DECO_CALLBACK::CLOSED:
		window.close();
		/*
		sf::FloatRect clsbtn(closeButton->getAbsolutePosition(), closeButton->getSize());
		if (clsbtn.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
		}
		else
		{
			// TODO: make this not suck
			closeButton->onStateChanged(SFUI::State::Default);
		}
		*/
		break;
	case DECO_CALLBACK::MAXIMISED:
	{
		if (!isMaximised)
		{
			windows::window::maximise(window.getSystemHandle());
			maximiseButtonTexture.loadFromFile("resources/interface/unmaximise.png");
		}
		else
		{
			windows::window::normal(window.getSystemHandle());
			maximiseButtonTexture.loadFromFile("resources/interface/maximise.png");
		}

		isMaximised = !isMaximised;
		break;
	}
	case DECO_CALLBACK::MINIMISED:
		windows::window::minimise(window.getSystemHandle());
		break;
	};

	if (grabbedWindow)
		window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
}

void WindowDecorations::Draw()
{
	window.draw(titlebar);
	window.draw(top);
	window.draw(title);
	window.draw(left);
	window.draw(right);

	window.draw(topLower);
	window.draw(topUpper);
	window.draw(rightLeftBorder);
	window.draw(leftRightBorder);

	window.draw(bottom);
	window.draw(leftLeftBorder);
	window.draw(rightRightBorder);

	window.draw(bottomUpperBorder);
	window.draw(bottomLowerBorder);

	window.draw(*closeMenu);
}

void WindowDecorations::updateWindowDecorations()
{
	title.setString("Source SDK");
	title.setFont(SFUI::Theme::getFont());
	title.setCharacterSize(16);
	title.setPosition(sf::Vector2f(borderWidth, (borderWidth / 2)));

	titlebar.setSize(sf::Vector2f(windowSize.x - borderWidth * 2, titlebarHeight));
	titlebar.setPosition(sf::Vector2f(borderWidth, borderWidth));

	top.setSize(sf::Vector2f(windowSize.x, borderWidth));

	topUpper.setSize(sf::Vector2f(top.getSize().x, 1));

	topLower.setSize(sf::Vector2f(windowSize.x - (borderWidth * 2), 1));
	topLower.setPosition(sf::Vector2f(borderWidth, titlebarHeight + borderWidth - 1));

	left.setSize(sf::Vector2f(borderWidth, windowSize.y));

	leftLeftBorder.setSize(sf::Vector2f(1, left.getSize().y));

	leftRightBorder.setSize(sf::Vector2f(1, left.getSize().y - BOTTOM - titlebarHeight - borderWidth + 1));
	leftRightBorder.setPosition(sf::Vector2f(borderWidth - 1, titlebarHeight + borderWidth - 1));

	right.setSize(sf::Vector2f(borderWidth, windowSize.y));
	right.setPosition(sf::Vector2f(windowSize.x - borderWidth, 0));

	rightLeftBorder.setSize(sf::Vector2f(1, right.getSize().y - BOTTOM - titlebarHeight - borderWidth + 1));
	rightLeftBorder.setPosition(sf::Vector2f(windowSize.x - borderWidth, titlebarHeight + borderWidth - 1));

	rightRightBorder.setSize(sf::Vector2f(1, right.getSize().y));
	rightRightBorder.setPosition(sf::Vector2f(windowSize.x - 1, 0));

	bottom.setSize(sf::Vector2f(windowSize.x + (borderWidth * 2), borderWidth));
	bottom.setPosition(sf::Vector2f(0, windowSize.y - borderWidth));

	bottomUpperBorder.setSize(sf::Vector2f(windowSize.x - (borderWidth * 2) + 2, 1));
	bottomUpperBorder.setPosition(sf::Vector2f(borderWidth - 1, windowSize.y - BOTTOM));

	bottomLowerBorder.setSize(sf::Vector2f(windowSize.x + (borderWidth * 2), 1));
	bottomLowerBorder.setPosition(sf::Vector2f(0, windowSize.y - 1));
}
