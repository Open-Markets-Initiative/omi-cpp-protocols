// Nasdaq.NsmEquities.NlsPlus.Itch.v3.0 canonical values, through the Tmp header: every value the Tmp reading hands
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
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::session>(); }) { values["packet.packetheader.session"] = canonical::text(std::string(header.template get<protocol::session>().value()), '\0', false); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { values["packet.packetheader.sequencenumber"] = canonical::number(header.template get<protocol::sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { values["packet.packetheader.messagecount"] = canonical::number(header.template get<protocol::message_count>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.messages.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::message_length>(); }) { values[entry + ".messageheader.messagelength"] = canonical::number(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::tracking_number>(); }) { values[entry + ".messageheader.trackingnumber"] = canonical::number(header.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { header.template get<protocol::timestamp>(); }) { values[entry + ".messageheader.timestamp"] = canonical::number(header.template get<protocol::timestamp>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(header.template get<protocol::message_type>().value())); }
    }

    void operator()(const protocol::system_event_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
        if constexpr (requires { message.template get<protocol::event_code>(); }) { values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message.template get<protocol::event_code>().value()), ' ', false); }
    }

    void operator()(const protocol::trade_report_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.tradereportmessage";
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { values[entry + ".payload.tradereportmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.template get<protocol::originating_market_center_identifier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.tradereportmessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.tradereportmessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_control_number>(); }) { values[entry + ".payload.tradereportmessage.tradecontrolnumber"] = canonical::text(std::string(message.template get<protocol::trade_control_number>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { values[entry + ".payload.tradereportmessage.tradeprice"] = canonical::scaled(message.template get<protocol::trade_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::trade_size>(); }) { values[entry + ".payload.tradereportmessage.tradesize"] = canonical::number(message.template get<protocol::trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { values[entry + ".payload.tradereportmessage.consolidatedvolume"] = canonical::number(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::long_form_trade_report_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.longformtradereportmessage";
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { values[entry + ".payload.longformtradereportmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.template get<protocol::originating_market_center_identifier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.longformtradereportmessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.longformtradereportmessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_control_number>(); }) { values[entry + ".payload.longformtradereportmessage.tradecontrolnumber"] = canonical::text(std::string(message.template get<protocol::trade_control_number>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_price_long>(); }) { values[entry + ".payload.longformtradereportmessage.tradepricelong"] = canonical::scaled(message.template get<protocol::trade_price_long>().value(), -4); }
        if constexpr (requires { message.template get<protocol::trade_size>(); }) { values[entry + ".payload.longformtradereportmessage.tradesize"] = canonical::number(message.template get<protocol::trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { values[entry + ".payload.longformtradereportmessage.consolidatedvolume"] = canonical::number(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::next_shares_trade_report_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.nextsharestradereportmessage";
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { values[entry + ".payload.nextsharestradereportmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.template get<protocol::originating_market_center_identifier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::next_shares_symbol>(); }) { values[entry + ".payload.nextsharestradereportmessage.nextsharessymbol"] = canonical::text(std::string(message.template get<protocol::next_shares_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.nextsharestradereportmessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_control_number>(); }) { values[entry + ".payload.nextsharestradereportmessage.tradecontrolnumber"] = canonical::text(std::string(message.template get<protocol::trade_control_number>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::proxy_price>(); }) { values[entry + ".payload.nextsharestradereportmessage.proxyprice"] = canonical::scaled(message.template get<protocol::proxy_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::trade_size>(); }) { values[entry + ".payload.nextsharestradereportmessage.tradesize"] = canonical::number(message.template get<protocol::trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::nav_offset_amount>(); }) { values[entry + ".payload.nextsharestradereportmessage.navoffsetamount"] = canonical::scaled(message.template get<protocol::nav_offset_amount>().value(), -4); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { values[entry + ".payload.nextsharestradereportmessage.consolidatedvolume"] = canonical::number(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::trade_cancel_error_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.tradecancelerrormessage";
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { values[entry + ".payload.tradecancelerrormessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.template get<protocol::originating_market_center_identifier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.tradecancelerrormessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.tradecancelerrormessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_trade_control_number>(); }) { values[entry + ".payload.tradecancelerrormessage.originaltradecontrolnumber"] = canonical::text(std::string(message.template get<protocol::original_trade_control_number>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_trade_price>(); }) { values[entry + ".payload.tradecancelerrormessage.originaltradeprice"] = canonical::scaled(message.template get<protocol::original_trade_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::original_trade_size>(); }) { values[entry + ".payload.tradecancelerrormessage.originaltradesize"] = canonical::number(message.template get<protocol::original_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { values[entry + ".payload.tradecancelerrormessage.consolidatedvolume"] = canonical::number(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::long_form_trade_cancel_error_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.longformtradecancelerrormessage";
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { values[entry + ".payload.longformtradecancelerrormessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.template get<protocol::originating_market_center_identifier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.longformtradecancelerrormessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.longformtradecancelerrormessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_trade_control_number>(); }) { values[entry + ".payload.longformtradecancelerrormessage.originaltradecontrolnumber"] = canonical::text(std::string(message.template get<protocol::original_trade_control_number>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_trade_price_long>(); }) { values[entry + ".payload.longformtradecancelerrormessage.originaltradepricelong"] = canonical::scaled(message.template get<protocol::original_trade_price_long>().value(), -4); }
        if constexpr (requires { message.template get<protocol::original_trade_size>(); }) { values[entry + ".payload.longformtradecancelerrormessage.originaltradesize"] = canonical::number(message.template get<protocol::original_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { values[entry + ".payload.longformtradecancelerrormessage.consolidatedvolume"] = canonical::number(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::next_shares_trade_cancel_error_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.nextsharestradecancelerrormessage";
        if constexpr (requires { message.template get<protocol::market_center>(); }) { values[entry + ".payload.nextsharestradecancelerrormessage.marketcenter"] = canonical::text(canonical::character(message.template get<protocol::market_center>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.nextsharestradecancelerrormessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.nextsharestradecancelerrormessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_trade_control_number>(); }) { values[entry + ".payload.nextsharestradecancelerrormessage.originaltradecontrolnumber"] = canonical::text(std::string(message.template get<protocol::original_trade_control_number>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_proxy_price>(); }) { values[entry + ".payload.nextsharestradecancelerrormessage.originalproxyprice"] = canonical::scaled(message.template get<protocol::original_proxy_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::original_nav_offset_amount>(); }) { values[entry + ".payload.nextsharestradecancelerrormessage.originalnavoffsetamount"] = canonical::scaled(message.template get<protocol::original_nav_offset_amount>().value(), -4); }
        if constexpr (requires { message.template get<protocol::original_trade_size>(); }) { values[entry + ".payload.nextsharestradecancelerrormessage.originaltradesize"] = canonical::number(message.template get<protocol::original_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { values[entry + ".payload.nextsharestradecancelerrormessage.consolidatedvolume"] = canonical::number(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::trade_correction_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.tradecorrectionmessage";
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { values[entry + ".payload.tradecorrectionmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.template get<protocol::originating_market_center_identifier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.tradecorrectionmessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.tradecorrectionmessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_trade_control_number>(); }) { values[entry + ".payload.tradecorrectionmessage.originaltradecontrolnumber"] = canonical::text(std::string(message.template get<protocol::original_trade_control_number>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_trade_price>(); }) { values[entry + ".payload.tradecorrectionmessage.originaltradeprice"] = canonical::scaled(message.template get<protocol::original_trade_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::original_trade_size>(); }) { values[entry + ".payload.tradecorrectionmessage.originaltradesize"] = canonical::number(message.template get<protocol::original_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_trade_control_number>(); }) { values[entry + ".payload.tradecorrectionmessage.correctedtradecontrolnumber"] = canonical::text(std::string(message.template get<protocol::corrected_trade_control_number>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::corrected_trade_price>(); }) { values[entry + ".payload.tradecorrectionmessage.correctedtradeprice"] = canonical::scaled(message.template get<protocol::corrected_trade_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::corrected_trade_size>(); }) { values[entry + ".payload.tradecorrectionmessage.correctedtradesize"] = canonical::number(message.template get<protocol::corrected_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { values[entry + ".payload.tradecorrectionmessage.consolidatedvolume"] = canonical::number(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::long_form_trade_correction_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.longformtradecorrectionmessage";
        if constexpr (requires { message.template get<protocol::originating_market_center_identifier>(); }) { values[entry + ".payload.longformtradecorrectionmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.template get<protocol::originating_market_center_identifier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.longformtradecorrectionmessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.longformtradecorrectionmessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_trade_control_number>(); }) { values[entry + ".payload.longformtradecorrectionmessage.originaltradecontrolnumber"] = canonical::text(std::string(message.template get<protocol::original_trade_control_number>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_trade_price_long>(); }) { values[entry + ".payload.longformtradecorrectionmessage.originaltradepricelong"] = canonical::scaled(message.template get<protocol::original_trade_price_long>().value(), -4); }
        if constexpr (requires { message.template get<protocol::original_trade_size>(); }) { values[entry + ".payload.longformtradecorrectionmessage.originaltradesize"] = canonical::number(message.template get<protocol::original_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_trade_control_number>(); }) { values[entry + ".payload.longformtradecorrectionmessage.correctedtradecontrolnumber"] = canonical::text(std::string(message.template get<protocol::corrected_trade_control_number>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::corrected_trade_price_long>(); }) { values[entry + ".payload.longformtradecorrectionmessage.correctedtradepricelong"] = canonical::scaled(message.template get<protocol::corrected_trade_price_long>().value(), -4); }
        if constexpr (requires { message.template get<protocol::corrected_trade_size>(); }) { values[entry + ".payload.longformtradecorrectionmessage.correctedtradesize"] = canonical::number(message.template get<protocol::corrected_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { values[entry + ".payload.longformtradecorrectionmessage.consolidatedvolume"] = canonical::number(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::next_shares_trade_correction_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.nextsharestradecorrectionmessage";
        if constexpr (requires { message.template get<protocol::market_center>(); }) { values[entry + ".payload.nextsharestradecorrectionmessage.marketcenter"] = canonical::text(canonical::character(message.template get<protocol::market_center>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.nextsharestradecorrectionmessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.nextsharestradecorrectionmessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_trade_control_number>(); }) { values[entry + ".payload.nextsharestradecorrectionmessage.originaltradecontrolnumber"] = canonical::text(std::string(message.template get<protocol::original_trade_control_number>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_proxy_price>(); }) { values[entry + ".payload.nextsharestradecorrectionmessage.originalproxyprice"] = canonical::scaled(message.template get<protocol::original_proxy_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::original_nav_offset_amount>(); }) { values[entry + ".payload.nextsharestradecorrectionmessage.originalnavoffsetamount"] = canonical::scaled(message.template get<protocol::original_nav_offset_amount>().value(), -4); }
        if constexpr (requires { message.template get<protocol::original_trade_size>(); }) { values[entry + ".payload.nextsharestradecorrectionmessage.originaltradesize"] = canonical::number(message.template get<protocol::original_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_trade_control_number>(); }) { values[entry + ".payload.nextsharestradecorrectionmessage.correctedtradecontrolnumber"] = canonical::text(std::string(message.template get<protocol::corrected_trade_control_number>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::corrected_proxy_price>(); }) { values[entry + ".payload.nextsharestradecorrectionmessage.correctedproxyprice"] = canonical::scaled(message.template get<protocol::corrected_proxy_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::corrected_nav_offset_amount>(); }) { values[entry + ".payload.nextsharestradecorrectionmessage.correctednavoffsetamount"] = canonical::scaled(message.template get<protocol::corrected_nav_offset_amount>().value(), -4); }
        if constexpr (requires { message.template get<protocol::corrected_trade_size>(); }) { values[entry + ".payload.nextsharestradecorrectionmessage.correctedtradesize"] = canonical::number(message.template get<protocol::corrected_trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { values[entry + ".payload.nextsharestradecorrectionmessage.consolidatedvolume"] = canonical::number(message.template get<protocol::consolidated_volume>().value()); }
    }

    void operator()(const protocol::stock_trading_action_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
        if constexpr (requires { message.template get<protocol::reserved>(); }) { values[entry + ".payload.stocktradingactionmessage.reserved"] = canonical::text(canonical::character(message.template get<protocol::reserved>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.stocktradingactionmessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.stocktradingactionmessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::current_trading_state>(); }) { values[entry + ".payload.stocktradingactionmessage.currenttradingstate"] = canonical::text(canonical::character(message.template get<protocol::current_trading_state>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reason>(); }) { values[entry + ".payload.stocktradingactionmessage.reason"] = canonical::text(std::string(message.template get<protocol::reason>().value()), ' ', false); }
    }

    void operator()(const protocol::stock_directory_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.stockdirectorymessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::market_category>(); }) { values[entry + ".payload.stockdirectorymessage.marketcategory"] = canonical::text(canonical::character(message.template get<protocol::market_category>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::financial_status_indicator>(); }) { values[entry + ".payload.stockdirectorymessage.financialstatusindicator"] = canonical::text(canonical::character(message.template get<protocol::financial_status_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::round_lot_size>(); }) { values[entry + ".payload.stockdirectorymessage.roundlotsize"] = canonical::number(message.template get<protocol::round_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::round_lots_only>(); }) { values[entry + ".payload.stockdirectorymessage.roundlotsonly"] = canonical::text(canonical::character(message.template get<protocol::round_lots_only>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_classification>(); }) { values[entry + ".payload.stockdirectorymessage.issueclassification"] = canonical::text(canonical::character(message.template get<protocol::issue_classification>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_sub_type>(); }) { values[entry + ".payload.stockdirectorymessage.issuesubtype"] = canonical::text(std::string(message.template get<protocol::issue_sub_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::authenticity>(); }) { values[entry + ".payload.stockdirectorymessage.authenticity"] = canonical::text(canonical::character(message.template get<protocol::authenticity>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::short_sale_threshold_indicator>(); }) { values[entry + ".payload.stockdirectorymessage.shortsalethresholdindicator"] = canonical::text(canonical::character(message.template get<protocol::short_sale_threshold_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::ipo_flag>(); }) { values[entry + ".payload.stockdirectorymessage.ipoflag"] = canonical::text(canonical::character(message.template get<protocol::ipo_flag>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::luld_reference_price_tier>(); }) { values[entry + ".payload.stockdirectorymessage.luldreferencepricetier"] = canonical::text(canonical::character(message.template get<protocol::luld_reference_price_tier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::etp_flag>(); }) { values[entry + ".payload.stockdirectorymessage.etpflag"] = canonical::text(canonical::character(message.template get<protocol::etp_flag>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::etp_leverage_factor>(); }) { values[entry + ".payload.stockdirectorymessage.etpleveragefactor"] = canonical::number(message.template get<protocol::etp_leverage_factor>().value()); }
        if constexpr (requires { message.template get<protocol::inverse_indicator>(); }) { values[entry + ".payload.stockdirectorymessage.inverseindicator"] = canonical::text(canonical::character(message.template get<protocol::inverse_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::bloomberg_id>(); }) { values[entry + ".payload.stockdirectorymessage.bloombergid"] = canonical::text(std::string(message.template get<protocol::bloomberg_id>().value()), ' ', false); }
    }

    void operator()(const protocol::reg_sho_short_sale_price_test_restricted_indicator_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.regshoshortsalepricetestrestrictedindicatormessage";
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reg_sho_action>(); }) { values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.regshoaction"] = canonical::text(canonical::character(message.template get<protocol::reg_sho_action>().value()), ' ', false); }
    }

    void operator()(const protocol::adjusted_closing_price_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.adjustedclosingpricemessage";
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.adjustedclosingpricemessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.adjustedclosingpricemessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::adjusted_closing_price>(); }) { values[entry + ".payload.adjustedclosingpricemessage.adjustedclosingprice"] = canonical::scaled(message.template get<protocol::adjusted_closing_price>().value(), -4); }
    }

    void operator()(const protocol::long_form_adjusted_closing_price_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.longformadjustedclosingpricemessage";
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.longformadjustedclosingpricemessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.longformadjustedclosingpricemessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::adjusted_closing_price_long>(); }) { values[entry + ".payload.longformadjustedclosingpricemessage.adjustedclosingpricelong"] = canonical::scaled(message.template get<protocol::adjusted_closing_price_long>().value(), -4); }
    }

    void operator()(const protocol::end_of_day_trade_summary_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.endofdaytradesummarymessage";
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.endofdaytradesummarymessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::market_category>(); }) { values[entry + ".payload.endofdaytradesummarymessage.marketcategory"] = canonical::text(canonical::character(message.template get<protocol::market_category>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::consolidated_high_price>(); }) { values[entry + ".payload.endofdaytradesummarymessage.consolidatedhighprice"] = canonical::scaled(message.template get<protocol::consolidated_high_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::consolidated_low_price>(); }) { values[entry + ".payload.endofdaytradesummarymessage.consolidatedlowprice"] = canonical::scaled(message.template get<protocol::consolidated_low_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::consolidated_closing_price>(); }) { values[entry + ".payload.endofdaytradesummarymessage.consolidatedclosingprice"] = canonical::scaled(message.template get<protocol::consolidated_closing_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { values[entry + ".payload.endofdaytradesummarymessage.consolidatedvolume"] = canonical::number(message.template get<protocol::consolidated_volume>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_open_price>(); }) { values[entry + ".payload.endofdaytradesummarymessage.consolidatedopenprice"] = canonical::scaled(message.template get<protocol::consolidated_open_price>().value(), -4); }
    }

    void operator()(const protocol::long_form_end_of_day_trade_summary_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.longformendofdaytradesummarymessage";
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.longformendofdaytradesummarymessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::market_category>(); }) { values[entry + ".payload.longformendofdaytradesummarymessage.marketcategory"] = canonical::text(canonical::character(message.template get<protocol::market_category>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::consolidated_high_price_long>(); }) { values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedhighpricelong"] = canonical::scaled(message.template get<protocol::consolidated_high_price_long>().value(), -4); }
        if constexpr (requires { message.template get<protocol::consolidated_low_price_long>(); }) { values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedlowpricelong"] = canonical::scaled(message.template get<protocol::consolidated_low_price_long>().value(), -4); }
        if constexpr (requires { message.template get<protocol::consolidated_closing_price_long>(); }) { values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedclosingpricelong"] = canonical::scaled(message.template get<protocol::consolidated_closing_price_long>().value(), -4); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedvolume"] = canonical::number(message.template get<protocol::consolidated_volume>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_open_price_long>(); }) { values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedopenpricelong"] = canonical::scaled(message.template get<protocol::consolidated_open_price_long>().value(), -4); }
    }

    void operator()(const protocol::next_shares_end_of_day_trade_summary_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.nextsharesendofdaytradesummarymessage";
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.nextsharesendofdaytradesummarymessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::market_category>(); }) { values[entry + ".payload.nextsharesendofdaytradesummarymessage.marketcategory"] = canonical::text(canonical::character(message.template get<protocol::market_category>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::consolidated_high_price>(); }) { values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedhighprice"] = canonical::scaled(message.template get<protocol::consolidated_high_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::nav_offset_amount_high>(); }) { values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamounthigh"] = canonical::scaled(message.template get<protocol::nav_offset_amount_high>().value(), -4); }
        if constexpr (requires { message.template get<protocol::consolidated_low_price>(); }) { values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedlowprice"] = canonical::scaled(message.template get<protocol::consolidated_low_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::nav_offset_amount_low>(); }) { values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamountlow"] = canonical::scaled(message.template get<protocol::nav_offset_amount_low>().value(), -4); }
        if constexpr (requires { message.template get<protocol::consolidated_closing_price>(); }) { values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedclosingprice"] = canonical::scaled(message.template get<protocol::consolidated_closing_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::nav_offset_amount_closing>(); }) { values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamountclosing"] = canonical::scaled(message.template get<protocol::nav_offset_amount_closing>().value(), -4); }
        if constexpr (requires { message.template get<protocol::consolidated_volume>(); }) { values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedvolume"] = canonical::number(message.template get<protocol::consolidated_volume>().value()); }
        if constexpr (requires { message.template get<protocol::consolidated_open_price>(); }) { values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedopenprice"] = canonical::scaled(message.template get<protocol::consolidated_open_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::nav_offset_amount_open>(); }) { values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamountopen"] = canonical::scaled(message.template get<protocol::nav_offset_amount_open>().value(), -4); }
    }

    void operator()(const protocol::ipo_information_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.ipoinformationmessage";
        if constexpr (requires { message.template get<protocol::issue_symbol>(); }) { values[entry + ".payload.ipoinformationmessage.issuesymbol"] = canonical::text(std::string(message.template get<protocol::issue_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.ipoinformationmessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reference_for_net_change>(); }) { values[entry + ".payload.ipoinformationmessage.referencefornetchange"] = canonical::text(canonical::character(message.template get<protocol::reference_for_net_change>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reference_price>(); }) { values[entry + ".payload.ipoinformationmessage.referenceprice"] = canonical::scaled(message.template get<protocol::reference_price>().value(), -4); }
    }

    void operator()(const protocol::mwcb_decline_level_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.mwcbdeclinelevelmessage";
        if constexpr (requires { message.template get<protocol::level_1>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.level1"] = canonical::scaled(message.template get<protocol::level_1>().value(), -8); }
        if constexpr (requires { message.template get<protocol::level_2>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.level2"] = canonical::scaled(message.template get<protocol::level_2>().value(), -8); }
        if constexpr (requires { message.template get<protocol::level_3>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.level3"] = canonical::scaled(message.template get<protocol::level_3>().value(), -8); }
    }

    void operator()(const protocol::mwcb_status_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.mwcbstatusmessage";
        if constexpr (requires { message.template get<protocol::breached_level>(); }) { values[entry + ".payload.mwcbstatusmessage.breachedlevel"] = canonical::text(canonical::character(message.template get<protocol::breached_level>().value()), ' ', false); }
    }

    void operator()(const protocol::ipo_quoting_period_update_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.ipoquotingperiodupdatemessage";
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.ipoquotingperiodupdatemessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::ipo_quotation_release_time>(); }) { values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasetime"] = canonical::number(message.template get<protocol::ipo_quotation_release_time>().value()); }
        if constexpr (requires { message.template get<protocol::ipo_quotation_release_qualifier>(); }) { values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasequalifier"] = canonical::text(canonical::character(message.template get<protocol::ipo_quotation_release_qualifier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::ipo_price>(); }) { values[entry + ".payload.ipoquotingperiodupdatemessage.ipoprice"] = canonical::scaled(message.template get<protocol::ipo_price>().value(), -4); }
    }

    void operator()(const protocol::operational_halt_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.operationalhaltmessage";
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.operationalhaltmessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::market_code>(); }) { values[entry + ".payload.operationalhaltmessage.marketcode"] = canonical::text(canonical::character(message.template get<protocol::market_code>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::operational_halt_action>(); }) { values[entry + ".payload.operationalhaltmessage.operationalhaltaction"] = canonical::text(canonical::character(message.template get<protocol::operational_halt_action>().value()), ' ', false); }
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
    std::printf("== Nasdaq.NsmEquities.NlsPlus.Itch.v3.0 (tmp values)\n");
    int failures = 0;
    failures += check("LongFormTradeReportMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/LongFormTradeReportMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/LongFormTradeReportMessage.values");
    failures += check("RegShoShortSalePriceTestRestrictedIndicatorMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/RegShoShortSalePriceTestRestrictedIndicatorMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/RegShoShortSalePriceTestRestrictedIndicatorMessage.values");
    failures += check("StockTradingActionMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/StockTradingActionMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/StockTradingActionMessage.values");
    failures += check("SystemEventMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/SystemEventMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/SystemEventMessage.values");
    failures += check("TradeReportMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/TradeReportMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/TradeReportMessage.values");
    return failures == 0 ? 0 : 1;
}
