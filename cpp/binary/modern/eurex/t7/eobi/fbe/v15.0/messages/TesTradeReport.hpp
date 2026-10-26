#pragma once

#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/TrdType.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/MultiLegReportingType.hpp"
#include "../types/MultiLegPriceModel.hpp"
#include "../types/Pad6.hpp"
#include "../types/NonDisclosedTradeVolume.hpp"
#include "../types/TransBkdTime.hpp"
#include "../types/NumberOfBuySides.hpp"
#include "../types/NumberOfSellSides.hpp"
#include "../types/Pad4.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

#pragma pack(push, 1)

// 
struct TesTradeReport {

    SecurityId security_id;
    TransactTime transact_time;
    LastQty last_qty;
    LastPx last_px;
    TrdMatchId trd_match_id;
    TrdType trd_type;
    TradeCondition trade_condition;
    MultiLegReportingType multi_leg_reporting_type;
    MultiLegPriceModel multi_leg_price_model;
    Pad6 pad6;
    NonDisclosedTradeVolume non_disclosed_trade_volume;
    TransBkdTime trans_bkd_time;
    NumberOfBuySides number_of_buy_sides;
    NumberOfSellSides number_of_sell_sides;
    Pad4 pad4;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13203;

    // parse method
    static TesTradeReport* parse(std::byte* buffer) {
        return reinterpret_cast<TesTradeReport*>(buffer);
    }

    // parse method const
    static const TesTradeReport* parse(const std::byte* buffer) {
        return reinterpret_cast<const TesTradeReport*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TesTradeReport* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const TesTradeReport*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
