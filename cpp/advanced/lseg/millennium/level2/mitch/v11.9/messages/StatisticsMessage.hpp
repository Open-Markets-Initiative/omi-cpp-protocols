#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanosecond.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/StatisticType.hpp"
#include "../types/Price.hpp"
#include "../types/OpenClosePriceIndicator.hpp"
#include "../types/StatisticsReserved.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// Statistics Message
struct statistics_message {

    struct fields_type {
        mitch_level2::nanosecond nanosecond;
        mitch_level2::instrument_id instrument_id;
        mitch_level2::reserved_a reserved_a;
        mitch_level2::reserved_b reserved_b;
        mitch_level2::statistic_type statistic_type;
        mitch_level2::price price;
        mitch_level2::open_close_price_indicator open_close_price_indicator;
        mitch_level2::statistics_reserved statistics_reserved;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::statistics_message};

    fields_type fields;

    // parse method
    static statistics_message* parse(std::byte* buffer) {
        return reinterpret_cast<statistics_message*>(buffer);
    }

    // parse method const
    static const statistics_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const statistics_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(statistics_message::fields_type, nanosecond) == 0, "unexpected offset of statistics_message::fields_type::nanosecond");
static_assert(offsetof(statistics_message::fields_type, instrument_id) == 4, "unexpected offset of statistics_message::fields_type::instrument_id");
static_assert(offsetof(statistics_message::fields_type, reserved_a) == 8, "unexpected offset of statistics_message::fields_type::reserved_a");
static_assert(offsetof(statistics_message::fields_type, reserved_b) == 9, "unexpected offset of statistics_message::fields_type::reserved_b");
static_assert(offsetof(statistics_message::fields_type, statistic_type) == 10, "unexpected offset of statistics_message::fields_type::statistic_type");
static_assert(offsetof(statistics_message::fields_type, price) == 11, "unexpected offset of statistics_message::fields_type::price");
static_assert(offsetof(statistics_message::fields_type, open_close_price_indicator) == 19, "unexpected offset of statistics_message::fields_type::open_close_price_indicator");
static_assert(offsetof(statistics_message::fields_type, statistics_reserved) == 20, "unexpected offset of statistics_message::fields_type::statistics_reserved");
static_assert(sizeof(statistics_message::fields_type) == 21, "unexpected sizeof statistics_message::fields_type");
static_assert(sizeof(statistics_message) == sizeof(mitch_level2::message_header) + 21, "unexpected sizeof statistics_message");

#pragma pack(pop)
}
