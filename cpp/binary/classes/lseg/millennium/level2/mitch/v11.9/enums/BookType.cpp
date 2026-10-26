#include "BookType.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

std::string_view to_string(BookType value) {
    switch (value) {
        case BookType::OnBook: return "On Book";
        case BookType::OffBook: return "Off Book";
        case BookType::PrivateRfq: return "Private Rfq";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BookType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace lseg::millennium::level2::mitch::v11_9
