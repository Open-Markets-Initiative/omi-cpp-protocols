#pragma once

#include "../types/Timestamp.hpp"
#include "../types/Instrument.hpp"
#include "../types/Isin.hpp"
#include "../bitfields/AllowedBookTypes.hpp"
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
#include "../structs/MessageHeader.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

#pragma pack(push, 1)

// Used to disseminate a common and limited set of data for all configured instrument types, except strategy instruments, on the real-time channels.
struct InstrumentDirectoryMessage {

    Timestamp timestamp;
    Instrument instrument;
    Isin isin;
    AllowedBookTypes allowed_book_types;
    SourceVenue source_venue;
    VenueInstrumentId venue_instrument_id;
    TickId tick_id;
    Reserved8 reserved_8;
    DynamicCircuitBreakerTolerances dynamic_circuit_breaker_tolerances;
    StaticCircuitBreakerTolerances static_circuit_breaker_tolerances;
    Segment segment;
    Reserved12 reserved_12;
    Reserved11 reserved_11;
    Currency currency;
    PartitionId partition_id;
    Reserved4 reserved_4;
    AverageDailyTurnoverAdt average_daily_turnover_adt;
    SecondReserved8 second_reserved_8;
    Reserved1 reserved_1;
    ThirdReserved8 third_reserved_8;
    FourthReserved8 fourth_reserved_8;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x70;

    // parse method
    static InstrumentDirectoryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<InstrumentDirectoryMessage*>(buffer);
    }

    // parse method const
    static const InstrumentDirectoryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrumentDirectoryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const InstrumentDirectoryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const InstrumentDirectoryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
