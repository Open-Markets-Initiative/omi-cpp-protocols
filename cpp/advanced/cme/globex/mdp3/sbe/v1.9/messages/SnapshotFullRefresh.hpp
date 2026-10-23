#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/TotNumReports.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/TransactTime.hpp"
#include "../types/LastUpdateTime.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdSecurityTradingStatus.hpp"
#include "../types/HighLimitPriceEx.hpp"
#include "../types/LowLimitPriceEx.hpp"
#include "../types/MaxPriceVariationEx.hpp"
#include "../types/MdEntryPxOptionalEx.hpp"
#include "../types/MdEntrySizeShortOptional.hpp"
#include "../types/NumberOfOrdersOptional.hpp"
#include "../types/MdPriceLevelOptional.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/SettlPriceType.hpp"
#include "../types/MdEntryType.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

#pragma pack(push, 1)
struct snapshot_full_refresh_groups_entry {
    sbe_mdp3::md_entry_px_optional_ex md_entry_px_optional_ex;
    sbe_mdp3::md_entry_size_short_optional md_entry_size_short_optional;
    sbe_mdp3::number_of_orders_optional number_of_orders_optional;
    sbe_mdp3::md_price_level_optional md_price_level_optional;
    sbe_mdp3::trading_reference_date trading_reference_date;
    sbe_mdp3::open_close_settl_flag open_close_settl_flag;
    sbe_mdp3::settl_price_type settl_price_type;
    sbe_mdp3::md_entry_type md_entry_type;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Snapshot Full Refresh
struct snapshot_full_refresh {

    struct fields_type {
        sbe_mdp3::last_msg_seq_num_processed last_msg_seq_num_processed;
        sbe_mdp3::tot_num_reports tot_num_reports;
        sbe_mdp3::security_id security_id;
        sbe_mdp3::rpt_seq rpt_seq;
        sbe_mdp3::transact_time transact_time;
        sbe_mdp3::last_update_time last_update_time;
        sbe_mdp3::trade_date trade_date;
        sbe_mdp3::md_security_trading_status md_security_trading_status;
        sbe_mdp3::high_limit_price_ex high_limit_price_ex;
        sbe_mdp3::low_limit_price_ex low_limit_price_ex;
        sbe_mdp3::max_price_variation_ex max_price_variation_ex;
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::snapshot_full_refresh, schema_id::enum_type::mktdata, version(9)};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(fields_type) - sizeof(sbe_mdp3::message_size);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(fields_type) + sizeof(sbe_mdp3::message_size)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(fields_type) - sizeof(sbe_mdp3::message_size));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<snapshot_full_refresh_groups_entry, group_size> snapshot_full_refresh_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static snapshot_full_refresh* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_full_refresh*>(buffer);
    }

    // parse method const
    static const snapshot_full_refresh* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_full_refresh*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_full_refresh::fields_type, last_msg_seq_num_processed) == 0, "unexpected offset of snapshot_full_refresh::fields_type::last_msg_seq_num_processed");
static_assert(offsetof(snapshot_full_refresh::fields_type, tot_num_reports) == 4, "unexpected offset of snapshot_full_refresh::fields_type::tot_num_reports");
static_assert(offsetof(snapshot_full_refresh::fields_type, security_id) == 8, "unexpected offset of snapshot_full_refresh::fields_type::security_id");
static_assert(offsetof(snapshot_full_refresh::fields_type, rpt_seq) == 12, "unexpected offset of snapshot_full_refresh::fields_type::rpt_seq");
static_assert(offsetof(snapshot_full_refresh::fields_type, transact_time) == 16, "unexpected offset of snapshot_full_refresh::fields_type::transact_time");
static_assert(offsetof(snapshot_full_refresh::fields_type, last_update_time) == 24, "unexpected offset of snapshot_full_refresh::fields_type::last_update_time");
static_assert(offsetof(snapshot_full_refresh::fields_type, trade_date) == 32, "unexpected offset of snapshot_full_refresh::fields_type::trade_date");
static_assert(offsetof(snapshot_full_refresh::fields_type, md_security_trading_status) == 34, "unexpected offset of snapshot_full_refresh::fields_type::md_security_trading_status");
static_assert(offsetof(snapshot_full_refresh::fields_type, high_limit_price_ex) == 35, "unexpected offset of snapshot_full_refresh::fields_type::high_limit_price_ex");
static_assert(offsetof(snapshot_full_refresh::fields_type, low_limit_price_ex) == 43, "unexpected offset of snapshot_full_refresh::fields_type::low_limit_price_ex");
static_assert(offsetof(snapshot_full_refresh::fields_type, max_price_variation_ex) == 51, "unexpected offset of snapshot_full_refresh::fields_type::max_price_variation_ex");
static_assert(sizeof(snapshot_full_refresh::fields_type) == 59, "unexpected sizeof snapshot_full_refresh::fields_type");

#pragma pack(pop)
}

#include "details/SnapshotFullRefreshWriter.hpp"
#include "details/SnapshotFullRefreshReader.hpp"
