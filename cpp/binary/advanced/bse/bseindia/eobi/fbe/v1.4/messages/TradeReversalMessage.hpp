#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/Pad4.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"
#include "../types/TrdRegTsExecutionTime.hpp"
#include "../types/NoMdEntries.hpp"
#include "../types/Pad7.hpp"
#include "../structs/MdTradeEntryGrp.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Trade Reversal Message
struct trade_reversal_message {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::transact_time transact_time;
        fbe_eobi::trd_match_id trd_match_id;
        fbe_eobi::pad_4 pad_4;
        fbe_eobi::last_qty last_qty;
        fbe_eobi::last_px last_px;
        fbe_eobi::trd_reg_ts_execution_time trd_reg_ts_execution_time;
        fbe_eobi::no_md_entries no_md_entries;
        fbe_eobi::pad_7 pad_7;
        fbe_eobi::md_trade_entry_grp md_trade_entry_grp;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::trade_reversal_message, {}};

    fields_type fields;

    // parse method
    static trade_reversal_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_reversal_message*>(buffer);
    }

    // parse method const
    static const trade_reversal_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_reversal_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_reversal_message::fields_type, security_id) == 0, "unexpected offset of trade_reversal_message::fields_type::security_id");
static_assert(offsetof(trade_reversal_message::fields_type, transact_time) == 8, "unexpected offset of trade_reversal_message::fields_type::transact_time");
static_assert(offsetof(trade_reversal_message::fields_type, trd_match_id) == 16, "unexpected offset of trade_reversal_message::fields_type::trd_match_id");
static_assert(offsetof(trade_reversal_message::fields_type, pad_4) == 20, "unexpected offset of trade_reversal_message::fields_type::pad_4");
static_assert(offsetof(trade_reversal_message::fields_type, last_qty) == 24, "unexpected offset of trade_reversal_message::fields_type::last_qty");
static_assert(offsetof(trade_reversal_message::fields_type, last_px) == 32, "unexpected offset of trade_reversal_message::fields_type::last_px");
static_assert(offsetof(trade_reversal_message::fields_type, trd_reg_ts_execution_time) == 40, "unexpected offset of trade_reversal_message::fields_type::trd_reg_ts_execution_time");
static_assert(offsetof(trade_reversal_message::fields_type, no_md_entries) == 48, "unexpected offset of trade_reversal_message::fields_type::no_md_entries");
static_assert(offsetof(trade_reversal_message::fields_type, pad_7) == 49, "unexpected offset of trade_reversal_message::fields_type::pad_7");
static_assert(offsetof(trade_reversal_message::fields_type, md_trade_entry_grp) == 56, "unexpected offset of trade_reversal_message::fields_type::md_trade_entry_grp");
static_assert(sizeof(trade_reversal_message::fields_type) == 80, "unexpected sizeof trade_reversal_message::fields_type");
static_assert(sizeof(trade_reversal_message) == sizeof(fbe_eobi::message_header) + 80, "unexpected sizeof trade_reversal_message");

#pragma pack(pop)
}
