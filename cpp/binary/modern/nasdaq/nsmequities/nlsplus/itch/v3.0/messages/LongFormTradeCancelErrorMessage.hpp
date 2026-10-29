#pragma once

#include "../types/OriginatingMarketCenterIdentifier.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/OriginalTradeControlNumber.hpp"
#include "../types/OriginalTradePriceLong.hpp"
#include "../types/OriginalTradeSize.hpp"
#include "../structs/OriginalSaleConditionModifier.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Trade Cancel/Error carrying an eight byte original trade price.
struct LongFormTradeCancelErrorMessage {

    OriginatingMarketCenterIdentifier originating_market_center_identifier;
    IssueSymbol issue_symbol;
    SecurityClass security_class;
    OriginalTradeControlNumber original_trade_control_number;
    OriginalTradePriceLong original_trade_price_long;
    OriginalTradeSize original_trade_size;
    OriginalSaleConditionModifier original_sale_condition_modifier;
    ConsolidatedVolume consolidated_volume;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'x';

    // parse method
    static LongFormTradeCancelErrorMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LongFormTradeCancelErrorMessage*>(buffer);
    }

    // parse method const
    static const LongFormTradeCancelErrorMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LongFormTradeCancelErrorMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LongFormTradeCancelErrorMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const LongFormTradeCancelErrorMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
