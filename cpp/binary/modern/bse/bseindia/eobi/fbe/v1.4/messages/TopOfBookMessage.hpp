#pragma once

#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/BidPx.hpp"
#include "../types/OfferPx.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Carries the best bid and offer of an order book outside continuous trading.
struct TopOfBookMessage {

    TransactTime transact_time;
    SecurityId security_id;
    BidPx bid_px;
    OfferPx offer_px;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13504;

    // parse method
    static TopOfBookMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TopOfBookMessage*>(buffer);
    }

    // parse method const
    static const TopOfBookMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TopOfBookMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TopOfBookMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TopOfBookMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
