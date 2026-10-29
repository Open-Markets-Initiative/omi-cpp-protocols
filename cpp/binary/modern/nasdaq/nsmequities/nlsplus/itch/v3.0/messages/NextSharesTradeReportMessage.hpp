#pragma once

#include "../types/OriginatingMarketCenterIdentifier.hpp"
#include "../types/NextSharesSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/TradeControlNumber.hpp"
#include "../types/ProxyPrice.hpp"
#include "../types/TradeSize.hpp"
#include "../types/NavOffsetAmount.hpp"
#include "../structs/SaleConditionModifier.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Relays trade transactions for NextShares exchange traded managed funds, reported as a proxy price with the Nav offset to apply to it.
struct NextSharesTradeReportMessage {

    OriginatingMarketCenterIdentifier originating_market_center_identifier;
    NextSharesSymbol next_shares_symbol;
    SecurityClass security_class;
    TradeControlNumber trade_control_number;
    ProxyPrice proxy_price;
    TradeSize trade_size;
    NavOffsetAmount nav_offset_amount;
    SaleConditionModifier sale_condition_modifier;
    ConsolidatedVolume consolidated_volume;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'M';

    // parse method
    static NextSharesTradeReportMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NextSharesTradeReportMessage*>(buffer);
    }

    // parse method const
    static const NextSharesTradeReportMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NextSharesTradeReportMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const NextSharesTradeReportMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const NextSharesTradeReportMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
