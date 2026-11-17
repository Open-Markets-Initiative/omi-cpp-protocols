// Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1: main.cpp
// Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/iseoptions/ordercombofeed/itch/v1.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/nasdaq/iseoptions/ordercombofeed/itch/v1.1/nasdaq_iseoptions_ordercombofeed_itch_v1_1.hpp"

// Nasdaq IseOptions OrderComboFeed Itch 1.1: the reading of its packets, through its Template Meta Programming header
namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

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

// Complex Strategy Auction Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_complex_strategy_auction_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& complex_strategy_auction_message_section_1_ = tmp::read<complex_strategy_auction_message_section_1>(data + offset, bound - offset, handler); offset += complex_strategy_auction_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(complex_strategy_auction_message_section_1_.template get<number_of_responses>()));
        while (count-- > 0) {
            offset += tmp::take<auction_response>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Complex Strategy Directory Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_complex_strategy_directory_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& complex_strategy_directory_message_section_1_ = tmp::read<complex_strategy_directory_message_section_1>(data + offset, bound - offset, handler); offset += complex_strategy_directory_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(complex_strategy_directory_message_section_1_.template get<number_of_legs>()));
        while (count-- > 0) {
            offset += tmp::take<leg_information>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_event_message_ = tmp::read<system_event_message>(data + offset, bound - offset, handler); offset += system_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_complex_strategy_directory_message(data + offset, bound - offset, handler);
        tmp::call(handler, complex_strategy_directory_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& strategy_trading_action_message_ = tmp::read<strategy_trading_action_message>(data + offset, bound - offset, handler); offset += strategy_trading_action_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& strategy_open_closed_message_ = tmp::read<strategy_open_closed_message>(data + offset, bound - offset, handler); offset += strategy_open_closed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& complex_strategy_order_on_book_message_ = tmp::read<complex_strategy_order_on_book_message>(data + offset, bound - offset, handler); offset += complex_strategy_order_on_book_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'J')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_complex_strategy_auction_message(data + offset, bound - offset, handler);
        tmp::call(handler, complex_strategy_auction_message{});
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


} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1

namespace protocol = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;

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
        if constexpr (requires { message.template get<protocol::event_code>(); }) { checksum += bench::digest(message.template get<protocol::event_code>().value()); }
        if constexpr (requires { message.template get<protocol::current_year>(); }) { checksum += bench::digest(message.template get<protocol::current_year>().value()); }
        if constexpr (requires { message.template get<protocol::current_month>(); }) { checksum += bench::digest(message.template get<protocol::current_month>().value()); }
        if constexpr (requires { message.template get<protocol::current_day>(); }) { checksum += bench::digest(message.template get<protocol::current_day>().value()); }
        if constexpr (requires { message.template get<protocol::version>(); }) { checksum += bench::digest(message.template get<protocol::version>().value()); }
        if constexpr (requires { message.template get<protocol::sub_version>(); }) { checksum += bench::digest(message.template get<protocol::sub_version>().value()); }
    }

    void operator()(const protocol::complex_strategy_directory_message&) {
    }

    void operator()(const protocol::strategy_trading_action_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::strategy_id>(); }) { checksum += bench::digest(message.template get<protocol::strategy_id>().value()); }
        if constexpr (requires { message.template get<protocol::current_trading_state>(); }) { checksum += bench::digest(message.template get<protocol::current_trading_state>().value()); }
    }

    void operator()(const protocol::strategy_open_closed_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::strategy_id>(); }) { checksum += bench::digest(message.template get<protocol::strategy_id>().value()); }
        if constexpr (requires { message.template get<protocol::open_state>(); }) { checksum += bench::digest(message.template get<protocol::open_state>().value()); }
    }

    void operator()(const protocol::complex_strategy_order_on_book_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::strategy_id>(); }) { checksum += bench::digest(message.template get<protocol::strategy_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_type>(); }) { checksum += bench::digest(message.template get<protocol::order_type>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { checksum += bench::digest(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::exec_flag>(); }) { checksum += bench::digest(message.template get<protocol::exec_flag>().value()); }
        if constexpr (requires { message.template get<protocol::order_capacity>(); }) { checksum += bench::digest(message.template get<protocol::order_capacity>().value()); }
        if constexpr (requires { message.template get<protocol::scope>(); }) { checksum += bench::digest(message.template get<protocol::scope>().value()); }
        if constexpr (requires { message.template get<protocol::owner_id>(); }) { checksum += bench::digest(message.template get<protocol::owner_id>().value()); }
        if constexpr (requires { message.template get<protocol::giveup>(); }) { checksum += bench::digest(message.template get<protocol::giveup>().value()); }
        if constexpr (requires { message.template get<protocol::cmta>(); }) { checksum += bench::digest(message.template get<protocol::cmta>().value()); }
    }

    void operator()(const protocol::complex_strategy_auction_message&) {
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
    return bench::run("Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
