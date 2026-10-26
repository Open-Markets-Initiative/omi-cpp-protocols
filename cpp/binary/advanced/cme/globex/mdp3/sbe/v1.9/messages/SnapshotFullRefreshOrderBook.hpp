#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/TotNumReports.hpp"
#include "../types/SecurityId.hpp"
#include "../types/NoChunks.hpp"
#include "../types/CurrentChunk.hpp"
#include "../types/TransactTime.hpp"
#include "../types/OrderId.hpp"
#include "../types/MdOrderPriority.hpp"
#include "../types/MdEntryPxEx.hpp"
#include "../types/MdDisplayQty.hpp"
#include "../types/MdEntryTypeBook.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

#pragma pack(push, 1)
struct snapshot_full_refresh_order_book_groups_entry {
    sbe_mdp3::order_id order_id;
    sbe_mdp3::md_order_priority md_order_priority;
    sbe_mdp3::md_entry_px_ex md_entry_px_ex;
    sbe_mdp3::md_display_qty md_display_qty;
    sbe_mdp3::md_entry_type_book md_entry_type_book;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Snapshot Full Refresh Order Book
struct snapshot_full_refresh_order_book {

    struct fields_type {
        sbe_mdp3::last_msg_seq_num_processed last_msg_seq_num_processed;
        sbe_mdp3::tot_num_reports tot_num_reports;
        sbe_mdp3::security_id security_id;
        sbe_mdp3::no_chunks no_chunks;
        sbe_mdp3::current_chunk current_chunk;
        sbe_mdp3::transact_time transact_time;
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
    sbe_group_iterator<snapshot_full_refresh_order_book_groups_entry, group_size> snapshot_full_refresh_order_book_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static snapshot_full_refresh_order_book* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_full_refresh_order_book*>(buffer);
    }

    // parse method const
    static const snapshot_full_refresh_order_book* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_full_refresh_order_book*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_full_refresh_order_book::fields_type, last_msg_seq_num_processed) == 0, "unexpected offset of snapshot_full_refresh_order_book::fields_type::last_msg_seq_num_processed");
static_assert(offsetof(snapshot_full_refresh_order_book::fields_type, tot_num_reports) == 4, "unexpected offset of snapshot_full_refresh_order_book::fields_type::tot_num_reports");
static_assert(offsetof(snapshot_full_refresh_order_book::fields_type, security_id) == 8, "unexpected offset of snapshot_full_refresh_order_book::fields_type::security_id");
static_assert(offsetof(snapshot_full_refresh_order_book::fields_type, no_chunks) == 12, "unexpected offset of snapshot_full_refresh_order_book::fields_type::no_chunks");
static_assert(offsetof(snapshot_full_refresh_order_book::fields_type, current_chunk) == 16, "unexpected offset of snapshot_full_refresh_order_book::fields_type::current_chunk");
static_assert(offsetof(snapshot_full_refresh_order_book::fields_type, transact_time) == 20, "unexpected offset of snapshot_full_refresh_order_book::fields_type::transact_time");
static_assert(sizeof(snapshot_full_refresh_order_book::fields_type) == 28, "unexpected sizeof snapshot_full_refresh_order_book::fields_type");

#pragma pack(pop)
}

#include "details/SnapshotFullRefreshOrderBookWriter.hpp"
#include "details/SnapshotFullRefreshOrderBookReader.hpp"
