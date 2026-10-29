#include "CallOrPut.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

std::string_view to_string(CallOrPut value) {
    switch (value) {
        case CallOrPut::Call: return "Call";
        case CallOrPut::Put: return "Put";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CallOrPut value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
