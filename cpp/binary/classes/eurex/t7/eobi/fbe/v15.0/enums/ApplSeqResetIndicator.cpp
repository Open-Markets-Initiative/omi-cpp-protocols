#include "ApplSeqResetIndicator.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(ApplSeqResetIndicator value) {
    switch (value) {
        case ApplSeqResetIndicator::NoReset: return "No Reset";
        case ApplSeqResetIndicator::Reset: return "Reset";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ApplSeqResetIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
