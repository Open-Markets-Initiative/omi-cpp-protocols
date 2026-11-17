// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/EndOfSpinMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/SpinType.hpp"
#include "../types/SpinMsgCt.hpp"
#include "../types/SpinEndTimeMilli.hpp"
#include "../types/SpinLastSeqNum.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

// End Of Spin Message
struct end_of_spin_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::spin_type spin_type;
        link_multicast::spin_msg_ct spin_msg_ct;
        link_multicast::spin_end_time_milli spin_end_time_milli;
        link_multicast::spin_last_seq_num spin_last_seq_num;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::end_of_spin_message};

    fields_type fields;

    // parse method
    static end_of_spin_message* parse(std::byte* buffer) {
        return reinterpret_cast<end_of_spin_message*>(buffer);
    }

    // parse method const
    static const end_of_spin_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const end_of_spin_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(end_of_spin_message::fields_type, channel_seq_num) == 0, "unexpected offset of end_of_spin_message::fields_type::channel_seq_num");
static_assert(offsetof(end_of_spin_message::fields_type, spin_type) == 4, "unexpected offset of end_of_spin_message::fields_type::spin_type");
static_assert(offsetof(end_of_spin_message::fields_type, spin_msg_ct) == 5, "unexpected offset of end_of_spin_message::fields_type::spin_msg_ct");
static_assert(offsetof(end_of_spin_message::fields_type, spin_end_time_milli) == 9, "unexpected offset of end_of_spin_message::fields_type::spin_end_time_milli");
static_assert(offsetof(end_of_spin_message::fields_type, spin_last_seq_num) == 17, "unexpected offset of end_of_spin_message::fields_type::spin_last_seq_num");
static_assert(sizeof(end_of_spin_message::fields_type) == 21, "unexpected sizeof end_of_spin_message::fields_type");
static_assert(sizeof(end_of_spin_message) == sizeof(link_multicast::message_header) + 21, "unexpected sizeof end_of_spin_message");

#pragma pack(pop)
}
