#include "MdOriginType.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(MdOriginType value) {
    switch (value) {
        case MdOriginType::Book: return "Book";
        case MdOriginType::OffBook: return "Off Book";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdOriginType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
