#ifndef SYNERGON_CORE_FILEHELPERS_H
#define SYNERGON_CORE_FILEHELPERS_H

#include <string>
#include <vector>

namespace Synergon::Core {
	std::vector<char> ReadFile(std::string_view path);
}

#endif  // SYNERGON_CORE_FILEHELPERS_H
