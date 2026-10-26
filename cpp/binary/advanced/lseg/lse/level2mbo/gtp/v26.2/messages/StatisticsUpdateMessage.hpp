#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Instrument.hpp"
#include "../types/SourceVenue.hpp"
#include "../types/StatisticType.hpp"
#include "../types/StatisticPrice.hpp"
#include "../types/StatisticSize.hpp"
#include "../types/AuctionType.hpp"
#include "../types/ImbalanceQuantity.hpp"
#include "../types/AuctionInfo.hpp"
#include "../types/OpeningClosingPriceIndicator.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

namespace gtp_level2mbo = ::lseg::lse::level2mbo::gtp::v26_2;

#pragma pack(push, 1)

// Statistics Update Message
struct statistics_update_message {

    struct fields_type {
        gtp_level2mbo::timestamp timestamp;
        gtp_level2mbo::instrument instrument;
        gtp_level2mbo::source_venue source_venue;
        gtp_level2mbo::statistic_type statistic_type;
        gtp_level2mbo::statistic_price statistic_price;
        gtp_level2mbo::statistic_size statistic_size;
        gtp_level2mbo::auction_type auction_type;
        gtp_level2mbo::imbalance_quantity imbalance_quantity;
        gtp_level2mbo::auction_info auction_info;
        gtp_level2mbo::opening_closing_price_indicator opening_closing_price_indicator;
    };

    gtp_level2mbo::message_header header = {std::uint16_t(sizeof(gtp_level2mbo::message_header) + sizeof(fields_type)), message_type::enum_type::statistics_update_message};

    fields_type fields;

    // parse method
    static statistics_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<statistics_update_message*>(buffer);
    }

    // parse method const
    static const statistics_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const statistics_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(statistics_update_message::fields_type, timestamp) == 0, "unexpected offset of statistics_update_message::fields_type::timestamp");
static_assert(offsetof(statistics_update_message::fields_type, instrument) == 8, "unexpected offset of statistics_update_message::fields_type::instrument");
static_assert(offsetof(statistics_update_message::fields_type, source_venue) == 16, "unexpected offset of statistics_update_message::fields_type::source_venue");
static_assert(offsetof(statistics_update_message::fields_type, statistic_type) == 18, "unexpected offset of statistics_update_message::fields_type::statistic_type");
static_assert(offsetof(statistics_update_message::fields_type, statistic_price) == 20, "unexpected offset of statistics_update_message::fields_type::statistic_price");
static_assert(offsetof(statistics_update_message::fields_type, statistic_size) == 28, "unexpected offset of statistics_update_message::fields_type::statistic_size");
static_assert(offsetof(statistics_update_message::fields_type, auction_type) == 36, "unexpected offset of statistics_update_message::fields_type::auction_type");
static_assert(offsetof(statistics_update_message::fields_type, imbalance_quantity) == 37, "unexpected offset of statistics_update_message::fields_type::imbalance_quantity");
static_assert(offsetof(statistics_update_message::fields_type, auction_info) == 45, "unexpected offset of statistics_update_message::fields_type::auction_info");
static_assert(offsetof(statistics_update_message::fields_type, opening_closing_price_indicator) == 46, "unexpected offset of statistics_update_message::fields_type::opening_closing_price_indicator");
static_assert(sizeof(statistics_update_message::fields_type) == 47, "unexpected sizeof statistics_update_message::fields_type");
static_assert(sizeof(statistics_update_message) == sizeof(gtp_level2mbo::message_header) + 47, "unexpected sizeof statistics_update_message");

#pragma pack(pop)
}
