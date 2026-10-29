#include "ExtendedHoursOrSequenceType.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(ExtendedHoursOrSequenceType value) {
    switch (value) {
        case ExtendedHoursOrSequenceType::NotExtendedHoursOrSoldOutOfSequence: return "Not Extended Hours Or Sold Out Of Sequence";
        case ExtendedHoursOrSequenceType::SoldLast: return "Sold Last";
        case ExtendedHoursOrSequenceType::ExtendedHoursTrade: return "Extended Hours Trade";
        case ExtendedHoursOrSequenceType::ExtendedHoursSold: return "Extended Hours Sold";
        case ExtendedHoursOrSequenceType::SoldOutOfSequence: return "Sold Out Of Sequence";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExtendedHoursOrSequenceType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
