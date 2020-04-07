#ifndef SFWS_RESOURCE_SETTINGS_HPP
#define SFWS_RESOURCE_SETTINGS_HPP

#include <string>

namespace SFWSUtil
{

struct ResourceSettings
{
public:
	std::string resizer;
	std::string maximise;
	std::string unmaximise;
	std::string minimise;
	std::string close;	
};

}

#endif // !SFWS_RESOURCE_SETTINGS_HPP
