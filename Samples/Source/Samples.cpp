#include <Synergon/Samples.hpp>
#include <iostream>
#include <format>

namespace Synergon {
	void SamplesTempFunction() {
		std::cout << std::vformat("Hello from Synergon::SamplesTempFunction() in {}\n", std::make_format_args(__FILE__));
	}
}  // namespace Synergon