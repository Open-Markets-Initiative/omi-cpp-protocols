// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/ExpectedOpeningPriceAndSizeMessage.hpp
#pragma once

#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/Eop.hpp"
#include "../types/Eos.hpp"
#include "../types/EopType.hpp"
#include "../types/LegalMarket.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

// The EOP message contains expected opening price and size information for a security.
struct ExpectedOpeningPriceAndSizeMessage {

    ClassKey class_key;
    SecurityId security_id;
    Eop eop;
    Eos eos;
    EopType eop_type;
    LegalMarket legal_market;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 15;

    // parse method
    static ExpectedOpeningPriceAndSizeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ExpectedOpeningPriceAndSizeMessage*>(buffer);
    }

    // parse method const
    static const ExpectedOpeningPriceAndSizeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExpectedOpeningPriceAndSizeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ExpectedOpeningPriceAndSizeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ExpectedOpeningPriceAndSizeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
