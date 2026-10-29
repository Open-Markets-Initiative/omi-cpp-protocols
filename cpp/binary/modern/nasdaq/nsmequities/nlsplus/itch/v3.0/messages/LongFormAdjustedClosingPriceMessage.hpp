#pragma once

#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/AdjustedClosingPriceLong.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Adjusted Closing Price carrying an eight byte price.
struct LongFormAdjustedClosingPriceMessage {

    IssueSymbol issue_symbol;
    SecurityClass security_class;
    AdjustedClosingPriceLong adjusted_closing_price_long;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'g';

    // parse method
    static LongFormAdjustedClosingPriceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LongFormAdjustedClosingPriceMessage*>(buffer);
    }

    // parse method const
    static const LongFormAdjustedClosingPriceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LongFormAdjustedClosingPriceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LongFormAdjustedClosingPriceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const LongFormAdjustedClosingPriceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
