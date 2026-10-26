#pragma once

#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/MdOriginType.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/TrdType.hpp"
#include "../types/MultiLegReportingType.hpp"
#include "../types/MultiLegPriceModel.hpp"
#include "../types/NonDisclosedTradeVolume.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

#pragma pack(push, 1)

struct MdInstrumentEntryGrpComp {

    MdEntryPx md_entry_px;
    MdEntrySize md_entry_size;
    MdOriginType md_origin_type;
    MdEntryType md_entry_type;
    TradeCondition trade_condition;
    TrdType trd_type;
    MultiLegReportingType multi_leg_reporting_type;
    MultiLegPriceModel multi_leg_price_model;
    NonDisclosedTradeVolume non_disclosed_trade_volume;

    // parse method
    static MdInstrumentEntryGrpComp* parse(std::byte* buffer) {
        return reinterpret_cast<MdInstrumentEntryGrpComp*>(buffer);
    }

    // parse method const
    static const MdInstrumentEntryGrpComp* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdInstrumentEntryGrpComp*>(buffer);
    }
};

#pragma pack(pop)
}
