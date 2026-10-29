#pragma once

#include "../types/OriginatingMarketCenterIdentifier.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/TradeControlNumber.hpp"
#include "../types/TradePrice.hpp"
#include "../types/TradeSize.hpp"
#include "../structs/SaleConditionModifier.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Relays Nasdaq execution system and Trf trade transactions reported for the current business day. Nasdaq reports only one side of a trade execution on the Nls Plus feed.
struct TradeReportMessage {

    OriginatingMarketCenterIdentifier originating_market_center_identifier;
    IssueSymbol issue_symbol;
    SecurityClass security_class;
    TradeControlNumber trade_control_number;
    TradePrice trade_price;
    TradeSize trade_size;
    SaleConditionModifier sale_condition_modifier;
    ConsolidatedVolume consolidated_volume;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'T';

    // parse method
    static TradeReportMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeReportMessage*>(buffer);
    }

    // parse method const
    static const TradeReportMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeReportMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeReportMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeReportMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
