// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/SecurityDefinitionMessage.hpp
#pragma once

#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

// Security definitions describe an exchange’s products by name and trading parameters and associates those products with a product security ID.
struct SecurityDefinitionMessage {


    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 13;

    // parse method
    static SecurityDefinitionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityDefinitionMessage*>(buffer);
    }

    // parse method const
    static const SecurityDefinitionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityDefinitionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecurityDefinitionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SecurityDefinitionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
