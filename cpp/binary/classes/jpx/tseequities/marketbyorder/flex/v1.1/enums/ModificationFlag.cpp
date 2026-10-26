#include "ModificationFlag.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(ModificationFlag value) {
    switch (value) {
        case ModificationFlag::CancelOrderOrModificationOrderThatChangesTimePriority: return "Cancel Order Or Modification Order That Changes Time Priority";
        case ModificationFlag::ModificationOrderThatDoesNotChangeTimePriority: return "Modification Order That Does Not Change Time Priority";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ModificationFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
