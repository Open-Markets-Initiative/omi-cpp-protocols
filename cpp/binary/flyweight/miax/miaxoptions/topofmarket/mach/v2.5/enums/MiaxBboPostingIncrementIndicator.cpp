#include "MiaxBboPostingIncrementIndicator.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(MiaxBboPostingIncrementIndicator value) {
    switch (value) {
        case MiaxBboPostingIncrementIndicator::Penny: return "Penny";
        case MiaxBboPostingIncrementIndicator::PennyOrNickel: return "Penny Or Nickel";
        case MiaxBboPostingIncrementIndicator::NickelOrDime: return "Nickel Or Dime";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MiaxBboPostingIncrementIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
