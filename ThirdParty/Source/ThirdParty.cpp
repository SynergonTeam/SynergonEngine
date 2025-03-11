#include <Synergon/ThirdParty.hpp>
#include <iostream>
#include <format>

namespace Synergon {
    void ThirdPartyTempFunction() {
        std::cout << std::vformat("Hello from Synergon::ThirdPartyTempFunction() in {}\n", std::make_format_args(__FILE__));
    }
}  // namespace Synergon