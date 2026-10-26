#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastUpdateTime.hpp"
#include "../types/TrdRegTsExecutionTime.hpp"
#include "../types/TotNoOrders.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/MarketCondition.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../types/SoldOutIndicator.hpp"
#include "../types/HighPx.hpp"
#include "../types/LowPx.hpp"
#include "../types/ProductComplex.hpp"
#include "../types/NoMdEntries.hpp"
#include "../types/TesSecurityStatus.hpp"
#include "../types/Pad5.hpp"
#include "../structs/MdInstrumentEntryGrpComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

// Instrument Summary
struct instrument_summary {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::last_update_time last_update_time;
        fbe_eobi::trd_reg_ts_execution_time trd_reg_ts_execution_time;
        fbe_eobi::tot_no_orders tot_no_orders;
        fbe_eobi::security_status security_status;
        fbe_eobi::security_trading_status security_trading_status;
        fbe_eobi::market_condition market_condition;
        fbe_eobi::fast_market_indicator fast_market_indicator;
        fbe_eobi::security_trading_event security_trading_event;
        fbe_eobi::sold_out_indicator sold_out_indicator;
        fbe_eobi::high_px high_px;
        fbe_eobi::low_px low_px;
        fbe_eobi::product_complex product_complex;
        fbe_eobi::no_md_entries no_md_entries;
        fbe_eobi::tes_security_status tes_security_status;
        fbe_eobi::pad5 pad5;
        fbe_eobi::md_instrument_entry_grp_comp md_instrument_entry_grp_comp;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::instrument_summary, {}};

    fields_type fields;

    // parse method
    static instrument_summary* parse(std::byte* buffer) {
        return reinterpret_cast<instrument_summary*>(buffer);
    }

    // parse method const
    static const instrument_summary* parse(const std::byte* buffer) {
        return reinterpret_cast<const instrument_summary*>(buffer);
    }

};

// layout verification
static_assert(offsetof(instrument_summary::fields_type, security_id) == 0, "unexpected offset of instrument_summary::fields_type::security_id");
static_assert(offsetof(instrument_summary::fields_type, last_update_time) == 8, "unexpected offset of instrument_summary::fields_type::last_update_time");
static_assert(offsetof(instrument_summary::fields_type, trd_reg_ts_execution_time) == 16, "unexpected offset of instrument_summary::fields_type::trd_reg_ts_execution_time");
static_assert(offsetof(instrument_summary::fields_type, tot_no_orders) == 24, "unexpected offset of instrument_summary::fields_type::tot_no_orders");
static_assert(offsetof(instrument_summary::fields_type, security_status) == 26, "unexpected offset of instrument_summary::fields_type::security_status");
static_assert(offsetof(instrument_summary::fields_type, security_trading_status) == 27, "unexpected offset of instrument_summary::fields_type::security_trading_status");
static_assert(offsetof(instrument_summary::fields_type, market_condition) == 28, "unexpected offset of instrument_summary::fields_type::market_condition");
static_assert(offsetof(instrument_summary::fields_type, fast_market_indicator) == 29, "unexpected offset of instrument_summary::fields_type::fast_market_indicator");
static_assert(offsetof(instrument_summary::fields_type, security_trading_event) == 30, "unexpected offset of instrument_summary::fields_type::security_trading_event");
static_assert(offsetof(instrument_summary::fields_type, sold_out_indicator) == 31, "unexpected offset of instrument_summary::fields_type::sold_out_indicator");
static_assert(offsetof(instrument_summary::fields_type, high_px) == 32, "unexpected offset of instrument_summary::fields_type::high_px");
static_assert(offsetof(instrument_summary::fields_type, low_px) == 40, "unexpected offset of instrument_summary::fields_type::low_px");
static_assert(offsetof(instrument_summary::fields_type, product_complex) == 48, "unexpected offset of instrument_summary::fields_type::product_complex");
static_assert(offsetof(instrument_summary::fields_type, no_md_entries) == 49, "unexpected offset of instrument_summary::fields_type::no_md_entries");
static_assert(offsetof(instrument_summary::fields_type, tes_security_status) == 50, "unexpected offset of instrument_summary::fields_type::tes_security_status");
static_assert(offsetof(instrument_summary::fields_type, pad5) == 51, "unexpected offset of instrument_summary::fields_type::pad5");
static_assert(offsetof(instrument_summary::fields_type, md_instrument_entry_grp_comp) == 56, "unexpected offset of instrument_summary::fields_type::md_instrument_entry_grp_comp");
static_assert(sizeof(instrument_summary::fields_type) == 88, "unexpected sizeof instrument_summary::fields_type");
static_assert(sizeof(instrument_summary) == sizeof(fbe_eobi::message_header_comp) + 88, "unexpected sizeof instrument_summary");

#pragma pack(pop)
}
