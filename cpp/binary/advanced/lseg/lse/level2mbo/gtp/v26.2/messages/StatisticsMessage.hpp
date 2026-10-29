#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Instrument.hpp"
#include "../types/SourceVenue.hpp"
#include "../types/Volume.hpp"
#include "../types/VolumeOnBookOnly.hpp"
#include "../types/Vwap.hpp"
#include "../types/VwapOnBookOnly.hpp"
#include "../types/NumberOfTrades.hpp"
#include "../types/NumberOfTradesOnBookOnly.hpp"
#include "../types/Turnover.hpp"
#include "../types/TurnoverOnBookOnly.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

namespace gtp_level2mbo = ::lseg::lse::level2mbo::gtp::v26_2;

#pragma pack(push, 1)

// Statistics Message
struct statistics_message {

    struct fields_type {
        gtp_level2mbo::timestamp timestamp;
        gtp_level2mbo::instrument instrument;
        gtp_level2mbo::source_venue source_venue;
        gtp_level2mbo::volume volume;
        gtp_level2mbo::volume_on_book_only volume_on_book_only;
        gtp_level2mbo::vwap vwap;
        gtp_level2mbo::vwap_on_book_only vwap_on_book_only;
        gtp_level2mbo::number_of_trades number_of_trades;
        gtp_level2mbo::number_of_trades_on_book_only number_of_trades_on_book_only;
        gtp_level2mbo::turnover turnover;
        gtp_level2mbo::turnover_on_book_only turnover_on_book_only;
    };

    gtp_level2mbo::message_header header = {std::uint16_t(sizeof(gtp_level2mbo::message_header) + sizeof(fields_type)), message_type::enum_type::statistics_message};

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
static_assert(offsetof(statistics_message::fields_type, timestamp) == 0, "unexpected offset of statistics_message::fields_type::timestamp");
static_assert(offsetof(statistics_message::fields_type, instrument) == 8, "unexpected offset of statistics_message::fields_type::instrument");
static_assert(offsetof(statistics_message::fields_type, source_venue) == 16, "unexpected offset of statistics_message::fields_type::source_venue");
static_assert(offsetof(statistics_message::fields_type, volume) == 18, "unexpected offset of statistics_message::fields_type::volume");
static_assert(offsetof(statistics_message::fields_type, volume_on_book_only) == 26, "unexpected offset of statistics_message::fields_type::volume_on_book_only");
static_assert(offsetof(statistics_message::fields_type, vwap) == 34, "unexpected offset of statistics_message::fields_type::vwap");
static_assert(offsetof(statistics_message::fields_type, vwap_on_book_only) == 42, "unexpected offset of statistics_message::fields_type::vwap_on_book_only");
static_assert(offsetof(statistics_message::fields_type, number_of_trades) == 50, "unexpected offset of statistics_message::fields_type::number_of_trades");
static_assert(offsetof(statistics_message::fields_type, number_of_trades_on_book_only) == 54, "unexpected offset of statistics_message::fields_type::number_of_trades_on_book_only");
static_assert(offsetof(statistics_message::fields_type, turnover) == 58, "unexpected offset of statistics_message::fields_type::turnover");
static_assert(offsetof(statistics_message::fields_type, turnover_on_book_only) == 66, "unexpected offset of statistics_message::fields_type::turnover_on_book_only");
static_assert(sizeof(statistics_message::fields_type) == 74, "unexpected sizeof statistics_message::fields_type");
static_assert(sizeof(statistics_message) == sizeof(gtp_level2mbo::message_header) + 74, "unexpected sizeof statistics_message");

#pragma pack(pop)
}
