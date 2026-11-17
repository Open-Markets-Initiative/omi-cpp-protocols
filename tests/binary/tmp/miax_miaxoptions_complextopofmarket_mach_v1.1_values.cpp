// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1 canonical values, through the Tmp header: every value the Tmp reading hands
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
#include "cpp/binary/tmp/miax/miaxoptions/complextopofmarket/mach/v1.1/miax_miaxoptions_complextopofmarket_mach_v1_1.hpp"

// Miax MiaxOptions ComplexTopOfMarket Mach 1.1: the reading of its packets, through its Template Meta Programming header
namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

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

// Complex Strategy Definition Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_complex_strategy_definition_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& complex_strategy_definition_message_section_1_ = tmp::read<complex_strategy_definition_message_section_1>(data + offset, bound - offset, handler); offset += complex_strategy_definition_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(complex_strategy_definition_message_section_1_.template get<number_of_legs>()));
        while (count-- > 0) {
            offset += tmp::take<leg_definition>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Data: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_data_type([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == '1')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_time_message_ = tmp::read<system_time_message>(data + offset, bound - offset, handler); offset += system_time_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& series_update_ = tmp::read<series_update>(data + offset, bound - offset, handler); offset += series_update::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_complex_strategy_definition_message(data + offset, bound - offset, handler);
        tmp::call(handler, complex_strategy_definition_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_state_message_ = tmp::read<system_state_message>(data + offset, bound - offset, handler); offset += system_state_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'b')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& compact_complex_top_of_market_bid_message_ = tmp::read<compact_complex_top_of_market_bid_message>(data + offset, bound - offset, handler); offset += compact_complex_top_of_market_bid_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'o')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& compact_complex_top_of_market_offer_message_ = tmp::read<compact_complex_top_of_market_offer_message>(data + offset, bound - offset, handler); offset += compact_complex_top_of_market_offer_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'e')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& wide_complex_top_of_market_bid_message_ = tmp::read<wide_complex_top_of_market_bid_message>(data + offset, bound - offset, handler); offset += wide_complex_top_of_market_bid_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'f')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& wide_complex_top_of_market_offer_message_ = tmp::read<wide_complex_top_of_market_offer_message>(data + offset, bound - offset, handler); offset += wide_complex_top_of_market_offer_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'm')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& compact_complex_double_sided_top_of_market_message_ = tmp::read<compact_complex_double_sided_top_of_market_message>(data + offset, bound - offset, handler); offset += compact_complex_double_sided_top_of_market_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'w')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& wide_complex_double_sided_top_of_market_message_ = tmp::read<wide_complex_double_sided_top_of_market_message>(data + offset, bound - offset, handler); offset += wide_complex_double_sided_top_of_market_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 't')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& strategy_trade_message_ = tmp::read<strategy_trade_message>(data + offset, bound - offset, handler); offset += strategy_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& underlying_trading_status_message_ = tmp::read<underlying_trading_status_message>(data + offset, bound - offset, handler); offset += underlying_trading_status_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Application Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_application_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& application_message_section_1_ = tmp::read<application_message_section_1>(data + offset, bound - offset, handler); offset += application_message_section_1::size;
    offset += parse_data_type(data + offset, bound - offset, handler, application_message_section_1_.template get<message_type>());
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const packet_type& packet_type_, const packet_length& packet_length_) {
    if (static_cast<bool>(tmp::rule(packet_type_) == 0)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, heartbeat{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(packet_type_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, start_of_session{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(packet_type_) == 2)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, end_of_session{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(packet_type_) == 3)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(packet_length_))) - 12);
            tmp::require(offset + size, bound);
            parse_application_message(data + offset, size, handler);
            offset += size;
        }
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Mach Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_mach_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& mach_packet_header_ = tmp::read<mach_packet_header>(data + offset, bound - offset, handler); offset += mach_packet_header::size;
    bound = static_cast<std::size_t>(tmp::rule(mach_packet_header_.template get<packet_length>()));
    tmp::require(bound, length);
    offset += parse_payload(data + offset, bound - offset, handler, mach_packet_header_.template get<packet_type>(), mach_packet_header_.template get<packet_length>());
    return bound;
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    {
        const std::size_t end = static_cast<std::size_t>(static_cast<std::int64_t>(bound));
        tmp::require(end, bound);
        while (offset < end) {
            [[maybe_unused]] const std::size_t bound = end;
            offset += parse_mach_message(data + offset, bound - offset, handler);
        }
    }
    return offset;
}


} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1

namespace protocol = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::mach_packet_header& header) {
        entry = "packet.machmessage[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { values[entry + ".machpacketheader.sequencenumber"] = canonical::number(header.template get<protocol::sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::packet_length>(); }) { values[entry + ".machpacketheader.packetlength"] = canonical::number(header.template get<protocol::packet_length>().value()); }
        if constexpr (requires { header.template get<protocol::packet_type>(); }) { values[entry + ".machpacketheader.packettype"] = canonical::number(header.template get<protocol::packet_type>().value()); }
        if constexpr (requires { header.template get<protocol::session_number>(); }) { values[entry + ".machpacketheader.sessionnumber"] = canonical::number(header.template get<protocol::session_number>().value()); }
    }

    void operator()(const protocol::application_message&) {
        values[entry + ".payload"] = "packet.machmessage.payload.applicationmessage";
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
    std::printf("== Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1 (tmp values)\n");
    int failures = 0;
    failures += check("Heartbeat", "Miax/MiaxOptions.ComplexTopOfMarket.Mach.v1.1/Heartbeat.pcap", "miax/miaxoptions/complextopofmarket/mach/v1.1/Heartbeat.values");
    failures += check("SystemStateMessage", "Miax/MiaxOptions.ComplexTopOfMarket.Mach.v1.1/SystemStateMessage.pcap", "miax/miaxoptions/complextopofmarket/mach/v1.1/SystemStateMessage.values");
    return failures == 0 ? 0 : 1;
}
