#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/OpenEligibilityStatus.hpp"
#include "../types/MinimumAllowablePrice.hpp"
#include "../types/MaximumAllowablePrice.hpp"
#include "../types/NearExecutionPrice.hpp"
#include "../types/NearExecutionTime.hpp"
#include "../types/LowerPriceRangeCollar.hpp"
#include "../types/UpperPriceRangeCollar.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Direct Listing With Capital Raise Price Discovery Message
struct direct_listing_with_capital_raise_price_discovery_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::stock stock;
        itch_totalview::open_eligibility_status open_eligibility_status;
        itch_totalview::minimum_allowable_price minimum_allowable_price;
        itch_totalview::maximum_allowable_price maximum_allowable_price;
        itch_totalview::near_execution_price near_execution_price;
        itch_totalview::near_execution_time near_execution_time;
        itch_totalview::lower_price_range_collar lower_price_range_collar;
        itch_totalview::upper_price_range_collar upper_price_range_collar;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::direct_listing_with_capital_raise_price_discovery_message};

    fields_type fields;

    // parse method
    static direct_listing_with_capital_raise_price_discovery_message* parse(std::byte* buffer) {
        return reinterpret_cast<direct_listing_with_capital_raise_price_discovery_message*>(buffer);
    }

    // parse method const
    static const direct_listing_with_capital_raise_price_discovery_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const direct_listing_with_capital_raise_price_discovery_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(direct_listing_with_capital_raise_price_discovery_message::fields_type, stock_locate) == 0, "unexpected offset of direct_listing_with_capital_raise_price_discovery_message::fields_type::stock_locate");
static_assert(offsetof(direct_listing_with_capital_raise_price_discovery_message::fields_type, tracking_number) == 2, "unexpected offset of direct_listing_with_capital_raise_price_discovery_message::fields_type::tracking_number");
static_assert(offsetof(direct_listing_with_capital_raise_price_discovery_message::fields_type, timestamp) == 4, "unexpected offset of direct_listing_with_capital_raise_price_discovery_message::fields_type::timestamp");
static_assert(offsetof(direct_listing_with_capital_raise_price_discovery_message::fields_type, stock) == 10, "unexpected offset of direct_listing_with_capital_raise_price_discovery_message::fields_type::stock");
static_assert(offsetof(direct_listing_with_capital_raise_price_discovery_message::fields_type, open_eligibility_status) == 18, "unexpected offset of direct_listing_with_capital_raise_price_discovery_message::fields_type::open_eligibility_status");
static_assert(offsetof(direct_listing_with_capital_raise_price_discovery_message::fields_type, minimum_allowable_price) == 19, "unexpected offset of direct_listing_with_capital_raise_price_discovery_message::fields_type::minimum_allowable_price");
static_assert(offsetof(direct_listing_with_capital_raise_price_discovery_message::fields_type, maximum_allowable_price) == 23, "unexpected offset of direct_listing_with_capital_raise_price_discovery_message::fields_type::maximum_allowable_price");
static_assert(offsetof(direct_listing_with_capital_raise_price_discovery_message::fields_type, near_execution_price) == 27, "unexpected offset of direct_listing_with_capital_raise_price_discovery_message::fields_type::near_execution_price");
static_assert(offsetof(direct_listing_with_capital_raise_price_discovery_message::fields_type, near_execution_time) == 31, "unexpected offset of direct_listing_with_capital_raise_price_discovery_message::fields_type::near_execution_time");
static_assert(offsetof(direct_listing_with_capital_raise_price_discovery_message::fields_type, lower_price_range_collar) == 39, "unexpected offset of direct_listing_with_capital_raise_price_discovery_message::fields_type::lower_price_range_collar");
static_assert(offsetof(direct_listing_with_capital_raise_price_discovery_message::fields_type, upper_price_range_collar) == 43, "unexpected offset of direct_listing_with_capital_raise_price_discovery_message::fields_type::upper_price_range_collar");
static_assert(sizeof(direct_listing_with_capital_raise_price_discovery_message::fields_type) == 47, "unexpected sizeof direct_listing_with_capital_raise_price_discovery_message::fields_type");
static_assert(sizeof(direct_listing_with_capital_raise_price_discovery_message) == sizeof(message_header) + 47, "unexpected sizeof direct_listing_with_capital_raise_price_discovery_message");

#pragma pack(pop)
}
