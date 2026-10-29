#pragma once

#include "../types/MarketCenter.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/OriginalTradeControlNumber.hpp"
#include "../types/OriginalProxyPrice.hpp"
#include "../types/OriginalNavOffsetAmount.hpp"
#include "../types/OriginalTradeSize.hpp"
#include "../structs/OriginalSaleConditionModifier.hpp"
#include "../types/CorrectedTradeControlNumber.hpp"
#include "../types/CorrectedProxyPrice.hpp"
#include "../types/CorrectedNavOffsetAmount.hpp"
#include "../types/CorrectedTradeSize.hpp"
#include "../structs/CorrectedSaleConditionModifier.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Indicates that a previously reported NextShares trade transaction has been corrected.
struct NextSharesTradeCorrectionMessage {

    MarketCenter market_center;
    IssueSymbol issue_symbol;
    SecurityClass security_class;
    OriginalTradeControlNumber original_trade_control_number;
    OriginalProxyPrice original_proxy_price;
    OriginalNavOffsetAmount original_nav_offset_amount;
    OriginalTradeSize original_trade_size;
    OriginalSaleConditionModifier original_sale_condition_modifier;
    CorrectedTradeControlNumber corrected_trade_control_number;
    CorrectedProxyPrice corrected_proxy_price;
    CorrectedNavOffsetAmount corrected_nav_offset_amount;
    CorrectedTradeSize corrected_trade_size;
    CorrectedSaleConditionModifier corrected_sale_condition_modifier;
    ConsolidatedVolume consolidated_volume;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Z';

    // parse method
    static NextSharesTradeCorrectionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NextSharesTradeCorrectionMessage*>(buffer);
    }

    // parse method const
    static const NextSharesTradeCorrectionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NextSharesTradeCorrectionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const NextSharesTradeCorrectionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const NextSharesTradeCorrectionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
