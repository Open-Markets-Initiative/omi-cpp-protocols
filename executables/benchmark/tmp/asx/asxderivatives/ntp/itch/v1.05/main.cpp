// Asx.AsxDerivatives.Ntp.Itch.v1.05 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/asx/asxderivatives/ntp/itch/v1.05.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/asx/asxderivatives/ntp/itch/v1.05/asx_asxderivatives_ntp_itch_v1_05.hpp"

// Asx AsxDerivatives Ntp Itch 1.05: the reading of its packets, through its Template Meta Programming header
namespace asx::asxderivatives::ntp::itch::v1_05 {

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

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 'T')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& seconds_message_ = tmp::read<seconds_message>(data + offset, bound - offset, handler); offset += seconds_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_business_trade_date_message_ = tmp::read<end_of_business_trade_date_message>(data + offset, bound - offset, handler); offset += end_of_business_trade_date_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'f')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& future_symbol_directory_message_ = tmp::read<future_symbol_directory_message>(data + offset, bound - offset, handler); offset += future_symbol_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'h')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_symbol_directory_message_ = tmp::read<options_symbol_directory_message>(data + offset, bound - offset, handler); offset += options_symbol_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'M')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& combination_symbol_directory_message_ = tmp::read<combination_symbol_directory_message>(data + offset, bound - offset, handler); offset += combination_symbol_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'm')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& bundles_symbol_directory_ = tmp::read<bundles_symbol_directory>(data + offset, bound - offset, handler); offset += bundles_symbol_directory::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_book_state_message_ = tmp::read<order_book_state_message>(data + offset, bound - offset, handler); offset += order_book_state_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_message_ = tmp::read<add_order_message>(data + offset, bound - offset, handler); offset += add_order_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_volume_cancelled_message_ = tmp::read<order_volume_cancelled_message>(data + offset, bound - offset, handler); offset += order_volume_cancelled_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_deleted_message_ = tmp::read<order_deleted_message>(data + offset, bound - offset, handler); offset += order_deleted_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'E')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_executed_message_ = tmp::read<order_executed_message>(data + offset, bound - offset, handler); offset += order_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& auction_order_executed_message_ = tmp::read<auction_order_executed_message>(data + offset, bound - offset, handler); offset += auction_order_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'e')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& combination_order_executed_message_ = tmp::read<combination_order_executed_message>(data + offset, bound - offset, handler); offset += combination_order_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'j')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& implied_order_added_message_ = tmp::read<implied_order_added_message>(data + offset, bound - offset, handler); offset += implied_order_added_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'l')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& implied_order_replaced_message_ = tmp::read<implied_order_replaced_message>(data + offset, bound - offset, handler); offset += implied_order_replaced_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'k')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& implied_order_deleted_message_ = tmp::read<implied_order_deleted_message>(data + offset, bound - offset, handler); offset += implied_order_deleted_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_executed_message_ = tmp::read<trade_executed_message>(data + offset, bound - offset, handler); offset += trade_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'p')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& combination_trade_executed_message_ = tmp::read<combination_trade_executed_message>(data + offset, bound - offset, handler); offset += combination_trade_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_cancellation_message_ = tmp::read<trade_cancellation_message>(data + offset, bound - offset, handler); offset += trade_cancellation_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Z')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& equilibrium_price_message_ = tmp::read<equilibrium_price_message>(data + offset, bound - offset, handler); offset += equilibrium_price_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 't')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& open_high_low_last_trade_adjustment_message_ = tmp::read<open_high_low_last_trade_adjustment_message>(data + offset, bound - offset, handler); offset += open_high_low_last_trade_adjustment_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Y')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& market_settlement_message_ = tmp::read<market_settlement_message>(data + offset, bound - offset, handler); offset += market_settlement_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'x')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& text_message_ = tmp::read<text_message>(data + offset, bound - offset, handler); offset += text_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& request_for_quote_message_ = tmp::read<request_for_quote_message>(data + offset, bound - offset, handler); offset += request_for_quote_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'W')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& anomalous_order_threshold_publish_message_ = tmp::read<anomalous_order_threshold_publish_message>(data + offset, bound - offset, handler); offset += anomalous_order_threshold_publish_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'V')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& volume_and_open_interest_message_ = tmp::read<volume_and_open_interest_message>(data + offset, bound - offset, handler); offset += volume_and_open_interest_message::size;
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
        parse_payload(data + offset, size, handler, message_header_.template get<message_type>());
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


} // namespace asx::asxderivatives::ntp::itch::v1_05

namespace protocol = ::asx::asxderivatives::ntp::itch::v1_05;

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

    void operator()(const protocol::seconds_message& message) {
        if constexpr (requires { message.template get<protocol::second>(); }) { checksum += bench::digest(message.template get<protocol::second>().value()); }
    }

    void operator()(const protocol::end_of_business_trade_date_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::event_code>(); }) { checksum += bench::digest(message.template get<protocol::event_code>().value()); }
    }

    void operator()(const protocol::future_symbol_directory_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_name>(); }) { checksum += bench::digest(message.template get<protocol::symbol_name>().value()); }
        if constexpr (requires { message.template get<protocol::long_name>(); }) { checksum += bench::digest(message.template get<protocol::long_name>().value()); }
        if constexpr (requires { message.template get<protocol::isin>(); }) { checksum += bench::digest(message.template get<protocol::isin>().value()); }
        if constexpr (requires { message.template get<protocol::exchange>(); }) { checksum += bench::digest(message.template get<protocol::exchange>().value()); }
        if constexpr (requires { message.template get<protocol::instrument>(); }) { checksum += bench::digest(message.template get<protocol::instrument>().value()); }
        if constexpr (requires { message.template get<protocol::cfi_code>(); }) { checksum += bench::digest(message.template get<protocol::cfi_code>().value()); }
        if constexpr (requires { message.template get<protocol::expiry_year>(); }) { checksum += bench::digest(message.template get<protocol::expiry_year>().value()); }
        if constexpr (requires { message.template get<protocol::expiry_month>(); }) { checksum += bench::digest(message.template get<protocol::expiry_month>().value()); }
        if constexpr (requires { message.template get<protocol::price_display_decimals>(); }) { checksum += bench::digest(message.template get<protocol::price_display_decimals>().value()); }
        if constexpr (requires { message.template get<protocol::price_fractional_denominator>(); }) { checksum += bench::digest(message.template get<protocol::price_fractional_denominator>().value()); }
        if constexpr (requires { message.template get<protocol::price_minimum_tick>(); }) { checksum += bench::digest(message.template get<protocol::price_minimum_tick>().value()); }
        if constexpr (requires { message.template get<protocol::last_trading_date>(); }) { checksum += bench::digest(message.template get<protocol::last_trading_date>().value()); }
        if constexpr (requires { message.template get<protocol::prior_day_settlement>(); }) { checksum += bench::digest(message.template get<protocol::prior_day_settlement>().value()); }
        if constexpr (requires { message.template get<protocol::currency>(); }) { checksum += bench::digest(message.template get<protocol::currency>().value()); }
        if constexpr (requires { message.template get<protocol::lot_size_or_face_value>(); }) { checksum += bench::digest(message.template get<protocol::lot_size_or_face_value>().value()); }
        if constexpr (requires { message.template get<protocol::maturity_value>(); }) { checksum += bench::digest(message.template get<protocol::maturity_value>().value()); }
        if constexpr (requires { message.template get<protocol::coupon_rate>(); }) { checksum += bench::digest(message.template get<protocol::coupon_rate>().value()); }
        if constexpr (requires { message.template get<protocol::payments_per_year>(); }) { checksum += bench::digest(message.template get<protocol::payments_per_year>().value()); }
        if constexpr (requires { message.template get<protocol::block_lot_size>(); }) { checksum += bench::digest(message.template get<protocol::block_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::expiry_date>(); }) { checksum += bench::digest(message.template get<protocol::expiry_date>().value()); }
    }

    void operator()(const protocol::options_symbol_directory_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_name>(); }) { checksum += bench::digest(message.template get<protocol::symbol_name>().value()); }
        if constexpr (requires { message.template get<protocol::long_name>(); }) { checksum += bench::digest(message.template get<protocol::long_name>().value()); }
        if constexpr (requires { message.template get<protocol::isin>(); }) { checksum += bench::digest(message.template get<protocol::isin>().value()); }
        if constexpr (requires { message.template get<protocol::exchange>(); }) { checksum += bench::digest(message.template get<protocol::exchange>().value()); }
        if constexpr (requires { message.template get<protocol::instrument>(); }) { checksum += bench::digest(message.template get<protocol::instrument>().value()); }
        if constexpr (requires { message.template get<protocol::cfi_code>(); }) { checksum += bench::digest(message.template get<protocol::cfi_code>().value()); }
        if constexpr (requires { message.template get<protocol::expiry_year>(); }) { checksum += bench::digest(message.template get<protocol::expiry_year>().value()); }
        if constexpr (requires { message.template get<protocol::expiry_month>(); }) { checksum += bench::digest(message.template get<protocol::expiry_month>().value()); }
        if constexpr (requires { message.template get<protocol::option_type>(); }) { checksum += bench::digest(message.template get<protocol::option_type>().value()); }
        if constexpr (requires { message.template get<protocol::strike>(); }) { checksum += bench::digest(message.template get<protocol::strike>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::underlying_tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::price_display_decimals>(); }) { checksum += bench::digest(message.template get<protocol::price_display_decimals>().value()); }
        if constexpr (requires { message.template get<protocol::price_fractional_denominator>(); }) { checksum += bench::digest(message.template get<protocol::price_fractional_denominator>().value()); }
        if constexpr (requires { message.template get<protocol::price_minimum_tick>(); }) { checksum += bench::digest(message.template get<protocol::price_minimum_tick>().value()); }
        if constexpr (requires { message.template get<protocol::strike_price_decimal_position>(); }) { checksum += bench::digest(message.template get<protocol::strike_price_decimal_position>().value()); }
        if constexpr (requires { message.template get<protocol::strike_price_fractional_denominator>(); }) { checksum += bench::digest(message.template get<protocol::strike_price_fractional_denominator>().value()); }
        if constexpr (requires { message.template get<protocol::strike_price_minimum_tick>(); }) { checksum += bench::digest(message.template get<protocol::strike_price_minimum_tick>().value()); }
        if constexpr (requires { message.template get<protocol::last_trading_date>(); }) { checksum += bench::digest(message.template get<protocol::last_trading_date>().value()); }
        if constexpr (requires { message.template get<protocol::prior_day_settlement>(); }) { checksum += bench::digest(message.template get<protocol::prior_day_settlement>().value()); }
        if constexpr (requires { message.template get<protocol::volatility>(); }) { checksum += bench::digest(message.template get<protocol::volatility>().value()); }
        if constexpr (requires { message.template get<protocol::currency>(); }) { checksum += bench::digest(message.template get<protocol::currency>().value()); }
        if constexpr (requires { message.template get<protocol::lot_size_or_face_value>(); }) { checksum += bench::digest(message.template get<protocol::lot_size_or_face_value>().value()); }
        if constexpr (requires { message.template get<protocol::maturity_value>(); }) { checksum += bench::digest(message.template get<protocol::maturity_value>().value()); }
        if constexpr (requires { message.template get<protocol::coupon_rate>(); }) { checksum += bench::digest(message.template get<protocol::coupon_rate>().value()); }
        if constexpr (requires { message.template get<protocol::payments_per_year>(); }) { checksum += bench::digest(message.template get<protocol::payments_per_year>().value()); }
        if constexpr (requires { message.template get<protocol::block_lot_size>(); }) { checksum += bench::digest(message.template get<protocol::block_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::expiry_date>(); }) { checksum += bench::digest(message.template get<protocol::expiry_date>().value()); }
        if constexpr (requires { message.template get<protocol::basis_of_quotation>(); }) { checksum += bench::digest(message.template get<protocol::basis_of_quotation>().value()); }
    }

    void operator()(const protocol::combination_symbol_directory_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_name>(); }) { checksum += bench::digest(message.template get<protocol::symbol_name>().value()); }
        if constexpr (requires { message.template get<protocol::long_name>(); }) { checksum += bench::digest(message.template get<protocol::long_name>().value()); }
        if constexpr (requires { message.template get<protocol::cfi_code>(); }) { checksum += bench::digest(message.template get<protocol::cfi_code>().value()); }
        if constexpr (requires { message.template get<protocol::price_method>(); }) { checksum += bench::digest(message.template get<protocol::price_method>().value()); }
        if constexpr (requires { message.template get<protocol::price_display_decimals>(); }) { checksum += bench::digest(message.template get<protocol::price_display_decimals>().value()); }
        if constexpr (requires { message.template get<protocol::price_fractional_denominator>(); }) { checksum += bench::digest(message.template get<protocol::price_fractional_denominator>().value()); }
        if constexpr (requires { message.template get<protocol::price_minimum_tick>(); }) { checksum += bench::digest(message.template get<protocol::price_minimum_tick>().value()); }
        if constexpr (requires { message.template get<protocol::legs>(); }) { checksum += bench::digest(message.template get<protocol::legs>().value()); }
    }

    void operator()(const protocol::bundles_symbol_directory& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_name>(); }) { checksum += bench::digest(message.template get<protocol::symbol_name>().value()); }
        if constexpr (requires { message.template get<protocol::long_name>(); }) { checksum += bench::digest(message.template get<protocol::long_name>().value()); }
        if constexpr (requires { message.template get<protocol::cfi_code>(); }) { checksum += bench::digest(message.template get<protocol::cfi_code>().value()); }
        if constexpr (requires { message.template get<protocol::price_method>(); }) { checksum += bench::digest(message.template get<protocol::price_method>().value()); }
        if constexpr (requires { message.template get<protocol::price_display_decimals>(); }) { checksum += bench::digest(message.template get<protocol::price_display_decimals>().value()); }
        if constexpr (requires { message.template get<protocol::price_fractional_denominator>(); }) { checksum += bench::digest(message.template get<protocol::price_fractional_denominator>().value()); }
        if constexpr (requires { message.template get<protocol::price_minimum_tick>(); }) { checksum += bench::digest(message.template get<protocol::price_minimum_tick>().value()); }
        if constexpr (requires { message.template get<protocol::legs>(); }) { checksum += bench::digest(message.template get<protocol::legs>().value()); }
    }

    void operator()(const protocol::order_book_state_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::session_state>(); }) { checksum += bench::digest(message.template get<protocol::session_state>().value()); }
    }

    void operator()(const protocol::add_order_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_priority>(); }) { checksum += bench::digest(message.template get<protocol::order_book_priority>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::order_volume_cancelled_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
    }

    void operator()(const protocol::order_deleted_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
    }

    void operator()(const protocol::order_executed_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity_remaining>(); }) { checksum += bench::digest(message.template get<protocol::quantity_remaining>().value()); }
        if constexpr (requires { message.template get<protocol::trade_type>(); }) { checksum += bench::digest(message.template get<protocol::trade_type>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { checksum += bench::digest(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { checksum += bench::digest(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::combination_trade_id>(); }) { checksum += bench::digest(message.template get<protocol::combination_trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::counter_party_id>(); }) { checksum += bench::digest(message.template get<protocol::counter_party_id>().value()); }
    }

    void operator()(const protocol::auction_order_executed_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity_remaining>(); }) { checksum += bench::digest(message.template get<protocol::quantity_remaining>().value()); }
        if constexpr (requires { message.template get<protocol::trade_type>(); }) { checksum += bench::digest(message.template get<protocol::trade_type>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { checksum += bench::digest(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { checksum += bench::digest(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::opposite_order_id>(); }) { checksum += bench::digest(message.template get<protocol::opposite_order_id>().value()); }
    }

    void operator()(const protocol::combination_order_executed_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity_remaining>(); }) { checksum += bench::digest(message.template get<protocol::quantity_remaining>().value()); }
        if constexpr (requires { message.template get<protocol::trade_type>(); }) { checksum += bench::digest(message.template get<protocol::trade_type>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { checksum += bench::digest(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { checksum += bench::digest(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::opposite_tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::opposite_tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::opposite_side>(); }) { checksum += bench::digest(message.template get<protocol::opposite_side>().value()); }
        if constexpr (requires { message.template get<protocol::opposite_order_id>(); }) { checksum += bench::digest(message.template get<protocol::opposite_order_id>().value()); }
        if constexpr (requires { message.template get<protocol::combination_trade_id>(); }) { checksum += bench::digest(message.template get<protocol::combination_trade_id>().value()); }
    }

    void operator()(const protocol::implied_order_added_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_priority>(); }) { checksum += bench::digest(message.template get<protocol::order_book_priority>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::implied_order_replaced_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_priority>(); }) { checksum += bench::digest(message.template get<protocol::order_book_priority>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::implied_order_deleted_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
    }

    void operator()(const protocol::trade_executed_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_type>(); }) { checksum += bench::digest(message.template get<protocol::trade_type>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { checksum += bench::digest(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { checksum += bench::digest(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::combination_trade_id>(); }) { checksum += bench::digest(message.template get<protocol::combination_trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::participant_id_buyer>(); }) { checksum += bench::digest(message.template get<protocol::participant_id_buyer>().value()); }
        if constexpr (requires { message.template get<protocol::participant_id_seller>(); }) { checksum += bench::digest(message.template get<protocol::participant_id_seller>().value()); }
    }

    void operator()(const protocol::combination_trade_executed_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_type>(); }) { checksum += bench::digest(message.template get<protocol::trade_type>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { checksum += bench::digest(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { checksum += bench::digest(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::buyer_tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::buyer_tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::buyer_side>(); }) { checksum += bench::digest(message.template get<protocol::buyer_side>().value()); }
        if constexpr (requires { message.template get<protocol::buyer_order_id>(); }) { checksum += bench::digest(message.template get<protocol::buyer_order_id>().value()); }
        if constexpr (requires { message.template get<protocol::buyer_combination_trade_id>(); }) { checksum += bench::digest(message.template get<protocol::buyer_combination_trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::buyer_participant_id>(); }) { checksum += bench::digest(message.template get<protocol::buyer_participant_id>().value()); }
        if constexpr (requires { message.template get<protocol::seller_tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::seller_tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::seller_side>(); }) { checksum += bench::digest(message.template get<protocol::seller_side>().value()); }
        if constexpr (requires { message.template get<protocol::seller_order_id>(); }) { checksum += bench::digest(message.template get<protocol::seller_order_id>().value()); }
        if constexpr (requires { message.template get<protocol::seller_combination_trade_id>(); }) { checksum += bench::digest(message.template get<protocol::seller_combination_trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::seller_participant_id>(); }) { checksum += bench::digest(message.template get<protocol::seller_participant_id>().value()); }
    }

    void operator()(const protocol::trade_cancellation_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
    }

    void operator()(const protocol::equilibrium_price_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::equilibrium_price>(); }) { checksum += bench::digest(message.template get<protocol::equilibrium_price>().value()); }
        if constexpr (requires { message.template get<protocol::matched_quantity>(); }) { checksum += bench::digest(message.template get<protocol::matched_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::bid_quantity>(); }) { checksum += bench::digest(message.template get<protocol::bid_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::ask_quantity>(); }) { checksum += bench::digest(message.template get<protocol::ask_quantity>().value()); }
    }

    void operator()(const protocol::open_high_low_last_trade_adjustment_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::opening_trade>(); }) { checksum += bench::digest(message.template get<protocol::opening_trade>().value()); }
        if constexpr (requires { message.template get<protocol::highest_trade>(); }) { checksum += bench::digest(message.template get<protocol::highest_trade>().value()); }
        if constexpr (requires { message.template get<protocol::lowest_trade>(); }) { checksum += bench::digest(message.template get<protocol::lowest_trade>().value()); }
        if constexpr (requires { message.template get<protocol::last_trade>(); }) { checksum += bench::digest(message.template get<protocol::last_trade>().value()); }
        if constexpr (requires { message.template get<protocol::last_volume>(); }) { checksum += bench::digest(message.template get<protocol::last_volume>().value()); }
        if constexpr (requires { message.template get<protocol::total_traded_volume>(); }) { checksum += bench::digest(message.template get<protocol::total_traded_volume>().value()); }
    }

    void operator()(const protocol::market_settlement_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::opening_trade>(); }) { checksum += bench::digest(message.template get<protocol::opening_trade>().value()); }
        if constexpr (requires { message.template get<protocol::highest_trade>(); }) { checksum += bench::digest(message.template get<protocol::highest_trade>().value()); }
        if constexpr (requires { message.template get<protocol::lowest_trade>(); }) { checksum += bench::digest(message.template get<protocol::lowest_trade>().value()); }
        if constexpr (requires { message.template get<protocol::last_trade>(); }) { checksum += bench::digest(message.template get<protocol::last_trade>().value()); }
        if constexpr (requires { message.template get<protocol::last_volume>(); }) { checksum += bench::digest(message.template get<protocol::last_volume>().value()); }
        if constexpr (requires { message.template get<protocol::total_traded_volume>(); }) { checksum += bench::digest(message.template get<protocol::total_traded_volume>().value()); }
    }

    void operator()(const protocol::text_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::source_id>(); }) { checksum += bench::digest(message.template get<protocol::source_id>().value()); }
        if constexpr (requires { message.template get<protocol::text>(); }) { checksum += bench::digest(message.template get<protocol::text>().value()); }
    }

    void operator()(const protocol::request_for_quote_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::rfq_side>(); }) { checksum += bench::digest(message.template get<protocol::rfq_side>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
    }

    void operator()(const protocol::anomalous_order_threshold_publish_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::aot_price>(); }) { checksum += bench::digest(message.template get<protocol::aot_price>().value()); }
        if constexpr (requires { message.template get<protocol::aot_upper_price>(); }) { checksum += bench::digest(message.template get<protocol::aot_upper_price>().value()); }
        if constexpr (requires { message.template get<protocol::aot_lower_price>(); }) { checksum += bench::digest(message.template get<protocol::aot_lower_price>().value()); }
        if constexpr (requires { message.template get<protocol::etr_price>(); }) { checksum += bench::digest(message.template get<protocol::etr_price>().value()); }
        if constexpr (requires { message.template get<protocol::etr_upper_price>(); }) { checksum += bench::digest(message.template get<protocol::etr_upper_price>().value()); }
        if constexpr (requires { message.template get<protocol::etr_lower_price>(); }) { checksum += bench::digest(message.template get<protocol::etr_lower_price>().value()); }
    }

    void operator()(const protocol::volume_and_open_interest_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { checksum += bench::digest(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::cumulative_volume>(); }) { checksum += bench::digest(message.template get<protocol::cumulative_volume>().value()); }
        if constexpr (requires { message.template get<protocol::open_interest>(); }) { checksum += bench::digest(message.template get<protocol::open_interest>().value()); }
        if constexpr (requires { message.template get<protocol::voi_trade_date>(); }) { checksum += bench::digest(message.template get<protocol::voi_trade_date>().value()); }
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
    return bench::run("Asx.AsxDerivatives.Ntp.Itch.v1.05", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
