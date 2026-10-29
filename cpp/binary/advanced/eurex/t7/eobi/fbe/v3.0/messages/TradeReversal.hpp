#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"
#include "../types/TrdRegTsExecutionTime.hpp"
#include "../types/NoMdEntries.hpp"
#include "../types/Pad7.hpp"
#include "../structs/MdTradeEntryGrpComp.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v3_0;

#pragma pack(push, 1)

// Trade Reversal
struct trade_reversal {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::transact_time transact_time;
        fbe_eobi::trd_match_id trd_match_id;
        fbe_eobi::last_qty last_qty;
        fbe_eobi::last_px last_px;
        fbe_eobi::trd_reg_ts_execution_time trd_reg_ts_execution_time;
        fbe_eobi::no_md_entries no_md_entries;
        fbe_eobi::pad7 pad7;
        fbe_eobi::md_trade_entry_grp_comp md_trade_entry_grp_comp;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::trade_reversal, {}};

    fields_type fields;

    // parse method
    static trade_reversal* parse(std::byte* buffer) {
        return reinterpret_cast<trade_reversal*>(buffer);
    }

    // parse method const
    static const trade_reversal* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_reversal*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_reversal::fields_type, security_id) == 0, "unexpected offset of trade_reversal::fields_type::security_id");
static_assert(offsetof(trade_reversal::fields_type, transact_time) == 8, "unexpected offset of trade_reversal::fields_type::transact_time");
static_assert(offsetof(trade_reversal::fields_type, trd_match_id) == 16, "unexpected offset of trade_reversal::fields_type::trd_match_id");
static_assert(offsetof(trade_reversal::fields_type, last_qty) == 20, "unexpected offset of trade_reversal::fields_type::last_qty");
static_assert(offsetof(trade_reversal::fields_type, last_px) == 24, "unexpected offset of trade_reversal::fields_type::last_px");
static_assert(offsetof(trade_reversal::fields_type, trd_reg_ts_execution_time) == 32, "unexpected offset of trade_reversal::fields_type::trd_reg_ts_execution_time");
static_assert(offsetof(trade_reversal::fields_type, no_md_entries) == 40, "unexpected offset of trade_reversal::fields_type::no_md_entries");
static_assert(offsetof(trade_reversal::fields_type, pad7) == 41, "unexpected offset of trade_reversal::fields_type::pad7");
static_assert(offsetof(trade_reversal::fields_type, md_trade_entry_grp_comp) == 48, "unexpected offset of trade_reversal::fields_type::md_trade_entry_grp_comp");
static_assert(sizeof(trade_reversal::fields_type) == 64, "unexpected sizeof trade_reversal::fields_type");
static_assert(sizeof(trade_reversal) == sizeof(fbe_eobi::message_header_comp) + 64, "unexpected sizeof trade_reversal");

#pragma pack(pop)
}
