#pragma once

#include "../types/OriginatingMarketCenterIdentifier.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/OriginalTradeControlNumber.hpp"
#include "../types/OriginalTradePrice.hpp"
#include "../types/OriginalTradeSize.hpp"
#include "../structs/OriginalSaleConditionModifier.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Indicates that a previously reported trade transaction has been cancelled or was reported in error.
struct TradeCancelErrorMessage {

    OriginatingMarketCenterIdentifier originating_market_center_identifier;
    IssueSymbol issue_symbol;
    SecurityClass security_class;
    OriginalTradeControlNumber original_trade_control_number;
    OriginalTradePrice original_trade_price;
    OriginalTradeSize original_trade_size;
    OriginalSaleConditionModifier original_sale_condition_modifier;
    ConsolidatedVolume consolidated_volume;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'X';

    // parse method
    static TradeCancelErrorMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCancelErrorMessage*>(buffer);
    }

    // parse method const
    static const TradeCancelErrorMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCancelErrorMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeCancelErrorMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeCancelErrorMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
