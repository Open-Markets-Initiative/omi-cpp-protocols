#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/IpoQuotationReleaseTime.hpp"
#include "../types/IpoQuotationReleaseQualifier.hpp"
#include "../types/IpoPrice.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Ipo Quoting Period Update
struct ipo_quoting_period_update {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::stock stock;
        itch_totalview::ipo_quotation_release_time ipo_quotation_release_time;
        itch_totalview::ipo_quotation_release_qualifier ipo_quotation_release_qualifier;
        itch_totalview::ipo_price ipo_price;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::ipo_quoting_period_update};

    fields_type fields;

    // parse method
    static ipo_quoting_period_update* parse(std::byte* buffer) {
        return reinterpret_cast<ipo_quoting_period_update*>(buffer);
    }

    // parse method const
    static const ipo_quoting_period_update* parse(const std::byte* buffer) {
        return reinterpret_cast<const ipo_quoting_period_update*>(buffer);
    }

};

// layout verification
static_assert(offsetof(ipo_quoting_period_update::fields_type, stock_locate) == 0, "unexpected offset of ipo_quoting_period_update::fields_type::stock_locate");
static_assert(offsetof(ipo_quoting_period_update::fields_type, tracking_number) == 2, "unexpected offset of ipo_quoting_period_update::fields_type::tracking_number");
static_assert(offsetof(ipo_quoting_period_update::fields_type, timestamp) == 4, "unexpected offset of ipo_quoting_period_update::fields_type::timestamp");
static_assert(offsetof(ipo_quoting_period_update::fields_type, stock) == 10, "unexpected offset of ipo_quoting_period_update::fields_type::stock");
static_assert(offsetof(ipo_quoting_period_update::fields_type, ipo_quotation_release_time) == 18, "unexpected offset of ipo_quoting_period_update::fields_type::ipo_quotation_release_time");
static_assert(offsetof(ipo_quoting_period_update::fields_type, ipo_quotation_release_qualifier) == 22, "unexpected offset of ipo_quoting_period_update::fields_type::ipo_quotation_release_qualifier");
static_assert(offsetof(ipo_quoting_period_update::fields_type, ipo_price) == 23, "unexpected offset of ipo_quoting_period_update::fields_type::ipo_price");
static_assert(sizeof(ipo_quoting_period_update::fields_type) == 27, "unexpected sizeof ipo_quoting_period_update::fields_type");
static_assert(sizeof(ipo_quoting_period_update) == sizeof(message_header) + 27, "unexpected sizeof ipo_quoting_period_update");

#pragma pack(pop)
}
