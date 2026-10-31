// Siac.Cts.Output.Cta.v2.9 canonical values, through the Tmp header: every value the Tmp reading hands
// over from each sample, at its address, held to what the model reads.

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
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/tmp/siac/cts/output/cta/v2.9/siac_cts_output_cta_v2_9.hpp"

// Siac Cts Output Cta 2.9: the reading of its packets, through its Template Meta Programming header
namespace siac::cts::output::cta::v2_9 {

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

    // The bytes before the first of a field's delimiters, which it leaves for what follows it; at
    // most its maximum, and the bytes must hold a delimiter when they are shorter than that
    template <std::size_t Count>
    std::size_t delimited(const std::byte* data, std::size_t length, std::size_t maximum, const std::array<std::byte, Count>& delimiters) {
        const std::size_t limit = std::min(maximum, length);
        for (std::size_t index = 0; index < limit; ++index) {
            for (const std::byte delimiter : delimiters) {
                if (data[index] == delimiter) { return index; }
            }
        }
        if (limit < length) { return limit; }
        throw short_read("no delimiter in " + std::to_string(length) + " bytes");
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

// Trade Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_trade_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const trade_message_type& trade_message_type_) {
    if (static_cast<bool>(tmp::rule(trade_message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& auction_status_message_ = tmp::read<auction_status_message>(data + offset, bound - offset, handler); offset += auction_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(trade_message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_correction_message_ = tmp::read<trade_correction_message>(data + offset, bound - offset, handler); offset += trade_correction_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(trade_message_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& long_trade_message_ = tmp::read<long_trade_message>(data + offset, bound - offset, handler); offset += long_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(trade_message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trading_status_message_ = tmp::read<trading_status_message>(data + offset, bound - offset, handler); offset += trading_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(trade_message_type_) == 'T')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& short_trade_message_ = tmp::read<short_trade_message>(data + offset, bound - offset, handler); offset += short_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(trade_message_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_cancel_error_message_ = tmp::read<trade_cancel_error_message>(data + offset, bound - offset, handler); offset += trade_cancel_error_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Trade Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_trade_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& trade_message_section_1_ = tmp::read<trade_message_section_1>(data + offset, bound - offset, handler); offset += trade_message_section_1::size;
    offset += parse_trade_message_payload(data + offset, bound - offset, handler, trade_message_section_1_.template get<trade_message_type>());
    return offset;
}

// Summary Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_summary_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const summary_message_type& summary_message_type_) {
    if (static_cast<bool>(tmp::rule(summary_message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& consolidated_start_of_day_summary_message_ = tmp::read<consolidated_start_of_day_summary_message>(data + offset, bound - offset, handler); offset += consolidated_start_of_day_summary_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(summary_message_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& participant_start_of_day_summary_message_ = tmp::read<participant_start_of_day_summary_message>(data + offset, bound - offset, handler); offset += participant_start_of_day_summary_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(summary_message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& consolidated_end_of_day_summary_message_ = tmp::read<consolidated_end_of_day_summary_message>(data + offset, bound - offset, handler); offset += consolidated_end_of_day_summary_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(summary_message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& participant_end_of_day_summary_message_ = tmp::read<participant_end_of_day_summary_message>(data + offset, bound - offset, handler); offset += participant_end_of_day_summary_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Summary Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_summary_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& summary_message_section_1_ = tmp::read<summary_message_section_1>(data + offset, bound - offset, handler); offset += summary_message_section_1::size;
    offset += parse_summary_message_payload(data + offset, bound - offset, handler, summary_message_section_1_.template get<summary_message_type>());
    return offset;
}

// Prior Day Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_prior_day_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const prior_day_message_type& prior_day_message_type_) {
    if (static_cast<bool>(tmp::rule(prior_day_message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& prior_day_trade_correction_message_ = tmp::read<prior_day_trade_correction_message>(data + offset, bound - offset, handler); offset += prior_day_trade_correction_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(prior_day_message_type_) == 'T')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& prior_day_trade_message_ = tmp::read<prior_day_trade_message>(data + offset, bound - offset, handler); offset += prior_day_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(prior_day_message_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& prior_day_trade_cancel_error_message_ = tmp::read<prior_day_trade_cancel_error_message>(data + offset, bound - offset, handler); offset += prior_day_trade_cancel_error_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Prior Day Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_prior_day_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& prior_day_message_section_1_ = tmp::read<prior_day_message_section_1>(data + offset, bound - offset, handler); offset += prior_day_message_section_1::size;
    offset += parse_prior_day_message_payload(data + offset, bound - offset, handler, prior_day_message_section_1_.template get<prior_day_message_type>());
    return offset;
}

// Approximate Adjusted Volume Market Center Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_approximate_adjusted_volume_market_center_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& approximate_adjusted_volume_market_center_message_section_1_ = tmp::read<approximate_adjusted_volume_market_center_message_section_1>(data + offset, bound - offset, handler); offset += approximate_adjusted_volume_market_center_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(approximate_adjusted_volume_market_center_message_section_1_.template get<number_of_participants>()));
        while (count-- > 0) {
            offset += tmp::take<participants>(data + offset, bound - offset, handler);
        }
    }
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
    if (static_cast<bool>(tmp::rule(market_status_message_type_) == 'N')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_approximate_adjusted_volume_market_center_message(data + offset, bound - offset, handler);
        tmp::call(handler, approximate_adjusted_volume_market_center_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(market_status_message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& approximate_trades_and_total_dollar_value_message_ = tmp::read<approximate_trades_and_total_dollar_value_message>(data + offset, bound - offset, handler); offset += approximate_trades_and_total_dollar_value_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(market_status_message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& crossing_session_summary_message_ = tmp::read<crossing_session_summary_message>(data + offset, bound - offset, handler); offset += crossing_session_summary_message::size;
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

// Indices Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_indices_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const indices_message_type& indices_message_type_) {
    if (static_cast<bool>(tmp::rule(indices_message_type_) == 'I')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& index_message_ = tmp::read<index_message>(data + offset, bound - offset, handler); offset += index_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(indices_message_type_) == 'Q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& bid_and_offer_index_message_ = tmp::read<bid_and_offer_index_message>(data + offset, bound - offset, handler); offset += bid_and_offer_index_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Indices Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_indices_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& indices_message_section_1_ = tmp::read<indices_message_section_1>(data + offset, bound - offset, handler); offset += indices_message_section_1::size;
    offset += parse_indices_message_payload(data + offset, bound - offset, handler, indices_message_section_1_.template get<indices_message_type>());
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
    if (static_cast<bool>(tmp::rule(control_message_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reset_block_sequence_number_message_ = tmp::read<reset_block_sequence_number_message>(data + offset, bound - offset, handler); offset += reset_block_sequence_number_message::size;
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
    if (static_cast<bool>(tmp::rule(administrative_message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& start_of_end_of_day_message_ = tmp::read<start_of_end_of_day_message>(data + offset, bound - offset, handler); offset += start_of_end_of_day_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(administrative_message_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_end_of_day_message_ = tmp::read<end_of_end_of_day_message>(data + offset, bound - offset, handler); offset += end_of_end_of_day_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(administrative_message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& start_of_start_of_day_message_ = tmp::read<start_of_start_of_day_message>(data + offset, bound - offset, handler); offset += start_of_start_of_day_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(administrative_message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_start_of_day_message_ = tmp::read<end_of_start_of_day_message>(data + offset, bound - offset, handler); offset += end_of_start_of_day_message::size;
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
    if (static_cast<bool>(tmp::rule(message_category_) == 'I')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_indices_message(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'M')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_market_status_message(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_prior_day_message(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_summary_message(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'T')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_trade_message(data + offset, bound - offset, handler);
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


} // namespace siac::cts::output::cta::v2_9

namespace protocol = ::siac::cts::output::cta::v2_9;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::block_header& header) {
        if constexpr (requires { header.template get<protocol::version>(); }) { values["packet.blockheader.version"] = canonical::number(header.template get<protocol::version>().value()); }
        if constexpr (requires { header.template get<protocol::block_size>(); }) { values["packet.blockheader.blocksize"] = canonical::number(header.template get<protocol::block_size>().value()); }
        if constexpr (requires { header.template get<protocol::data_feed_indicator>(); }) { values["packet.blockheader.datafeedindicator"] = canonical::text(canonical::character(header.template get<protocol::data_feed_indicator>().value())); }
        if constexpr (requires { header.template get<protocol::retransmission_indicator>(); }) { values["packet.blockheader.retransmissionindicator"] = canonical::text(canonical::character(header.template get<protocol::retransmission_indicator>().value())); }
        if constexpr (requires { header.template get<protocol::block_sequence_number>(); }) { values["packet.blockheader.blocksequencenumber"] = canonical::number(header.template get<protocol::block_sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::messages_in_block>(); }) { values["packet.blockheader.messagesinblock"] = canonical::number(header.template get<protocol::messages_in_block>().value()); }
        if constexpr (requires { header.template get<protocol::block_checksum>(); }) { values["packet.blockheader.blockchecksum"] = canonical::number(header.template get<protocol::block_checksum>().value()); }
    }

    void operator()(const protocol::administrative_message&) {
        values[entry + ".categorypayload"] = "packet.message.categorypayload.administrativemessage";
    }

    void operator()(const protocol::control_message&) {
        values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
    }

    void operator()(const protocol::indices_message&) {
        values[entry + ".categorypayload"] = "packet.message.categorypayload.indicesmessage";
    }

    void operator()(const protocol::market_status_message&) {
        values[entry + ".categorypayload"] = "packet.message.categorypayload.marketstatusmessage";
    }

    void operator()(const protocol::prior_day_message&) {
        values[entry + ".categorypayload"] = "packet.message.categorypayload.priordaymessage";
    }

    void operator()(const protocol::summary_message&) {
        values[entry + ".categorypayload"] = "packet.message.categorypayload.summarymessage";
    }

    void operator()(const protocol::trade_message&) {
        values[entry + ".categorypayload"] = "packet.message.categorypayload.trademessage";
    }
};

// The values the Tmp reading reads from one datagram, by indexed address. A datagram it cannot read
// is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Tmp and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Siac.Cts.Output.Cta.v2.9 (tmp values)\n");
    int failures = 0;
    failures += check("LineIntegrityMessage", "Siac/Cts.Output.Cta.v2.9/LineIntegrityMessage.pcap", "siac/cts/output/cta/v2.9/LineIntegrityMessage.values");
    failures += check("LongTradeMessage", "Siac/Cts.Output.Cta.v2.9/LongTradeMessage.pcap", "siac/cts/output/cta/v2.9/LongTradeMessage.values");
    failures += check("TradingStatusMessage", "Siac/Cts.Output.Cta.v2.9/TradingStatusMessage.pcap", "siac/cts/output/cta/v2.9/TradingStatusMessage.values");
    return failures == 0 ? 0 : 1;
}
