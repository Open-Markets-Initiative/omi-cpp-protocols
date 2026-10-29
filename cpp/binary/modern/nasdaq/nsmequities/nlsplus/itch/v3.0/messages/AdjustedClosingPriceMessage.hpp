#pragma once

#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/AdjustedClosingPrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Denotes the adjusted previous close price to be used for intraday net change calculations.
struct AdjustedClosingPriceMessage {

    IssueSymbol issue_symbol;
    SecurityClass security_class;
    AdjustedClosingPrice adjusted_closing_price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'G';

    // parse method
    static AdjustedClosingPriceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AdjustedClosingPriceMessage*>(buffer);
    }

    // parse method const
    static const AdjustedClosingPriceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AdjustedClosingPriceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AdjustedClosingPriceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AdjustedClosingPriceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
