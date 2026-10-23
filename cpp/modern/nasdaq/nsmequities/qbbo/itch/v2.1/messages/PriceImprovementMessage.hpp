#pragma once

#include "../types/Tracking.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/Stock.hpp"
#include "../types/InterestFlag.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

#pragma pack(push, 1)

// Indicates a retail interest indication of the Bid, Ask or both the Bid and Ask for Nasdaq-listed securities.
struct PriceImprovementMessage {

    Tracking tracking;
    TimeStamp time_stamp;
    Stock stock;
    InterestFlag interest_flag;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'N';

    // parse method
    static PriceImprovementMessage* parse(std::byte* buffer) {
        return reinterpret_cast<PriceImprovementMessage*>(buffer);
    }

    // parse method const
    static const PriceImprovementMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const PriceImprovementMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const PriceImprovementMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const PriceImprovementMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
