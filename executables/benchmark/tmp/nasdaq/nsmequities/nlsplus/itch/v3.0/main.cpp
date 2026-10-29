// Nasdaq.NsmEquities.NlsPlus.Itch.v3.0 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/nlsplus/itch/v3.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/nasdaq/nsmequities/nlsplus/itch/v3.0/nasdaq_nsmequities_nlsplus_itch_v3_0.hpp"

// Nasdaq NsmEquities NlsPlus Itch 3.0: the reading of its packets, through its Template Meta Programming header
namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

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

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_event_message_ = tmp::read<system_event_message>(data + offset, bound - offset, handler); offset += system_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'T')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_report_message_ = tmp::read<trade_report_message>(data + offset, bound - offset, handler); offset += trade_report_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 't')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& long_form_trade_report_message_ = tmp::read<long_form_trade_report_message>(data + offset, bound - offset, handler); offset += long_form_trade_report_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'M')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& next_shares_trade_report_message_ = tmp::read<next_shares_trade_report_message>(data + offset, bound - offset, handler); offset += next_shares_trade_report_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_cancel_error_message_ = tmp::read<trade_cancel_error_message>(data + offset, bound - offset, handler); offset += trade_cancel_error_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'x')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& long_form_trade_cancel_error_message_ = tmp::read<long_form_trade_cancel_error_message>(data + offset, bound - offset, handler); offset += long_form_trade_cancel_error_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& next_shares_trade_cancel_error_message_ = tmp::read<next_shares_trade_cancel_error_message>(data + offset, bound - offset, handler); offset += next_shares_trade_cancel_error_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_correction_message_ = tmp::read<trade_correction_message>(data + offset, bound - offset, handler); offset += trade_correction_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'c')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& long_form_trade_correction_message_ = tmp::read<long_form_trade_correction_message>(data + offset, bound - offset, handler); offset += long_form_trade_correction_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Z')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& next_shares_trade_correction_message_ = tmp::read<next_shares_trade_correction_message>(data + offset, bound - offset, handler); offset += next_shares_trade_correction_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& stock_trading_action_message_ = tmp::read<stock_trading_action_message>(data + offset, bound - offset, handler); offset += stock_trading_action_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& stock_directory_message_ = tmp::read<stock_directory_message>(data + offset, bound - offset, handler); offset += stock_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Y')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reg_sho_short_sale_price_test_restricted_indicator_message_ = tmp::read<reg_sho_short_sale_price_test_restricted_indicator_message>(data + offset, bound - offset, handler); offset += reg_sho_short_sale_price_test_restricted_indicator_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'G')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& adjusted_closing_price_message_ = tmp::read<adjusted_closing_price_message>(data + offset, bound - offset, handler); offset += adjusted_closing_price_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'g')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& long_form_adjusted_closing_price_message_ = tmp::read<long_form_adjusted_closing_price_message>(data + offset, bound - offset, handler); offset += long_form_adjusted_closing_price_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'J')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_day_trade_summary_message_ = tmp::read<end_of_day_trade_summary_message>(data + offset, bound - offset, handler); offset += end_of_day_trade_summary_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'j')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& long_form_end_of_day_trade_summary_message_ = tmp::read<long_form_end_of_day_trade_summary_message>(data + offset, bound - offset, handler); offset += long_form_end_of_day_trade_summary_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'N')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& next_shares_end_of_day_trade_summary_message_ = tmp::read<next_shares_end_of_day_trade_summary_message>(data + offset, bound - offset, handler); offset += next_shares_end_of_day_trade_summary_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'I')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& ipo_information_message_ = tmp::read<ipo_information_message>(data + offset, bound - offset, handler); offset += ipo_information_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'V')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& mwcb_decline_level_message_ = tmp::read<mwcb_decline_level_message>(data + offset, bound - offset, handler); offset += mwcb_decline_level_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'W')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& mwcb_status_message_ = tmp::read<mwcb_status_message>(data + offset, bound - offset, handler); offset += mwcb_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'K')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& ipo_quoting_period_update_message_ = tmp::read<ipo_quoting_period_update_message>(data + offset, bound - offset, handler); offset += ipo_quoting_period_update_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'h')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& operational_halt_message_ = tmp::read<operational_halt_message>(data + offset, bound - offset, handler); offset += operational_halt_message::size;
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
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_length>()))) - 9);
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


} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0

namespace protocol = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

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
        if constexpr (requires { header.template get<protocol::tracking_number>(); }) { checksum += bench::digest(header.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { header.template get<protocol::timestamp>(); }) { checksum += bench::digest(header.template get<protocol::timestamp>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { checksum += bench::digest(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::system_event_message& message) {
        if constexpr (requires { message.template get<protocol::event_code>(); }) { checksum += bench::digest(message.template get<protocol::event_code>().value()); }
    }

    void operator()(const protocol::trade_report_message& message) {
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { checksum += bench::digest(message.template get<protocol::originating_market_center_identifier>().value()); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::trade_control_number>(); }) { checksum += bench::digest(message.template get<protocol::trade_control_number>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { checksum += bench::digest(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::trade_size>(); }) { checksum += bench::digest(message.template get<protocol::trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::long_form_trade_report_message& message) {
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { checksum += bench::digest(message.template get<protocol::originating_market_center_identifier>().value()); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::trade_control_number>(); }) { checksum += bench::digest(message.template get<protocol::trade_control_number>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price_long>(); }) { checksum += bench::digest(message.template get<protocol::trade_price_long>().value()); }
        if constexpr (requires { message.template get<protocol::trade_size>(); }) { checksum += bench::digest(message.template get<protocol::trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::next_shares_trade_report_message& message) {
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { checksum += bench::digest(message.template get<protocol::originating_market_center_identifier>().value()); }
        if constexpr (requires { message.template get<protocol::next_shares_symbol>(); }) { checksum += bench::digest(message.template get<protocol::next_shares_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::trade_control_number>(); }) { checksum += bench::digest(message.template get<protocol::trade_control_number>().value()); }
        if constexpr (requires { message.template get<protocol::proxy_price>(); }) { checksum += bench::digest(message.template get<protocol::proxy_price>().value()); }
        if constexpr (requires { message.template get<protocol::trade_size>(); }) { checksum += bench::digest(message.template get<protocol::trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::nav_offset_amount>(); }) { checksum += bench::digest(message.template get<protocol::nav_offset_amount>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::trade_cancel_error_message& message) {
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { checksum += bench::digest(message.template get<protocol::originating_market_center_identifier>().value()); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_control_number>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_control_number>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_price>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_size>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::long_form_trade_cancel_error_message& message) {
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { checksum += bench::digest(message.template get<protocol::originating_market_center_identifier>().value()); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_control_number>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_control_number>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_price_long>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_price_long>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_size>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::next_shares_trade_cancel_error_message& message) {
        if constexpr (requires { message.template get<protocol::market_center>(); }) { checksum += bench::digest(message.template get<protocol::market_center>().value()); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_control_number>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_control_number>().value()); }
        if constexpr (requires { message.template get<protocol::original_proxy_price>(); }) { checksum += bench::digest(message.template get<protocol::original_proxy_price>().value()); }
        if constexpr (requires { message.template get<protocol::original_nav_offset_amount>(); }) { checksum += bench::digest(message.template get<protocol::original_nav_offset_amount>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_size>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::trade_correction_message& message) {
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { checksum += bench::digest(message.template get<protocol::originating_market_center_identifier>().value()); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_control_number>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_control_number>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_price>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_size>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_trade_control_number>(); }) { checksum += bench::digest(message.template get<protocol::corrected_trade_control_number>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_trade_price>(); }) { checksum += bench::digest(message.template get<protocol::corrected_trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_trade_size>(); }) { checksum += bench::digest(message.template get<protocol::corrected_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::long_form_trade_correction_message& message) {
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { checksum += bench::digest(message.template get<protocol::originating_market_center_identifier>().value()); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_control_number>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_control_number>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_price_long>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_price_long>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_size>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_trade_control_number>(); }) { checksum += bench::digest(message.template get<protocol::corrected_trade_control_number>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_trade_price_long>(); }) { checksum += bench::digest(message.template get<protocol::corrected_trade_price_long>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_trade_size>(); }) { checksum += bench::digest(message.template get<protocol::corrected_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::next_shares_trade_correction_message& message) {
        if constexpr (requires { message.template get<protocol::market_center>(); }) { checksum += bench::digest(message.template get<protocol::market_center>().value()); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_control_number>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_control_number>().value()); }
        if constexpr (requires { message.template get<protocol::original_proxy_price>(); }) { checksum += bench::digest(message.template get<protocol::original_proxy_price>().value()); }
        if constexpr (requires { message.template get<protocol::original_nav_offset_amount>(); }) { checksum += bench::digest(message.template get<protocol::original_nav_offset_amount>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_size>(); }) { checksum += bench::digest(message.template get<protocol::original_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_trade_control_number>(); }) { checksum += bench::digest(message.template get<protocol::corrected_trade_control_number>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_proxy_price>(); }) { checksum += bench::digest(message.template get<protocol::corrected_proxy_price>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_nav_offset_amount>(); }) { checksum += bench::digest(message.template get<protocol::corrected_nav_offset_amount>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_trade_size>(); }) { checksum += bench::digest(message.template get<protocol::corrected_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::stock_trading_action_message& message) {
        if constexpr (requires { message.template get<protocol::reserved>(); }) { checksum += bench::digest(message.template get<protocol::reserved>().value()); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::current_trading_state>(); }) { checksum += bench::digest(message.template get<protocol::current_trading_state>().value()); }
        if constexpr (requires { message.template get<protocol::reason>(); }) { checksum += bench::digest(message.template get<protocol::reason>().value()); }
    }

    void operator()(const protocol::stock_directory_message& message) {
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::market_category>(); }) { checksum += bench::digest(message.template get<protocol::market_category>().value()); }
        if constexpr (requires { message.template get<protocol::financial_status_indicator>(); }) { checksum += bench::digest(message.template get<protocol::financial_status_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::round_lot_size>(); }) { checksum += bench::digest(message.template get<protocol::round_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::round_lots_only>(); }) { checksum += bench::digest(message.template get<protocol::round_lots_only>().value()); }
        if constexpr (requires { message.template get<protocol::issue_classification>(); }) { checksum += bench::digest(message.template get<protocol::issue_classification>().value()); }
        if constexpr (requires { message.template get<protocol::issue_sub_type>(); }) { checksum += bench::digest(message.template get<protocol::issue_sub_type>().value()); }
        if constexpr (requires { message.template get<protocol::authenticity>(); }) { checksum += bench::digest(message.template get<protocol::authenticity>().value()); }
        if constexpr (requires { message.template get<protocol::short_sale_threshold_indicator>(); }) { checksum += bench::digest(message.template get<protocol::short_sale_threshold_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::ipo_flag>(); }) { checksum += bench::digest(message.template get<protocol::ipo_flag>().value()); }
        if constexpr (requires { message.template get<protocol::luld_reference_price_tier>(); }) { checksum += bench::digest(message.template get<protocol::luld_reference_price_tier>().value()); }
        if constexpr (requires { message.template get<protocol::etp_flag>(); }) { checksum += bench::digest(message.template get<protocol::etp_flag>().value()); }
        if constexpr (requires { message.template get<protocol::etp_leverage_factor>(); }) { checksum += bench::digest(message.template get<protocol::etp_leverage_factor>().value()); }
        if constexpr (requires { message.template get<protocol::inverse_indicator>(); }) { checksum += bench::digest(message.template get<protocol::inverse_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::bloomberg_id>(); }) { checksum += bench::digest(message.template get<protocol::bloomberg_id>().value()); }
    }

    void operator()(const protocol::reg_sho_short_sale_price_test_restricted_indicator_message& message) {
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::reg_sho_action>(); }) { checksum += bench::digest(message.template get<protocol::reg_sho_action>().value()); }
    }

    void operator()(const protocol::adjusted_closing_price_message& message) {
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::adjusted_closing_price>(); }) { checksum += bench::digest(message.template get<protocol::adjusted_closing_price>().value()); }
    }

    void operator()(const protocol::long_form_adjusted_closing_price_message& message) {
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::adjusted_closing_price_long>(); }) { checksum += bench::digest(message.template get<protocol::adjusted_closing_price_long>().value()); }
    }

    void operator()(const protocol::end_of_day_trade_summary_message& message) {
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::market_category>(); }) { checksum += bench::digest(message.template get<protocol::market_category>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_high_price>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_high_price>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_low_price>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_low_price>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_closing_price>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_closing_price>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_volume>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_open_price>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_open_price>().value()); }
    }

    void operator()(const protocol::long_form_end_of_day_trade_summary_message& message) {
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::market_category>(); }) { checksum += bench::digest(message.template get<protocol::market_category>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_high_price_long>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_high_price_long>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_low_price_long>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_low_price_long>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_closing_price_long>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_closing_price_long>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_volume>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_open_price_long>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_open_price_long>().value()); }
    }

    void operator()(const protocol::next_shares_end_of_day_trade_summary_message& message) {
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::market_category>(); }) { checksum += bench::digest(message.template get<protocol::market_category>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_high_price>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_high_price>().value()); }
        if constexpr (requires { message.template get<protocol::nav_offset_amount_high>(); }) { checksum += bench::digest(message.template get<protocol::nav_offset_amount_high>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_low_price>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_low_price>().value()); }
        if constexpr (requires { message.template get<protocol::nav_offset_amount_low>(); }) { checksum += bench::digest(message.template get<protocol::nav_offset_amount_low>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_closing_price>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_closing_price>().value()); }
        if constexpr (requires { message.template get<protocol::nav_offset_amount_closing>(); }) { checksum += bench::digest(message.template get<protocol::nav_offset_amount_closing>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_volume>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_open_price>(); }) { checksum += bench::digest(message.template get<protocol::consolidated_open_price>().value()); }
        if constexpr (requires { message.template get<protocol::nav_offset_amount_open>(); }) { checksum += bench::digest(message.template get<protocol::nav_offset_amount_open>().value()); }
    }

    void operator()(const protocol::ipo_information_message& message) {
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { checksum += bench::digest(message.template get<protocol::issue_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { checksum += bench::digest(message.template get<protocol::security_class>().value()); }
        if constexpr (requires { message.template get<protocol::reference_for_net_change>(); }) { checksum += bench::digest(message.template get<protocol::reference_for_net_change>().value()); }
        if constexpr (requires { message.template get<protocol::reference_price>(); }) { checksum += bench::digest(message.template get<protocol::reference_price>().value()); }
    }

    void operator()(const protocol::mwcb_decline_level_message& message) {
        if constexpr (requires { message.template get<protocol::level_1>(); }) { checksum += bench::digest(message.template get<protocol::level_1>().value()); }
        if constexpr (requires { message.template get<protocol::level_2>(); }) { checksum += bench::digest(message.template get<protocol::level_2>().value()); }
        if constexpr (requires { message.template get<protocol::level_3>(); }) { checksum += bench::digest(message.template get<protocol::level_3>().value()); }
    }

    void operator()(const protocol::mwcb_status_message& message) {
        if constexpr (requires { message.template get<protocol::breached_level>(); }) { checksum += bench::digest(message.template get<protocol::breached_level>().value()); }
    }

    void operator()(const protocol::ipo_quoting_period_update_message& message) {
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::ipo_quotation_release_time>(); }) { checksum += bench::digest(message.template get<protocol::ipo_quotation_release_time>().value()); }
        if constexpr (requires { message.template get<protocol::ipo_quotation_release_qualifier>(); }) { checksum += bench::digest(message.template get<protocol::ipo_quotation_release_qualifier>().value()); }
        if constexpr (requires { message.template get<protocol::ipo_price>(); }) { checksum += bench::digest(message.template get<protocol::ipo_price>().value()); }
    }

    void operator()(const protocol::operational_halt_message& message) {
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::market_code>(); }) { checksum += bench::digest(message.template get<protocol::market_code>().value()); }
        if constexpr (requires { message.template get<protocol::operational_halt_action>(); }) { checksum += bench::digest(message.template get<protocol::operational_halt_action>().value()); }
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
    return bench::run("Nasdaq.NsmEquities.NlsPlus.Itch.v3.0", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
