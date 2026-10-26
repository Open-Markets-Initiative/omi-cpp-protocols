#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Market-data Refresh request/response discriminator carried over the SesM unsequenced channel
// (Request Type R, Response Type r, End of Refresh E)
enum class UnsequencedMessageType : char {
    RefreshRequestMessage = 'R',           // Refresh Request Message
    RefreshResponseMessage = 'r',          // Refresh Response Message
    EndOfRefreshNotificationMessage = 'E', // End Of Refresh Notification Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(UnsequencedMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, UnsequencedMessageType value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
