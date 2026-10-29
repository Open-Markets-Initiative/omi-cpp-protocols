#pragma once

#include "../types/OriginatingMarketCenterIdentifier.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/TradeControlNumber.hpp"
#include "../types/TradePriceLong.hpp"
#include "../types/TradeSize.hpp"
#include "../structs/SaleConditionModifier.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Trade Report carrying an eight byte trade price, used when the price breaches the maximum value the four byte form can carry.
struct LongFormTradeReportMessage {

    OriginatingMarketCenterIdentifier originating_market_center_identifier;
    IssueSymbol issue_symbol;
    SecurityClass security_class;
    TradeControlNumber trade_control_number;
    TradePriceLong trade_price_long;
    TradeSize trade_size;
    SaleConditionModifier sale_condition_modifier;
    ConsolidatedVolume consolidated_volume;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 't';

    // parse method
    static LongFormTradeReportMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LongFormTradeReportMessage*>(buffer);
    }

    // parse method const
    static const LongFormTradeReportMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LongFormTradeReportMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LongFormTradeReportMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const LongFormTradeReportMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
