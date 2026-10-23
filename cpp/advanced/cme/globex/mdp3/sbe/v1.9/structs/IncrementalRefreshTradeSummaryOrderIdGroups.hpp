#pragma once

#include <cstddef>
#include "../structs/GroupSize8Byte.hpp"

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

#pragma pack(push, 1)

struct incremental_refresh_trade_summary_order_id_groups {

    sbe_mdp3::group_size_8_byte group_size_8_byte;

    // parse method
    static incremental_refresh_trade_summary_order_id_groups* parse(std::byte* buffer) {
        return reinterpret_cast<incremental_refresh_trade_summary_order_id_groups*>(buffer);
    }

    // parse method const
    static const incremental_refresh_trade_summary_order_id_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const incremental_refresh_trade_summary_order_id_groups*>(buffer);
    }
};

#pragma pack(pop)
}
