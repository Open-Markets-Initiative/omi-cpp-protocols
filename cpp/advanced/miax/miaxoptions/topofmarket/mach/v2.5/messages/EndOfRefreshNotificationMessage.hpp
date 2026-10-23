#pragma once

#include <cstddef>
#include "../structs/SesmPacketHeader.hpp"
#include "../types/RefreshMessageType.hpp"
#include "../types/UnsequencedMessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

// End Of Refresh Notification Message
struct end_of_refresh_notification_message {

    struct fields_type {
        mach_topofmarket::refresh_message_type refresh_message_type;
    };

    mach_topofmarket::sesm_packet_header header = {std::uint16_t(sizeof(mach_topofmarket::sesm_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::unsequenced_message_type) - 2), sesm_packet_type::enum_type::unsequenced_data_packet};
    mach_topofmarket::unsequenced_message_type unsequenced_message_type = mach_topofmarket::unsequenced_message_type::enum_type::end_of_refresh_notification_message;

    fields_type fields;

    // parse method
    static end_of_refresh_notification_message* parse(std::byte* buffer) {
        return reinterpret_cast<end_of_refresh_notification_message*>(buffer);
    }

    // parse method const
    static const end_of_refresh_notification_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const end_of_refresh_notification_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(end_of_refresh_notification_message::fields_type, refresh_message_type) == 0, "unexpected offset of end_of_refresh_notification_message::fields_type::refresh_message_type");
static_assert(sizeof(end_of_refresh_notification_message::fields_type) == 1, "unexpected sizeof end_of_refresh_notification_message::fields_type");
static_assert(sizeof(end_of_refresh_notification_message) == sizeof(mach_topofmarket::sesm_packet_header) + sizeof(mach_topofmarket::unsequenced_message_type) + 1, "unexpected sizeof end_of_refresh_notification_message");

#pragma pack(pop)
}
