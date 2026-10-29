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
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/MdEntryPxOptional.hpp"
#include "../types/MdEntrySizeOptional.hpp"
#include "../types/NumberOfOrders.hpp"
#include "../types/MdPriceLevelOptional.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/SettlPriceType.hpp"
#include "../types/MdEntryType.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

#pragma pack(push, 1)
struct snapshot_full_refresh_groups_entry {
    sbe_mdp3::md_entry_px_optional md_entry_px_optional;
    sbe_mdp3::md_entry_size_optional md_entry_size_optional;
    sbe_mdp3::number_of_orders number_of_orders;
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
        sbe_mdp3::high_limit_price high_limit_price;
        sbe_mdp3::low_limit_price low_limit_price;
        sbe_mdp3::max_price_variation max_price_variation;
    };

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header) + sizeof(fields_type)), {}};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(fields_type));
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
static_assert(offsetof(snapshot_full_refresh::fields_type, high_limit_price) == 35, "unexpected offset of snapshot_full_refresh::fields_type::high_limit_price");
static_assert(offsetof(snapshot_full_refresh::fields_type, low_limit_price) == 43, "unexpected offset of snapshot_full_refresh::fields_type::low_limit_price");
static_assert(offsetof(snapshot_full_refresh::fields_type, max_price_variation) == 51, "unexpected offset of snapshot_full_refresh::fields_type::max_price_variation");
static_assert(sizeof(snapshot_full_refresh::fields_type) == 59, "unexpected sizeof snapshot_full_refresh::fields_type");

#pragma pack(pop)
}

#include "details/SnapshotFullRefreshWriter.hpp"
#include "details/SnapshotFullRefreshReader.hpp"
