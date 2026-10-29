#include "CancelOnDisconnectType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(CancelOnDisconnectType value) {
    switch (value) {
        case CancelOnDisconnectType::DoNotCancelOnDisconnectOrTerminate: return "Do Not Cancel On Disconnect Or Terminate";
        case CancelOnDisconnectType::CancelOnDisconnectOnly: return "Cancel On Disconnect Only";
        case CancelOnDisconnectType::CancelOnTerminateOnly: return "Cancel On Terminate Only";
        case CancelOnDisconnectType::CancelOnDisconnectOrTerminate: return "Cancel On Disconnect Or Terminate";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CancelOnDisconnectType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
