#include "ShortSaleRestriction.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

std::string_view to_string(ShortSaleRestriction value) {
    switch (value) {
        case ShortSaleRestriction::False: return "False";
        case ShortSaleRestriction::True: return "True";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ShortSaleRestriction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
