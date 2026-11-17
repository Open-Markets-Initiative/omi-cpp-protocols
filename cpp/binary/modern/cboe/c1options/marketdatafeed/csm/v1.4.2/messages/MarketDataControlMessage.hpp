// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/MarketDataControlMessage.hpp
#pragma once

#include "../types/MdControlType.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

// Market Data Control messages mark the start and end of the end of session Summary and the end of session Settlement data transmissions.
struct MarketDataControlMessage {

    MdControlType md_control_type;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 25;

    // parse method
    static MarketDataControlMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MarketDataControlMessage*>(buffer);
    }

    // parse method const
    static const MarketDataControlMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketDataControlMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MarketDataControlMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const MarketDataControlMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
