#pragma once

#include <cstddef>
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

#pragma pack(push, 1)

struct snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups {

    sbe_binaryumdf::group_size_encoding group_size_encoding;

    // parse method
    static snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups*>(buffer);
    }

    // parse method const
    static const snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups*>(buffer);
    }
};

#pragma pack(pop)
}
