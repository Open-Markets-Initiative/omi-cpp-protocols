#include "ExecFlag.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

std::string_view to_string(ExecFlag value) {
    switch (value) {
        case ExecFlag::None: return "None";
        case ExecFlag::Aon: return "Aon";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExecFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
