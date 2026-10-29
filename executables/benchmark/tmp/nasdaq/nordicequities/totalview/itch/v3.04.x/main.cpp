// Nasdaq.NordicEquities.TotalView.Itch.v3.04.X benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nordicequities/totalview/itch/v3.04.x.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/nasdaq/nordicequities/totalview/itch/v3.04.x/nasdaq_nordicequities_totalview_itch_v3_04_x.hpp"

// Nasdaq NordicEquities TotalView Itch 3.04.X: the reading of its packets, through its Template Meta Programming header
namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

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
    if (static_cast<bool>(tmp::rule(message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_book_trading_action_message_ = tmp::read<order_book_trading_action_message>(data + offset, bound - offset, handler); offset += order_book_trading_action_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_book_directory_message_ = tmp::read<order_book_directory_message>(data + offset, bound - offset, handler); offset += order_book_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_message_ = tmp::read<add_order_message>(data + offset, bound - offset, handler); offset += add_order_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'F')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_mpid_attribution_message_ = tmp::read<add_order_mpid_attribution_message>(data + offset, bound - offset, handler); offset += add_order_mpid_attribution_message::size;
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
        [[maybe_unused]] const auto& order_executed_with_price_message_ = tmp::read<order_executed_with_price_message>(data + offset, bound - offset, handler); offset += order_executed_with_price_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_cancel_message_ = tmp::read<order_cancel_message>(data + offset, bound - offset, handler); offset += order_cancel_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_delete_message_ = tmp::read<order_delete_message>(data + offset, bound - offset, handler); offset += order_delete_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Y')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_book_flush_message_ = tmp::read<order_book_flush_message>(data + offset, bound - offset, handler); offset += order_book_flush_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'U')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_replace_message_ = tmp::read<order_replace_message>(data + offset, bound - offset, handler); offset += order_replace_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_message_ = tmp::read<trade_message>(data + offset, bound - offset, handler); offset += trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& cross_trade_message_ = tmp::read<cross_trade_message>(data + offset, bound - offset, handler); offset += cross_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& broken_trade_message_ = tmp::read<broken_trade_message>(data + offset, bound - offset, handler); offset += broken_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'I')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& noii_message_ = tmp::read<noii_message>(data + offset, bound - offset, handler); offset += noii_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'J')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& moii_message_ = tmp::read<moii_message>(data + offset, bound - offset, handler); offset += moii_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'K')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& execution_summary_message_ = tmp::read<execution_summary_message>(data + offset, bound - offset, handler); offset += execution_summary_message::size;
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


} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x

namespace protocol = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

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
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::event_code>(); }) { checksum += bench::digest(message.template get<protocol::event_code>().value()); }
    }

    void operator()(const protocol::order_book_trading_action_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::order_book>(); }) { checksum += bench::digest(message.template get<protocol::order_book>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_state>(); }) { checksum += bench::digest(message.template get<protocol::symbol_state>().value()); }
        if constexpr (requires { message.template get<protocol::extension>(); }) { checksum += bench::digest(message.template get<protocol::extension>().value()); }
        if constexpr (requires { message.template get<protocol::reason>(); }) { checksum += bench::digest(message.template get<protocol::reason>().value()); }
    }

    void operator()(const protocol::order_book_directory_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::order_book>(); }) { checksum += bench::digest(message.template get<protocol::order_book>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::isin>(); }) { checksum += bench::digest(message.template get<protocol::isin>().value()); }
        if constexpr (requires { message.template get<protocol::financial_product>(); }) { checksum += bench::digest(message.template get<protocol::financial_product>().value()); }
        if constexpr (requires { message.template get<protocol::trading_currency>(); }) { checksum += bench::digest(message.template get<protocol::trading_currency>().value()); }
        if constexpr (requires { message.template get<protocol::mic>(); }) { checksum += bench::digest(message.template get<protocol::mic>().value()); }
        if constexpr (requires { message.template get<protocol::market_segment_id>(); }) { checksum += bench::digest(message.template get<protocol::market_segment_id>().value()); }
        if constexpr (requires { message.template get<protocol::round_lot_size>(); }) { checksum += bench::digest(message.template get<protocol::round_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::nordic_mid_mic>(); }) { checksum += bench::digest(message.template get<protocol::nordic_mid_mic>().value()); }
        if constexpr (requires { message.template get<protocol::aod_mic>(); }) { checksum += bench::digest(message.template get<protocol::aod_mic>().value()); }
        if constexpr (requires { message.template get<protocol::notation_of_qty>(); }) { checksum += bench::digest(message.template get<protocol::notation_of_qty>().value()); }
        if constexpr (requires { message.template get<protocol::notional_amount>(); }) { checksum += bench::digest(message.template get<protocol::notional_amount>().value()); }
        if constexpr (requires { message.template get<protocol::currency>(); }) { checksum += bench::digest(message.template get<protocol::currency>().value()); }
        if constexpr (requires { message.template get<protocol::price_notation>(); }) { checksum += bench::digest(message.template get<protocol::price_notation>().value()); }
        if constexpr (requires { message.template get<protocol::multiplier_for_calculating_quantity_in_measurement_unit>(); }) { checksum += bench::digest(message.template get<protocol::multiplier_for_calculating_quantity_in_measurement_unit>().value()); }
        if constexpr (requires { message.template get<protocol::pure_stream_mic>(); }) { checksum += bench::digest(message.template get<protocol::pure_stream_mic>().value()); }
    }

    void operator()(const protocol::add_order_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::buy_sell_indicator>(); }) { checksum += bench::digest(message.template get<protocol::buy_sell_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::order_book>(); }) { checksum += bench::digest(message.template get<protocol::order_book>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::add_order_mpid_attribution_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::buy_sell_indicator>(); }) { checksum += bench::digest(message.template get<protocol::buy_sell_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::order_book>(); }) { checksum += bench::digest(message.template get<protocol::order_book>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::attribution>(); }) { checksum += bench::digest(message.template get<protocol::attribution>().value()); }
    }

    void operator()(const protocol::order_executed_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { checksum += bench::digest(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
        if constexpr (requires { message.template get<protocol::mpid>(); }) { checksum += bench::digest(message.template get<protocol::mpid>().value()); }
        if constexpr (requires { message.template get<protocol::mpid_counterparty>(); }) { checksum += bench::digest(message.template get<protocol::mpid_counterparty>().value()); }
    }

    void operator()(const protocol::order_executed_with_price_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { checksum += bench::digest(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
        if constexpr (requires { message.template get<protocol::printable>(); }) { checksum += bench::digest(message.template get<protocol::printable>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { checksum += bench::digest(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::mpid_owner>(); }) { checksum += bench::digest(message.template get<protocol::mpid_owner>().value()); }
        if constexpr (requires { message.template get<protocol::mpid_counterparty>(); }) { checksum += bench::digest(message.template get<protocol::mpid_counterparty>().value()); }
    }

    void operator()(const protocol::order_cancel_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::canceled_quantity>(); }) { checksum += bench::digest(message.template get<protocol::canceled_quantity>().value()); }
    }

    void operator()(const protocol::order_delete_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
    }

    void operator()(const protocol::order_book_flush_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::order_book>(); }) { checksum += bench::digest(message.template get<protocol::order_book>().value()); }
    }

    void operator()(const protocol::order_replace_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::original_order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::original_order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::new_order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::new_order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::trade_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::trade_type>(); }) { checksum += bench::digest(message.template get<protocol::trade_type>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::order_book>(); }) { checksum += bench::digest(message.template get<protocol::order_book>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { checksum += bench::digest(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::participant_id_buyer>(); }) { checksum += bench::digest(message.template get<protocol::participant_id_buyer>().value()); }
        if constexpr (requires { message.template get<protocol::participant_id_seller>(); }) { checksum += bench::digest(message.template get<protocol::participant_id_seller>().value()); }
    }

    void operator()(const protocol::cross_trade_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::order_book>(); }) { checksum += bench::digest(message.template get<protocol::order_book>().value()); }
        if constexpr (requires { message.template get<protocol::cross_price>(); }) { checksum += bench::digest(message.template get<protocol::cross_price>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { checksum += bench::digest(message.template get<protocol::cross_type>().value()); }
        if constexpr (requires { message.template get<protocol::number_of_trades>(); }) { checksum += bench::digest(message.template get<protocol::number_of_trades>().value()); }
    }

    void operator()(const protocol::broken_trade_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
    }

    void operator()(const protocol::noii_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::paired_quantity>(); }) { checksum += bench::digest(message.template get<protocol::paired_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_quantity>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_direction>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_direction>().value()); }
        if constexpr (requires { message.template get<protocol::order_book>(); }) { checksum += bench::digest(message.template get<protocol::order_book>().value()); }
        if constexpr (requires { message.template get<protocol::equilibrium_price>(); }) { checksum += bench::digest(message.template get<protocol::equilibrium_price>().value()); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { checksum += bench::digest(message.template get<protocol::cross_type>().value()); }
        if constexpr (requires { message.template get<protocol::best_bid_price>(); }) { checksum += bench::digest(message.template get<protocol::best_bid_price>().value()); }
        if constexpr (requires { message.template get<protocol::best_bid_quantity>(); }) { checksum += bench::digest(message.template get<protocol::best_bid_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::best_ask_price>(); }) { checksum += bench::digest(message.template get<protocol::best_ask_price>().value()); }
        if constexpr (requires { message.template get<protocol::best_ask_quantity>(); }) { checksum += bench::digest(message.template get<protocol::best_ask_quantity>().value()); }
    }

    void operator()(const protocol::moii_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::paired_quantity>(); }) { checksum += bench::digest(message.template get<protocol::paired_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::order_book>(); }) { checksum += bench::digest(message.template get<protocol::order_book>().value()); }
        if constexpr (requires { message.template get<protocol::equilibrium_price>(); }) { checksum += bench::digest(message.template get<protocol::equilibrium_price>().value()); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { checksum += bench::digest(message.template get<protocol::cross_type>().value()); }
        if constexpr (requires { message.template get<protocol::cross_level>(); }) { checksum += bench::digest(message.template get<protocol::cross_level>().value()); }
    }

    void operator()(const protocol::execution_summary_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::order_book>(); }) { checksum += bench::digest(message.template get<protocol::order_book>().value()); }
        if constexpr (requires { message.template get<protocol::aggressing_side>(); }) { checksum += bench::digest(message.template get<protocol::aggressing_side>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::hidden_quantity>(); }) { checksum += bench::digest(message.template get<protocol::hidden_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::stp_cancel_quantity>(); }) { checksum += bench::digest(message.template get<protocol::stp_cancel_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::far_price>(); }) { checksum += bench::digest(message.template get<protocol::far_price>().value()); }
        if constexpr (requires { message.template get<protocol::add_quantity>(); }) { checksum += bench::digest(message.template get<protocol::add_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::number_of_lit_executions>(); }) { checksum += bench::digest(message.template get<protocol::number_of_lit_executions>().value()); }
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
    return bench::run("Nasdaq.NordicEquities.TotalView.Itch.v3.04.X", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
