#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/CumulativeVolume.hpp"
#include "../types/OpenInterest.hpp"
#include "../types/VoiTradeDate.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Volume And Open Interest Message
struct volume_and_open_interest_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::cumulative_volume cumulative_volume;
        itch_ntp::open_interest open_interest;
        itch_ntp::voi_trade_date voi_trade_date;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::volume_and_open_interest_message};

    fields_type fields;

    // parse method
    static volume_and_open_interest_message* parse(std::byte* buffer) {
        return reinterpret_cast<volume_and_open_interest_message*>(buffer);
    }

    // parse method const
    static const volume_and_open_interest_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const volume_and_open_interest_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(volume_and_open_interest_message::fields_type, nanoseconds) == 0, "unexpected offset of volume_and_open_interest_message::fields_type::nanoseconds");
static_assert(offsetof(volume_and_open_interest_message::fields_type, trade_date) == 4, "unexpected offset of volume_and_open_interest_message::fields_type::trade_date");
static_assert(offsetof(volume_and_open_interest_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of volume_and_open_interest_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(volume_and_open_interest_message::fields_type, cumulative_volume) == 10, "unexpected offset of volume_and_open_interest_message::fields_type::cumulative_volume");
static_assert(offsetof(volume_and_open_interest_message::fields_type, open_interest) == 18, "unexpected offset of volume_and_open_interest_message::fields_type::open_interest");
static_assert(offsetof(volume_and_open_interest_message::fields_type, voi_trade_date) == 26, "unexpected offset of volume_and_open_interest_message::fields_type::voi_trade_date");
static_assert(sizeof(volume_and_open_interest_message::fields_type) == 28, "unexpected sizeof volume_and_open_interest_message::fields_type");
static_assert(sizeof(volume_and_open_interest_message) == sizeof(itch_ntp::message_header) + 28, "unexpected sizeof volume_and_open_interest_message");

#pragma pack(pop)
}
