#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastUpdateTime.hpp"
#include "../types/TrdRegTsExecutionTime.hpp"
#include "../types/TotNoOrders.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/NoMdEntries.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/NoOfTrades.hpp"
#include "../types/Pad4.hpp"
#include "../structs/MdInstrumentEntryGrp.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Instrument Summary Message
struct instrument_summary_message {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::last_update_time last_update_time;
        fbe_eobi::trd_reg_ts_execution_time trd_reg_ts_execution_time;
        fbe_eobi::tot_no_orders tot_no_orders;
        fbe_eobi::security_status security_status;
        fbe_eobi::security_trading_status security_trading_status;
        fbe_eobi::fast_market_indicator fast_market_indicator;
        fbe_eobi::no_md_entries no_md_entries;
        fbe_eobi::trade_volume trade_volume;
        fbe_eobi::no_of_trades no_of_trades;
        fbe_eobi::pad_4 pad_4;
        fbe_eobi::md_instrument_entry_grp md_instrument_entry_grp;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::instrument_summary_message, {}};

    fields_type fields;

    // parse method
    static instrument_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<instrument_summary_message*>(buffer);
    }

    // parse method const
    static const instrument_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const instrument_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(instrument_summary_message::fields_type, security_id) == 0, "unexpected offset of instrument_summary_message::fields_type::security_id");
static_assert(offsetof(instrument_summary_message::fields_type, last_update_time) == 8, "unexpected offset of instrument_summary_message::fields_type::last_update_time");
static_assert(offsetof(instrument_summary_message::fields_type, trd_reg_ts_execution_time) == 16, "unexpected offset of instrument_summary_message::fields_type::trd_reg_ts_execution_time");
static_assert(offsetof(instrument_summary_message::fields_type, tot_no_orders) == 24, "unexpected offset of instrument_summary_message::fields_type::tot_no_orders");
static_assert(offsetof(instrument_summary_message::fields_type, security_status) == 28, "unexpected offset of instrument_summary_message::fields_type::security_status");
static_assert(offsetof(instrument_summary_message::fields_type, security_trading_status) == 29, "unexpected offset of instrument_summary_message::fields_type::security_trading_status");
static_assert(offsetof(instrument_summary_message::fields_type, fast_market_indicator) == 30, "unexpected offset of instrument_summary_message::fields_type::fast_market_indicator");
static_assert(offsetof(instrument_summary_message::fields_type, no_md_entries) == 31, "unexpected offset of instrument_summary_message::fields_type::no_md_entries");
static_assert(offsetof(instrument_summary_message::fields_type, trade_volume) == 32, "unexpected offset of instrument_summary_message::fields_type::trade_volume");
static_assert(offsetof(instrument_summary_message::fields_type, no_of_trades) == 40, "unexpected offset of instrument_summary_message::fields_type::no_of_trades");
static_assert(offsetof(instrument_summary_message::fields_type, pad_4) == 44, "unexpected offset of instrument_summary_message::fields_type::pad_4");
static_assert(offsetof(instrument_summary_message::fields_type, md_instrument_entry_grp) == 48, "unexpected offset of instrument_summary_message::fields_type::md_instrument_entry_grp");
static_assert(sizeof(instrument_summary_message::fields_type) == 72, "unexpected sizeof instrument_summary_message::fields_type");
static_assert(sizeof(instrument_summary_message) == sizeof(fbe_eobi::message_header) + 72, "unexpected sizeof instrument_summary_message");

#pragma pack(pop)
}
