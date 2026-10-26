#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/PairedQuantity.hpp"
#include "../types/Reserved4.hpp"
#include "../types/Reserved1.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/Price.hpp"
#include "../types/AuctionType.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// 9 Used to disseminate the indicative auction price and the tradable quantity and imbalance at this price.
struct AuctionInfoMessage {

    Nanosecond nanosecond;
    PairedQuantity paired_quantity;
    Reserved4 reserved_4;
    Reserved1 reserved_1;
    InstrumentId instrument_id;
    ReservedA reserved_a;
    ReservedB reserved_b;
    Price price;
    AuctionType auction_type;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x49;

    // parse method
    static AuctionInfoMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionInfoMessage*>(buffer);
    }

    // parse method const
    static const AuctionInfoMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionInfoMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionInfoMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AuctionInfoMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
