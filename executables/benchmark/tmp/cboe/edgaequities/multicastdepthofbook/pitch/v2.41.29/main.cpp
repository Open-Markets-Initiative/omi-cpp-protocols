// Cboe.EdgaEquities.MulticastDepthOfBook.Pitch.v2.41.29 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/edgaequities/multicastdepthofbook/pitch/v2.41.29.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/cboe/edgaequities/multicastdepthofbook/pitch/v2.41.29/cboe_edgaequities_multicastdepthofbook_pitch_v2_41_29.hpp"

// Cboe EdgaEquities MulticastDepthOfBook Pitch 2.41.29: the reading of its packets, through its Template Meta Programming header
namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

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
    if (static_cast<bool>(tmp::rule(message_type_) == 0x20)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& time_message_ = tmp::read<time_message>(data + offset, bound - offset, handler); offset += time_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x97)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& unit_clear_message_ = tmp::read<unit_clear_message>(data + offset, bound - offset, handler); offset += unit_clear_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x21)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_long_message_ = tmp::read<add_order_long_message>(data + offset, bound - offset, handler); offset += add_order_long_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x22)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_short_message_ = tmp::read<add_order_short_message>(data + offset, bound - offset, handler); offset += add_order_short_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2F)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_expanded_message_ = tmp::read<add_order_expanded_message>(data + offset, bound - offset, handler); offset += add_order_expanded_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x23)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_executed_message_ = tmp::read<order_executed_message>(data + offset, bound - offset, handler); offset += order_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x24)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_executed_at_price_size_message_ = tmp::read<order_executed_at_price_size_message>(data + offset, bound - offset, handler); offset += order_executed_at_price_size_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x25)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reduce_size_long_message_ = tmp::read<reduce_size_long_message>(data + offset, bound - offset, handler); offset += reduce_size_long_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x26)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reduce_size_short_message_ = tmp::read<reduce_size_short_message>(data + offset, bound - offset, handler); offset += reduce_size_short_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x27)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& modify_order_long_message_ = tmp::read<modify_order_long_message>(data + offset, bound - offset, handler); offset += modify_order_long_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x28)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& modify_order_short_message_ = tmp::read<modify_order_short_message>(data + offset, bound - offset, handler); offset += modify_order_short_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x29)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& delete_order_message_ = tmp::read<delete_order_message>(data + offset, bound - offset, handler); offset += delete_order_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2A)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_long_message_ = tmp::read<trade_long_message>(data + offset, bound - offset, handler); offset += trade_long_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2B)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_short_message_ = tmp::read<trade_short_message>(data + offset, bound - offset, handler); offset += trade_short_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x30)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_expanded_message_ = tmp::read<trade_expanded_message>(data + offset, bound - offset, handler); offset += trade_expanded_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2C)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_break_message_ = tmp::read<trade_break_message>(data + offset, bound - offset, handler); offset += trade_break_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2D)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_session_ = tmp::read<end_of_session>(data + offset, bound - offset, handler); offset += end_of_session::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x31)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trading_status_message_ = tmp::read<trading_status_message>(data + offset, bound - offset, handler); offset += trading_status_message::size;
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
    bound = static_cast<std::size_t>(tmp::rule(message_header_.template get<message_length>()));
    tmp::require(bound, length);
    offset += parse_payload(data + offset, bound - offset, handler, message_header_.template get<message_type>());
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
    {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
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


} // namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29

namespace protocol = ::cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::length_type>(); }) { checksum += bench::digest(header.template get<protocol::length_type>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { checksum += bench::digest(header.template get<protocol::message_count>().value()); }
        if constexpr (requires { header.template get<protocol::unit>(); }) { checksum += bench::digest(header.template get<protocol::unit>().value()); }
        if constexpr (requires { header.template get<protocol::sequence>(); }) { checksum += bench::digest(header.template get<protocol::sequence>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::message_length>(); }) { checksum += bench::digest(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { checksum += bench::digest(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::time_message& message) {
        if constexpr (requires { message.template get<protocol::time>(); }) { checksum += bench::digest(message.template get<protocol::time>().value()); }
    }

    void operator()(const protocol::unit_clear_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
    }

    void operator()(const protocol::add_order_long_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side_indicator>(); }) { checksum += bench::digest(message.template get<protocol::side_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_short>(); }) { checksum += bench::digest(message.template get<protocol::symbol_short>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::add_order_short_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side_indicator>(); }) { checksum += bench::digest(message.template get<protocol::side_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::quantity_short>(); }) { checksum += bench::digest(message.template get<protocol::quantity_short>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_short>(); }) { checksum += bench::digest(message.template get<protocol::symbol_short>().value()); }
        if constexpr (requires { message.template get<protocol::price_short>(); }) { checksum += bench::digest(message.template get<protocol::price_short>().value()); }
    }

    void operator()(const protocol::add_order_expanded_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side_indicator>(); }) { checksum += bench::digest(message.template get<protocol::side_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_long>(); }) { checksum += bench::digest(message.template get<protocol::symbol_long>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::participant_id>(); }) { checksum += bench::digest(message.template get<protocol::participant_id>().value()); }
        if constexpr (requires { message.template get<protocol::customer_indicator>(); }) { checksum += bench::digest(message.template get<protocol::customer_indicator>().value()); }
    }

    void operator()(const protocol::order_executed_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { checksum += bench::digest(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { checksum += bench::digest(message.template get<protocol::execution_id>().value()); }
    }

    void operator()(const protocol::order_executed_at_price_size_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { checksum += bench::digest(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::remaining_quantity>(); }) { checksum += bench::digest(message.template get<protocol::remaining_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { checksum += bench::digest(message.template get<protocol::execution_id>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::reduce_size_long_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::canceled_quantity>(); }) { checksum += bench::digest(message.template get<protocol::canceled_quantity>().value()); }
    }

    void operator()(const protocol::reduce_size_short_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::canceled_quantity_short>(); }) { checksum += bench::digest(message.template get<protocol::canceled_quantity_short>().value()); }
    }

    void operator()(const protocol::modify_order_long_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::modify_order_short_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity_short>(); }) { checksum += bench::digest(message.template get<protocol::quantity_short>().value()); }
        if constexpr (requires { message.template get<protocol::price_short>(); }) { checksum += bench::digest(message.template get<protocol::price_short>().value()); }
    }

    void operator()(const protocol::delete_order_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
    }

    void operator()(const protocol::trade_long_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side_indicator>(); }) { checksum += bench::digest(message.template get<protocol::side_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_short>(); }) { checksum += bench::digest(message.template get<protocol::symbol_short>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { checksum += bench::digest(message.template get<protocol::execution_id>().value()); }
    }

    void operator()(const protocol::trade_short_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side_indicator>(); }) { checksum += bench::digest(message.template get<protocol::side_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::quantity_short>(); }) { checksum += bench::digest(message.template get<protocol::quantity_short>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_short>(); }) { checksum += bench::digest(message.template get<protocol::symbol_short>().value()); }
        if constexpr (requires { message.template get<protocol::price_short>(); }) { checksum += bench::digest(message.template get<protocol::price_short>().value()); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { checksum += bench::digest(message.template get<protocol::execution_id>().value()); }
    }

    void operator()(const protocol::trade_expanded_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side_indicator>(); }) { checksum += bench::digest(message.template get<protocol::side_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_long>(); }) { checksum += bench::digest(message.template get<protocol::symbol_long>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { checksum += bench::digest(message.template get<protocol::execution_id>().value()); }
    }

    void operator()(const protocol::trade_break_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { checksum += bench::digest(message.template get<protocol::execution_id>().value()); }
    }

    void operator()(const protocol::end_of_session& message) {
        if constexpr (requires { message.template get<protocol::last_timestamp>(); }) { checksum += bench::digest(message.template get<protocol::last_timestamp>().value()); }
    }

    void operator()(const protocol::trading_status_message& message) {
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { checksum += bench::digest(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_long>(); }) { checksum += bench::digest(message.template get<protocol::symbol_long>().value()); }
        if constexpr (requires { message.template get<protocol::trading_status>(); }) { checksum += bench::digest(message.template get<protocol::trading_status>().value()); }
        if constexpr (requires { message.template get<protocol::reg_sho_action>(); }) { checksum += bench::digest(message.template get<protocol::reg_sho_action>().value()); }
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
    return bench::run("Cboe.EdgaEquities.MulticastDepthOfBook.Pitch.v2.41.29", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
