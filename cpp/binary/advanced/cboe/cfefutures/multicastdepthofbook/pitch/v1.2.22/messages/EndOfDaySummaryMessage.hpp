#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/TradeDate.hpp"
#include "../types/OpenInterest.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/OpenPrice.hpp"
#include "../types/ClosePrice.hpp"
#include "../types/TotalVolume.hpp"
#include "../types/BlockVolume.hpp"
#include "../types/EcrpVolume.hpp"
#include "../types/SummaryFlags.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

#pragma pack(push, 1)

// End Of Day Summary Message
struct end_of_day_summary_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::symbol symbol;
        pitch_multicastdepthofbook::trade_date trade_date;
        pitch_multicastdepthofbook::open_interest open_interest;
        pitch_multicastdepthofbook::high_price high_price;
        pitch_multicastdepthofbook::low_price low_price;
        pitch_multicastdepthofbook::open_price open_price;
        pitch_multicastdepthofbook::close_price close_price;
        pitch_multicastdepthofbook::total_volume total_volume;
        pitch_multicastdepthofbook::block_volume block_volume;
        pitch_multicastdepthofbook::ecrp_volume ecrp_volume;
        pitch_multicastdepthofbook::summary_flags summary_flags;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::end_of_day_summary_message};

    fields_type fields;

    // parse method
    static end_of_day_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<end_of_day_summary_message*>(buffer);
    }

    // parse method const
    static const end_of_day_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const end_of_day_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(end_of_day_summary_message::fields_type, time_offset) == 0, "unexpected offset of end_of_day_summary_message::fields_type::time_offset");
static_assert(offsetof(end_of_day_summary_message::fields_type, symbol) == 4, "unexpected offset of end_of_day_summary_message::fields_type::symbol");
static_assert(offsetof(end_of_day_summary_message::fields_type, trade_date) == 10, "unexpected offset of end_of_day_summary_message::fields_type::trade_date");
static_assert(offsetof(end_of_day_summary_message::fields_type, open_interest) == 14, "unexpected offset of end_of_day_summary_message::fields_type::open_interest");
static_assert(offsetof(end_of_day_summary_message::fields_type, high_price) == 18, "unexpected offset of end_of_day_summary_message::fields_type::high_price");
static_assert(offsetof(end_of_day_summary_message::fields_type, low_price) == 26, "unexpected offset of end_of_day_summary_message::fields_type::low_price");
static_assert(offsetof(end_of_day_summary_message::fields_type, open_price) == 34, "unexpected offset of end_of_day_summary_message::fields_type::open_price");
static_assert(offsetof(end_of_day_summary_message::fields_type, close_price) == 42, "unexpected offset of end_of_day_summary_message::fields_type::close_price");
static_assert(offsetof(end_of_day_summary_message::fields_type, total_volume) == 50, "unexpected offset of end_of_day_summary_message::fields_type::total_volume");
static_assert(offsetof(end_of_day_summary_message::fields_type, block_volume) == 54, "unexpected offset of end_of_day_summary_message::fields_type::block_volume");
static_assert(offsetof(end_of_day_summary_message::fields_type, ecrp_volume) == 58, "unexpected offset of end_of_day_summary_message::fields_type::ecrp_volume");
static_assert(offsetof(end_of_day_summary_message::fields_type, summary_flags) == 62, "unexpected offset of end_of_day_summary_message::fields_type::summary_flags");
static_assert(sizeof(end_of_day_summary_message::fields_type) == 63, "unexpected sizeof end_of_day_summary_message::fields_type");
static_assert(sizeof(end_of_day_summary_message) == sizeof(pitch_multicastdepthofbook::message_header) + 63, "unexpected sizeof end_of_day_summary_message");

#pragma pack(pop)
}
