#include <Synergon/Engine.hpp>
#include <iostream>
#include <format>

namespace Synergon {
    void EngineTempFunction() {
        std::cout << std::vformat("Hello from Synergon::EngineTempFunction() in {}\n", std::make_format_args(__FILE__));
    }
}  // namespace Synergon
