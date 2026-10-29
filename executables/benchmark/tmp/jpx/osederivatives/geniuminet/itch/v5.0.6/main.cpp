// Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/jpx/osederivatives/geniuminet/itch/v5.0.6.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
        if constexpr (requires { message.template get<protocol::seconds>(); }) { checksum += bench::digest(message.template get<protocol::seconds>().value()); }
    }

    void operator()(const protocol::order_book_directory& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { checksum += bench::digest(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::long_name>(); }) { checksum += bench::digest(message.template get<protocol::long_name>().value()); }
        if constexpr (requires { message.template get<protocol::isin>(); }) { checksum += bench::digest(message.template get<protocol::isin>().value()); }
        if constexpr (requires { message.template get<protocol::financial_product>(); }) { checksum += bench::digest(message.template get<protocol::financial_product>().value()); }
        if constexpr (requires { message.template get<protocol::trading_currency>(); }) { checksum += bench::digest(message.template get<protocol::trading_currency>().value()); }
        if constexpr (requires { message.template get<protocol::decimals_in_price>(); }) { checksum += bench::digest(message.template get<protocol::decimals_in_price>().value()); }
        if constexpr (requires { message.template get<protocol::decimals_in_nominal_value>(); }) { checksum += bench::digest(message.template get<protocol::decimals_in_nominal_value>().value()); }
        if constexpr (requires { message.template get<protocol::odd_lot_size>(); }) { checksum += bench::digest(message.template get<protocol::odd_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::round_lot_size>(); }) { checksum += bench::digest(message.template get<protocol::round_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::block_lot_size>(); }) { checksum += bench::digest(message.template get<protocol::block_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::nominal_value>(); }) { checksum += bench::digest(message.template get<protocol::nominal_value>().value()); }
        if constexpr (requires { message.template get<protocol::number_of_legs>(); }) { checksum += bench::digest(message.template get<protocol::number_of_legs>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_orderbook_id>(); }) { checksum += bench::digest(message.template get<protocol::underlying_orderbook_id>().value()); }
        if constexpr (requires { message.template get<protocol::strike_price>(); }) { checksum += bench::digest(message.template get<protocol::strike_price>().value()); }
        if constexpr (requires { message.template get<protocol::expiration_date>(); }) { checksum += bench::digest(message.template get<protocol::expiration_date>().value()); }
        if constexpr (requires { message.template get<protocol::decimals_in_strike_price>(); }) { checksum += bench::digest(message.template get<protocol::decimals_in_strike_price>().value()); }
        if constexpr (requires { message.template get<protocol::put_or_call>(); }) { checksum += bench::digest(message.template get<protocol::put_or_call>().value()); }
    }

    void operator()(const protocol::combination_orderbook_leg& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::combination_orderbook_id>(); }) { checksum += bench::digest(message.template get<protocol::combination_orderbook_id>().value()); }
        if constexpr (requires { message.template get<protocol::leg_orderbook_id>(); }) { checksum += bench::digest(message.template get<protocol::leg_orderbook_id>().value()); }
        if constexpr (requires { message.template get<protocol::leg_side>(); }) { checksum += bench::digest(message.template get<protocol::leg_side>().value()); }
        if constexpr (requires { message.template get<protocol::leg_ratio>(); }) { checksum += bench::digest(message.template get<protocol::leg_ratio>().value()); }
    }

    void operator()(const protocol::tick_size_table_entry& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { checksum += bench::digest(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::tick_size>(); }) { checksum += bench::digest(message.template get<protocol::tick_size>().value()); }
        if constexpr (requires { message.template get<protocol::price_from>(); }) { checksum += bench::digest(message.template get<protocol::price_from>().value()); }
        if constexpr (requires { message.template get<protocol::price_to>(); }) { checksum += bench::digest(message.template get<protocol::price_to>().value()); }
    }

    void operator()(const protocol::system_event_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::event_code>(); }) { checksum += bench::digest(message.template get<protocol::event_code>().value()); }
    }

    void operator()(const protocol::order_book_state_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { checksum += bench::digest(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::state_name>(); }) { checksum += bench::digest(message.template get<protocol::state_name>().value()); }
    }

    void operator()(const protocol::add_order_no_mpid& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { checksum += bench::digest(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_position>(); }) { checksum += bench::digest(message.template get<protocol::order_book_position>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::lot_type>(); }) { checksum += bench::digest(message.template get<protocol::lot_type>().value()); }
    }

    void operator()(const protocol::add_order_with_mpid& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { checksum += bench::digest(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_position>(); }) { checksum += bench::digest(message.template get<protocol::order_book_position>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::lot_type>(); }) { checksum += bench::digest(message.template get<protocol::lot_type>().value()); }
        if constexpr (requires { message.template get<protocol::participant_id>(); }) { checksum += bench::digest(message.template get<protocol::participant_id>().value()); }
    }

    void operator()(const protocol::order_executed_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { checksum += bench::digest(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { checksum += bench::digest(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::match_id>(); }) { checksum += bench::digest(message.template get<protocol::match_id>().value()); }
        if constexpr (requires { message.template get<protocol::combo_group_id>(); }) { checksum += bench::digest(message.template get<protocol::combo_group_id>().value()); }
        if constexpr (requires { message.template get<protocol::participant_id_owner>(); }) { checksum += bench::digest(message.template get<protocol::participant_id_owner>().value()); }
        if constexpr (requires { message.template get<protocol::participant_id_counterparty>(); }) { checksum += bench::digest(message.template get<protocol::participant_id_counterparty>().value()); }
    }

    void operator()(const protocol::order_executed_with_price_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { checksum += bench::digest(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { checksum += bench::digest(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::match_id>(); }) { checksum += bench::digest(message.template get<protocol::match_id>().value()); }
        if constexpr (requires { message.template get<protocol::combo_group_id>(); }) { checksum += bench::digest(message.template get<protocol::combo_group_id>().value()); }
        if constexpr (requires { message.template get<protocol::owner_participant_id>(); }) { checksum += bench::digest(message.template get<protocol::owner_participant_id>().value()); }
        if constexpr (requires { message.template get<protocol::counterparty_participant_id>(); }) { checksum += bench::digest(message.template get<protocol::counterparty_participant_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { checksum += bench::digest(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::occurred_at_cross>(); }) { checksum += bench::digest(message.template get<protocol::occurred_at_cross>().value()); }
        if constexpr (requires { message.template get<protocol::printable>(); }) { checksum += bench::digest(message.template get<protocol::printable>().value()); }
    }

    void operator()(const protocol::order_replace_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { checksum += bench::digest(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::new_orderbook_position>(); }) { checksum += bench::digest(message.template get<protocol::new_orderbook_position>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::order_delete_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { checksum += bench::digest(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
    }

    void operator()(const protocol::trade_message& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::match_id>(); }) { checksum += bench::digest(message.template get<protocol::match_id>().value()); }
        if constexpr (requires { message.template get<protocol::combo_group_id>(); }) { checksum += bench::digest(message.template get<protocol::combo_group_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { checksum += bench::digest(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { checksum += bench::digest(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::owner_participant_id>(); }) { checksum += bench::digest(message.template get<protocol::owner_participant_id>().value()); }
        if constexpr (requires { message.template get<protocol::counterparty_participant_id>(); }) { checksum += bench::digest(message.template get<protocol::counterparty_participant_id>().value()); }
        if constexpr (requires { message.template get<protocol::printable>(); }) { checksum += bench::digest(message.template get<protocol::printable>().value()); }
        if constexpr (requires { message.template get<protocol::occurred_at_cross>(); }) { checksum += bench::digest(message.template get<protocol::occurred_at_cross>().value()); }
    }

    void operator()(const protocol::equilibrium_price_update& message) {
        if constexpr (requires { message.template get<protocol::nanoseconds>(); }) { checksum += bench::digest(message.template get<protocol::nanoseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_id>(); }) { checksum += bench::digest(message.template get<protocol::order_book_id>().value()); }
        if constexpr (requires { message.template get<protocol::available_bid_quantity_at_equilibrium_price>(); }) { checksum += bench::digest(message.template get<protocol::available_bid_quantity_at_equilibrium_price>().value()); }
        if constexpr (requires { message.template get<protocol::available_ask_quantity_at_equilibrium_price>(); }) { checksum += bench::digest(message.template get<protocol::available_ask_quantity_at_equilibrium_price>().value()); }
        if constexpr (requires { message.template get<protocol::equilibrium_price>(); }) { checksum += bench::digest(message.template get<protocol::equilibrium_price>().value()); }
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
    return bench::run("Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
