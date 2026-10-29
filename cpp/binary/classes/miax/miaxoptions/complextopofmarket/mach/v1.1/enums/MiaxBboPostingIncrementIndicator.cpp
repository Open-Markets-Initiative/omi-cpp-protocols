#include "MiaxBboPostingIncrementIndicator.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

std::string_view to_string(MiaxBboPostingIncrementIndicator value) {
    switch (value) {
        case MiaxBboPostingIncrementIndicator::Penny: return "Penny";
        case MiaxBboPostingIncrementIndicator::Nickel: return "Nickel";
        case MiaxBboPostingIncrementIndicator::Dime: return "Dime";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MiaxBboPostingIncrementIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
