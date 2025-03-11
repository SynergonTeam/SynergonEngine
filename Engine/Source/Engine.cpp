#include "Synergon/Engine.hpp"

#include <format>
#include <iostream>

namespace Synergon
{
	void EngineTempFunction()
	{
		std::cout << std::vformat("Hello from Synergon::SamplesTempFunction() in {}\n", std::make_format_args(__FILE__));
	}
}
