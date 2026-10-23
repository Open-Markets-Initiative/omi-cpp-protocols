#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/CombinationOrderbookId.hpp"
#include "../types/LegOrderbookId.hpp"
#include "../types/LegSide.hpp"
#include "../types/LegRatio.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

namespace itch_geniuminet = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

#pragma pack(push, 1)

// Combination Orderbook Leg
struct combination_orderbook_leg {

    struct fields_type {
        itch_geniuminet::nanoseconds nanoseconds;
        itch_geniuminet::combination_orderbook_id combination_orderbook_id;
        itch_geniuminet::leg_orderbook_id leg_orderbook_id;
        itch_geniuminet::leg_side leg_side;
        itch_geniuminet::leg_ratio leg_ratio;
    };

    itch_geniuminet::message_header header = {std::uint16_t(sizeof(itch_geniuminet::message_header) + sizeof(fields_type) - 2), message_type::enum_type::combination_orderbook_leg};

    fields_type fields;

    // parse method
    static combination_orderbook_leg* parse(std::byte* buffer) {
        return reinterpret_cast<combination_orderbook_leg*>(buffer);
    }

    // parse method const
    static const combination_orderbook_leg* parse(const std::byte* buffer) {
        return reinterpret_cast<const combination_orderbook_leg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(combination_orderbook_leg::fields_type, nanoseconds) == 0, "unexpected offset of combination_orderbook_leg::fields_type::nanoseconds");
static_assert(offsetof(combination_orderbook_leg::fields_type, combination_orderbook_id) == 4, "unexpected offset of combination_orderbook_leg::fields_type::combination_orderbook_id");
static_assert(offsetof(combination_orderbook_leg::fields_type, leg_orderbook_id) == 8, "unexpected offset of combination_orderbook_leg::fields_type::leg_orderbook_id");
static_assert(offsetof(combination_orderbook_leg::fields_type, leg_side) == 12, "unexpected offset of combination_orderbook_leg::fields_type::leg_side");
static_assert(offsetof(combination_orderbook_leg::fields_type, leg_ratio) == 13, "unexpected offset of combination_orderbook_leg::fields_type::leg_ratio");
static_assert(sizeof(combination_orderbook_leg::fields_type) == 17, "unexpected sizeof combination_orderbook_leg::fields_type");
static_assert(sizeof(combination_orderbook_leg) == sizeof(itch_geniuminet::message_header) + 17, "unexpected sizeof combination_orderbook_leg");

#pragma pack(pop)
}
