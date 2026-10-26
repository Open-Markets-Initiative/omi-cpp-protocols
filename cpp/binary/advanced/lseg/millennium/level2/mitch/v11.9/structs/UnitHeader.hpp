#pragma once

#include <cstddef>
#include "../types/Length.hpp"
#include "../types/MessageCount.hpp"
#include "../types/MarketDataGroup.hpp"
#include "../types/SequenceNumber.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

struct unit_header {

    mitch_level2::length length;
    mitch_level2::message_count message_count;
    mitch_level2::market_data_group market_data_group;
    mitch_level2::sequence_number sequence_number;

    // parse method
    static unit_header* parse(std::byte* buffer) {
        return reinterpret_cast<unit_header*>(buffer);
    }

    // parse method const
    static const unit_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const unit_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(unit_header, length) == 0, "unexpected offset of unit_header::length");
static_assert(offsetof(unit_header, message_count) == 2, "unexpected offset of unit_header::message_count");
static_assert(offsetof(unit_header, market_data_group) == 3, "unexpected offset of unit_header::market_data_group");
static_assert(offsetof(unit_header, sequence_number) == 4, "unexpected offset of unit_header::sequence_number");
static_assert(sizeof(unit_header) == 8, "unexpected sizeof unit_header");

#pragma pack(pop)
}
