// CixAts.CixAspen.MarketDataFeed.Aspen.v1.4 canonical values, through the Tmp header: every value the Tmp reading hands
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
#include "cpp/binary/tmp/cixats/cixaspen/marketdatafeed/aspen/v1.4/cixats_cixaspen_marketdatafeed_aspen_v1_4.hpp"

// CixAts CixAspen MarketDataFeed Aspen 1.4: the reading of its packets, through its Template Meta Programming header
namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

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
    if (static_cast<bool>(tmp::rule(message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& market_event_message_ = tmp::read<market_event_message>(data + offset, bound - offset, handler); offset += market_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& symbol_information_message_ = tmp::read<symbol_information_message>(data + offset, bound - offset, handler); offset += symbol_information_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& symbol_state_message_ = tmp::read<symbol_state_message>(data + offset, bound - offset, handler); offset += symbol_state_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& new_order_add_message_ = tmp::read<new_order_add_message>(data + offset, bound - offset, handler); offset += new_order_add_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'F')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_partial_cancel_message_ = tmp::read<order_partial_cancel_message>(data + offset, bound - offset, handler); offset += order_partial_cancel_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'G')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_cancel_all_message_ = tmp::read<order_cancel_all_message>(data + offset, bound - offset, handler); offset += order_cancel_all_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'J')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_executed_message_ = tmp::read<order_executed_message>(data + offset, bound - offset, handler); offset += order_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'K')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_message_ = tmp::read<trade_message>(data + offset, bound - offset, handler); offset += trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_cancel_message_ = tmp::read<trade_cancel_message>(data + offset, bound - offset, handler); offset += trade_cancel_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'M')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_correct_message_ = tmp::read<trade_correct_message>(data + offset, bound - offset, handler); offset += trade_correct_message::size;
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
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<length_type>()))) + 2);
    tmp::require(bound, length);
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<length_type>()))) - 1);
        tmp::require(offset + size, bound);
        parse_payload(data + offset, size, handler, message_header_.template get<message_type>());
        offset += size;
    }
    return bound;
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
    {
        const std::size_t end = static_cast<std::size_t>(static_cast<std::int64_t>(bound));
        tmp::require(end, bound);
        while (offset < end) {
            [[maybe_unused]] const std::size_t bound = end;
            offset += parse_message(data + offset, bound - offset, handler);
        }
    }
    return offset;
}


} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4

namespace protocol = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

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
        if constexpr (requires { header.template get<protocol::market_day_identifier>(); }) { values["packet.packetheader.marketdayidentifier"] = canonical::numeric(std::string(header.template get<protocol::market_day_identifier>().raw())); }
        if constexpr (requires { header.template get<protocol::feed_identifier>(); }) { values["packet.packetheader.feedidentifier"] = canonical::text(canonical::character(header.template get<protocol::feed_identifier>().value())); }
        if constexpr (requires { header.template get<protocol::sequence>(); }) { values["packet.packetheader.sequence"] = canonical::number(header.template get<protocol::sequence>().value()); }
        if constexpr (requires { header.template get<protocol::count_type>(); }) { values["packet.packetheader.count"] = canonical::number(header.template get<protocol::count_type>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::length_type>(); }) { values[entry + ".messageheader.length"] = canonical::number(header.template get<protocol::length_type>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(header.template get<protocol::message_type>().value())); }
    }

    void operator()(const protocol::market_event_message& message) {
        values[entry + ".payload"] = "packet.message.payload.marketeventmessage";
        if constexpr (requires { message.template get<protocol::reserved_2>(); }) { values[entry + ".payload.marketeventmessage.reserved2"] = canonical::text(std::string(message.template get<protocol::reserved_2>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.marketeventmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::event>(); }) { values[entry + ".payload.marketeventmessage.event"] = canonical::text(canonical::character(message.template get<protocol::event>().value()), ' ', false); }
    }

    void operator()(const protocol::symbol_information_message& message) {
        values[entry + ".payload"] = "packet.message.payload.symbolinformationmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.symbolinformationmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_id>(); }) { values[entry + ".payload.symbolinformationmessage.symbolid"] = canonical::number(message.template get<protocol::symbol_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".payload.symbolinformationmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::listing_market>(); }) { values[entry + ".payload.symbolinformationmessage.listingmarket"] = canonical::text(canonical::character(message.template get<protocol::listing_market>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::board_lot_size>(); }) { values[entry + ".payload.symbolinformationmessage.boardlotsize"] = canonical::number(message.template get<protocol::board_lot_size>().value()); }
    }

    void operator()(const protocol::symbol_state_message& message) {
        values[entry + ".payload"] = "packet.message.payload.symbolstatemessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.symbolstatemessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_id>(); }) { values[entry + ".payload.symbolstatemessage.symbolid"] = canonical::number(message.template get<protocol::symbol_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".payload.symbolstatemessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::state>(); }) { values[entry + ".payload.symbolstatemessage.state"] = canonical::text(canonical::character(message.template get<protocol::state>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reserved_1>(); }) { values[entry + ".payload.symbolstatemessage.reserved1"] = canonical::text(canonical::character(message.template get<protocol::reserved_1>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::info>(); }) { values[entry + ".payload.symbolstatemessage.info"] = canonical::text(std::string(message.template get<protocol::info>().value()), ' ', false); }
    }

    void operator()(const protocol::new_order_add_message& message) {
        values[entry + ".payload"] = "packet.message.payload.neworderaddmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.neworderaddmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_id>(); }) { values[entry + ".payload.neworderaddmessage.symbolid"] = canonical::number(message.template get<protocol::symbol_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.neworderaddmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.neworderaddmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.neworderaddmessage.quantity"] = canonical::scaled(message.template get<protocol::quantity>().value(), -6); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".payload.neworderaddmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.neworderaddmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -6); }
        if constexpr (requires { message.template get<protocol::broker>(); }) { values[entry + ".payload.neworderaddmessage.broker"] = canonical::text(std::string(message.template get<protocol::broker>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reserved_1>(); }) { values[entry + ".payload.neworderaddmessage.reserved1"] = canonical::text(canonical::character(message.template get<protocol::reserved_1>().value()), ' ', false); }
    }

    void operator()(const protocol::order_partial_cancel_message& message) {
        values[entry + ".payload"] = "packet.message.payload.orderpartialcancelmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.orderpartialcancelmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.orderpartialcancelmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity_canceled>(); }) { values[entry + ".payload.orderpartialcancelmessage.quantitycanceled"] = canonical::scaled(message.template get<protocol::quantity_canceled>().value(), -6); }
    }

    void operator()(const protocol::order_cancel_all_message& message) {
        values[entry + ".payload"] = "packet.message.payload.ordercancelallmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.ordercancelallmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.ordercancelallmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
    }

    void operator()(const protocol::order_executed_message& message) {
        values[entry + ".payload"] = "packet.message.payload.orderexecutedmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.orderexecutedmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.orderexecutedmessage.quantity"] = canonical::scaled(message.template get<protocol::quantity>().value(), -6); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { values[entry + ".payload.orderexecutedmessage.executionid"] = canonical::number(message.template get<protocol::execution_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.orderexecutedmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.orderexecutedmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -6); }
        if constexpr (requires { message.template get<protocol::broker>(); }) { values[entry + ".payload.orderexecutedmessage.broker"] = canonical::text(std::string(message.template get<protocol::broker>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::contra_broker>(); }) { values[entry + ".payload.orderexecutedmessage.contrabroker"] = canonical::text(std::string(message.template get<protocol::contra_broker>().value()), ' ', false); }
    }

    void operator()(const protocol::trade_message& message) {
        values[entry + ".payload"] = "packet.message.payload.trademessage";
        if constexpr (requires { message.template get<protocol::symbol_id>(); }) { values[entry + ".payload.trademessage.symbolid"] = canonical::number(message.template get<protocol::symbol_id>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.trademessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::reserved_8>(); }) { values[entry + ".payload.trademessage.reserved8"] = canonical::number(message.template get<protocol::reserved_8>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.trademessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::shares>(); }) { values[entry + ".payload.trademessage.shares"] = canonical::scaled(message.template get<protocol::shares>().value(), -6); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".payload.trademessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.trademessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -6); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { values[entry + ".payload.trademessage.executionid"] = canonical::number(message.template get<protocol::execution_id>().value()); }
        if constexpr (requires { message.template get<protocol::broker>(); }) { values[entry + ".payload.trademessage.broker"] = canonical::text(std::string(message.template get<protocol::broker>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::contra_broker>(); }) { values[entry + ".payload.trademessage.contrabroker"] = canonical::text(std::string(message.template get<protocol::contra_broker>().value()), ' ', false); }
    }

    void operator()(const protocol::trade_cancel_message& message) {
        values[entry + ".payload"] = "packet.message.payload.tradecancelmessage";
        if constexpr (requires { message.template get<protocol::symbol_id>(); }) { values[entry + ".payload.tradecancelmessage.symbolid"] = canonical::number(message.template get<protocol::symbol_id>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.tradecancelmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::reserved_8>(); }) { values[entry + ".payload.tradecancelmessage.reserved8"] = canonical::number(message.template get<protocol::reserved_8>().value()); }
        if constexpr (requires { message.template get<protocol::reserved_1>(); }) { values[entry + ".payload.tradecancelmessage.reserved1"] = canonical::text(canonical::character(message.template get<protocol::reserved_1>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::shares>(); }) { values[entry + ".payload.tradecancelmessage.shares"] = canonical::scaled(message.template get<protocol::shares>().value(), -6); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".payload.tradecancelmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.tradecancelmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -6); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { values[entry + ".payload.tradecancelmessage.executionid"] = canonical::number(message.template get<protocol::execution_id>().value()); }
        if constexpr (requires { message.template get<protocol::broker>(); }) { values[entry + ".payload.tradecancelmessage.broker"] = canonical::text(std::string(message.template get<protocol::broker>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::contra_broker>(); }) { values[entry + ".payload.tradecancelmessage.contrabroker"] = canonical::text(std::string(message.template get<protocol::contra_broker>().value()), ' ', false); }
    }

    void operator()(const protocol::trade_correct_message& message) {
        values[entry + ".payload"] = "packet.message.payload.tradecorrectmessage";
        if constexpr (requires { message.template get<protocol::symbol_id>(); }) { values[entry + ".payload.tradecorrectmessage.symbolid"] = canonical::number(message.template get<protocol::symbol_id>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.tradecorrectmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::reserved_8>(); }) { values[entry + ".payload.tradecorrectmessage.reserved8"] = canonical::number(message.template get<protocol::reserved_8>().value()); }
        if constexpr (requires { message.template get<protocol::reserved_1>(); }) { values[entry + ".payload.tradecorrectmessage.reserved1"] = canonical::text(canonical::character(message.template get<protocol::reserved_1>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".payload.tradecorrectmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { values[entry + ".payload.tradecorrectmessage.executionid"] = canonical::number(message.template get<protocol::execution_id>().value()); }
        if constexpr (requires { message.template get<protocol::broker>(); }) { values[entry + ".payload.tradecorrectmessage.broker"] = canonical::text(std::string(message.template get<protocol::broker>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::contra_broker>(); }) { values[entry + ".payload.tradecorrectmessage.contrabroker"] = canonical::text(std::string(message.template get<protocol::contra_broker>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::original_execution_id>(); }) { values[entry + ".payload.tradecorrectmessage.originalexecutionid"] = canonical::number(message.template get<protocol::original_execution_id>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_price>(); }) { values[entry + ".payload.tradecorrectmessage.originaltradeprice"] = canonical::scaled(message.template get<protocol::original_trade_price>().value(), -6); }
        if constexpr (requires { message.template get<protocol::original_trade_quantity>(); }) { values[entry + ".payload.tradecorrectmessage.originaltradequantity"] = canonical::scaled(message.template get<protocol::original_trade_quantity>().value(), -6); }
        if constexpr (requires { message.template get<protocol::corrected_trade_price>(); }) { values[entry + ".payload.tradecorrectmessage.correctedtradeprice"] = canonical::scaled(message.template get<protocol::corrected_trade_price>().value(), -6); }
        if constexpr (requires { message.template get<protocol::corrected_trade_quantity>(); }) { values[entry + ".payload.tradecorrectmessage.correctedtradequantity"] = canonical::scaled(message.template get<protocol::corrected_trade_quantity>().value(), -6); }
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
    std::printf("== CixAts.CixAspen.MarketDataFeed.Aspen.v1.4 (tmp values)\n");
    int failures = 0;
    failures += check("MarketEventMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/MarketEventMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/MarketEventMessage.values");
    failures += check("NewOrderAddMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/NewOrderAddMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/NewOrderAddMessage.values");
    failures += check("OrderCancelAllMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/OrderCancelAllMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/OrderCancelAllMessage.values");
    failures += check("OrderExecutedMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/OrderExecutedMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/OrderExecutedMessage.values");
    failures += check("OrderPartialCancelMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/OrderPartialCancelMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/OrderPartialCancelMessage.values");
    failures += check("SymbolInformationMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/SymbolInformationMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/SymbolInformationMessage.values");
    failures += check("SymbolStateMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/SymbolStateMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/SymbolStateMessage.values");
    failures += check("TradeMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/TradeMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/TradeMessage.values");
    return failures == 0 ? 0 : 1;
}
