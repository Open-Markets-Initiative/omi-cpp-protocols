// Jnx.JnxEquities.Pts.Itch.v1.6 canonical values, through the Tmp header: every value the Tmp reading hands
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
#include "cpp/binary/tmp/jnx/jnxequities/pts/itch/v1.6/jnx_jnxequities_pts_itch_v1_6.hpp"

// Jnx JnxEquities Pts Itch 1.6: the reading of its packets, through its Template Meta Programming header
namespace jnx::jnxequities::pts::itch::v1_6 {

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
        [[maybe_unused]] const auto& system_event_message_ = tmp::read<system_event_message>(data + offset, bound - offset, handler); offset += system_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& price_tick_size_message_ = tmp::read<price_tick_size_message>(data + offset, bound - offset, handler); offset += price_tick_size_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& orderbook_directory_message_ = tmp::read<orderbook_directory_message>(data + offset, bound - offset, handler); offset += orderbook_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trading_state_message_ = tmp::read<trading_state_message>(data + offset, bound - offset, handler); offset += trading_state_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Y')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& short_selling_price_restriction_state_message_ = tmp::read<short_selling_price_restriction_state_message>(data + offset, bound - offset, handler); offset += short_selling_price_restriction_state_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_added_without_attributes_message_ = tmp::read<order_added_without_attributes_message>(data + offset, bound - offset, handler); offset += order_added_without_attributes_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'F')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_added_with_attributes_message_ = tmp::read<order_added_with_attributes_message>(data + offset, bound - offset, handler); offset += order_added_with_attributes_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'E')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_executed_message_ = tmp::read<order_executed_message>(data + offset, bound - offset, handler); offset += order_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_deleted_message_ = tmp::read<order_deleted_message>(data + offset, bound - offset, handler); offset += order_deleted_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'U')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_replaced_message_ = tmp::read<order_replaced_message>(data + offset, bound - offset, handler); offset += order_replaced_message::size;
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


} // namespace jnx::jnxequities::pts::itch::v1_6

namespace protocol = ::jnx::jnxequities::pts::itch::v1_6;

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
        if constexpr (requires { message.template get<protocol::seconds>(); }) { values[entry + ".payload.secondsmessage.seconds"] = canonical::number(message.template get<protocol::seconds>().value()); }
    }

    void operator()(const protocol::system_event_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.systemeventmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::group>(); }) { values[entry + ".payload.systemeventmessage.group"] = canonical::text(std::string(message.template get<protocol::group>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::system_event>(); }) { values[entry + ".payload.systemeventmessage.systemevent"] = canonical::text(canonical::character(message.template get<protocol::system_event>().value()), ' ', false); }
    }

    void operator()(const protocol::price_tick_size_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.priceticksizemessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.priceticksizemessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::price_tick_size_table_id>(); }) { values[entry + ".payload.priceticksizemessage.priceticksizetableid"] = canonical::number(message.template get<protocol::price_tick_size_table_id>().value()); }
        if constexpr (requires { message.template get<protocol::price_tick_size>(); }) { values[entry + ".payload.priceticksizemessage.priceticksize"] = canonical::scaled(message.template get<protocol::price_tick_size>().value(), -1); }
        if constexpr (requires { message.template get<protocol::price_start>(); }) { values[entry + ".payload.priceticksizemessage.pricestart"] = canonical::scaled(message.template get<protocol::price_start>().value(), -1); }
    }

    void operator()(const protocol::orderbook_directory_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderbookdirectorymessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderbookdirectorymessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::orderbook_id>(); }) { values[entry + ".payload.orderbookdirectorymessage.orderbookid"] = canonical::number(message.template get<protocol::orderbook_id>().value()); }
        if constexpr (requires { message.template get<protocol::orderbook_code>(); }) { values[entry + ".payload.orderbookdirectorymessage.orderbookcode"] = canonical::text(std::string(message.template get<protocol::orderbook_code>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::group>(); }) { values[entry + ".payload.orderbookdirectorymessage.group"] = canonical::text(std::string(message.template get<protocol::group>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::round_lot_size>(); }) { values[entry + ".payload.orderbookdirectorymessage.roundlotsize"] = canonical::number(message.template get<protocol::round_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::price_tick_size_table_id>(); }) { values[entry + ".payload.orderbookdirectorymessage.priceticksizetableid"] = canonical::number(message.template get<protocol::price_tick_size_table_id>().value()); }
        if constexpr (requires { message.template get<protocol::price_decimals>(); }) { values[entry + ".payload.orderbookdirectorymessage.pricedecimals"] = canonical::number(message.template get<protocol::price_decimals>().value()); }
        if constexpr (requires { message.template get<protocol::upper_price_limit>(); }) { values[entry + ".payload.orderbookdirectorymessage.upperpricelimit"] = canonical::scaled(message.template get<protocol::upper_price_limit>().value(), -1); }
        if constexpr (requires { message.template get<protocol::lower_price_limit>(); }) { values[entry + ".payload.orderbookdirectorymessage.lowerpricelimit"] = canonical::scaled(message.template get<protocol::lower_price_limit>().value(), -1); }
    }

    void operator()(const protocol::trading_state_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.tradingstatemessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.tradingstatemessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::orderbook_id>(); }) { values[entry + ".payload.tradingstatemessage.orderbookid"] = canonical::number(message.template get<protocol::orderbook_id>().value()); }
        if constexpr (requires { message.template get<protocol::group>(); }) { values[entry + ".payload.tradingstatemessage.group"] = canonical::text(std::string(message.template get<protocol::group>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trading_state>(); }) { values[entry + ".payload.tradingstatemessage.tradingstate"] = canonical::text(canonical::character(message.template get<protocol::trading_state>().value()), ' ', false); }
    }

    void operator()(const protocol::short_selling_price_restriction_state_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.shortsellingpricerestrictionstatemessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.shortsellingpricerestrictionstatemessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::orderbook_id>(); }) { values[entry + ".payload.shortsellingpricerestrictionstatemessage.orderbookid"] = canonical::number(message.template get<protocol::orderbook_id>().value()); }
        if constexpr (requires { message.template get<protocol::group>(); }) { values[entry + ".payload.shortsellingpricerestrictionstatemessage.group"] = canonical::text(std::string(message.template get<protocol::group>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::short_selling_state>(); }) { values[entry + ".payload.shortsellingpricerestrictionstatemessage.shortsellingstate"] = canonical::text(canonical::character(message.template get<protocol::short_selling_state>().value()), ' ', false); }
    }

    void operator()(const protocol::order_added_without_attributes_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderaddedwithoutattributesmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderaddedwithoutattributesmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_number>(); }) { values[entry + ".payload.orderaddedwithoutattributesmessage.ordernumber"] = canonical::number(message.template get<protocol::order_number>().value()); }
        if constexpr (requires { message.template get<protocol::buy_sell_indicator>(); }) { values[entry + ".payload.orderaddedwithoutattributesmessage.buysellindicator"] = canonical::text(canonical::character(message.template get<protocol::buy_sell_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.orderaddedwithoutattributesmessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::orderbook_id>(); }) { values[entry + ".payload.orderaddedwithoutattributesmessage.orderbookid"] = canonical::number(message.template get<protocol::orderbook_id>().value()); }
        if constexpr (requires { message.template get<protocol::group>(); }) { values[entry + ".payload.orderaddedwithoutattributesmessage.group"] = canonical::text(std::string(message.template get<protocol::group>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.orderaddedwithoutattributesmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -1); }
    }

    void operator()(const protocol::order_added_with_attributes_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderaddedwithattributesmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderaddedwithattributesmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_number>(); }) { values[entry + ".payload.orderaddedwithattributesmessage.ordernumber"] = canonical::number(message.template get<protocol::order_number>().value()); }
        if constexpr (requires { message.template get<protocol::buy_sell_indicator>(); }) { values[entry + ".payload.orderaddedwithattributesmessage.buysellindicator"] = canonical::text(canonical::character(message.template get<protocol::buy_sell_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.orderaddedwithattributesmessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::orderbook_id>(); }) { values[entry + ".payload.orderaddedwithattributesmessage.orderbookid"] = canonical::number(message.template get<protocol::orderbook_id>().value()); }
        if constexpr (requires { message.template get<protocol::group>(); }) { values[entry + ".payload.orderaddedwithattributesmessage.group"] = canonical::text(std::string(message.template get<protocol::group>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.orderaddedwithattributesmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -1); }
        if constexpr (requires { message.template get<protocol::attribution>(); }) { values[entry + ".payload.orderaddedwithattributesmessage.attribution"] = canonical::text(std::string(message.template get<protocol::attribution>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_type>(); }) { values[entry + ".payload.orderaddedwithattributesmessage.ordertype"] = canonical::text(canonical::character(message.template get<protocol::order_type>().value()), ' ', false); }
    }

    void operator()(const protocol::order_executed_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderexecutedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_number>(); }) { values[entry + ".payload.orderexecutedmessage.ordernumber"] = canonical::number(message.template get<protocol::order_number>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { values[entry + ".payload.orderexecutedmessage.matchnumber"] = canonical::number(message.template get<protocol::match_number>().value()); }
    }

    void operator()(const protocol::order_deleted_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderdeletedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderdeletedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_number>(); }) { values[entry + ".payload.orderdeletedmessage.ordernumber"] = canonical::number(message.template get<protocol::order_number>().value()); }
    }

    void operator()(const protocol::order_replaced_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderreplacedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderreplacedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::original_order_number>(); }) { values[entry + ".payload.orderreplacedmessage.originalordernumber"] = canonical::number(message.template get<protocol::original_order_number>().value()); }
        if constexpr (requires { message.template get<protocol::new_order_number>(); }) { values[entry + ".payload.orderreplacedmessage.newordernumber"] = canonical::number(message.template get<protocol::new_order_number>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.orderreplacedmessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.orderreplacedmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -1); }
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
    std::printf("== Jnx.JnxEquities.Pts.Itch.v1.6 (tmp values)\n");
    int failures = 0;
    failures += check("OrderDeletedMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/OrderDeletedMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/OrderDeletedMessage.values");
    failures += check("OrderExecutedMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/OrderExecutedMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/OrderExecutedMessage.values");
    failures += check("OrderReplacedMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/OrderReplacedMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/OrderReplacedMessage.values");
    failures += check("SecondsMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/SecondsMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/SecondsMessage.values");
    failures += check("ShortSellingPriceRestrictionStateMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/ShortSellingPriceRestrictionStateMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/ShortSellingPriceRestrictionStateMessage.values");
    return failures == 0 ? 0 : 1;
}
