// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/StartOfSpinMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/SpinType.hpp"
#include "../types/SpinStartTimeMilli.hpp"
#include "../types/SpinLastSeqNum.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

// Start Of Spin Message
struct start_of_spin_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::spin_type spin_type;
        link_multicast::spin_start_time_milli spin_start_time_milli;
        link_multicast::spin_last_seq_num spin_last_seq_num;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::start_of_spin_message};

    fields_type fields;

    // parse method
    static start_of_spin_message* parse(std::byte* buffer) {
        return reinterpret_cast<start_of_spin_message*>(buffer);
    }

    // parse method const
    static const start_of_spin_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const start_of_spin_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(start_of_spin_message::fields_type, channel_seq_num) == 0, "unexpected offset of start_of_spin_message::fields_type::channel_seq_num");
static_assert(offsetof(start_of_spin_message::fields_type, spin_type) == 4, "unexpected offset of start_of_spin_message::fields_type::spin_type");
static_assert(offsetof(start_of_spin_message::fields_type, spin_start_time_milli) == 5, "unexpected offset of start_of_spin_message::fields_type::spin_start_time_milli");
static_assert(offsetof(start_of_spin_message::fields_type, spin_last_seq_num) == 13, "unexpected offset of start_of_spin_message::fields_type::spin_last_seq_num");
static_assert(sizeof(start_of_spin_message::fields_type) == 17, "unexpected sizeof start_of_spin_message::fields_type");
static_assert(sizeof(start_of_spin_message) == sizeof(link_multicast::message_header) + 17, "unexpected sizeof start_of_spin_message");

#pragma pack(pop)
}
