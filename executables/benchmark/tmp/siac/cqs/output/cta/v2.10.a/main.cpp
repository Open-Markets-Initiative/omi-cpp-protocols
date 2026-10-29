// Siac.Cqs.Output.Cta.v2.10.a benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/siac/cqs/output/cta/v2.10.a.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/tmp/siac/cqs/output/cta/v2.10.a/siac_cqs_output_cta_v2_10_a.hpp"

// Siac Cqs Output Cta 2.10.a: the reading of its packets, through its Template Meta Programming header
namespace siac::cqs::output::cta::v2_10_a {

/////////////////////////////////////////////////////////////////////
// Reading
/////////////////////////////////////////////////////////////////////

namespace tmp {
    // Thrown when the bytes end before what they must hold
    struct short_read : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    inline void require(std::size_t needed, std::size_t available) {
        if (needed > available) {
            throw short_read(std::to_string(needed) + " bytes needed, " + std::to_string(available) + " available");
        }
    }

    // The bytes left for a member when the members after it take some: refused when fewer remain
    inline std::size_t leaving(std::size_t available, std::size_t taken) {
        require(taken, available);
        return available - taken;
    }

    // Hand the handler a value, when it takes one
    template <typename Handler, typename T>
    constexpr void call(Handler& handler, const T& value) {
        if constexpr (requires { handler(value); }) { handler(value); }
    }

    // A type laid over its bytes, handed to the handler
    template <typename T, typename Handler>
    const T& read(const std::byte* data, std::size_t length, Handler& handler) {
        require(T::size, length);
        const auto& value = *reinterpret_cast<const T*>(data);
        call(handler, value);
        return value;
    }

    // A field as a rule reads it: an enum by the code the wire holds, a field by its value, and a
    // bit - which its bitfield answers as a value - as it is
    template <typename T>
    constexpr auto rule(const T& field) noexcept {
        if constexpr (requires { field.raw(); }) { return field.raw(); }
        else if constexpr (requires { field.value(); }) { return field.value(); }
        else { return field; }
    }

    // A field an optional member may hold, read as its type's zero when the member is absent
    template <typename T>
    struct maybe {
        const T* field;

        constexpr auto value() const noexcept {
            using type = decltype(field->value());
            return field != nullptr ? field->value() : type{};
        }

        constexpr auto raw() const noexcept requires requires(const T& held) { held.raw(); } {
            using type = decltype(field->raw());
            return field != nullptr ? field->raw() : type{};
        }

        // a bit of an optional bitfield, nothing when the bitfield is absent
        template <typename Bit>
        constexpr auto get() const noexcept requires requires(const T& held) { held.template get<Bit>(); } {
            using type = std::remove_cvref_t<decltype(field->template get<Bit>())>;
            return field != nullptr ? type{ field->template get<Bit>() } : type{};
        }
    };

    // A type laid over its bytes without handing it on: a frame's length, read before the frame is
    template <typename T>
    const T& at(const std::byte* data) noexcept {
        return *reinterpret_cast<const T*>(data);
    }

    // A type laid over bytes ahead of the walk, at a place every byte before it fixes, which a rule
    // reads before the walk reaches it: a branch's code in the header its messages begin with
    template <typename T>
    const T& ahead(const std::byte* data, std::size_t length, std::size_t at) {
        require(at + T::size, length);
        return *reinterpret_cast<const T*>(data + at);
    }

    // A type laid over its bytes and handed to the handler; what it returns is the bytes it took
    template <typename T, typename Handler>
    std::size_t take(const std::byte* data, std::size_t length, Handler& handler) {
        read<T>(data, length, handler);
        return T::size;
    }

    // The characters before a terminating zero, which the bytes must hold
    inline std::size_t terminated(const std::byte* data, std::size_t length) {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == std::byte{ 0 }) { return index; }
        }
        throw short_read("no terminator in " + std::to_string(length) + " bytes");
    }

    // The bytes of a frame ending on a terminator, the terminator included; none while the bytes
    // do not hold it yet
    inline std::size_t through(const std::byte* data, std::size_t length, std::byte terminator) noexcept {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == terminator) { return index + 1; }
        }
        return 0;
    }

    // Bytes a branch's code selects no message for, handed to the handler when it takes them
    template <typename Handler>
    void unknown(Handler& handler, const std::byte* data, std::size_t length) {
        if constexpr (requires { handler.unknown(data, length); }) { handler.unknown(data, length); }
    }

    // How many a count or a length states: a number, or digits of text
    template <typename T>
        requires std::is_integral_v<T>
    constexpr std::size_t count(T value) noexcept { return static_cast<std::size_t>(value); }

    inline std::size_t count(char digit) {
        if (digit < '0' || digit > '9') { throw short_read(std::string("'") + digit + "' is not a digit"); }
        return static_cast<std::size_t>(digit - '0');
    }

    inline std::size_t count(std::string_view digits) {
        std::size_t value = 0;
        for (const char digit : digits) {
            if (digit == ' ') { continue; }
            if (digit < '0' || digit > '9') { throw short_read("\"" + std::string(digits) + "\" is not a number"); }
            value = value * 10 + static_cast<std::size_t>(digit - '0');
        }
        return value;
    }
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Parsing
/////////////////////////////////////////////////////////////////////

// Special Long Quote Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_special_long_quote_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& special_long_quote_message_section_1_ = tmp::read<special_long_quote_message_section_1>(data + offset, bound - offset, handler); offset += special_long_quote_message_section_1::size;
    if (static_cast<bool>(tmp::rule(special_long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'Q' || tmp::rule(special_long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'S' || tmp::rule(special_long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'W')) {
        offset += tmp::take<national_best_bid_long_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(special_long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'I' || tmp::rule(special_long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'N')) {
        offset += tmp::take<national_best_offer_long_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(special_long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'U')) {
        offset += tmp::take<national_best_bid_and_offer_long_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(special_long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'P' || tmp::rule(special_long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'R' || tmp::rule(special_long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'V')) {
        offset += tmp::take<national_best_bid_short_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(special_long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'H' || tmp::rule(special_long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'M')) {
        offset += tmp::take<national_best_offer_short_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(special_long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'T')) {
        offset += tmp::take<national_best_bid_and_offer_short_appendage>(data + offset, bound - offset, handler);
    }
    return offset;
}

// Short Quote Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_short_quote_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& short_quote_message_section_1_ = tmp::read<short_quote_message_section_1>(data + offset, bound - offset, handler); offset += short_quote_message_section_1::size;
    if (static_cast<bool>(tmp::rule(short_quote_message_section_1_.template get<national_bbo_indicator>()) == 'Q' || tmp::rule(short_quote_message_section_1_.template get<national_bbo_indicator>()) == 'S' || tmp::rule(short_quote_message_section_1_.template get<national_bbo_indicator>()) == 'W')) {
        offset += tmp::take<national_best_bid_long_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(short_quote_message_section_1_.template get<national_bbo_indicator>()) == 'I' || tmp::rule(short_quote_message_section_1_.template get<national_bbo_indicator>()) == 'N')) {
        offset += tmp::take<national_best_offer_long_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(short_quote_message_section_1_.template get<national_bbo_indicator>()) == 'U')) {
        offset += tmp::take<national_best_bid_and_offer_long_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(short_quote_message_section_1_.template get<national_bbo_indicator>()) == 'P' || tmp::rule(short_quote_message_section_1_.template get<national_bbo_indicator>()) == 'R' || tmp::rule(short_quote_message_section_1_.template get<national_bbo_indicator>()) == 'V')) {
        offset += tmp::take<national_best_bid_short_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(short_quote_message_section_1_.template get<national_bbo_indicator>()) == 'H' || tmp::rule(short_quote_message_section_1_.template get<national_bbo_indicator>()) == 'M')) {
        offset += tmp::take<national_best_offer_short_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(short_quote_message_section_1_.template get<national_bbo_indicator>()) == 'T')) {
        offset += tmp::take<national_best_bid_and_offer_short_appendage>(data + offset, bound - offset, handler);
    }
    return offset;
}

// Long Quote Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_long_quote_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& long_quote_message_section_1_ = tmp::read<long_quote_message_section_1>(data + offset, bound - offset, handler); offset += long_quote_message_section_1::size;
    if (static_cast<bool>(tmp::rule(long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'Q' || tmp::rule(long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'S' || tmp::rule(long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'W')) {
        offset += tmp::take<national_best_bid_long_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'I' || tmp::rule(long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'N')) {
        offset += tmp::take<national_best_offer_long_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'U')) {
        offset += tmp::take<national_best_bid_and_offer_long_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'P' || tmp::rule(long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'R' || tmp::rule(long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'V')) {
        offset += tmp::take<national_best_bid_short_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'H' || tmp::rule(long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'M')) {
        offset += tmp::take<national_best_offer_short_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(long_quote_message_section_1_.template get<national_bbo_indicator>()) == 'T')) {
        offset += tmp::take<national_best_bid_and_offer_short_appendage>(data + offset, bound - offset, handler);
    }
    return offset;
}

// Quote Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_quote_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const quote_message_type& quote_message_type_) {
    if (static_cast<bool>(tmp::rule(quote_message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& auction_status_message_ = tmp::read<auction_status_message>(data + offset, bound - offset, handler); offset += auction_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(quote_message_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_long_quote_message(data + offset, bound - offset, handler);
        tmp::call(handler, long_quote_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(quote_message_type_) == 'Q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_short_quote_message(data + offset, bound - offset, handler);
        tmp::call(handler, short_quote_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(quote_message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_special_long_quote_message(data + offset, bound - offset, handler);
        tmp::call(handler, special_long_quote_message{});
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Quote Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_quote_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& quote_message_section_1_ = tmp::read<quote_message_section_1>(data + offset, bound - offset, handler); offset += quote_message_section_1::size;
    offset += parse_quote_message_payload(data + offset, bound - offset, handler, quote_message_section_1_.template get<quote_message_type>());
    return offset;
}

// Market Status Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_market_status_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const market_status_message_type& market_status_message_type_) {
    if (static_cast<bool>(tmp::rule(market_status_message_type_) == 'K')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& market_wide_circuit_breaker_decline_level_status_message_ = tmp::read<market_wide_circuit_breaker_decline_level_status_message>(data + offset, bound - offset, handler); offset += market_wide_circuit_breaker_decline_level_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(market_status_message_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& market_wide_circuit_breaker_status_message_ = tmp::read<market_wide_circuit_breaker_status_message>(data + offset, bound - offset, handler); offset += market_wide_circuit_breaker_status_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Market Status Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_market_status_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& market_status_message_section_1_ = tmp::read<market_status_message_section_1>(data + offset, bound - offset, handler); offset += market_status_message_section_1::size;
    offset += parse_market_status_message_payload(data + offset, bound - offset, handler, market_status_message_section_1_.template get<market_status_message_type>());
    return offset;
}

// Control Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_control_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const control_message_type& control_message_type_) {
    if (static_cast<bool>(tmp::rule(control_message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& start_of_day_message_ = tmp::read<start_of_day_message>(data + offset, bound - offset, handler); offset += start_of_day_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(control_message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& finra_close_message_ = tmp::read<finra_close_message>(data + offset, bound - offset, handler); offset += finra_close_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(control_message_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reset_block_sequence_number_message_ = tmp::read<reset_block_sequence_number_message>(data + offset, bound - offset, handler); offset += reset_block_sequence_number_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(control_message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& finra_open_message_ = tmp::read<finra_open_message>(data + offset, bound - offset, handler); offset += finra_open_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(control_message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& disaster_recovery_data_center_activation_message_ = tmp::read<disaster_recovery_data_center_activation_message>(data + offset, bound - offset, handler); offset += disaster_recovery_data_center_activation_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(control_message_type_) == 'T')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& line_integrity_message_ = tmp::read<line_integrity_message>(data + offset, bound - offset, handler); offset += line_integrity_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(control_message_type_) == 'Z')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_day_message_ = tmp::read<end_of_day_message>(data + offset, bound - offset, handler); offset += end_of_day_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Control Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_control_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& control_message_section_1_ = tmp::read<control_message_section_1>(data + offset, bound - offset, handler); offset += control_message_section_1::size;
    offset += parse_control_message_payload(data + offset, bound - offset, handler, control_message_section_1_.template get<control_message_type>());
    return offset;
}

// Administrative Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_administrative_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const administrative_message_type& administrative_message_type_) {
    if (static_cast<bool>(tmp::rule(administrative_message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& symbol_reference_data_message_ = tmp::read<symbol_reference_data_message>(data + offset, bound - offset, handler); offset += symbol_reference_data_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Administrative Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_administrative_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& administrative_message_section_1_ = tmp::read<administrative_message_section_1>(data + offset, bound - offset, handler); offset += administrative_message_section_1::size;
    offset += parse_administrative_message_payload(data + offset, bound - offset, handler, administrative_message_section_1_.template get<administrative_message_type>());
    return offset;
}

// Category Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_category_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_category& message_category_) {
    if (static_cast<bool>(tmp::rule(message_category_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_administrative_message(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_control_message(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'M')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_market_status_message(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'Q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_quote_message(data + offset, bound - offset, handler);
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& message_section_1_ = tmp::read<message_section_1>(data + offset, bound - offset, handler); offset += message_section_1::size;
    bound = static_cast<std::size_t>(tmp::rule(message_section_1_.template get<message_length>()));
    tmp::require(bound, length);
    offset += parse_category_payload(data + offset, bound - offset, handler, message_section_1_.template get<message_category>());
    return bound;
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& block_header_ = tmp::read<block_header>(data + offset, bound - offset, handler); offset += block_header::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(block_header_.template get<messages_in_block>()));
        while (count-- > 0) {
            offset += parse_message(data + offset, bound - offset, handler);
        }
    }
    [[maybe_unused]] const block_pad_byte* block_pad_byte_at = nullptr;
    if (static_cast<bool>((offset % 2 != 0))) {
        block_pad_byte_at = &tmp::read<block_pad_byte>(data + offset, bound - offset, handler); offset += block_pad_byte::size;
    }
    return offset;
}


} // namespace siac::cqs::output::cta::v2_10_a

namespace protocol = ::siac::cqs::output::cta::v2_10_a;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::block_header& header) {
        if constexpr (requires { header.template get<protocol::version>(); }) { checksum += bench::digest(header.template get<protocol::version>().value()); }
        if constexpr (requires { header.template get<protocol::block_size>(); }) { checksum += bench::digest(header.template get<protocol::block_size>().value()); }
        if constexpr (requires { header.template get<protocol::data_feed_indicator>(); }) { checksum += bench::digest(header.template get<protocol::data_feed_indicator>().value()); }
        if constexpr (requires { header.template get<protocol::retransmission_indicator>(); }) { checksum += bench::digest(header.template get<protocol::retransmission_indicator>().value()); }
        if constexpr (requires { header.template get<protocol::block_sequence_number>(); }) { checksum += bench::digest(header.template get<protocol::block_sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::messages_in_block>(); }) { checksum += bench::digest(header.template get<protocol::messages_in_block>().value()); }
        if constexpr (requires { header.template get<protocol::block_checksum>(); }) { checksum += bench::digest(header.template get<protocol::block_checksum>().value()); }
    }

    void operator()(const protocol::administrative_message&) {
    }

    void operator()(const protocol::control_message&) {
    }

    void operator()(const protocol::market_status_message&) {
    }

    void operator()(const protocol::quote_message&) {
    }
};

// The values the Tmp reading reads from one datagram, folded into a checksum. A datagram it cannot read
// is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Siac.Cqs.Output.Cta.v2.10.a", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
