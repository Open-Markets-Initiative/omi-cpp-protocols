#include "TestModeFlag.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(TestModeFlag value) {
    switch (value) {
        case TestModeFlag::Production: return "Production";
        case TestModeFlag::Test: return "Test";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TestModeFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
