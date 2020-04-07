#ifdef _WIN32
#ifndef WIN32_WRAPPER_HPP
#define WIN32_WRAPPER_HPP

#include <SFML/Window/WindowHandle.hpp>

namespace windows
{
	namespace window
	{
//		void maximise(const sf::WindowHandle& handle);
		void maximise(sf::WindowHandle handle);

		void normal(sf::WindowHandle handle);

		void minimise(sf::WindowHandle handle);
	}
}

#endif // !WIN32_WRAPPER_HPP
#endif
