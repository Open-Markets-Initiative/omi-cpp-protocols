// Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22 benchmark.
//
// Reads a capture's datagrams into memory, then times reading them: every datagram parsed by the
// reading below, over the types and structs of the Tmp header, and every field of every message
// read through get<Field>() and folded into a checksum, so no read can be skipped. Each figure is
// the best of the passes asked for.

#include <algorithm>
#include <bit>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <map>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "cpp/binary/tmp/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/cboe_cfefutures_multicastdepthofbook_pitch_v1_2_22.hpp"

// Cboe CfeFutures MulticastDepthOfBook Pitch 1.2.22: the reading of its packets, through its Template Meta Programming header
namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

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

// Futures Instrument Definition Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_futures_instrument_definition_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& futures_instrument_definition_message_section_1_ = tmp::read<futures_instrument_definition_message_section_1>(data + offset, bound - offset, handler); offset += futures_instrument_definition_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(futures_instrument_definition_message_section_1_.template get<leg_count>()));
        while (count-- > 0) {
            offset += tmp::take<future_leg>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 0xB1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& time_reference_message_ = tmp::read<time_reference_message>(data + offset, bound - offset, handler); offset += time_reference_message::size;
        return offset;
    }
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
    if (static_cast<bool>(tmp::rule(message_type_) == 0xBB)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_futures_instrument_definition_message(data + offset, bound - offset, handler);
        tmp::call(handler, futures_instrument_definition_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0xFA)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& futures_variance_symbol_mapping_message_ = tmp::read<futures_variance_symbol_mapping_message>(data + offset, bound - offset, handler); offset += futures_variance_symbol_mapping_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0xBE)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& price_limits_message_ = tmp::read<price_limits_message>(data + offset, bound - offset, handler); offset += price_limits_message::size;
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
    if (static_cast<bool>(tmp::rule(message_type_) == 0x23)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_executed_message_ = tmp::read<order_executed_message>(data + offset, bound - offset, handler); offset += order_executed_message::size;
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
    if (static_cast<bool>(tmp::rule(message_type_) == 0xBC)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& transaction_begin_message_ = tmp::read<transaction_begin_message>(data + offset, bound - offset, handler); offset += transaction_begin_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0xBD)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& transaction_end_message_ = tmp::read<transaction_end_message>(data + offset, bound - offset, handler); offset += transaction_end_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2C)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_break_message_ = tmp::read<trade_break_message>(data + offset, bound - offset, handler); offset += trade_break_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0xB9)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& settlement_message_ = tmp::read<settlement_message>(data + offset, bound - offset, handler); offset += settlement_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0xD3)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& open_interest_message_ = tmp::read<open_interest_message>(data + offset, bound - offset, handler); offset += open_interest_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0xBA)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_day_summary_message_ = tmp::read<end_of_day_summary_message>(data + offset, bound - offset, handler); offset += end_of_day_summary_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x31)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trading_status_message_ = tmp::read<trading_status_message>(data + offset, bound - offset, handler); offset += trading_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2D)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_session_message_ = tmp::read<end_of_session_message>(data + offset, bound - offset, handler); offset += end_of_session_message::size;
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


} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22

namespace protocol = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

namespace {

using clock = std::chrono::steady_clock;

// A value folded into the checksum, whatever its type
template <typename T>
std::uint64_t digest(const T& value) {
    if constexpr (std::is_enum_v<T>) { return static_cast<std::uint64_t>(std::to_underlying(value)); }
    else if constexpr (std::is_same_v<T, bool>) { return value ? 1u : 0u; }
    else if constexpr (std::is_integral_v<T>) { return static_cast<std::uint64_t>(value); }
    else if constexpr (std::is_floating_point_v<T>) { return std::bit_cast<std::uint64_t>(static_cast<double>(value)); }
    else if constexpr (std::is_same_v<T, std::string_view>) { return value.size() + (value.empty() ? 0u : static_cast<unsigned char>(value.front())); }
    else { return value.size() + (value.empty() ? 0u : std::to_integer<std::uint64_t>(value.front())); }
}

template <typename Struct, typename... Fields>
std::uint64_t fold(const Struct& value, protocol::tmp::list<Fields...>);

// A field read through its value; a struct within a struct read field by field
template <typename Field>
std::uint64_t read(const Field& field) {
    if constexpr (requires { typename Field::fields; }) { return fold(field, typename Field::fields{}); }
    else { return digest(field.value()); }
}

// Every field of a struct, each asked for by its type
template <typename Struct, typename... Fields>
std::uint64_t fold(const Struct& value, protocol::tmp::list<Fields...>) {
    return (std::uint64_t{ 0 } + ... + read(value.template get<Fields>()));
}

// Every field of a message, or nothing for a message of no fields
template <typename Message>
std::uint64_t every(const Message& message) {
    if constexpr (requires { typename Message::fields; }) { return fold(message, typename Message::fields{}); }
    else { return 0; }
}

// Is a type the reader hands over a message, not a header or a field?
template <typename T>
constexpr bool is_message = requires { requires T::is_message; };

// Is a type the reader hands over a section of a message no struct lies over?
template <typename T>
constexpr bool is_section = requires { requires T::is_section; };

// The whole read: every message of every datagram, every field of it. A message no struct lies
// over is handed over a section at a time, then announced: its sections' fields are read as they
// come, and the message is counted once.
struct Reading {
    std::uint64_t checksum = 0;
    std::size_t messages = 0;

    template <typename T>
    void operator()(const T& value) {
        if constexpr (is_message<T>) {
            ++messages;
            checksum += every(value);
        }
        else if constexpr (is_section<T>) {
            checksum += every(value);
        }
    }
};

// The messages of one type: how many, where those with fields lie, and how to read every field of them
struct Gathered {
    std::size_t count = 0;
    std::vector<const std::byte*> at;
    std::uint64_t (*run)(const std::vector<const std::byte*>&) = nullptr;
};

template <typename Message>
std::uint64_t run(const std::vector<const std::byte*>& at) {
    std::uint64_t checksum = 0;
    for (const std::byte* bytes : at) { checksum += every(*reinterpret_cast<const Message*>(bytes)); }
    return checksum;
}

// Gathers every message by its type, untimed. A message no struct lies over - one the reader parses
// field by field and then announces - has no bytes of its own to gather; it is only counted.
struct Census {
    std::map<std::string_view, Gathered> types;

    template <typename T>
    void operator()(const T& value) {
        if constexpr (is_message<T>) {
            auto& gathered = types[T::name];
            ++gathered.count;
            if constexpr (requires { typename T::fields; }) {
                gathered.at.push_back(reinterpret_cast<const std::byte*>(&value));
                gathered.run = &run<T>;
            }
        }
    }
};

// The best of the passes, in nanoseconds
template <typename Pass>
double best(int passes, Pass pass) {
    double fastest = 0;
    for (int index = 0; index < passes; ++index) {
        const auto start = clock::now();
        pass();
        const double took = std::chrono::duration<double, std::nano>(clock::now() - start).count();
        if (index == 0 || took < fastest) { fastest = took; }
    }
    return fastest;
}

}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: %s <capture.pcap> [passes]\n", argv[0]);
        return 2;
    }

    const int passes = argc > 2 ? std::max(1, std::atoi(argv[2])) : 10;

    // the capture's datagrams, held in memory so only the reading is timed
    std::vector<std::byte> bytes;
    std::vector<std::pair<std::size_t, std::size_t>> datagrams;
    {
        std::vector<std::pair<std::string, std::int64_t>> sources;
        sources.emplace_back(argv[1], 0);
        packet::PcapIterator captures(sources);

        while (captures.advance()) {
            const packet::Frame frame(captures.data(), captures.length());
            if (!frame.valid() || !frame.is_udp()) { continue; }
            datagrams.emplace_back(bytes.size(), frame.payload_len);
            bytes.insert(bytes.end(), frame.payload, frame.payload + frame.payload_len);
        }
    }

    // untimed: which datagrams parse, and every message gathered by its type
    Census census;
    std::vector<std::pair<std::size_t, std::size_t>> read;
    std::size_t failed = 0;
    std::size_t length = 0;

    for (const auto& [offset, size] : datagrams) {
        try {
            protocol::parse_packet(bytes.data() + offset, size, census);
            read.emplace_back(offset, size);
            length += size;
        } catch (const std::exception&) {
            ++failed;
        }
    }

    // timed: the whole read
    Reading reading;
    const double whole = best(passes, [&] {
        reading = Reading{};
        for (const auto& [offset, size] : read) { protocol::parse_packet(bytes.data() + offset, size, reading); }
    });

    std::printf("Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22\n");
    std::printf("  %zu datagrams read, %zu did not parse; %zu bytes, %zu messages\n", read.size(), failed, length, reading.messages);
    std::printf("  whole read, best of %d: %.3f ms, %.1f ns/datagram, %.1f ns/message, %.2f M messages/s, %.1f MB/s\n",
        passes, whole / 1e6,
        read.empty() ? 0.0 : whole / static_cast<double>(read.size()),
        reading.messages == 0 ? 0.0 : whole / static_cast<double>(reading.messages),
        whole == 0 ? 0.0 : static_cast<double>(reading.messages) / whole * 1e3,
        whole == 0 ? 0.0 : static_cast<double>(length) / whole * 1e3);
    std::printf("  checksum %016llx\n", static_cast<unsigned long long>(reading.checksum));

    // timed: each message type's field reads on their own
    std::printf("  every field of each message type, best of %d:\n", passes);
    for (const auto& [name, gathered] : census.types) {
        if (gathered.run == nullptr) {
            std::printf("    %-48.*s %10zu  (read field by field in the whole read)\n",
                static_cast<int>(name.size()), name.data(), gathered.count);
            continue;
        }

        std::uint64_t checksum = 0;
        const double took = best(passes, [&] { checksum = gathered.run(gathered.at); });
        std::printf("    %-48.*s %10zu  %8.2f ns/message  (checksum %016llx)\n",
            static_cast<int>(name.size()), name.data(), gathered.count,
            gathered.at.empty() ? 0.0 : took / static_cast<double>(gathered.at.size()),
            static_cast<unsigned long long>(checksum));
    }

    return failed == 0 ? 0 : 1;
}
