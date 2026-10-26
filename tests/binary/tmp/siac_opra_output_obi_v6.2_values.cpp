// Siac.Opra.Output.Obi.v6.2 canonical values, through the Tmp header: every value the Tmp reading hands
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
#include "cpp/binary/tmp/siac/opra/output/obi/v6.2/siac_opra_output_obi_v6_2.hpp"

// Siac Opra Output Obi 6.2: the reading of its packets, through its Template Meta Programming header
namespace siac::opra::output::obi::v6_2 {

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

// Underlying Value Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_underlying_value_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const underlying_value_message_type& underlying_value_message_type_) {
    if (static_cast<bool>(tmp::rule(underlying_value_message_type_) == ' ')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& underlying_value_last_sale_message_ = tmp::read<underlying_value_last_sale_message>(data + offset, bound - offset, handler); offset += underlying_value_last_sale_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(underlying_value_message_type_) == 'I')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& underlying_value_bid_and_offer_message_ = tmp::read<underlying_value_bid_and_offer_message>(data + offset, bound - offset, handler); offset += underlying_value_bid_and_offer_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Underlying Value Category: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_underlying_value_category([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& underlying_value_category_section_1_ = tmp::read<underlying_value_category_section_1>(data + offset, bound - offset, handler); offset += underlying_value_category_section_1::size;
    offset += parse_underlying_value_message_payload(data + offset, bound - offset, handler, underlying_value_category_section_1_.template get<underlying_value_message_type>());
    return offset;
}

// Short Equity And Index Quote Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_short_equity_and_index_quote_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& short_equity_and_index_quote_message_section_1_ = tmp::read<short_equity_and_index_quote_message_section_1>(data + offset, bound - offset, handler); offset += short_equity_and_index_quote_message_section_1::size;
    if (static_cast<bool>(tmp::rule(short_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'M' || tmp::rule(short_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'N' || tmp::rule(short_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'P')) {
        offset += tmp::take<best_bid_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(short_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'C' || tmp::rule(short_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'G' || tmp::rule(short_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'K')) {
        offset += tmp::take<best_offer_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(short_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'O')) {
        offset += tmp::take<best_bid_and_offer_appendage>(data + offset, bound - offset, handler);
    }
    return offset;
}

// Short Equity And Index Quote Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_short_equity_and_index_quote_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const short_equity_and_index_quote_message_type& short_equity_and_index_quote_message_type_) {
    if (static_cast<bool>(tmp::rule(short_equity_and_index_quote_message_type_) == ' ' || tmp::rule(short_equity_and_index_quote_message_type_) == 'F' || tmp::rule(short_equity_and_index_quote_message_type_) == 'I' || tmp::rule(short_equity_and_index_quote_message_type_) == 'R' || tmp::rule(short_equity_and_index_quote_message_type_) == 'T' || tmp::rule(short_equity_and_index_quote_message_type_) == 'A' || tmp::rule(short_equity_and_index_quote_message_type_) == 'B' || tmp::rule(short_equity_and_index_quote_message_type_) == 'O' || tmp::rule(short_equity_and_index_quote_message_type_) == 'C' || tmp::rule(short_equity_and_index_quote_message_type_) == 'X' || tmp::rule(short_equity_and_index_quote_message_type_) == 'Y')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_short_equity_and_index_quote_message(data + offset, bound - offset, handler);
        tmp::call(handler, short_equity_and_index_quote_message{});
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Short Equity And Index Quote Category: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_short_equity_and_index_quote_category([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& short_equity_and_index_quote_category_section_1_ = tmp::read<short_equity_and_index_quote_category_section_1>(data + offset, bound - offset, handler); offset += short_equity_and_index_quote_category_section_1::size;
    offset += parse_short_equity_and_index_quote_message_payload(data + offset, bound - offset, handler, short_equity_and_index_quote_category_section_1_.template get<short_equity_and_index_quote_message_type>());
    return offset;
}

// Long Equity And Index Quote Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_long_equity_and_index_quote_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& long_equity_and_index_quote_message_section_1_ = tmp::read<long_equity_and_index_quote_message_section_1>(data + offset, bound - offset, handler); offset += long_equity_and_index_quote_message_section_1::size;
    if (static_cast<bool>(tmp::rule(long_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'M' || tmp::rule(long_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'N' || tmp::rule(long_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'P')) {
        offset += tmp::take<best_bid_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(long_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'C' || tmp::rule(long_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'G' || tmp::rule(long_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'K')) {
        offset += tmp::take<best_offer_appendage>(data + offset, bound - offset, handler);
    }
    if (static_cast<bool>(tmp::rule(long_equity_and_index_quote_message_section_1_.template get<bbo_indicator>()) == 'O')) {
        offset += tmp::take<best_bid_and_offer_appendage>(data + offset, bound - offset, handler);
    }
    return offset;
}

// Long Equity And Index Quote Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_long_equity_and_index_quote_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const long_equity_and_index_quote_message_type& long_equity_and_index_quote_message_type_) {
    if (static_cast<bool>(tmp::rule(long_equity_and_index_quote_message_type_) == ' ' || tmp::rule(long_equity_and_index_quote_message_type_) == 'F' || tmp::rule(long_equity_and_index_quote_message_type_) == 'I' || tmp::rule(long_equity_and_index_quote_message_type_) == 'R' || tmp::rule(long_equity_and_index_quote_message_type_) == 'T' || tmp::rule(long_equity_and_index_quote_message_type_) == 'A' || tmp::rule(long_equity_and_index_quote_message_type_) == 'B' || tmp::rule(long_equity_and_index_quote_message_type_) == 'O' || tmp::rule(long_equity_and_index_quote_message_type_) == 'C' || tmp::rule(long_equity_and_index_quote_message_type_) == 'X' || tmp::rule(long_equity_and_index_quote_message_type_) == 'Y')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_long_equity_and_index_quote_message(data + offset, bound - offset, handler);
        tmp::call(handler, long_equity_and_index_quote_message{});
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Long Equity And Index Quote Category: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_long_equity_and_index_quote_category([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& long_equity_and_index_quote_category_section_1_ = tmp::read<long_equity_and_index_quote_category_section_1>(data + offset, bound - offset, handler); offset += long_equity_and_index_quote_category_section_1::size;
    offset += parse_long_equity_and_index_quote_message_payload(data + offset, bound - offset, handler, long_equity_and_index_quote_category_section_1_.template get<long_equity_and_index_quote_message_type>());
    return offset;
}

// Equity And Index End Of Day Summary Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_equity_and_index_end_of_day_summary_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const equity_and_index_end_of_day_summary_message_type& equity_and_index_end_of_day_summary_message_type_) {
    if (static_cast<bool>(tmp::rule(equity_and_index_end_of_day_summary_message_type_) == ' ')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& equity_and_index_end_of_day_summary_message_ = tmp::read<equity_and_index_end_of_day_summary_message>(data + offset, bound - offset, handler); offset += equity_and_index_end_of_day_summary_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Equity And Index End Of Day Summary Category: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_equity_and_index_end_of_day_summary_category([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& equity_and_index_end_of_day_summary_category_section_1_ = tmp::read<equity_and_index_end_of_day_summary_category_section_1>(data + offset, bound - offset, handler); offset += equity_and_index_end_of_day_summary_category_section_1::size;
    offset += parse_equity_and_index_end_of_day_summary_message_payload(data + offset, bound - offset, handler, equity_and_index_end_of_day_summary_category_section_1_.template get<equity_and_index_end_of_day_summary_message_type>());
    return offset;
}

// Open Interest Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_open_interest_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const open_interest_message_type& open_interest_message_type_) {
    if (static_cast<bool>(tmp::rule(open_interest_message_type_) == ' ')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& open_interest_message_ = tmp::read<open_interest_message>(data + offset, bound - offset, handler); offset += open_interest_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Open Interest Category: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_open_interest_category([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& open_interest_category_section_1_ = tmp::read<open_interest_category_section_1>(data + offset, bound - offset, handler); offset += open_interest_category_section_1::size;
    offset += parse_open_interest_message_payload(data + offset, bound - offset, handler, open_interest_category_section_1_.template get<open_interest_message_type>());
    return offset;
}

// Equity And Index Last Sale Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_equity_and_index_last_sale_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const equity_and_index_last_sale_message_type& equity_and_index_last_sale_message_type_) {
    if (static_cast<bool>(tmp::rule(equity_and_index_last_sale_message_type_) == 'A' || tmp::rule(equity_and_index_last_sale_message_type_) == 'B' || tmp::rule(equity_and_index_last_sale_message_type_) == 'C' || tmp::rule(equity_and_index_last_sale_message_type_) == 'D' || tmp::rule(equity_and_index_last_sale_message_type_) == 'E' || tmp::rule(equity_and_index_last_sale_message_type_) == 'F' || tmp::rule(equity_and_index_last_sale_message_type_) == 'G' || tmp::rule(equity_and_index_last_sale_message_type_) == 'H' || tmp::rule(equity_and_index_last_sale_message_type_) == 'I' || tmp::rule(equity_and_index_last_sale_message_type_) == 'J' || tmp::rule(equity_and_index_last_sale_message_type_) == 'K' || tmp::rule(equity_and_index_last_sale_message_type_) == 'L' || tmp::rule(equity_and_index_last_sale_message_type_) == 'M' || tmp::rule(equity_and_index_last_sale_message_type_) == 'N' || tmp::rule(equity_and_index_last_sale_message_type_) == 'O' || tmp::rule(equity_and_index_last_sale_message_type_) == 'P' || tmp::rule(equity_and_index_last_sale_message_type_) == 'Q' || tmp::rule(equity_and_index_last_sale_message_type_) == 'R' || tmp::rule(equity_and_index_last_sale_message_type_) == 'S' || tmp::rule(equity_and_index_last_sale_message_type_) == 'T' || tmp::rule(equity_and_index_last_sale_message_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& equity_and_index_last_sale_message_ = tmp::read<equity_and_index_last_sale_message>(data + offset, bound - offset, handler); offset += equity_and_index_last_sale_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Equity And Index Last Sale Category: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_equity_and_index_last_sale_category([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& equity_and_index_last_sale_category_section_1_ = tmp::read<equity_and_index_last_sale_category_section_1>(data + offset, bound - offset, handler); offset += equity_and_index_last_sale_category_section_1::size;
    offset += parse_equity_and_index_last_sale_message_payload(data + offset, bound - offset, handler, equity_and_index_last_sale_category_section_1_.template get<equity_and_index_last_sale_message_type>());
    return offset;
}

// Control Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_control_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const control_message_type& control_message_type_) {
    if (static_cast<bool>(tmp::rule(control_message_type_) == 'C' || tmp::rule(control_message_type_) == 'E' || tmp::rule(control_message_type_) == 'F' || tmp::rule(control_message_type_) == 'J' || tmp::rule(control_message_type_) == 'K' || tmp::rule(control_message_type_) == 'L' || tmp::rule(control_message_type_) == 'M' || tmp::rule(control_message_type_) == 'N' || tmp::rule(control_message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& control_message_ = tmp::read<control_message>(data + offset, bound - offset, handler); offset += control_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Control Category: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_control_category([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& control_category_section_1_ = tmp::read<control_category_section_1>(data + offset, bound - offset, handler); offset += control_category_section_1::size;
    offset += parse_control_message_payload(data + offset, bound - offset, handler, control_category_section_1_.template get<control_message_type>());
    return offset;
}

// Administrative Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_administrative_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& administrative_message_section_1_ = tmp::read<administrative_message_section_1>(data + offset, bound - offset, handler); offset += administrative_message_section_1::size;
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(administrative_message_section_1_.template get<message_data_length>()))) + 11);
    tmp::require(bound, length);
    if (static_cast<bool>(tmp::rule(administrative_message_section_1_.template get<message_data_length>()) > 0)) {
        {
            const std::size_t size = static_cast<std::size_t>(tmp::rule(administrative_message_section_1_.template get<message_data_length>()));
            tmp::require(offset + size, bound);
            tmp::call(handler, message_data{ data + offset, size });
            offset += size;
        }
    }
    return bound;
}

// Administrative Message Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_administrative_message_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const administrative_message_type& administrative_message_type_) {
    if (static_cast<bool>(tmp::rule(administrative_message_type_) == ' ')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_administrative_message(data + offset, bound - offset, handler);
        tmp::call(handler, administrative_message{});
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Administrative Category: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_administrative_category([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& administrative_category_section_1_ = tmp::read<administrative_category_section_1>(data + offset, bound - offset, handler); offset += administrative_category_section_1::size;
    offset += parse_administrative_message_payload(data + offset, bound - offset, handler, administrative_category_section_1_.template get<administrative_message_type>());
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_category& message_category_) {
    if (static_cast<bool>(tmp::rule(message_category_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_administrative_category(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_control_category(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'a')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_equity_and_index_last_sale_category(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'd')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_open_interest_category(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'f')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_equity_and_index_end_of_day_summary_category(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'k')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_long_equity_and_index_quote_category(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_short_equity_and_index_quote_category(data + offset, bound - offset, handler);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_category_) == 'Y')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_underlying_value_category(data + offset, bound - offset, handler);
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& message_header_ = tmp::read<message_header>(data + offset, bound - offset, handler); offset += message_header::size;
    offset += parse_payload(data + offset, bound - offset, handler, message_header_.template get<message_category>());
    return offset;
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


} // namespace siac::opra::output::obi::v6_2

namespace protocol = ::siac::opra::output::obi::v6_2;

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
        if constexpr (requires { header.template get<protocol::session_indicator>(); }) { values["packet.blockheader.sessionindicator"] = canonical::number(header.template get<protocol::session_indicator>().value()); }
        if constexpr (requires { header.template get<protocol::block_sequence_number>(); }) { values["packet.blockheader.blocksequencenumber"] = canonical::number(header.template get<protocol::block_sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::messages_in_block>(); }) { values["packet.blockheader.messagesinblock"] = canonical::number(header.template get<protocol::messages_in_block>().value()); }
        if constexpr (requires { header.template get<protocol::block_checksum>(); }) { values["packet.blockheader.blockchecksum"] = canonical::number(header.template get<protocol::block_checksum>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::participant_id>(); }) { values[entry + ".messageheader.participantid"] = canonical::text(canonical::character(header.template get<protocol::participant_id>().value())); }
        if constexpr (requires { header.template get<protocol::message_category>(); }) { values[entry + ".messageheader.messagecategory"] = canonical::text(canonical::character(header.template get<protocol::message_category>().value())); }
    }

    void operator()(const protocol::administrative_category&) {
        values[entry + ".payload"] = "packet.message.payload.administrativecategory";
    }

    void operator()(const protocol::control_category&) {
        values[entry + ".payload"] = "packet.message.payload.controlcategory";
    }

    void operator()(const protocol::equity_and_index_last_sale_category&) {
        values[entry + ".payload"] = "packet.message.payload.equityandindexlastsalecategory";
    }

    void operator()(const protocol::open_interest_category&) {
        values[entry + ".payload"] = "packet.message.payload.openinterestcategory";
    }

    void operator()(const protocol::equity_and_index_end_of_day_summary_category&) {
        values[entry + ".payload"] = "packet.message.payload.equityandindexendofdaysummarycategory";
    }

    void operator()(const protocol::long_equity_and_index_quote_category&) {
        values[entry + ".payload"] = "packet.message.payload.longequityandindexquotecategory";
    }

    void operator()(const protocol::short_equity_and_index_quote_category&) {
        values[entry + ".payload"] = "packet.message.payload.shortequityandindexquotecategory";
    }

    void operator()(const protocol::underlying_value_category&) {
        values[entry + ".payload"] = "packet.message.payload.underlyingvaluecategory";
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
    std::printf("== Siac.Opra.Output.Obi.v6.2 (tmp values)\n");
    int failures = 0;
    failures += check("AdministrativeMessage", "Siac/Opra.Output.Obi.v6.2/AdministrativeMessage.pcap", "siac/opra/output/obi/v6.2/AdministrativeMessage.values");
    failures += check("ControlMessage", "Siac/Opra.Output.Obi.v6.2/ControlMessage.pcap", "siac/opra/output/obi/v6.2/ControlMessage.values");
    failures += check("LongEquityAndIndexQuoteMessage", "Siac/Opra.Output.Obi.v6.2/LongEquityAndIndexQuoteMessage.pcap", "siac/opra/output/obi/v6.2/LongEquityAndIndexQuoteMessage.values");
    failures += check("ShortEquityAndIndexQuoteMessage", "Siac/Opra.Output.Obi.v6.2/ShortEquityAndIndexQuoteMessage.pcap", "siac/opra/output/obi/v6.2/ShortEquityAndIndexQuoteMessage.values");
    return failures == 0 ? 0 : 1;
}
