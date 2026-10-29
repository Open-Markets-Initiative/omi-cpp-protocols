#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/StrategyType.hpp"
#include "../types/Source.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/NumberOfLegs.hpp"
#include "../types/OptionId.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/LegId.hpp"
#include "../types/ExpirationYear.hpp"
#include "../types/ExpirationMonth.hpp"
#include "../types/ExpirationDay.hpp"
#include "../types/ExplicitStrikePrice.hpp"
#include "../types/OptionType.hpp"
#include "../types/Side.hpp"
#include "../types/LegRatio.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

namespace itch_topcomboquotefeed = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

#pragma pack(push, 1)
struct complex_strategy_directory_message_leg_information_entry {
    itch_topcomboquotefeed::option_id option_id;
    itch_topcomboquotefeed::security_symbol security_symbol;
    itch_topcomboquotefeed::leg_id leg_id;
    itch_topcomboquotefeed::expiration_year expiration_year;
    itch_topcomboquotefeed::expiration_month expiration_month;
    itch_topcomboquotefeed::expiration_day expiration_day;
    itch_topcomboquotefeed::explicit_strike_price explicit_strike_price;
    itch_topcomboquotefeed::option_type option_type;
    itch_topcomboquotefeed::side side;
    itch_topcomboquotefeed::leg_ratio leg_ratio;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Complex Strategy Directory Message
struct complex_strategy_directory_message {

    struct fields_type {
        itch_topcomboquotefeed::timestamp timestamp;
        itch_topcomboquotefeed::strategy_id strategy_id;
        itch_topcomboquotefeed::strategy_type strategy_type;
        itch_topcomboquotefeed::source source;
        itch_topcomboquotefeed::underlying_symbol underlying_symbol;
        itch_topcomboquotefeed::number_of_legs number_of_legs;
    };

    itch_topcomboquotefeed::message_header header = {std::uint16_t(sizeof(itch_topcomboquotefeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::complex_strategy_directory_message};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(itch_topcomboquotefeed::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_length.get().value();
        return (sz + 2) == sizeof(itch_topcomboquotefeed::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + ((sz + 2) - sizeof(itch_topcomboquotefeed::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    external_count_iterator<complex_strategy_directory_message_leg_information_entry> leg_information() const {
        return { tail_begin(), fields.number_of_legs.get().value(), tail_end() };
    }


    // parse method
    static complex_strategy_directory_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_strategy_directory_message*>(buffer);
    }

    // parse method const
    static const complex_strategy_directory_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_strategy_directory_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_strategy_directory_message::fields_type, timestamp) == 0, "unexpected offset of complex_strategy_directory_message::fields_type::timestamp");
static_assert(offsetof(complex_strategy_directory_message::fields_type, strategy_id) == 6, "unexpected offset of complex_strategy_directory_message::fields_type::strategy_id");
static_assert(offsetof(complex_strategy_directory_message::fields_type, strategy_type) == 10, "unexpected offset of complex_strategy_directory_message::fields_type::strategy_type");
static_assert(offsetof(complex_strategy_directory_message::fields_type, source) == 11, "unexpected offset of complex_strategy_directory_message::fields_type::source");
static_assert(offsetof(complex_strategy_directory_message::fields_type, underlying_symbol) == 12, "unexpected offset of complex_strategy_directory_message::fields_type::underlying_symbol");
static_assert(offsetof(complex_strategy_directory_message::fields_type, number_of_legs) == 25, "unexpected offset of complex_strategy_directory_message::fields_type::number_of_legs");
static_assert(sizeof(complex_strategy_directory_message::fields_type) == 26, "unexpected sizeof complex_strategy_directory_message::fields_type");

#pragma pack(pop)
}

#include "details/ComplexStrategyDirectoryMessageWriter.hpp"
#include "details/ComplexStrategyDirectoryMessageReader.hpp"
