#pragma once

#include "../bitfields/SecurityDirectoryFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/AdjustedPocPrice.hpp"
#include "../types/LuldTier.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

#pragma pack(push, 1)

// The System Event Message is used to indicate events that apply to the market or the data feed.
struct SecurityDirectoryMessage {

    SecurityDirectoryFlags security_directory_flags;
    Timestamp timestamp;
    Symbol symbol;
    RoundLotSize round_lot_size;
    AdjustedPocPrice adjusted_poc_price;
    LuldTier luld_tier;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'D';

    // parse method
    static SecurityDirectoryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityDirectoryMessage*>(buffer);
    }

    // parse method const
    static const SecurityDirectoryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityDirectoryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecurityDirectoryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SecurityDirectoryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
