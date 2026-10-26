#include "MdUpdateAction.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

std::string_view to_string(MdUpdateAction value) {
    switch (value) {
        case MdUpdateAction::New: return "New";
        case MdUpdateAction::Change: return "Change";
        case MdUpdateAction::Delete: return "Delete";
        case MdUpdateAction::DeleteThru: return "Delete Thru";
        case MdUpdateAction::DeleteFrom: return "Delete From";
        case MdUpdateAction::Overlay: return "Overlay";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdUpdateAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
