#include "Category3.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(Category3 value) {
    switch (value) {
        case Category3::NotExtendedHoursOrSoldOutOfSequence: return "Not Extended Hours Or Sold Out Of Sequence";
        case Category3::SoldLast: return "Sold Last";
        case Category3::ExtendedHoursTrade: return "Extended Hours Trade";
        case Category3::ExtendedHoursSold: return "Extended Hours Sold";
        case Category3::SoldOutOfSequence: return "Sold Out Of Sequence";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Category3 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
