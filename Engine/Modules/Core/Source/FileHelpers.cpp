#include "Synergon/Core/FileHelpers.hpp"

#include <fstream>
#include <stdexcept>

namespace Synergon::Core {
	std::vector<char> ReadFile(std::string_view path) {
		std::ifstream file(path.data(), std::ios::binary | std::ios::ate);
		if (!file) {
			throw std::runtime_error("Failed to open file: " + std::string(path));
		}
		const std::streamsize fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		// Read into a buffer
		std::vector<char> buffer(fileSize);
		if (!file.read(buffer.data(), fileSize)) {
			throw std::runtime_error("Failed to read file: " + std::string(path));
		}
		return buffer;
	}
}  // namespace Synergon::Core
