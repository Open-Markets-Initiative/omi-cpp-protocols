// Asx.AsxDerivatives.Ntp.Itch.v1.05 canonical values, through the Tmp header: every value the Tmp reading hands
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
#include "cpp/tmp/asx/asxderivatives/ntp/itch/v1.05/asx_asxderivatives_ntp_itch_v1_05.hpp"

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
        if constexpr (requires { header.template get<protocol::message_type>(); }) { values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(header.template get<protocol::message_type>().value())); }
    }

    void operator()(const protocol::seconds_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.secondsmessage";
        if constexpr (requires { message.template get<protocol::second>(); }) { values[entry + ".payload.secondsmessage.second"] = canonical::number(message.template get<protocol::second>().value()); }
    }

    void operator()(const protocol::end_of_business_trade_date_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.endofbusinesstradedatemessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.endofbusinesstradedatemessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.endofbusinesstradedatemessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::event_code>(); }) { values[entry + ".payload.endofbusinesstradedatemessage.eventcode"] = canonical::text(canonical::character(message.template get<protocol::event_code>().value()), ' ', false); }
    }

    void operator()(const protocol::future_symbol_directory_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.futuresymboldirectorymessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.futuresymboldirectorymessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.futuresymboldirectorymessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.futuresymboldirectorymessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_name>(); }) { values[entry + ".payload.futuresymboldirectorymessage.symbolname"] = canonical::text(std::string(message.template get<protocol::symbol_name>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::long_name>(); }) { values[entry + ".payload.futuresymboldirectorymessage.longname"] = canonical::text(std::string(message.template get<protocol::long_name>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::isin>(); }) { values[entry + ".payload.futuresymboldirectorymessage.isin"] = canonical::text(std::string(message.template get<protocol::isin>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::exchange>(); }) { values[entry + ".payload.futuresymboldirectorymessage.exchange"] = canonical::text(std::string(message.template get<protocol::exchange>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::instrument>(); }) { values[entry + ".payload.futuresymboldirectorymessage.instrument"] = canonical::text(std::string(message.template get<protocol::instrument>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::cfi_code>(); }) { values[entry + ".payload.futuresymboldirectorymessage.cficode"] = canonical::text(std::string(message.template get<protocol::cfi_code>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::expiry_year>(); }) { values[entry + ".payload.futuresymboldirectorymessage.expiryyear"] = canonical::number(message.template get<protocol::expiry_year>().value()); }
        if constexpr (requires { message.template get<protocol::expiry_month>(); }) { values[entry + ".payload.futuresymboldirectorymessage.expirymonth"] = canonical::number(message.template get<protocol::expiry_month>().value()); }
        if constexpr (requires { message.template get<protocol::price_display_decimals>(); }) { values[entry + ".payload.futuresymboldirectorymessage.pricedisplaydecimals"] = canonical::number(message.template get<protocol::price_display_decimals>().value()); }
        if constexpr (requires { message.template get<protocol::price_fractional_denominator>(); }) { values[entry + ".payload.futuresymboldirectorymessage.pricefractionaldenominator"] = canonical::number(message.template get<protocol::price_fractional_denominator>().value()); }
        if constexpr (requires { message.template get<protocol::price_minimum_tick>(); }) { values[entry + ".payload.futuresymboldirectorymessage.priceminimumtick"] = canonical::number(message.template get<protocol::price_minimum_tick>().value()); }
        if constexpr (requires { message.template get<protocol::last_trading_date>(); }) { values[entry + ".payload.futuresymboldirectorymessage.lasttradingdate"] = canonical::number(message.template get<protocol::last_trading_date>().value()); }
        if constexpr (requires { message.template get<protocol::prior_day_settlement>(); }) { values[entry + ".payload.futuresymboldirectorymessage.priordaysettlement"] = canonical::scaled(message.template get<protocol::prior_day_settlement>().value(), -2); }
        if constexpr (requires { message.template get<protocol::currency>(); }) { values[entry + ".payload.futuresymboldirectorymessage.currency"] = canonical::text(std::string(message.template get<protocol::currency>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::lot_size_or_face_value>(); }) { values[entry + ".payload.futuresymboldirectorymessage.lotsizeorfacevalue"] = canonical::number(message.template get<protocol::lot_size_or_face_value>().value()); }
        if constexpr (requires { message.template get<protocol::maturity_value>(); }) { values[entry + ".payload.futuresymboldirectorymessage.maturityvalue"] = canonical::number(message.template get<protocol::maturity_value>().value()); }
        if constexpr (requires { message.template get<protocol::coupon_rate>(); }) { values[entry + ".payload.futuresymboldirectorymessage.couponrate"] = canonical::number(message.template get<protocol::coupon_rate>().value()); }
        if constexpr (requires { message.template get<protocol::payments_per_year>(); }) { values[entry + ".payload.futuresymboldirectorymessage.paymentsperyear"] = canonical::number(message.template get<protocol::payments_per_year>().value()); }
        if constexpr (requires { message.template get<protocol::block_lot_size>(); }) { values[entry + ".payload.futuresymboldirectorymessage.blocklotsize"] = canonical::number(message.template get<protocol::block_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::expiry_date>(); }) { values[entry + ".payload.futuresymboldirectorymessage.expirydate"] = canonical::number(message.template get<protocol::expiry_date>().value()); }
    }

    void operator()(const protocol::options_symbol_directory_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.optionssymboldirectorymessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.optionssymboldirectorymessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.optionssymboldirectorymessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.optionssymboldirectorymessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_name>(); }) { values[entry + ".payload.optionssymboldirectorymessage.symbolname"] = canonical::text(std::string(message.template get<protocol::symbol_name>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::long_name>(); }) { values[entry + ".payload.optionssymboldirectorymessage.longname"] = canonical::text(std::string(message.template get<protocol::long_name>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::isin>(); }) { values[entry + ".payload.optionssymboldirectorymessage.isin"] = canonical::text(std::string(message.template get<protocol::isin>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::exchange>(); }) { values[entry + ".payload.optionssymboldirectorymessage.exchange"] = canonical::text(std::string(message.template get<protocol::exchange>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::instrument>(); }) { values[entry + ".payload.optionssymboldirectorymessage.instrument"] = canonical::text(std::string(message.template get<protocol::instrument>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::cfi_code>(); }) { values[entry + ".payload.optionssymboldirectorymessage.cficode"] = canonical::text(std::string(message.template get<protocol::cfi_code>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::expiry_year>(); }) { values[entry + ".payload.optionssymboldirectorymessage.expiryyear"] = canonical::number(message.template get<protocol::expiry_year>().value()); }
        if constexpr (requires { message.template get<protocol::expiry_month>(); }) { values[entry + ".payload.optionssymboldirectorymessage.expirymonth"] = canonical::number(message.template get<protocol::expiry_month>().value()); }
        if constexpr (requires { message.template get<protocol::option_type>(); }) { values[entry + ".payload.optionssymboldirectorymessage.optiontype"] = canonical::text(canonical::character(message.template get<protocol::option_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::strike>(); }) { values[entry + ".payload.optionssymboldirectorymessage.strike"] = canonical::scaled(message.template get<protocol::strike>().value(), -2); }
        if constexpr (requires { message.template get<protocol::underlying_tradeable_instrument_id>(); }) { values[entry + ".payload.optionssymboldirectorymessage.underlyingtradeableinstrumentid"] = canonical::number(message.template get<protocol::underlying_tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::price_display_decimals>(); }) { values[entry + ".payload.optionssymboldirectorymessage.pricedisplaydecimals"] = canonical::number(message.template get<protocol::price_display_decimals>().value()); }
        if constexpr (requires { message.template get<protocol::price_fractional_denominator>(); }) { values[entry + ".payload.optionssymboldirectorymessage.pricefractionaldenominator"] = canonical::number(message.template get<protocol::price_fractional_denominator>().value()); }
        if constexpr (requires { message.template get<protocol::price_minimum_tick>(); }) { values[entry + ".payload.optionssymboldirectorymessage.priceminimumtick"] = canonical::number(message.template get<protocol::price_minimum_tick>().value()); }
        if constexpr (requires { message.template get<protocol::strike_price_decimal_position>(); }) { values[entry + ".payload.optionssymboldirectorymessage.strikepricedecimalposition"] = canonical::number(message.template get<protocol::strike_price_decimal_position>().value()); }
        if constexpr (requires { message.template get<protocol::strike_price_fractional_denominator>(); }) { values[entry + ".payload.optionssymboldirectorymessage.strikepricefractionaldenominator"] = canonical::number(message.template get<protocol::strike_price_fractional_denominator>().value()); }
        if constexpr (requires { message.template get<protocol::strike_price_minimum_tick>(); }) { values[entry + ".payload.optionssymboldirectorymessage.strikepriceminimumtick"] = canonical::number(message.template get<protocol::strike_price_minimum_tick>().value()); }
        if constexpr (requires { message.template get<protocol::last_trading_date>(); }) { values[entry + ".payload.optionssymboldirectorymessage.lasttradingdate"] = canonical::number(message.template get<protocol::last_trading_date>().value()); }
        if constexpr (requires { message.template get<protocol::prior_day_settlement>(); }) { values[entry + ".payload.optionssymboldirectorymessage.priordaysettlement"] = canonical::scaled(message.template get<protocol::prior_day_settlement>().value(), -2); }
        if constexpr (requires { message.template get<protocol::volatility>(); }) { values[entry + ".payload.optionssymboldirectorymessage.volatility"] = canonical::number(message.template get<protocol::volatility>().value()); }
        if constexpr (requires { message.template get<protocol::currency>(); }) { values[entry + ".payload.optionssymboldirectorymessage.currency"] = canonical::text(std::string(message.template get<protocol::currency>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::lot_size_or_face_value>(); }) { values[entry + ".payload.optionssymboldirectorymessage.lotsizeorfacevalue"] = canonical::number(message.template get<protocol::lot_size_or_face_value>().value()); }
        if constexpr (requires { message.template get<protocol::maturity_value>(); }) { values[entry + ".payload.optionssymboldirectorymessage.maturityvalue"] = canonical::number(message.template get<protocol::maturity_value>().value()); }
        if constexpr (requires { message.template get<protocol::coupon_rate>(); }) { values[entry + ".payload.optionssymboldirectorymessage.couponrate"] = canonical::number(message.template get<protocol::coupon_rate>().value()); }
        if constexpr (requires { message.template get<protocol::payments_per_year>(); }) { values[entry + ".payload.optionssymboldirectorymessage.paymentsperyear"] = canonical::number(message.template get<protocol::payments_per_year>().value()); }
        if constexpr (requires { message.template get<protocol::block_lot_size>(); }) { values[entry + ".payload.optionssymboldirectorymessage.blocklotsize"] = canonical::number(message.template get<protocol::block_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::expiry_date>(); }) { values[entry + ".payload.optionssymboldirectorymessage.expirydate"] = canonical::number(message.template get<protocol::expiry_date>().value()); }
        if constexpr (requires { message.template get<protocol::basis_of_quotation>(); }) { values[entry + ".payload.optionssymboldirectorymessage.basisofquotation"] = canonical::text(std::string(message.template get<protocol::basis_of_quotation>().value()), ' ', false); }
    }

    void operator()(const protocol::combination_symbol_directory_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.combinationsymboldirectorymessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.combinationsymboldirectorymessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.combinationsymboldirectorymessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.combinationsymboldirectorymessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_name>(); }) { values[entry + ".payload.combinationsymboldirectorymessage.symbolname"] = canonical::text(std::string(message.template get<protocol::symbol_name>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::long_name>(); }) { values[entry + ".payload.combinationsymboldirectorymessage.longname"] = canonical::text(std::string(message.template get<protocol::long_name>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::cfi_code>(); }) { values[entry + ".payload.combinationsymboldirectorymessage.cficode"] = canonical::text(std::string(message.template get<protocol::cfi_code>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price_method>(); }) { values[entry + ".payload.combinationsymboldirectorymessage.pricemethod"] = canonical::number(message.template get<protocol::price_method>().value()); }
        if constexpr (requires { message.template get<protocol::price_display_decimals>(); }) { values[entry + ".payload.combinationsymboldirectorymessage.pricedisplaydecimals"] = canonical::number(message.template get<protocol::price_display_decimals>().value()); }
        if constexpr (requires { message.template get<protocol::price_fractional_denominator>(); }) { values[entry + ".payload.combinationsymboldirectorymessage.pricefractionaldenominator"] = canonical::number(message.template get<protocol::price_fractional_denominator>().value()); }
        if constexpr (requires { message.template get<protocol::price_minimum_tick>(); }) { values[entry + ".payload.combinationsymboldirectorymessage.priceminimumtick"] = canonical::number(message.template get<protocol::price_minimum_tick>().value()); }
        if constexpr (requires { message.template get<protocol::legs>(); }) { values[entry + ".payload.combinationsymboldirectorymessage.legs"] = canonical::number(message.template get<protocol::legs>().value()); }
    }

    void operator()(const protocol::bundles_symbol_directory& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.bundlessymboldirectory";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.bundlessymboldirectory.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.bundlessymboldirectory.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.bundlessymboldirectory.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_name>(); }) { values[entry + ".payload.bundlessymboldirectory.symbolname"] = canonical::text(std::string(message.template get<protocol::symbol_name>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::long_name>(); }) { values[entry + ".payload.bundlessymboldirectory.longname"] = canonical::text(std::string(message.template get<protocol::long_name>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::cfi_code>(); }) { values[entry + ".payload.bundlessymboldirectory.cficode"] = canonical::text(std::string(message.template get<protocol::cfi_code>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price_method>(); }) { values[entry + ".payload.bundlessymboldirectory.pricemethod"] = canonical::number(message.template get<protocol::price_method>().value()); }
        if constexpr (requires { message.template get<protocol::price_display_decimals>(); }) { values[entry + ".payload.bundlessymboldirectory.pricedisplaydecimals"] = canonical::number(message.template get<protocol::price_display_decimals>().value()); }
        if constexpr (requires { message.template get<protocol::price_fractional_denominator>(); }) { values[entry + ".payload.bundlessymboldirectory.pricefractionaldenominator"] = canonical::number(message.template get<protocol::price_fractional_denominator>().value()); }
        if constexpr (requires { message.template get<protocol::price_minimum_tick>(); }) { values[entry + ".payload.bundlessymboldirectory.priceminimumtick"] = canonical::number(message.template get<protocol::price_minimum_tick>().value()); }
        if constexpr (requires { message.template get<protocol::legs>(); }) { values[entry + ".payload.bundlessymboldirectory.legs"] = canonical::number(message.template get<protocol::legs>().value()); }
    }

    void operator()(const protocol::order_book_state_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderbookstatemessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderbookstatemessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.orderbookstatemessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.orderbookstatemessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::session_state>(); }) { values[entry + ".payload.orderbookstatemessage.sessionstate"] = canonical::text(canonical::character(message.template get<protocol::session_state>().value()), ' ', false); }
    }

    void operator()(const protocol::add_order_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.addordermessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.addordermessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.addordermessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.addordermessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.addordermessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.addordermessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_priority>(); }) { values[entry + ".payload.addordermessage.orderbookpriority"] = canonical::number(message.template get<protocol::order_book_priority>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.addordermessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.addordermessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -2); }
    }

    void operator()(const protocol::order_volume_cancelled_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.ordervolumecancelledmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.ordervolumecancelledmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.ordervolumecancelledmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.ordervolumecancelledmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.ordervolumecancelledmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.ordervolumecancelledmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.ordervolumecancelledmessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
    }

    void operator()(const protocol::order_deleted_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderdeletedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderdeletedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.orderdeletedmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.orderdeletedmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.orderdeletedmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.orderdeletedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
    }

    void operator()(const protocol::order_executed_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderexecutedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.orderexecutedmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.orderexecutedmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.orderexecutedmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity_remaining>(); }) { values[entry + ".payload.orderexecutedmessage.quantityremaining"] = canonical::number(message.template get<protocol::quantity_remaining>().value()); }
        if constexpr (requires { message.template get<protocol::trade_type>(); }) { values[entry + ".payload.orderexecutedmessage.tradetype"] = canonical::text(canonical::character(message.template get<protocol::trade_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.orderexecutedmessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { values[entry + ".payload.orderexecutedmessage.tradeprice"] = canonical::scaled(message.template get<protocol::trade_price>().value(), -2); }
        if constexpr (requires { message.template get<protocol::combination_trade_id>(); }) { values[entry + ".payload.orderexecutedmessage.combinationtradeid"] = canonical::number(message.template get<protocol::combination_trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::counter_party_id>(); }) { values[entry + ".payload.orderexecutedmessage.counterpartyid"] = canonical::text(std::string(message.template get<protocol::counter_party_id>().value()), ' ', false); }
    }

    void operator()(const protocol::auction_order_executed_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.auctionorderexecutedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.auctionorderexecutedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.auctionorderexecutedmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.auctionorderexecutedmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.auctionorderexecutedmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.auctionorderexecutedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity_remaining>(); }) { values[entry + ".payload.auctionorderexecutedmessage.quantityremaining"] = canonical::number(message.template get<protocol::quantity_remaining>().value()); }
        if constexpr (requires { message.template get<protocol::trade_type>(); }) { values[entry + ".payload.auctionorderexecutedmessage.tradetype"] = canonical::text(canonical::character(message.template get<protocol::trade_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.auctionorderexecutedmessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { values[entry + ".payload.auctionorderexecutedmessage.executedquantity"] = canonical::number(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { values[entry + ".payload.auctionorderexecutedmessage.tradeprice"] = canonical::scaled(message.template get<protocol::trade_price>().value(), -2); }
        if constexpr (requires { message.template get<protocol::opposite_order_id>(); }) { values[entry + ".payload.auctionorderexecutedmessage.oppositeorderid"] = canonical::number(message.template get<protocol::opposite_order_id>().value()); }
    }

    void operator()(const protocol::combination_order_executed_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.combinationorderexecutedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.combinationorderexecutedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.combinationorderexecutedmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.combinationorderexecutedmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.combinationorderexecutedmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.combinationorderexecutedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity_remaining>(); }) { values[entry + ".payload.combinationorderexecutedmessage.quantityremaining"] = canonical::number(message.template get<protocol::quantity_remaining>().value()); }
        if constexpr (requires { message.template get<protocol::trade_type>(); }) { values[entry + ".payload.combinationorderexecutedmessage.tradetype"] = canonical::text(canonical::character(message.template get<protocol::trade_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.combinationorderexecutedmessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { values[entry + ".payload.combinationorderexecutedmessage.executedquantity"] = canonical::number(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { values[entry + ".payload.combinationorderexecutedmessage.tradeprice"] = canonical::scaled(message.template get<protocol::trade_price>().value(), -2); }
        if constexpr (requires { message.template get<protocol::opposite_tradeable_instrument_id>(); }) { values[entry + ".payload.combinationorderexecutedmessage.oppositetradeableinstrumentid"] = canonical::number(message.template get<protocol::opposite_tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::opposite_side>(); }) { values[entry + ".payload.combinationorderexecutedmessage.oppositeside"] = canonical::text(canonical::character(message.template get<protocol::opposite_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::opposite_order_id>(); }) { values[entry + ".payload.combinationorderexecutedmessage.oppositeorderid"] = canonical::number(message.template get<protocol::opposite_order_id>().value()); }
        if constexpr (requires { message.template get<protocol::combination_trade_id>(); }) { values[entry + ".payload.combinationorderexecutedmessage.combinationtradeid"] = canonical::number(message.template get<protocol::combination_trade_id>().value()); }
    }

    void operator()(const protocol::implied_order_added_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.impliedorderaddedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.impliedorderaddedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.impliedorderaddedmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.impliedorderaddedmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.impliedorderaddedmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.impliedorderaddedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_priority>(); }) { values[entry + ".payload.impliedorderaddedmessage.orderbookpriority"] = canonical::number(message.template get<protocol::order_book_priority>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.impliedorderaddedmessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.impliedorderaddedmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -2); }
    }

    void operator()(const protocol::implied_order_replaced_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.impliedorderreplacedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.impliedorderreplacedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.impliedorderreplacedmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.impliedorderreplacedmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.impliedorderreplacedmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.impliedorderreplacedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_priority>(); }) { values[entry + ".payload.impliedorderreplacedmessage.orderbookpriority"] = canonical::number(message.template get<protocol::order_book_priority>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.impliedorderreplacedmessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.impliedorderreplacedmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -2); }
    }

    void operator()(const protocol::implied_order_deleted_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.impliedorderdeletedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.impliedorderdeletedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.impliedorderdeletedmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.impliedorderdeletedmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.impliedorderdeletedmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.impliedorderdeletedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
    }

    void operator()(const protocol::trade_executed_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.tradeexecutedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.tradeexecutedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.tradeexecutedmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.tradeexecutedmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_type>(); }) { values[entry + ".payload.tradeexecutedmessage.tradetype"] = canonical::text(canonical::character(message.template get<protocol::trade_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.tradeexecutedmessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { values[entry + ".payload.tradeexecutedmessage.executedquantity"] = canonical::number(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { values[entry + ".payload.tradeexecutedmessage.tradeprice"] = canonical::scaled(message.template get<protocol::trade_price>().value(), -2); }
        if constexpr (requires { message.template get<protocol::combination_trade_id>(); }) { values[entry + ".payload.tradeexecutedmessage.combinationtradeid"] = canonical::number(message.template get<protocol::combination_trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::participant_id_buyer>(); }) { values[entry + ".payload.tradeexecutedmessage.participantidbuyer"] = canonical::text(std::string(message.template get<protocol::participant_id_buyer>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::participant_id_seller>(); }) { values[entry + ".payload.tradeexecutedmessage.participantidseller"] = canonical::text(std::string(message.template get<protocol::participant_id_seller>().value()), ' ', false); }
    }

    void operator()(const protocol::combination_trade_executed_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.combinationtradeexecutedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_type>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.tradetype"] = canonical::text(canonical::character(message.template get<protocol::trade_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.executedquantity"] = canonical::number(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.tradeprice"] = canonical::scaled(message.template get<protocol::trade_price>().value(), -2); }
        if constexpr (requires { message.template get<protocol::buyer_tradeable_instrument_id>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.buyertradeableinstrumentid"] = canonical::number(message.template get<protocol::buyer_tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::buyer_side>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.buyerside"] = canonical::text(canonical::character(message.template get<protocol::buyer_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::buyer_order_id>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.buyerorderid"] = canonical::number(message.template get<protocol::buyer_order_id>().value()); }
        if constexpr (requires { message.template get<protocol::buyer_combination_trade_id>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.buyercombinationtradeid"] = canonical::number(message.template get<protocol::buyer_combination_trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::buyer_participant_id>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.buyerparticipantid"] = canonical::text(std::string(message.template get<protocol::buyer_participant_id>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::seller_tradeable_instrument_id>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.sellertradeableinstrumentid"] = canonical::number(message.template get<protocol::seller_tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::seller_side>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.sellerside"] = canonical::text(canonical::character(message.template get<protocol::seller_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::seller_order_id>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.sellerorderid"] = canonical::number(message.template get<protocol::seller_order_id>().value()); }
        if constexpr (requires { message.template get<protocol::seller_combination_trade_id>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.sellercombinationtradeid"] = canonical::number(message.template get<protocol::seller_combination_trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::seller_participant_id>(); }) { values[entry + ".payload.combinationtradeexecutedmessage.sellerparticipantid"] = canonical::text(std::string(message.template get<protocol::seller_participant_id>().value()), ' ', false); }
    }

    void operator()(const protocol::trade_cancellation_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.tradecancellationmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.tradecancellationmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.tradecancellationmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.tradecancellationmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.tradecancellationmessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
    }

    void operator()(const protocol::equilibrium_price_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.equilibriumpricemessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.equilibriumpricemessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.equilibriumpricemessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.equilibriumpricemessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::equilibrium_price>(); }) { values[entry + ".payload.equilibriumpricemessage.equilibriumprice"] = canonical::scaled(message.template get<protocol::equilibrium_price>().value(), -2); }
        if constexpr (requires { message.template get<protocol::matched_quantity>(); }) { values[entry + ".payload.equilibriumpricemessage.matchedquantity"] = canonical::number(message.template get<protocol::matched_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::bid_quantity>(); }) { values[entry + ".payload.equilibriumpricemessage.bidquantity"] = canonical::number(message.template get<protocol::bid_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::ask_quantity>(); }) { values[entry + ".payload.equilibriumpricemessage.askquantity"] = canonical::number(message.template get<protocol::ask_quantity>().value()); }
    }

    void operator()(const protocol::open_high_low_last_trade_adjustment_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.openhighlowlasttradeadjustmentmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.openhighlowlasttradeadjustmentmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.openhighlowlasttradeadjustmentmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.openhighlowlasttradeadjustmentmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::opening_trade>(); }) { values[entry + ".payload.openhighlowlasttradeadjustmentmessage.openingtrade"] = canonical::scaled(message.template get<protocol::opening_trade>().value(), -2); }
        if constexpr (requires { message.template get<protocol::highest_trade>(); }) { values[entry + ".payload.openhighlowlasttradeadjustmentmessage.highesttrade"] = canonical::scaled(message.template get<protocol::highest_trade>().value(), -2); }
        if constexpr (requires { message.template get<protocol::lowest_trade>(); }) { values[entry + ".payload.openhighlowlasttradeadjustmentmessage.lowesttrade"] = canonical::scaled(message.template get<protocol::lowest_trade>().value(), -2); }
        if constexpr (requires { message.template get<protocol::last_trade>(); }) { values[entry + ".payload.openhighlowlasttradeadjustmentmessage.lasttrade"] = canonical::scaled(message.template get<protocol::last_trade>().value(), -2); }
        if constexpr (requires { message.template get<protocol::last_volume>(); }) { values[entry + ".payload.openhighlowlasttradeadjustmentmessage.lastvolume"] = canonical::number(message.template get<protocol::last_volume>().value()); }
        if constexpr (requires { message.template get<protocol::total_traded_volume>(); }) { values[entry + ".payload.openhighlowlasttradeadjustmentmessage.totaltradedvolume"] = canonical::number(message.template get<protocol::total_traded_volume>().value()); }
    }

    void operator()(const protocol::market_settlement_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.marketsettlementmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.marketsettlementmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.marketsettlementmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.marketsettlementmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::opening_trade>(); }) { values[entry + ".payload.marketsettlementmessage.openingtrade"] = canonical::scaled(message.template get<protocol::opening_trade>().value(), -2); }
        if constexpr (requires { message.template get<protocol::highest_trade>(); }) { values[entry + ".payload.marketsettlementmessage.highesttrade"] = canonical::scaled(message.template get<protocol::highest_trade>().value(), -2); }
        if constexpr (requires { message.template get<protocol::lowest_trade>(); }) { values[entry + ".payload.marketsettlementmessage.lowesttrade"] = canonical::scaled(message.template get<protocol::lowest_trade>().value(), -2); }
        if constexpr (requires { message.template get<protocol::last_trade>(); }) { values[entry + ".payload.marketsettlementmessage.lasttrade"] = canonical::scaled(message.template get<protocol::last_trade>().value(), -2); }
        if constexpr (requires { message.template get<protocol::last_volume>(); }) { values[entry + ".payload.marketsettlementmessage.lastvolume"] = canonical::number(message.template get<protocol::last_volume>().value()); }
        if constexpr (requires { message.template get<protocol::total_traded_volume>(); }) { values[entry + ".payload.marketsettlementmessage.totaltradedvolume"] = canonical::number(message.template get<protocol::total_traded_volume>().value()); }
    }

    void operator()(const protocol::text_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.textmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.textmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.textmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::source_id>(); }) { values[entry + ".payload.textmessage.sourceid"] = canonical::text(std::string(message.template get<protocol::source_id>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::text>(); }) { values[entry + ".payload.textmessage.text"] = canonical::text(std::string(message.template get<protocol::text>().value()), ' ', false); }
    }

    void operator()(const protocol::request_for_quote_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.requestforquotemessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.requestforquotemessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.requestforquotemessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.requestforquotemessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::rfq_side>(); }) { values[entry + ".payload.requestforquotemessage.rfqside"] = canonical::text(canonical::character(message.template get<protocol::rfq_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.requestforquotemessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
    }

    void operator()(const protocol::anomalous_order_threshold_publish_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.anomalousorderthresholdpublishmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.anomalousorderthresholdpublishmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.anomalousorderthresholdpublishmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.anomalousorderthresholdpublishmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::aot_price>(); }) { values[entry + ".payload.anomalousorderthresholdpublishmessage.aotprice"] = canonical::scaled(message.template get<protocol::aot_price>().value(), -2); }
        if constexpr (requires { message.template get<protocol::aot_upper_price>(); }) { values[entry + ".payload.anomalousorderthresholdpublishmessage.aotupperprice"] = canonical::scaled(message.template get<protocol::aot_upper_price>().value(), -2); }
        if constexpr (requires { message.template get<protocol::aot_lower_price>(); }) { values[entry + ".payload.anomalousorderthresholdpublishmessage.aotlowerprice"] = canonical::scaled(message.template get<protocol::aot_lower_price>().value(), -2); }
        if constexpr (requires { message.template get<protocol::etr_price>(); }) { values[entry + ".payload.anomalousorderthresholdpublishmessage.etrprice"] = canonical::scaled(message.template get<protocol::etr_price>().value(), -2); }
        if constexpr (requires { message.template get<protocol::etr_upper_price>(); }) { values[entry + ".payload.anomalousorderthresholdpublishmessage.etrupperprice"] = canonical::scaled(message.template get<protocol::etr_upper_price>().value(), -2); }
        if constexpr (requires { message.template get<protocol::etr_lower_price>(); }) { values[entry + ".payload.anomalousorderthresholdpublishmessage.etrlowerprice"] = canonical::scaled(message.template get<protocol::etr_lower_price>().value(), -2); }
    }

    void operator()(const protocol::volume_and_open_interest_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.volumeandopeninterestmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.volumeandopeninterestmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.volumeandopeninterestmessage.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::tradeable_instrument_id>(); }) { values[entry + ".payload.volumeandopeninterestmessage.tradeableinstrumentid"] = canonical::number(message.template get<protocol::tradeable_instrument_id>().value()); }
        if constexpr (requires { message.template get<protocol::cumulative_volume>(); }) { values[entry + ".payload.volumeandopeninterestmessage.cumulativevolume"] = canonical::number(message.template get<protocol::cumulative_volume>().value()); }
        if constexpr (requires { message.template get<protocol::open_interest>(); }) { values[entry + ".payload.volumeandopeninterestmessage.openinterest"] = canonical::number(message.template get<protocol::open_interest>().value()); }
        if constexpr (requires { message.template get<protocol::voi_trade_date>(); }) { values[entry + ".payload.volumeandopeninterestmessage.voitradedate"] = canonical::number(message.template get<protocol::voi_trade_date>().value()); }
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
    std::printf("== Asx.AsxDerivatives.Ntp.Itch.v1.05 (tmp values)\n");
    int failures = 0;
    failures += check("AddOrderMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/AddOrderMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/AddOrderMessage.values");
    failures += check("AnomalousOrderThresholdPublishMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/AnomalousOrderThresholdPublishMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/AnomalousOrderThresholdPublishMessage.values");
    failures += check("AuctionOrderExecutedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/AuctionOrderExecutedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/AuctionOrderExecutedMessage.values");
    failures += check("CombinationOrderExecutedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/CombinationOrderExecutedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/CombinationOrderExecutedMessage.values");
    failures += check("CombinationSymbolDirectoryMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/CombinationSymbolDirectoryMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/CombinationSymbolDirectoryMessage.values");
    failures += check("CombinationTradeExecutedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/CombinationTradeExecutedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/CombinationTradeExecutedMessage.values");
    failures += check("EquilibriumPriceMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/EquilibriumPriceMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/EquilibriumPriceMessage.values");
    failures += check("FutureSymbolDirectoryMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/FutureSymbolDirectoryMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/FutureSymbolDirectoryMessage.values");
    failures += check("Heartbeat", "Asx/AsxDerivatives.Ntp.Itch.v1.05/Heartbeat.pcap", "asx/asxderivatives/ntp/itch/v1.05/Heartbeat.values");
    failures += check("ImpliedOrderAddedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/ImpliedOrderAddedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/ImpliedOrderAddedMessage.values");
    failures += check("ImpliedOrderDeletedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/ImpliedOrderDeletedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/ImpliedOrderDeletedMessage.values");
    failures += check("ImpliedOrderReplacedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/ImpliedOrderReplacedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/ImpliedOrderReplacedMessage.values");
    failures += check("OpenHighLowLastTradeAdjustmentMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/OpenHighLowLastTradeAdjustmentMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/OpenHighLowLastTradeAdjustmentMessage.values");
    failures += check("OptionsSymbolDirectoryMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/OptionsSymbolDirectoryMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/OptionsSymbolDirectoryMessage.values");
    failures += check("OrderBookStateMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/OrderBookStateMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/OrderBookStateMessage.values");
    failures += check("OrderDeletedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/OrderDeletedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/OrderDeletedMessage.values");
    failures += check("OrderExecutedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/OrderExecutedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/OrderExecutedMessage.values");
    failures += check("OrderVolumeCancelledMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/OrderVolumeCancelledMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/OrderVolumeCancelledMessage.values");
    failures += check("SecondsMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/SecondsMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/SecondsMessage.values");
    failures += check("TextMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/TextMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/TextMessage.values");
    failures += check("TradeExecutedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/TradeExecutedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/TradeExecutedMessage.values");
    return failures == 0 ? 0 : 1;
}