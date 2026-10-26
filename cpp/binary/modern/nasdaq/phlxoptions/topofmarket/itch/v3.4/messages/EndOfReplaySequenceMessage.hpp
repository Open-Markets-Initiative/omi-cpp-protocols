#pragma once

#include "../types/EndOfReplaySequenceNumber.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// The End of replay Sequence message reflects the sequence number at the time replay of existing messages is complete. The firms can then use this sequence number to resume on the real time Mold channel. Only for SoupBINTCP.
struct EndOfReplaySequenceMessage {

    EndOfReplaySequenceNumber end_of_replay_sequence_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'M';

    // parse method
    static EndOfReplaySequenceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EndOfReplaySequenceMessage*>(buffer);
    }

    // parse method const
    static const EndOfReplaySequenceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EndOfReplaySequenceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const EndOfReplaySequenceMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const EndOfReplaySequenceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
