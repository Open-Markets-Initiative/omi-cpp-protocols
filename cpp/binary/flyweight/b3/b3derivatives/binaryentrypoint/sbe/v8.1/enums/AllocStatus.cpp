#include "AllocStatus.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(AllocStatus value) {
    switch (value) {
        case AllocStatus::Accepted: return "Accepted";
        case AllocStatus::RejectedByIntermediary: return "Rejected By Intermediary";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AllocStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
