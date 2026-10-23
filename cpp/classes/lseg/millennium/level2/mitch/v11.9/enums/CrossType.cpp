#include "CrossType.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

std::string_view to_string(CrossType value) {
    switch (value) {
        case CrossType::InternalCross: return "Internal Cross";
        case CrossType::InternalBtf: return "Internal Btf";
        case CrossType::CommittedCross: return "Committed Cross";
        case CrossType::CommittedBtf: return "Committed Btf";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace lseg::millennium::level2::mitch::v11_9
