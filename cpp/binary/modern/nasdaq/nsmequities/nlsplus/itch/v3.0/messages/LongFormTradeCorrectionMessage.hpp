#pragma once

#include "../types/OriginatingMarketCenterIdentifier.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/OriginalTradeControlNumber.hpp"
#include "../types/OriginalTradePriceLong.hpp"
#include "../types/OriginalTradeSize.hpp"
#include "../structs/OriginalSaleConditionModifier.hpp"
#include "../types/CorrectedTradeControlNumber.hpp"
#include "../types/CorrectedTradePriceLong.hpp"
#include "../types/CorrectedTradeSize.hpp"
#include "../structs/CorrectedSaleConditionModifier.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Trade Correction carrying eight byte original and corrected trade prices.
struct LongFormTradeCorrectionMessage {

    OriginatingMarketCenterIdentifier originating_market_center_identifier;
    IssueSymbol issue_symbol;
    SecurityClass security_class;
    OriginalTradeControlNumber original_trade_control_number;
    OriginalTradePriceLong original_trade_price_long;
    OriginalTradeSize original_trade_size;
    OriginalSaleConditionModifier original_sale_condition_modifier;
    CorrectedTradeControlNumber corrected_trade_control_number;
    CorrectedTradePriceLong corrected_trade_price_long;
    CorrectedTradeSize corrected_trade_size;
    CorrectedSaleConditionModifier corrected_sale_condition_modifier;
    ConsolidatedVolume consolidated_volume;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'c';

    // parse method
    static LongFormTradeCorrectionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LongFormTradeCorrectionMessage*>(buffer);
    }

    // parse method const
    static const LongFormTradeCorrectionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LongFormTradeCorrectionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LongFormTradeCorrectionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const LongFormTradeCorrectionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
