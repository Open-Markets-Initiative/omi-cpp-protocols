// Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 canonical values, through the Tmp header: every value the Tmp reading hands
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
#include "cpp/binary/tmp/jpx/osederivatives/geniuminet/itch/v5.0.6/jpx_osederivatives_geniuminet_itch_v5_0_6.hpp"

// Jpx OseDerivatives GeniumInet Itch 5.0.6: the reading of its packets, through its Template Meta Programming header
namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

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
    if (static_cast<bool>(tmp::rule(message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_book_directory_ = tmp::read<order_book_directory>(data + offset, bound - offset, handler); offset += order_book_directory::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'M')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& combination_orderbook_leg_ = tmp::read<combination_orderbook_leg>(data + offset, bound - offset, handler); offset += combination_orderbook_leg::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& tick_size_table_entry_ = tmp::read<tick_size_table_entry>(data + offset, bound - offset, handler); offset += tick_size_table_entry::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_event_message_ = tmp::read<system_event_message>(data + offset, bound - offset, handler); offset += system_event_message::size;
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
        [[maybe_unused]] const auto& add_order_no_mpid_ = tmp::read<add_order_no_mpid>(data + offset, bound - offset, handler); offset += add_order_no_mpid::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'F')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_with_mpid_ = tmp::read<add_order_with_mpid>(data + offset, bound - offset, handler); offset += add_order_with_mpid::size;
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
    if (static_cast<bool>(tmp::rule(message_type_) == 'U')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_replace_message_ = tmp::read<order_replace_message>(data + offset, bound - offset, handler); offset += order_replace_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_delete_message_ = tmp::read<order_delete_message>(data + offset, bound - offset, handler); offset += order_delete_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_message_ = tmp::read<trade_message>(data + offset, bound - offset, handler); offset += trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Z')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& equilibrium_price_update_ = tmp::read<equilibrium_price_update>(data + offset, bound - offset, handler); offset += equilibrium_price_update::size;
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


} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6

namespace protocol = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

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

    void operator()(const protocol::order_book_directory& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderbookdirectory";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderbookdirectory.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { values[entry + ".payload.orderbookdirectory.orderbookid"] = canonical::number(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".payload.orderbookdirectory.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::long_name>(); }) { values[entry + ".payload.orderbookdirectory.longname"] = canonical::text(std::string(message.template get<protocol::long_name>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::isin>(); }) { values[entry + ".payload.orderbookdirectory.isin"] = canonical::text(std::string(message.template get<protocol::isin>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::financial_product>(); }) { values[entry + ".payload.orderbookdirectory.financialproduct"] = canonical::number(message.template get<protocol::financial_product>().value()); }
        if constexpr (requires { message.template get<protocol::trading_currency>(); }) { values[entry + ".payload.orderbookdirectory.tradingcurrency"] = canonical::text(std::string(message.template get<protocol::trading_currency>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::decimals_in_price>(); }) { values[entry + ".payload.orderbookdirectory.decimalsinprice"] = canonical::number(message.template get<protocol::decimals_in_price>().value()); }
        if constexpr (requires { message.template get<protocol::decimals_in_nominal_value>(); }) { values[entry + ".payload.orderbookdirectory.decimalsinnominalvalue"] = canonical::number(message.template get<protocol::decimals_in_nominal_value>().value()); }
        if constexpr (requires { message.template get<protocol::odd_lot_size>(); }) { values[entry + ".payload.orderbookdirectory.oddlotsize"] = canonical::number(message.template get<protocol::odd_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::round_lot_size>(); }) { values[entry + ".payload.orderbookdirectory.roundlotsize"] = canonical::number(message.template get<protocol::round_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::block_lot_size>(); }) { values[entry + ".payload.orderbookdirectory.blocklotsize"] = canonical::number(message.template get<protocol::block_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::nominal_value>(); }) { values[entry + ".payload.orderbookdirectory.nominalvalue"] = canonical::number(message.template get<protocol::nominal_value>().value()); }
        if constexpr (requires { message.template get<protocol::number_of_legs>(); }) { values[entry + ".payload.orderbookdirectory.numberoflegs"] = canonical::number(message.template get<protocol::number_of_legs>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_orderbook_id>(); }) { values[entry + ".payload.orderbookdirectory.underlyingorderbookid"] = canonical::number(message.template get<protocol::underlying_orderbook_id>().value()); }
        if constexpr (requires { message.template get<protocol::strike_price>(); }) { values[entry + ".payload.orderbookdirectory.strikeprice"] = canonical::number(message.template get<protocol::strike_price>().value()); }
        if constexpr (requires { message.template get<protocol::expiration_date>(); }) { values[entry + ".payload.orderbookdirectory.expirationdate"] = canonical::number(message.template get<protocol::expiration_date>().value()); }
        if constexpr (requires { message.template get<protocol::decimals_in_strike_price>(); }) { values[entry + ".payload.orderbookdirectory.decimalsinstrikeprice"] = canonical::number(message.template get<protocol::decimals_in_strike_price>().value()); }
        if constexpr (requires { message.template get<protocol::put_or_call>(); }) { values[entry + ".payload.orderbookdirectory.putorcall"] = canonical::number(message.template get<protocol::put_or_call>().value()); }
    }

    void operator()(const protocol::combination_orderbook_leg& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.combinationorderbookleg";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.combinationorderbookleg.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::combination_orderbook_id>(); }) { values[entry + ".payload.combinationorderbookleg.combinationorderbookid"] = canonical::number(message.template get<protocol::combination_orderbook_id>().value()); }
        if constexpr (requires { message.template get<protocol::leg_orderbook_id>(); }) { values[entry + ".payload.combinationorderbookleg.legorderbookid"] = canonical::number(message.template get<protocol::leg_orderbook_id>().value()); }
        if constexpr (requires { message.template get<protocol::leg_side>(); }) { values[entry + ".payload.combinationorderbookleg.legside"] = canonical::text(canonical::character(message.template get<protocol::leg_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::leg_ratio>(); }) { values[entry + ".payload.combinationorderbookleg.legratio"] = canonical::number(message.template get<protocol::leg_ratio>().value()); }
    }

    void operator()(const protocol::tick_size_table_entry& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.ticksizetableentry";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.ticksizetableentry.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { values[entry + ".payload.ticksizetableentry.orderbookid"] = canonical::number(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::tick_size>(); }) { values[entry + ".payload.ticksizetableentry.ticksize"] = canonical::number(message.template get<protocol::tick_size>().value()); }
        if constexpr (requires { message.template get<protocol::price_from>(); }) { values[entry + ".payload.ticksizetableentry.pricefrom"] = canonical::number(message.template get<protocol::price_from>().value()); }
        if constexpr (requires { message.template get<protocol::price_to>(); }) { values[entry + ".payload.ticksizetableentry.priceto"] = canonical::number(message.template get<protocol::price_to>().value()); }
    }

    void operator()(const protocol::system_event_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.systemeventmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::event_code>(); }) { values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message.template get<protocol::event_code>().value()), ' ', false); }
    }

    void operator()(const protocol::order_book_state_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderbookstatemessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderbookstatemessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { values[entry + ".payload.orderbookstatemessage.orderbookid"] = canonical::number(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::state_name>(); }) { values[entry + ".payload.orderbookstatemessage.statename"] = canonical::text(std::string(message.template get<protocol::state_name>().value()), ' ', false); }
    }

    void operator()(const protocol::add_order_no_mpid& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.addordernompid";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.addordernompid.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.addordernompid.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { values[entry + ".payload.addordernompid.orderbookid"] = canonical::number(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.addordernompid.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_book_position>(); }) { values[entry + ".payload.addordernompid.orderbookposition"] = canonical::number(message.template get<protocol::order_book_position>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.addordernompid.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.addordernompid.price"] = canonical::number(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::lot_type>(); }) { values[entry + ".payload.addordernompid.lottype"] = canonical::number(message.template get<protocol::lot_type>().value()); }
    }

    void operator()(const protocol::add_order_with_mpid& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.addorderwithmpid";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.addorderwithmpid.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.addorderwithmpid.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { values[entry + ".payload.addorderwithmpid.orderbookid"] = canonical::number(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.addorderwithmpid.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_book_position>(); }) { values[entry + ".payload.addorderwithmpid.orderbookposition"] = canonical::number(message.template get<protocol::order_book_position>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.addorderwithmpid.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.addorderwithmpid.price"] = canonical::number(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::lot_type>(); }) { values[entry + ".payload.addorderwithmpid.lottype"] = canonical::number(message.template get<protocol::lot_type>().value()); }
        if constexpr (requires { message.template get<protocol::participant_id>(); }) { values[entry + ".payload.addorderwithmpid.participantid"] = canonical::text(std::string(message.template get<protocol::participant_id>().value()), ' ', false); }
    }

    void operator()(const protocol::order_executed_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderexecutedmessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { values[entry + ".payload.orderexecutedmessage.orderbookid"] = canonical::number(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.orderexecutedmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::match_id>(); }) { values[entry + ".payload.orderexecutedmessage.matchid"] = canonical::number(message.template get<protocol::match_id>().value()); }
        if constexpr (requires { message.template get<protocol::combo_group_id>(); }) { values[entry + ".payload.orderexecutedmessage.combogroupid"] = canonical::number(message.template get<protocol::combo_group_id>().value()); }
        if constexpr (requires { message.template get<protocol::participant_id_owner>(); }) { values[entry + ".payload.orderexecutedmessage.participantidowner"] = canonical::text(std::string(message.template get<protocol::participant_id_owner>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::participant_id_counterparty>(); }) { values[entry + ".payload.orderexecutedmessage.participantidcounterparty"] = canonical::text(std::string(message.template get<protocol::participant_id_counterparty>().value()), ' ', false); }
    }

    void operator()(const protocol::order_executed_with_price_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedwithpricemessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.orderbookid"] = canonical::number(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.executedquantity"] = canonical::number(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::match_id>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.matchid"] = canonical::number(message.template get<protocol::match_id>().value()); }
        if constexpr (requires { message.template get<protocol::combo_group_id>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.combogroupid"] = canonical::number(message.template get<protocol::combo_group_id>().value()); }
        if constexpr (requires { message.template get<protocol::owner_participant_id>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.ownerparticipantid"] = canonical::text(std::string(message.template get<protocol::owner_participant_id>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::counterparty_participant_id>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.counterpartyparticipantid"] = canonical::text(std::string(message.template get<protocol::counterparty_participant_id>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.tradeprice"] = canonical::number(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::occurred_at_cross>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.occurredatcross"] = canonical::text(canonical::character(message.template get<protocol::occurred_at_cross>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::printable>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.printable"] = canonical::text(canonical::character(message.template get<protocol::printable>().value()), ' ', false); }
    }

    void operator()(const protocol::order_replace_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderreplacemessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderreplacemessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.orderreplacemessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { values[entry + ".payload.orderreplacemessage.orderbookid"] = canonical::number(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.orderreplacemessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::new_orderbook_position>(); }) { values[entry + ".payload.orderreplacemessage.neworderbookposition"] = canonical::number(message.template get<protocol::new_orderbook_position>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.orderreplacemessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.orderreplacemessage.price"] = canonical::number(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::order_delete_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderdeletemessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.orderdeletemessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.orderdeletemessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { values[entry + ".payload.orderdeletemessage.orderbookid"] = canonical::number(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.orderdeletemessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
    }

    void operator()(const protocol::trade_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.trademessage";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.trademessage.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::match_id>(); }) { values[entry + ".payload.trademessage.matchid"] = canonical::number(message.template get<protocol::match_id>().value()); }
        if constexpr (requires { message.template get<protocol::combo_group_id>(); }) { values[entry + ".payload.trademessage.combogroupid"] = canonical::number(message.template get<protocol::combo_group_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.trademessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".payload.trademessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { values[entry + ".payload.trademessage.orderbookid"] = canonical::number(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { values[entry + ".payload.trademessage.tradeprice"] = canonical::number(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::owner_participant_id>(); }) { values[entry + ".payload.trademessage.ownerparticipantid"] = canonical::text(std::string(message.template get<protocol::owner_participant_id>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::counterparty_participant_id>(); }) { values[entry + ".payload.trademessage.counterpartyparticipantid"] = canonical::text(std::string(message.template get<protocol::counterparty_participant_id>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::printable>(); }) { values[entry + ".payload.trademessage.printable"] = canonical::text(canonical::character(message.template get<protocol::printable>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::occurred_at_cross>(); }) { values[entry + ".payload.trademessage.occurredatcross"] = canonical::text(canonical::character(message.template get<protocol::occurred_at_cross>().value()), ' ', false); }
    }

    void operator()(const protocol::equilibrium_price_update& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.equilibriumpriceupdate";
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { values[entry + ".payload.equilibriumpriceupdate.nanoseconds"] = canonical::number(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { values[entry + ".payload.equilibriumpriceupdate.orderbookid"] = canonical::number(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::available_bid_quantity_at_equilibrium_price>(); }) { values[entry + ".payload.equilibriumpriceupdate.availablebidquantityatequilibriumprice"] = canonical::number(message.template get<protocol::available_bid_quantity_at_equilibrium_price>().value()); }
        if constexpr (requires { message.template get<protocol::available_ask_quantity_at_equilibrium_price>(); }) { values[entry + ".payload.equilibriumpriceupdate.availableaskquantityatequilibriumprice"] = canonical::number(message.template get<protocol::available_ask_quantity_at_equilibrium_price>().value()); }
        if constexpr (requires { message.template get<protocol::equilibrium_price>(); }) { values[entry + ".payload.equilibriumpriceupdate.equilibriumprice"] = canonical::number(message.template get<protocol::equilibrium_price>().value()); }
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
    std::printf("== Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 (tmp values)\n");
    int failures = 0;
    failures += check("AddOrderNoMpid", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/AddOrderNoMpid.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/AddOrderNoMpid.values");
    failures += check("EquilibriumPriceUpdate", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/EquilibriumPriceUpdate.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/EquilibriumPriceUpdate.values");
    failures += check("OrderBookStateMessage", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/OrderBookStateMessage.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/OrderBookStateMessage.values");
    failures += check("OrderDeleteMessage", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/OrderDeleteMessage.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/OrderDeleteMessage.values");
    failures += check("OrderExecutedMessage", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/OrderExecutedMessage.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/OrderExecutedMessage.values");
    failures += check("OrderExecutedWithPriceMessage", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/OrderExecutedWithPriceMessage.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/OrderExecutedWithPriceMessage.values");
    failures += check("SecondsMessage", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/SecondsMessage.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/SecondsMessage.values");
    return failures == 0 ? 0 : 1;
}
