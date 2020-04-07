#include "TitleBarButtons.hpp"

#include "SFWS.hpp"

#include <SFUI/SFUI.hpp>

TitleBarButtons::TitleBarButtons(SFWS* interface_)
{
	interface = interface_;
	SFWSUtil::ResourceSettings settings;
	build();
}

TitleBarButtons::~TitleBarButtons()
{
	delete closeMenu;
}

SFWS* TitleBarButtons::bindToInterface(SFWS* interface_, SFWSUtil::ResourceSettings settings_)
{
	std::cout << "initialise buttons" << std::endl;

	interface = interface_;
	settings = settings_;
	std::cout << "buiidl bbutton" << std::endl;
	build();

	std::cout << "initialised buttons" << std::endl;

	return interface;
}

void TitleBarButtons::build()
{
	std::cout << "building" << std::endl;

	closeMenu = new SFUI::Menu(*interface->getWindow());

	SFUI::HorizontalBoxLayout* closehbox = closeMenu->addHorizontalBoxLayout();

	minimiseButtonTexture.loadFromFile(settings.minimise);
	minimiseButton = new SFUI::SpriteButton(minimiseButtonTexture);
	closehbox->add(minimiseButton, Callbacks::Minimised);

	/*
	// does this application really need to be maximised?
	maximiseButtonTexture.loadFromFile(settings.maximise);
	maximiseButton = new SFUI::SpriteButton(maximiseButtonTexture);
	closehbox->add(maximiseButton, Callbacks::Maximised);
	*/

	closeButtonTexture.loadFromFile(settings.close);
	closeButton = new SFUI::SpriteButton(closeButtonTexture);
	closehbox->add(closeButton, Callbacks::Closed);

	closeMenu->setPosition(sf::Vector2f(interface->windowSize.x - closeMenu->getSize().x - interface->sizes.right, interface->sizes.top - 2.0f));
	menuBounds = { closeMenu->getAbsolutePosition(), closeMenu->getSize() };
}

void TitleBarButtons::onEvent(const sf::Event& event)
{
	int id = closeMenu->onEvent(event);

	switch (id)
	{
	case Callbacks::Closed:
		interface->getWindow()->close();
		break;
	case Callbacks::Maximised:
	{
#ifdef _WIN32
		if (interface->isMaximised)
		{
			windows::window::normal(interface->getWindow()->getSystemHandle());
			maximiseButtonTexture.loadFromFile(settings.maximise);
		}
		else
		{
			windows::window::maximise(interface->getWindow()->getSystemHandle());
			maximiseButtonTexture.loadFromFile(settings.unmaximise);
		}

		interface->isMaximised = !interface->isMaximised;
#endif // _WIN32
		break;
	}
	case Callbacks::Minimised:
	{
#ifdef _WIN32
		windows::window::minimise(interface->getWindow()->getSystemHandle());
		interface->isMaximised = false;
		break;
#endif // _WIN32
	}
	};
}

void TitleBarButtons::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*closeMenu, states);
}
