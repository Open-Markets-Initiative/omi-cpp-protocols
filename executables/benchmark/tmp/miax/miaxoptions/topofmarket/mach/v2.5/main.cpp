// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: main.cpp
// Miax.MiaxOptions.TopOfMarket.Mach.v2.5 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/miax/miaxoptions/topofmarket/mach/v2.5.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/miax/miaxoptions/topofmarket/mach/v2.5/miax_miaxoptions_topofmarket_mach_v2_5.hpp"

// Miax MiaxOptions TopOfMarket Mach 2.5: the reading of its packets, through its Template Meta Programming header
namespace miax::miaxoptions::topofmarket::mach::v2_5 {

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

// Test Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_test_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const sesm_packet_length& sesm_packet_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(sesm_packet_length_))) - 1);
        tmp::require(offset + size, bound);
        tmp::call(handler, test_text{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Goodbye Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_goodbye_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const sesm_packet_length& sesm_packet_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& goodbye_packet_section_1_ = tmp::read<goodbye_packet_section_1>(data + offset, bound - offset, handler); offset += goodbye_packet_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(sesm_packet_length_))) - 2);
        tmp::require(offset + size, bound);
        tmp::call(handler, logout_text{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Logout Request: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_logout_request([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const sesm_packet_length& sesm_packet_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& logout_request_section_1_ = tmp::read<logout_request_section_1>(data + offset, bound - offset, handler); offset += logout_request_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(sesm_packet_length_))) - 2);
        tmp::require(offset + size, bound);
        tmp::call(handler, logout_text{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Data: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_data_type([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == '1')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_time_message_ = tmp::read<system_time_message>(data + offset, bound - offset, handler); offset += system_time_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& simple_series_update_message_ = tmp::read<simple_series_update_message>(data + offset, bound - offset, handler); offset += simple_series_update_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_state_message_ = tmp::read<system_state_message>(data + offset, bound - offset, handler); offset += system_state_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& simple_top_of_market_best_bid_or_offer_compact_bid_message_ = tmp::read<simple_top_of_market_best_bid_or_offer_compact_bid_message>(data + offset, bound - offset, handler); offset += simple_top_of_market_best_bid_or_offer_compact_bid_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& simple_top_of_market_best_bid_or_offer_compact_offer_message_ = tmp::read<simple_top_of_market_best_bid_or_offer_compact_offer_message>(data + offset, bound - offset, handler); offset += simple_top_of_market_best_bid_or_offer_compact_offer_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'b')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& simple_top_of_market_best_bid_or_offer_wide_bid_message_ = tmp::read<simple_top_of_market_best_bid_or_offer_wide_bid_message>(data + offset, bound - offset, handler); offset += simple_top_of_market_best_bid_or_offer_wide_bid_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'o')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& simple_top_of_market_best_bid_or_offer_wide_offer_message_ = tmp::read<simple_top_of_market_best_bid_or_offer_wide_offer_message>(data + offset, bound - offset, handler); offset += simple_top_of_market_best_bid_or_offer_wide_offer_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'd')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& simple_double_sided_top_of_market_best_bid_or_offer_compact_message_ = tmp::read<simple_double_sided_top_of_market_best_bid_or_offer_compact_message>(data + offset, bound - offset, handler); offset += simple_double_sided_top_of_market_best_bid_or_offer_compact_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& simple_double_sided_top_of_market_best_bid_or_offer_wide_message_ = tmp::read<simple_double_sided_top_of_market_best_bid_or_offer_wide_message>(data + offset, bound - offset, handler); offset += simple_double_sided_top_of_market_best_bid_or_offer_wide_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'T')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& last_sale_message_ = tmp::read<last_sale_message>(data + offset, bound - offset, handler); offset += last_sale_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_cancel_message_ = tmp::read<trade_cancel_message>(data + offset, bound - offset, handler); offset += trade_cancel_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& underlying_trading_status_notification_message_ = tmp::read<underlying_trading_status_notification_message>(data + offset, bound - offset, handler); offset += underlying_trading_status_notification_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Application Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_application_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& application_message_section_1_ = tmp::read<application_message_section_1>(data + offset, bound - offset, handler); offset += application_message_section_1::size;
    offset += parse_data_type(data + offset, bound - offset, handler, application_message_section_1_.template get<message_type>());
    return offset;
}

// Refresh Response Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_refresh_response_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const sesm_packet_length& sesm_packet_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& refresh_response_message_section_1_ = tmp::read<refresh_response_message_section_1>(data + offset, bound - offset, handler); offset += refresh_response_message_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(sesm_packet_length_))) - 10);
        tmp::require(offset + size, bound);
        parse_application_message(data + offset, size, handler);
        offset += size;
    }
    return offset;
}

// Unsequenced Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_unsequenced_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const unsequenced_message_type& unsequenced_message_type_, const sesm_packet_length& sesm_packet_length_) {
    if (static_cast<bool>(tmp::rule(unsequenced_message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& refresh_request_message_ = tmp::read<refresh_request_message>(data + offset, bound - offset, handler); offset += refresh_request_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(unsequenced_message_type_) == 'r')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_refresh_response_message(data + offset, bound - offset, handler, sesm_packet_length_);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(unsequenced_message_type_) == 'E')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_refresh_notification_message_ = tmp::read<end_of_refresh_notification_message>(data + offset, bound - offset, handler); offset += end_of_refresh_notification_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Unsequenced Data Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_unsequenced_data_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const sesm_packet_length& sesm_packet_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& unsequenced_data_packet_section_1_ = tmp::read<unsequenced_data_packet_section_1>(data + offset, bound - offset, handler); offset += unsequenced_data_packet_section_1::size;
    offset += parse_unsequenced_message(data + offset, bound - offset, handler, unsequenced_data_packet_section_1_.template get<unsequenced_message_type>(), sesm_packet_length_);
    return offset;
}

// Sequenced Data Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_sequenced_data_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& sequenced_data_packet_section_1_ = tmp::read<sequenced_data_packet_section_1>(data + offset, bound - offset, handler); offset += sequenced_data_packet_section_1::size;
    tmp::call(handler, sequenced_message{});
    return offset;
}

// Sesm Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_sesm_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const sesm_packet_type& sesm_packet_type_, const sesm_packet_length& sesm_packet_length_) {
    if (static_cast<bool>(tmp::rule(sesm_packet_type_) == 's')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(sesm_packet_length_))) - 1);
            tmp::require(offset + size, bound);
            parse_sequenced_data_packet(data + offset, size, handler);
            tmp::call(handler, sequenced_data_packet{});
            offset += size;
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sesm_packet_type_) == 'U')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(sesm_packet_length_))) - 1);
            tmp::require(offset + size, bound);
            parse_unsequenced_data_packet(data + offset, size, handler, sesm_packet_length_);
            offset += size;
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sesm_packet_type_) == 'l')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& login_request_ = tmp::read<login_request>(data + offset, bound - offset, handler); offset += login_request::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sesm_packet_type_) == 'r')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& login_response_ = tmp::read<login_response>(data + offset, bound - offset, handler); offset += login_response::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sesm_packet_type_) == 'c')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& synchronization_complete_ = tmp::read<synchronization_complete>(data + offset, bound - offset, handler); offset += synchronization_complete::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sesm_packet_type_) == 'a')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& retransmission_request_ = tmp::read<retransmission_request>(data + offset, bound - offset, handler); offset += retransmission_request::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sesm_packet_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_logout_request(data + offset, bound - offset, handler, sesm_packet_length_);
        tmp::call(handler, logout_request{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sesm_packet_type_) == 'G')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_goodbye_packet(data + offset, bound - offset, handler, sesm_packet_length_);
        tmp::call(handler, goodbye_packet{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sesm_packet_type_) == 'u')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, trading_session_update{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sesm_packet_type_) == '0')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, server_heartbeat{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sesm_packet_type_) == '1')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, client_heartbeat{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sesm_packet_type_) == 'T')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_test_packet(data + offset, bound - offset, handler, sesm_packet_length_);
        tmp::call(handler, test_packet{});
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Sesm Tcp Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_sesm_tcp_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& sesm_packet_header_ = tmp::read<sesm_packet_header>(data + offset, bound - offset, handler); offset += sesm_packet_header::size;
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(sesm_packet_header_.template get<sesm_packet_length>()))) + 2);
    tmp::require(bound, length);
    offset += parse_sesm_payload(data + offset, bound - offset, handler, sesm_packet_header_.template get<sesm_packet_type>(), sesm_packet_header_.template get<sesm_packet_length>());
    return bound;
}

// Tcp Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_tcp_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    while (offset < bound) {
        if (bound - offset < 0 + sesm_packet_length::size) { return offset; }
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(tmp::at<sesm_packet_length>(data + offset + 0)))) + 2);
        if (bound - offset < size) { return offset; }
        parse_sesm_tcp_packet(data + offset, size, handler);
        offset += size;
    }
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const packet_type& packet_type_, const packet_length& packet_length_) {
    if (static_cast<bool>(tmp::rule(packet_type_) == 0)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, heartbeat{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(packet_type_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, start_of_session{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(packet_type_) == 2)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, end_of_session{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(packet_type_) == 3)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(packet_length_))) - 12);
            tmp::require(offset + size, bound);
            parse_application_message(data + offset, size, handler);
            offset += size;
        }
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Mach Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_mach_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& mach_packet_header_ = tmp::read<mach_packet_header>(data + offset, bound - offset, handler); offset += mach_packet_header::size;
    bound = static_cast<std::size_t>(tmp::rule(mach_packet_header_.template get<packet_length>()));
    tmp::require(bound, length);
    offset += parse_payload(data + offset, bound - offset, handler, mach_packet_header_.template get<packet_type>(), mach_packet_header_.template get<packet_length>());
    return bound;
}

// Udp Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_udp_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    {
        const std::size_t end = static_cast<std::size_t>(static_cast<std::int64_t>(bound));
        tmp::require(end, bound);
        while (offset < end) {
            [[maybe_unused]] const std::size_t bound = end;
            offset += parse_mach_message(data + offset, bound - offset, handler);
        }
    }
    return offset;
}


} // namespace miax::miaxoptions::topofmarket::mach::v2_5

namespace protocol = ::miax::miaxoptions::topofmarket::mach::v2_5;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::mach_packet_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { checksum += bench::digest(header.template get<protocol::sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::packet_length>(); }) { checksum += bench::digest(header.template get<protocol::packet_length>().value()); }
        if constexpr (requires { header.template get<protocol::packet_type>(); }) { checksum += bench::digest(header.template get<protocol::packet_type>().value()); }
        if constexpr (requires { header.template get<protocol::session_number>(); }) { checksum += bench::digest(header.template get<protocol::session_number>().value()); }
    }

    void operator()(const protocol::application_message&) {
    }
};

// The values the Tmp reading reads from one datagram, folded into a checksum. A datagram it cannot read
// is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_udp_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Miax.MiaxOptions.TopOfMarket.Mach.v2.5", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
