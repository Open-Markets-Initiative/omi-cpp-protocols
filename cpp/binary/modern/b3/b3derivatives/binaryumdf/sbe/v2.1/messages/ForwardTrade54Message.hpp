#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/TradingSessionId.hpp"
#include "../bitfields/TradeCondition.hpp"
#include "../types/MdFuturePrice.hpp"
#include "../types/MdEntrySizeQuantity.hpp"
#include "../types/TradeId.hpp"
#include "../types/MdEntryBuyer.hpp"
#include "../types/MdEntrySeller.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TransactTime.hpp"
#include "../types/RptSeq.hpp"
#include "../types/SellerDays.hpp"
#include "../types/MdEntryInterestRate.hpp"
#include "../types/TrdSubType.hpp"
#include "../types/Padding3.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

#pragma pack(push, 1)

// ForwardTrade_54Message
struct ForwardTrade54Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    TradingSessionId trading_session_id;
    TradeCondition trade_condition;
    MdFuturePrice md_future_price;
    MdEntrySizeQuantity md_entry_size_quantity;
    TradeId trade_id;
    MdEntryBuyer md_entry_buyer;
    MdEntrySeller md_entry_seller;
    TradeDate trade_date;
    TransactTime transact_time;
    RptSeq rpt_seq;
    SellerDays seller_days;
    MdEntryInterestRate md_entry_interest_rate;
    TrdSubType trd_sub_type;
    Padding3 padding_3;

    // parse method
    static ForwardTrade54Message* parse(std::byte* buffer) {
        return reinterpret_cast<ForwardTrade54Message*>(buffer);
    }

    // parse method const
    static const ForwardTrade54Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const ForwardTrade54Message*>(buffer);
    }
};

#pragma pack(pop)
}
