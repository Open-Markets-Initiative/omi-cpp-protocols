#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/Stock.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/BestBidPrice.hpp"
#include "../types/BestBidSize.hpp"
#include "../types/BestOfferPrice.hpp"
#include "../types/BestOfferSize.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

namespace itch_qbbo = ::nasdaq::nsmequities::qbbo::itch::v2_1;

#pragma pack(push, 1)

// Bbo Quotation Message
struct bbo_quotation_message {

    struct fields_type {
        itch_qbbo::tracking_number tracking_number;
        itch_qbbo::time_stamp time_stamp;
        itch_qbbo::stock stock;
        itch_qbbo::security_class security_class;
        itch_qbbo::best_bid_price best_bid_price;
        itch_qbbo::best_bid_size best_bid_size;
        itch_qbbo::best_offer_price best_offer_price;
        itch_qbbo::best_offer_size best_offer_size;
    };

    itch_qbbo::message_header header = {std::uint16_t(sizeof(itch_qbbo::message_header) + sizeof(fields_type) - 2), message_type::enum_type::bbo_quotation_message};

    fields_type fields;

    // parse method
    static bbo_quotation_message* parse(std::byte* buffer) {
        return reinterpret_cast<bbo_quotation_message*>(buffer);
    }

    // parse method const
    static const bbo_quotation_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const bbo_quotation_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(bbo_quotation_message::fields_type, tracking_number) == 0, "unexpected offset of bbo_quotation_message::fields_type::tracking_number");
static_assert(offsetof(bbo_quotation_message::fields_type, time_stamp) == 2, "unexpected offset of bbo_quotation_message::fields_type::time_stamp");
static_assert(offsetof(bbo_quotation_message::fields_type, stock) == 8, "unexpected offset of bbo_quotation_message::fields_type::stock");
static_assert(offsetof(bbo_quotation_message::fields_type, security_class) == 16, "unexpected offset of bbo_quotation_message::fields_type::security_class");
static_assert(offsetof(bbo_quotation_message::fields_type, best_bid_price) == 17, "unexpected offset of bbo_quotation_message::fields_type::best_bid_price");
static_assert(offsetof(bbo_quotation_message::fields_type, best_bid_size) == 21, "unexpected offset of bbo_quotation_message::fields_type::best_bid_size");
static_assert(offsetof(bbo_quotation_message::fields_type, best_offer_price) == 25, "unexpected offset of bbo_quotation_message::fields_type::best_offer_price");
static_assert(offsetof(bbo_quotation_message::fields_type, best_offer_size) == 29, "unexpected offset of bbo_quotation_message::fields_type::best_offer_size");
static_assert(sizeof(bbo_quotation_message::fields_type) == 33, "unexpected sizeof bbo_quotation_message::fields_type");
static_assert(sizeof(bbo_quotation_message) == sizeof(itch_qbbo::message_header) + 33, "unexpected sizeof bbo_quotation_message");

#pragma pack(pop)
}
