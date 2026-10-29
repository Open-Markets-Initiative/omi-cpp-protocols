#include "RegShoAction.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

std::string_view to_string(RegShoAction value) {
    switch (value) {
        case RegShoAction::NoPriceTest: return "No Price Test";
        case RegShoAction::RegShoInEffect: return "Reg Sho In Effect";
        case RegShoAction::RegShoRemains: return "Reg Sho Remains";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RegShoAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
