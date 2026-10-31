// Nasdaq.NomOptions.Itto.Itch.v4.0.2025 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nomoptions/itto/itch/v4.0.2025.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/nasdaq/nomoptions/itto/itch/v4.0.2025/nasdaq_nomoptions_itto_itch_v4_0_2025.hpp"

// Nasdaq NomOptions Itto Itch 4.0.2025: the reading of its packets, through its Template Meta Programming header
namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

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

// Udp Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_udp_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_event_message_ = tmp::read<system_event_message>(data + offset, bound - offset, handler); offset += system_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_directory_message_ = tmp::read<options_directory_message>(data + offset, bound - offset, handler); offset += options_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trading_action_message_ = tmp::read<trading_action_message>(data + offset, bound - offset, handler); offset += trading_action_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& security_open_message_ = tmp::read<security_open_message>(data + offset, bound - offset, handler); offset += security_open_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'a')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_message_short_message_form_ = tmp::read<add_order_message_short_message_form>(data + offset, bound - offset, handler); offset += add_order_message_short_message_form::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_message_long_form_message_ = tmp::read<add_order_message_long_form_message>(data + offset, bound - offset, handler); offset += add_order_message_long_form_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'j')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_quote_message_short_form_message_ = tmp::read<add_quote_message_short_form_message>(data + offset, bound - offset, handler); offset += add_quote_message_short_form_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'J')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_quote_message_long_form_message_ = tmp::read<add_quote_message_long_form_message>(data + offset, bound - offset, handler); offset += add_quote_message_long_form_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'E')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& single_side_executed_message_ = tmp::read<single_side_executed_message>(data + offset, bound - offset, handler); offset += single_side_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& single_side_executed_with_price_message_ = tmp::read<single_side_executed_with_price_message>(data + offset, bound - offset, handler); offset += single_side_executed_with_price_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_cancel_message_ = tmp::read<order_cancel_message>(data + offset, bound - offset, handler); offset += order_cancel_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'u')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& single_side_replace_message_short_form_ = tmp::read<single_side_replace_message_short_form>(data + offset, bound - offset, handler); offset += single_side_replace_message_short_form::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'U')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& single_side_replace_message_long_form_ = tmp::read<single_side_replace_message_long_form>(data + offset, bound - offset, handler); offset += single_side_replace_message_long_form::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& single_side_delete_message_ = tmp::read<single_side_delete_message>(data + offset, bound - offset, handler); offset += single_side_delete_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'G')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& single_side_change_message_ = tmp::read<single_side_change_message>(data + offset, bound - offset, handler); offset += single_side_change_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'k')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& quote_replace_message_short_form_ = tmp::read<quote_replace_message_short_form>(data + offset, bound - offset, handler); offset += quote_replace_message_short_form::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'K')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& quote_replace_message_long_form_ = tmp::read<quote_replace_message_long_form>(data + offset, bound - offset, handler); offset += quote_replace_message_long_form::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Y')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& quote_delete_message_ = tmp::read<quote_delete_message>(data + offset, bound - offset, handler); offset += quote_delete_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_trade_messages_non_auction_ = tmp::read<options_trade_messages_non_auction>(data + offset, bound - offset, handler); offset += options_trade_messages_non_auction::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_cross_trade_message_ = tmp::read<options_cross_trade_message>(data + offset, bound - offset, handler); offset += options_cross_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& broken_trade_order_executed_message_ = tmp::read<broken_trade_order_executed_message>(data + offset, bound - offset, handler); offset += broken_trade_order_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'I')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& noii_message_ = tmp::read<noii_message>(data + offset, bound - offset, handler); offset += noii_message::size;
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
    [[maybe_unused]] const auto& message_header_ = tmp::read<message_header>(data + offset, bound - offset, handler); offset += message_header::size;
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_length>()))) + 2);
    tmp::require(bound, length);
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_length>()))) - 1);
        tmp::require(offset + size, bound);
        parse_udp_payload(data + offset, size, handler, message_header_.template get<message_type>());
        offset += size;
    }
    return bound;
}

// Messages: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_messages([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_count& message_count_) {
    if (static_cast<bool>(tmp::rule(message_count_) == 0)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, heartbeat{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_count_) == 65535)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, end_of_session{});
        return offset;
    }
    {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            std::size_t count = static_cast<std::size_t>(tmp::rule(message_count_));
            while (count-- > 0) {
                offset += parse_message(data + offset, bound - offset, handler);
            }
        }
        return offset;
    }
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
    offset += parse_messages(data + offset, bound - offset, handler, packet_header_.template get<message_count>());
    return offset;
}

// Sequenced Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_sequenced_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const sequenced_message_type& sequenced_message_type_) {
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_event_message_ = tmp::read<system_event_message>(data + offset, bound - offset, handler); offset += system_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_directory_message_ = tmp::read<options_directory_message>(data + offset, bound - offset, handler); offset += options_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trading_action_message_ = tmp::read<trading_action_message>(data + offset, bound - offset, handler); offset += trading_action_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& security_open_message_ = tmp::read<security_open_message>(data + offset, bound - offset, handler); offset += security_open_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'a')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_message_short_message_form_ = tmp::read<add_order_message_short_message_form>(data + offset, bound - offset, handler); offset += add_order_message_short_message_form::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_message_long_form_message_ = tmp::read<add_order_message_long_form_message>(data + offset, bound - offset, handler); offset += add_order_message_long_form_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'j')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_quote_message_short_form_message_ = tmp::read<add_quote_message_short_form_message>(data + offset, bound - offset, handler); offset += add_quote_message_short_form_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'J')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_quote_message_long_form_message_ = tmp::read<add_quote_message_long_form_message>(data + offset, bound - offset, handler); offset += add_quote_message_long_form_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'E')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& single_side_executed_message_ = tmp::read<single_side_executed_message>(data + offset, bound - offset, handler); offset += single_side_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& single_side_executed_with_price_message_ = tmp::read<single_side_executed_with_price_message>(data + offset, bound - offset, handler); offset += single_side_executed_with_price_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_cancel_message_ = tmp::read<order_cancel_message>(data + offset, bound - offset, handler); offset += order_cancel_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'u')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& single_side_replace_message_short_form_ = tmp::read<single_side_replace_message_short_form>(data + offset, bound - offset, handler); offset += single_side_replace_message_short_form::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'U')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& single_side_replace_message_long_form_ = tmp::read<single_side_replace_message_long_form>(data + offset, bound - offset, handler); offset += single_side_replace_message_long_form::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& single_side_delete_message_ = tmp::read<single_side_delete_message>(data + offset, bound - offset, handler); offset += single_side_delete_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'G')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& single_side_change_message_ = tmp::read<single_side_change_message>(data + offset, bound - offset, handler); offset += single_side_change_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'k')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& quote_replace_message_short_form_ = tmp::read<quote_replace_message_short_form>(data + offset, bound - offset, handler); offset += quote_replace_message_short_form::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'K')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& quote_replace_message_long_form_ = tmp::read<quote_replace_message_long_form>(data + offset, bound - offset, handler); offset += quote_replace_message_long_form::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'Y')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& quote_delete_message_ = tmp::read<quote_delete_message>(data + offset, bound - offset, handler); offset += quote_delete_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_trade_messages_non_auction_ = tmp::read<options_trade_messages_non_auction>(data + offset, bound - offset, handler); offset += options_trade_messages_non_auction::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'Q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_cross_trade_message_ = tmp::read<options_cross_trade_message>(data + offset, bound - offset, handler); offset += options_cross_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& broken_trade_order_executed_message_ = tmp::read<broken_trade_order_executed_message>(data + offset, bound - offset, handler); offset += broken_trade_order_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'I')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& noii_message_ = tmp::read<noii_message>(data + offset, bound - offset, handler); offset += noii_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'M')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_replay_sequence_message_ = tmp::read<end_of_replay_sequence_message>(data + offset, bound - offset, handler); offset += end_of_replay_sequence_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Sequenced Data Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_sequenced_data_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const packet_length& packet_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& sequenced_data_packet_section_1_ = tmp::read<sequenced_data_packet_section_1>(data + offset, bound - offset, handler); offset += sequenced_data_packet_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(packet_length_))) - 2);
        tmp::require(offset + size, bound);
        parse_sequenced_message(data + offset, size, handler, sequenced_data_packet_section_1_.template get<sequenced_message_type>());
        offset += size;
    }
    return offset;
}

// Debug Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_debug_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const packet_length& packet_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(packet_length_))) - 1);
        tmp::require(offset + size, bound);
        tmp::call(handler, debug_text{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Server Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_server_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const server_packet_type& server_packet_type_, const packet_length& packet_length_) {
    if (static_cast<bool>(tmp::rule(server_packet_type_) == '+')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_debug_packet(data + offset, bound - offset, handler, packet_length_);
        tmp::call(handler, debug_packet{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(server_packet_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& login_accepted_packet_ = tmp::read<login_accepted_packet>(data + offset, bound - offset, handler); offset += login_accepted_packet::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(server_packet_type_) == 'J')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& login_rejected_packet_ = tmp::read<login_rejected_packet>(data + offset, bound - offset, handler); offset += login_rejected_packet::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(server_packet_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(packet_length_))) - 1);
            tmp::require(offset + size, bound);
            parse_sequenced_data_packet(data + offset, size, handler, packet_length_);
            offset += size;
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(server_packet_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, server_heartbeat_packet{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(server_packet_type_) == 'Z')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, end_of_session_packet{});
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Server Soup Bin Tcp Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_server_soup_bin_tcp_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& server_packet_header_ = tmp::read<server_packet_header>(data + offset, bound - offset, handler); offset += server_packet_header::size;
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(server_packet_header_.template get<packet_length>()))) + 2);
    tmp::require(bound, length);
    offset += parse_server_payload(data + offset, bound - offset, handler, server_packet_header_.template get<server_packet_type>(), server_packet_header_.template get<packet_length>());
    return bound;
}

// Server Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_server_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    while (offset < bound) {
        if (bound - offset < 0 + packet_length::size) { return offset; }
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(tmp::at<packet_length>(data + offset + 0)))) + 2);
        if (bound - offset < size) { return offset; }
        parse_server_soup_bin_tcp_packet(data + offset, size, handler);
        offset += size;
    }
    return offset;
}

// Unsequenced Data Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_unsequenced_data_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const packet_length& packet_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& unsequenced_data_packet_section_1_ = tmp::read<unsequenced_data_packet_section_1>(data + offset, bound - offset, handler); offset += unsequenced_data_packet_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(packet_length_))) - 2);
        tmp::require(offset + size, bound);
        tmp::call(handler, unsequenced_message{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Client Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_client_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const client_packet_type& client_packet_type_, const packet_length& packet_length_) {
    if (static_cast<bool>(tmp::rule(client_packet_type_) == '+')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_debug_packet(data + offset, bound - offset, handler, packet_length_);
        tmp::call(handler, debug_packet{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(client_packet_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& login_request_packet_ = tmp::read<login_request_packet>(data + offset, bound - offset, handler); offset += login_request_packet::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(client_packet_type_) == 'U')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(packet_length_))) - 1);
            tmp::require(offset + size, bound);
            parse_unsequenced_data_packet(data + offset, size, handler, packet_length_);
            tmp::call(handler, unsequenced_data_packet{});
            offset += size;
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(client_packet_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, client_heartbeat_packet{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(client_packet_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, logout_request_packet{});
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Client Soup Bin Tcp Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_client_soup_bin_tcp_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& client_packet_header_ = tmp::read<client_packet_header>(data + offset, bound - offset, handler); offset += client_packet_header::size;
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(client_packet_header_.template get<packet_length>()))) + 2);
    tmp::require(bound, length);
    offset += parse_client_payload(data + offset, bound - offset, handler, client_packet_header_.template get<client_packet_type>(), client_packet_header_.template get<packet_length>());
    return bound;
}

// Client Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_client_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    while (offset < bound) {
        if (bound - offset < 0 + packet_length::size) { return offset; }
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(tmp::at<packet_length>(data + offset + 0)))) + 2);
        if (bound - offset < size) { return offset; }
        parse_client_soup_bin_tcp_packet(data + offset, size, handler);
        offset += size;
    }
    return offset;
}


} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025

namespace protocol = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::session>(); }) { checksum += bench::digest(header.template get<protocol::session>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { checksum += bench::digest(header.template get<protocol::sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { checksum += bench::digest(header.template get<protocol::message_count>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::message_length>(); }) { checksum += bench::digest(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { checksum += bench::digest(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::system_event_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::event_code>(); }) { checksum += bench::digest(message.template get<protocol::event_code>().value()); }
    }

    void operator()(const protocol::options_directory_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::option_id>(); }) { checksum += bench::digest(message.template get<protocol::option_id>().value()); }
        if constexpr (requires { message.template get<protocol::security_symbol>(); }) { checksum += bench::digest(message.template get<protocol::security_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::expiration_year>(); }) { checksum += bench::digest(message.template get<protocol::expiration_year>().value()); }
        if constexpr (requires { message.template get<protocol::expiration_month>(); }) { checksum += bench::digest(message.template get<protocol::expiration_month>().value()); }
        if constexpr (requires { message.template get<protocol::expiration_date>(); }) { checksum += bench::digest(message.template get<protocol::expiration_date>().value()); }
        if constexpr (requires { message.template get<protocol::explicit_strike_price>(); }) { checksum += bench::digest(message.template get<protocol::explicit_strike_price>().value()); }
        if constexpr (requires { message.template get<protocol::option_type>(); }) { checksum += bench::digest(message.template get<protocol::option_type>().value()); }
        if constexpr (requires { message.template get<protocol::source>(); }) { checksum += bench::digest(message.template get<protocol::source>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_symbol>(); }) { checksum += bench::digest(message.template get<protocol::underlying_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::options_closing_type>(); }) { checksum += bench::digest(message.template get<protocol::options_closing_type>().value()); }
        if constexpr (requires { message.template get<protocol::tradable>(); }) { checksum += bench::digest(message.template get<protocol::tradable>().value()); }
        if constexpr (requires { message.template get<protocol::mpv>(); }) { checksum += bench::digest(message.template get<protocol::mpv>().value()); }
    }

    void operator()(const protocol::trading_action_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::option_id>(); }) { checksum += bench::digest(message.template get<protocol::option_id>().value()); }
        if constexpr (requires { message.template get<protocol::current_trading_state>(); }) { checksum += bench::digest(message.template get<protocol::current_trading_state>().value()); }
    }

    void operator()(const protocol::security_open_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::option_id>(); }) { checksum += bench::digest(message.template get<protocol::option_id>().value()); }
        if constexpr (requires { message.template get<protocol::open_state>(); }) { checksum += bench::digest(message.template get<protocol::open_state>().value()); }
    }

    void operator()(const protocol::add_order_message_short_message_form& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::market_side>(); }) { checksum += bench::digest(message.template get<protocol::market_side>().value()); }
        if constexpr (requires { message.template get<protocol::option_id>(); }) { checksum += bench::digest(message.template get<protocol::option_id>().value()); }
        if constexpr (requires { message.template get<protocol::price_short>(); }) { checksum += bench::digest(message.template get<protocol::price_short>().value()); }
        if constexpr (requires { message.template get<protocol::volume_short>(); }) { checksum += bench::digest(message.template get<protocol::volume_short>().value()); }
    }

    void operator()(const protocol::add_order_message_long_form_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::market_side>(); }) { checksum += bench::digest(message.template get<protocol::market_side>().value()); }
        if constexpr (requires { message.template get<protocol::option_id>(); }) { checksum += bench::digest(message.template get<protocol::option_id>().value()); }
        if constexpr (requires { message.template get<protocol::price_long>(); }) { checksum += bench::digest(message.template get<protocol::price_long>().value()); }
        if constexpr (requires { message.template get<protocol::volume_long>(); }) { checksum += bench::digest(message.template get<protocol::volume_long>().value()); }
    }

    void operator()(const protocol::add_quote_message_short_form_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::bid_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::bid_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::ask_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::ask_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::option_id>(); }) { checksum += bench::digest(message.template get<protocol::option_id>().value()); }
        if constexpr (requires { message.template get<protocol::bid_price_short>(); }) { checksum += bench::digest(message.template get<protocol::bid_price_short>().value()); }
        if constexpr (requires { message.template get<protocol::bid_size_short>(); }) { checksum += bench::digest(message.template get<protocol::bid_size_short>().value()); }
        if constexpr (requires { message.template get<protocol::ask_price_short>(); }) { checksum += bench::digest(message.template get<protocol::ask_price_short>().value()); }
        if constexpr (requires { message.template get<protocol::ask_size_short>(); }) { checksum += bench::digest(message.template get<protocol::ask_size_short>().value()); }
    }

    void operator()(const protocol::add_quote_message_long_form_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::bid_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::bid_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::ask_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::ask_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::option_id>(); }) { checksum += bench::digest(message.template get<protocol::option_id>().value()); }
        if constexpr (requires { message.template get<protocol::bid>(); }) { checksum += bench::digest(message.template get<protocol::bid>().value()); }
        if constexpr (requires { message.template get<protocol::bid_size_long>(); }) { checksum += bench::digest(message.template get<protocol::bid_size_long>().value()); }
        if constexpr (requires { message.template get<protocol::ask>(); }) { checksum += bench::digest(message.template get<protocol::ask>().value()); }
        if constexpr (requires { message.template get<protocol::ask_size_long>(); }) { checksum += bench::digest(message.template get<protocol::ask_size_long>().value()); }
    }

    void operator()(const protocol::single_side_executed_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::reference_number>(); }) { checksum += bench::digest(message.template get<protocol::reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::executed_contracts>(); }) { checksum += bench::digest(message.template get<protocol::executed_contracts>().value()); }
        if constexpr (requires { message.template get<protocol::cross_number>(); }) { checksum += bench::digest(message.template get<protocol::cross_number>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
    }

    void operator()(const protocol::single_side_executed_with_price_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::reference_number>(); }) { checksum += bench::digest(message.template get<protocol::reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::cross_number>(); }) { checksum += bench::digest(message.template get<protocol::cross_number>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
        if constexpr (requires { message.template get<protocol::printable>(); }) { checksum += bench::digest(message.template get<protocol::printable>().value()); }
        if constexpr (requires { message.template get<protocol::price_long>(); }) { checksum += bench::digest(message.template get<protocol::price_long>().value()); }
        if constexpr (requires { message.template get<protocol::volume_long>(); }) { checksum += bench::digest(message.template get<protocol::volume_long>().value()); }
    }

    void operator()(const protocol::order_cancel_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::cancelled_contracts>(); }) { checksum += bench::digest(message.template get<protocol::cancelled_contracts>().value()); }
    }

    void operator()(const protocol::single_side_replace_message_short_form& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::original_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::original_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::new_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::new_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::price_short>(); }) { checksum += bench::digest(message.template get<protocol::price_short>().value()); }
        if constexpr (requires { message.template get<protocol::volume_short>(); }) { checksum += bench::digest(message.template get<protocol::volume_short>().value()); }
    }

    void operator()(const protocol::single_side_replace_message_long_form& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::original_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::original_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::new_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::new_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::price_long>(); }) { checksum += bench::digest(message.template get<protocol::price_long>().value()); }
        if constexpr (requires { message.template get<protocol::volume_long>(); }) { checksum += bench::digest(message.template get<protocol::volume_long>().value()); }
    }

    void operator()(const protocol::single_side_delete_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::reference_number>(); }) { checksum += bench::digest(message.template get<protocol::reference_number>().value()); }
    }

    void operator()(const protocol::single_side_change_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::reference_number>(); }) { checksum += bench::digest(message.template get<protocol::reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::change_reason>(); }) { checksum += bench::digest(message.template get<protocol::change_reason>().value()); }
        if constexpr (requires { message.template get<protocol::price_long>(); }) { checksum += bench::digest(message.template get<protocol::price_long>().value()); }
        if constexpr (requires { message.template get<protocol::volume_long>(); }) { checksum += bench::digest(message.template get<protocol::volume_long>().value()); }
    }

    void operator()(const protocol::quote_replace_message_short_form& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::original_bid_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::original_bid_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::bid_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::bid_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::original_ask_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::original_ask_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::ask_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::ask_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::bid_price_short>(); }) { checksum += bench::digest(message.template get<protocol::bid_price_short>().value()); }
        if constexpr (requires { message.template get<protocol::bid_size_short>(); }) { checksum += bench::digest(message.template get<protocol::bid_size_short>().value()); }
        if constexpr (requires { message.template get<protocol::ask_price_short>(); }) { checksum += bench::digest(message.template get<protocol::ask_price_short>().value()); }
        if constexpr (requires { message.template get<protocol::ask_size_short>(); }) { checksum += bench::digest(message.template get<protocol::ask_size_short>().value()); }
    }

    void operator()(const protocol::quote_replace_message_long_form& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::original_bid_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::original_bid_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::bid_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::bid_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::original_ask_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::original_ask_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::ask_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::ask_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::bid_price_long>(); }) { checksum += bench::digest(message.template get<protocol::bid_price_long>().value()); }
        if constexpr (requires { message.template get<protocol::bid_size_long>(); }) { checksum += bench::digest(message.template get<protocol::bid_size_long>().value()); }
        if constexpr (requires { message.template get<protocol::ask_price_long>(); }) { checksum += bench::digest(message.template get<protocol::ask_price_long>().value()); }
        if constexpr (requires { message.template get<protocol::ask_size_long>(); }) { checksum += bench::digest(message.template get<protocol::ask_size_long>().value()); }
    }

    void operator()(const protocol::quote_delete_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::bid_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::bid_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::ask_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::ask_reference_number>().value()); }
    }

    void operator()(const protocol::options_trade_messages_non_auction& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::buy_sell_indicator>(); }) { checksum += bench::digest(message.template get<protocol::buy_sell_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::option_id>(); }) { checksum += bench::digest(message.template get<protocol::option_id>().value()); }
        if constexpr (requires { message.template get<protocol::cross_number>(); }) { checksum += bench::digest(message.template get<protocol::cross_number>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
        if constexpr (requires { message.template get<protocol::price_long>(); }) { checksum += bench::digest(message.template get<protocol::price_long>().value()); }
        if constexpr (requires { message.template get<protocol::volume_long>(); }) { checksum += bench::digest(message.template get<protocol::volume_long>().value()); }
    }

    void operator()(const protocol::options_cross_trade_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::option_id>(); }) { checksum += bench::digest(message.template get<protocol::option_id>().value()); }
        if constexpr (requires { message.template get<protocol::cross_number>(); }) { checksum += bench::digest(message.template get<protocol::cross_number>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { checksum += bench::digest(message.template get<protocol::cross_type>().value()); }
        if constexpr (requires { message.template get<protocol::price_long>(); }) { checksum += bench::digest(message.template get<protocol::price_long>().value()); }
        if constexpr (requires { message.template get<protocol::volume_long>(); }) { checksum += bench::digest(message.template get<protocol::volume_long>().value()); }
    }

    void operator()(const protocol::broken_trade_order_executed_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::cross_number>(); }) { checksum += bench::digest(message.template get<protocol::cross_number>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
    }

    void operator()(const protocol::noii_message& message) {
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::auction_id>(); }) { checksum += bench::digest(message.template get<protocol::auction_id>().value()); }
        if constexpr (requires { message.template get<protocol::auction_type>(); }) { checksum += bench::digest(message.template get<protocol::auction_type>().value()); }
        if constexpr (requires { message.template get<protocol::paired_contracts>(); }) { checksum += bench::digest(message.template get<protocol::paired_contracts>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_direction>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_direction>().value()); }
        if constexpr (requires { message.template get<protocol::option_id>(); }) { checksum += bench::digest(message.template get<protocol::option_id>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_price>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_price>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_volume>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_volume>().value()); }
        if constexpr (requires { message.template get<protocol::customer_firm_indicator>(); }) { checksum += bench::digest(message.template get<protocol::customer_firm_indicator>().value()); }
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
    return bench::run("Nasdaq.NomOptions.Itto.Itch.v4.0.2025", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
