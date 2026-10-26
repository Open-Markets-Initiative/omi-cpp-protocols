#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/MatchNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

#pragma pack(push, 1)

// Firms that use the ITCH feed to create time-and-sales displays or calculate market statistics should be prepared to process the broken trade message. If a firm is only using the ITCH feed to build a book, however, it may ignore these messages as they have no impact on the current book.
struct BrokenTradeMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    MatchNumber match_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'B';

    // parse method
    static BrokenTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<BrokenTradeMessage*>(buffer);
    }

    // parse method const
    static const BrokenTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const BrokenTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const BrokenTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const BrokenTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
