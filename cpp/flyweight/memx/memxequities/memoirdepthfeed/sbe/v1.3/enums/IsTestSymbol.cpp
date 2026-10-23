#include "IsTestSymbol.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

std::string_view to_string(IsTestSymbol value) {
    switch (value) {
        case IsTestSymbol::False: return "False";
        case IsTestSymbol::True: return "True";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IsTestSymbol value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
