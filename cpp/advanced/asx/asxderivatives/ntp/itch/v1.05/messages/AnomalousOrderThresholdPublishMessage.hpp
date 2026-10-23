#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/AotPrice.hpp"
#include "../types/AotUpperPrice.hpp"
#include "../types/AotLowerPrice.hpp"
#include "../types/EtrPrice.hpp"
#include "../types/EtrUpperPrice.hpp"
#include "../types/EtrLowerPrice.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Anomalous Order Threshold Publish Message
struct anomalous_order_threshold_publish_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::aot_price aot_price;
        itch_ntp::aot_upper_price aot_upper_price;
        itch_ntp::aot_lower_price aot_lower_price;
        itch_ntp::etr_price etr_price;
        itch_ntp::etr_upper_price etr_upper_price;
        itch_ntp::etr_lower_price etr_lower_price;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::anomalous_order_threshold_publish_message};

    fields_type fields;

    // parse method
    static anomalous_order_threshold_publish_message* parse(std::byte* buffer) {
        return reinterpret_cast<anomalous_order_threshold_publish_message*>(buffer);
    }

    // parse method const
    static const anomalous_order_threshold_publish_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const anomalous_order_threshold_publish_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(anomalous_order_threshold_publish_message::fields_type, nanoseconds) == 0, "unexpected offset of anomalous_order_threshold_publish_message::fields_type::nanoseconds");
static_assert(offsetof(anomalous_order_threshold_publish_message::fields_type, trade_date) == 4, "unexpected offset of anomalous_order_threshold_publish_message::fields_type::trade_date");
static_assert(offsetof(anomalous_order_threshold_publish_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of anomalous_order_threshold_publish_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(anomalous_order_threshold_publish_message::fields_type, aot_price) == 10, "unexpected offset of anomalous_order_threshold_publish_message::fields_type::aot_price");
static_assert(offsetof(anomalous_order_threshold_publish_message::fields_type, aot_upper_price) == 18, "unexpected offset of anomalous_order_threshold_publish_message::fields_type::aot_upper_price");
static_assert(offsetof(anomalous_order_threshold_publish_message::fields_type, aot_lower_price) == 26, "unexpected offset of anomalous_order_threshold_publish_message::fields_type::aot_lower_price");
static_assert(offsetof(anomalous_order_threshold_publish_message::fields_type, etr_price) == 34, "unexpected offset of anomalous_order_threshold_publish_message::fields_type::etr_price");
static_assert(offsetof(anomalous_order_threshold_publish_message::fields_type, etr_upper_price) == 42, "unexpected offset of anomalous_order_threshold_publish_message::fields_type::etr_upper_price");
static_assert(offsetof(anomalous_order_threshold_publish_message::fields_type, etr_lower_price) == 50, "unexpected offset of anomalous_order_threshold_publish_message::fields_type::etr_lower_price");
static_assert(sizeof(anomalous_order_threshold_publish_message::fields_type) == 58, "unexpected sizeof anomalous_order_threshold_publish_message::fields_type");
static_assert(sizeof(anomalous_order_threshold_publish_message) == sizeof(itch_ntp::message_header) + 58, "unexpected sizeof anomalous_order_threshold_publish_message");

#pragma pack(pop)
}
