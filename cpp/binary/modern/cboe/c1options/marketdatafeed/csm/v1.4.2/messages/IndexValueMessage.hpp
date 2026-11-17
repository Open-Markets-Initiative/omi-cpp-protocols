// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/IndexValueMessage.hpp
#pragma once

#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

// Index value messages contain the values associated with a calculated index. They are transmitted when an index is calculated.
struct IndexValueMessage {


    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 22;

    // parse method
    static IndexValueMessage* parse(std::byte* buffer) {
        return reinterpret_cast<IndexValueMessage*>(buffer);
    }

    // parse method const
    static const IndexValueMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const IndexValueMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const IndexValueMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const IndexValueMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
