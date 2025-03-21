#pragma once

#include <string>
#include <vector>

namespace Synergon::Core {
	std::vector<char> ReadFile(std::string_view path);
}
