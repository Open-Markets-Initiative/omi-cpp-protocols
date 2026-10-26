#pragma once

#include <cstddef>
#include "../structs/ServerPacketHeader.hpp"
#include "../types/EndOfReplaySequenceNumber.hpp"
#include "../types/SequencedMessageType.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

namespace itch_topofmarket = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

#pragma pack(push, 1)

// End Of Replay Sequence Message
struct end_of_replay_sequence_message {

    struct fields_type {
        itch_topofmarket::end_of_replay_sequence_number end_of_replay_sequence_number;
    };

    itch_topofmarket::server_packet_header header = {std::uint16_t(sizeof(itch_topofmarket::server_packet_header) + sizeof(fields_type) + sizeof(itch_topofmarket::sequenced_message_type) - 2), server_packet_type::enum_type::sequenced_data_packet};
    itch_topofmarket::sequenced_message_type sequenced_message_type = itch_topofmarket::sequenced_message_type::enum_type::end_of_replay_sequence_message;

    fields_type fields;

    // parse method
    static end_of_replay_sequence_message* parse(std::byte* buffer) {
        return reinterpret_cast<end_of_replay_sequence_message*>(buffer);
    }

    // parse method const
    static const end_of_replay_sequence_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const end_of_replay_sequence_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(end_of_replay_sequence_message::fields_type, end_of_replay_sequence_number) == 0, "unexpected offset of end_of_replay_sequence_message::fields_type::end_of_replay_sequence_number");
static_assert(sizeof(end_of_replay_sequence_message::fields_type) == 20, "unexpected sizeof end_of_replay_sequence_message::fields_type");
static_assert(sizeof(end_of_replay_sequence_message) == sizeof(itch_topofmarket::server_packet_header) + sizeof(itch_topofmarket::sequenced_message_type) + 20, "unexpected sizeof end_of_replay_sequence_message");

#pragma pack(pop)
}
