#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Instrument.hpp"
#include "../types/Isin.hpp"
#include "../types/AllowedBookTypes.hpp"
#include "../types/SourceVenue.hpp"
#include "../types/VenueInstrumentId.hpp"
#include "../types/TickId.hpp"
#include "../types/Reserved8.hpp"
#include "../types/DynamicCircuitBreakerTolerances.hpp"
#include "../types/StaticCircuitBreakerTolerances.hpp"
#include "../types/Segment.hpp"
#include "../types/Reserved12.hpp"
#include "../types/Reserved11.hpp"
#include "../types/Currency.hpp"
#include "../types/PartitionId.hpp"
#include "../types/Reserved4.hpp"
#include "../types/AverageDailyTurnoverAdt.hpp"
#include "../types/SecondReserved8.hpp"
#include "../types/Reserved1.hpp"
#include "../types/ThirdReserved8.hpp"
#include "../types/FourthReserved8.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

namespace gtp_level2mbo = ::lseg::lse::level2mbo::gtp::v26_2;

#pragma pack(push, 1)

// Instrument Directory Message
struct instrument_directory_message {

    struct fields_type {
        gtp_level2mbo::timestamp timestamp;
        gtp_level2mbo::instrument instrument;
        gtp_level2mbo::isin isin;
        gtp_level2mbo::allowed_book_types allowed_book_types;
        gtp_level2mbo::source_venue source_venue;
        gtp_level2mbo::venue_instrument_id venue_instrument_id;
        gtp_level2mbo::tick_id tick_id;
        gtp_level2mbo::reserved_8 reserved_8;
        gtp_level2mbo::dynamic_circuit_breaker_tolerances dynamic_circuit_breaker_tolerances;
        gtp_level2mbo::static_circuit_breaker_tolerances static_circuit_breaker_tolerances;
        gtp_level2mbo::segment segment;
        gtp_level2mbo::reserved_12 reserved_12;
        gtp_level2mbo::reserved_11 reserved_11;
        gtp_level2mbo::currency currency;
        gtp_level2mbo::partition_id partition_id;
        gtp_level2mbo::reserved_4 reserved_4;
        gtp_level2mbo::average_daily_turnover_adt average_daily_turnover_adt;
        gtp_level2mbo::second_reserved_8 second_reserved_8;
        gtp_level2mbo::reserved_1 reserved_1;
        gtp_level2mbo::third_reserved_8 third_reserved_8;
        gtp_level2mbo::fourth_reserved_8 fourth_reserved_8;
    };

    gtp_level2mbo::message_header header = {std::uint16_t(sizeof(gtp_level2mbo::message_header) + sizeof(fields_type)), message_type::enum_type::instrument_directory_message};

    fields_type fields;

    // parse method
    static instrument_directory_message* parse(std::byte* buffer) {
        return reinterpret_cast<instrument_directory_message*>(buffer);
    }

    // parse method const
    static const instrument_directory_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const instrument_directory_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(instrument_directory_message::fields_type, timestamp) == 0, "unexpected offset of instrument_directory_message::fields_type::timestamp");
static_assert(offsetof(instrument_directory_message::fields_type, instrument) == 8, "unexpected offset of instrument_directory_message::fields_type::instrument");
static_assert(offsetof(instrument_directory_message::fields_type, isin) == 16, "unexpected offset of instrument_directory_message::fields_type::isin");
static_assert(offsetof(instrument_directory_message::fields_type, allowed_book_types) == 28, "unexpected offset of instrument_directory_message::fields_type::allowed_book_types");
static_assert(offsetof(instrument_directory_message::fields_type, source_venue) == 29, "unexpected offset of instrument_directory_message::fields_type::source_venue");
static_assert(offsetof(instrument_directory_message::fields_type, venue_instrument_id) == 31, "unexpected offset of instrument_directory_message::fields_type::venue_instrument_id");
static_assert(offsetof(instrument_directory_message::fields_type, tick_id) == 42, "unexpected offset of instrument_directory_message::fields_type::tick_id");
static_assert(offsetof(instrument_directory_message::fields_type, reserved_8) == 44, "unexpected offset of instrument_directory_message::fields_type::reserved_8");
static_assert(offsetof(instrument_directory_message::fields_type, dynamic_circuit_breaker_tolerances) == 52, "unexpected offset of instrument_directory_message::fields_type::dynamic_circuit_breaker_tolerances");
static_assert(offsetof(instrument_directory_message::fields_type, static_circuit_breaker_tolerances) == 60, "unexpected offset of instrument_directory_message::fields_type::static_circuit_breaker_tolerances");
static_assert(offsetof(instrument_directory_message::fields_type, segment) == 68, "unexpected offset of instrument_directory_message::fields_type::segment");
static_assert(offsetof(instrument_directory_message::fields_type, reserved_12) == 74, "unexpected offset of instrument_directory_message::fields_type::reserved_12");
static_assert(offsetof(instrument_directory_message::fields_type, reserved_11) == 86, "unexpected offset of instrument_directory_message::fields_type::reserved_11");
static_assert(offsetof(instrument_directory_message::fields_type, currency) == 97, "unexpected offset of instrument_directory_message::fields_type::currency");
static_assert(offsetof(instrument_directory_message::fields_type, partition_id) == 100, "unexpected offset of instrument_directory_message::fields_type::partition_id");
static_assert(offsetof(instrument_directory_message::fields_type, reserved_4) == 101, "unexpected offset of instrument_directory_message::fields_type::reserved_4");
static_assert(offsetof(instrument_directory_message::fields_type, average_daily_turnover_adt) == 105, "unexpected offset of instrument_directory_message::fields_type::average_daily_turnover_adt");
static_assert(offsetof(instrument_directory_message::fields_type, second_reserved_8) == 113, "unexpected offset of instrument_directory_message::fields_type::second_reserved_8");
static_assert(offsetof(instrument_directory_message::fields_type, reserved_1) == 121, "unexpected offset of instrument_directory_message::fields_type::reserved_1");
static_assert(offsetof(instrument_directory_message::fields_type, third_reserved_8) == 122, "unexpected offset of instrument_directory_message::fields_type::third_reserved_8");
static_assert(offsetof(instrument_directory_message::fields_type, fourth_reserved_8) == 130, "unexpected offset of instrument_directory_message::fields_type::fourth_reserved_8");
static_assert(sizeof(instrument_directory_message::fields_type) == 138, "unexpected sizeof instrument_directory_message::fields_type");
static_assert(sizeof(instrument_directory_message) == sizeof(gtp_level2mbo::message_header) + 138, "unexpected sizeof instrument_directory_message");

#pragma pack(pop)
}
