#pragma once

#include <MorrisGame/IMorrisLogger.h>
#include <iostream>

class SDLMorrisLogger : public Morris::IMorrisLogger
{
	public:
		void OnLog(const std::string& message) override
		{
			std::cout << message << std::endl;
		}
};