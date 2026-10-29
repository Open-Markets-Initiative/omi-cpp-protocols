// Jpx.TseEquities.MarketByOrder.Flex.v1.1 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/jpx/tseequities/marketbyorder/flex/v1.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/jpx/tseequities/marketbyorder/flex/v1.1/jpx_tseequities_marketbyorder_flex_v1_1.hpp"

// Jpx TseEquities MarketByOrder Flex 1.1: the reading of its packets, through its Template Meta Programming header
namespace jpx::tseequities::marketbyorder::flex::v1_1 {

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

// Message Response Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message_response_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    {
        const std::size_t rest = bound - offset;
        tmp::call(handler, data_type{ data + offset, rest });
        offset += rest;
    }
    return offset;
}

// Tcp Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_tcp_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const packet_type& packet_type_) {
    if (static_cast<bool>(tmp::rule(packet_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& login_request_retransmission_message_ = tmp::read<login_request_retransmission_message>(data + offset, bound - offset, handler); offset += login_request_retransmission_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(packet_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& login_request_snapshot_message_ = tmp::read<login_request_snapshot_message>(data + offset, bound - offset, handler); offset += login_request_snapshot_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(packet_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& login_result_accepted_message_ = tmp::read<login_result_accepted_message>(data + offset, bound - offset, handler); offset += login_result_accepted_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(packet_type_) == 'J')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& login_result_rejected_message_ = tmp::read<login_result_rejected_message>(data + offset, bound - offset, handler); offset += login_result_rejected_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(packet_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_message_response_message(data + offset, bound - offset, handler);
        tmp::call(handler, message_response_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(packet_type_) == 'G')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_message_message_ = tmp::read<end_of_message_message>(data + offset, bound - offset, handler); offset += end_of_message_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Tcp Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_tcp_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& tcp_packet_header_ = tmp::read<tcp_packet_header>(data + offset, bound - offset, handler); offset += tcp_packet_header::size;
    offset += parse_tcp_payload(data + offset, bound - offset, handler, tcp_packet_header_.template get<packet_type>());
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 'T')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& seconds_timestamp_message_ = tmp::read<seconds_timestamp_message>(data + offset, bound - offset, handler); offset += seconds_timestamp_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trading_status_message_ = tmp::read<trading_status_message>(data + offset, bound - offset, handler); offset += trading_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'K')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& execution_summary_message_ = tmp::read<execution_summary_message>(data + offset, bound - offset, handler); offset += execution_summary_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_message_ = tmp::read<add_order_message>(data + offset, bound - offset, handler); offset += add_order_message::size;
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
    if (static_cast<bool>(tmp::rule(message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_delete_message_ = tmp::read<order_delete_message>(data + offset, bound - offset, handler); offset += order_delete_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reset_message_ = tmp::read<reset_message>(data + offset, bound - offset, handler); offset += reset_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& communication_control_message_ = tmp::read<communication_control_message>(data + offset, bound - offset, handler); offset += communication_control_message::size;
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
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<tag_length>()))) + 1);
    tmp::require(bound, length);
    offset += parse_payload(data + offset, bound - offset, handler, message_header_.template get<message_type>());
    return bound;
}

// Udp Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_udp_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(packet_header_.template get<message_count>()));
        while (count-- > 0) {
            offset += parse_message(data + offset, bound - offset, handler);
        }
    }
    return offset;
}


} // namespace jpx::tseequities::marketbyorder::flex::v1_1

namespace protocol = ::jpx::tseequities::marketbyorder::flex::v1_1;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::multicast_group_number>(); }) { checksum += bench::digest(header.template get<protocol::multicast_group_number>().value()); }
        if constexpr (requires { header.template get<protocol::number_of_system_reboots>(); }) { checksum += bench::digest(header.template get<protocol::number_of_system_reboots>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { checksum += bench::digest(header.template get<protocol::sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::issue_code>(); }) { checksum += bench::digest(header.template get<protocol::issue_code>().value()); }
        if constexpr (requires { header.template get<protocol::update_number>(); }) { checksum += bench::digest(header.template get<protocol::update_number>().value()); }
        if constexpr (requires { header.template get<protocol::packet_number>(); }) { checksum += bench::digest(header.template get<protocol::packet_number>().value()); }
        if constexpr (requires { header.template get<protocol::total_number_of_packets>(); }) { checksum += bench::digest(header.template get<protocol::total_number_of_packets>().value()); }
        if constexpr (requires { header.template get<protocol::utility_flag>(); }) { checksum += bench::digest(header.template get<protocol::utility_flag>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { checksum += bench::digest(header.template get<protocol::message_count>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::tag_length>(); }) { checksum += bench::digest(header.template get<protocol::tag_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { checksum += bench::digest(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::seconds_timestamp_message& message) {
        if constexpr (requires { message.template get<protocol::time_seconds>(); }) { checksum += bench::digest(message.template get<protocol::time_seconds>().value()); }
    }

    void operator()(const protocol::trading_status_message& message) {
        if constexpr (requires { message.template get<protocol::time_microseconds>(); }) { checksum += bench::digest(message.template get<protocol::time_microseconds>().value()); }
        if constexpr (requires { message.template get<protocol::market_status>(); }) { checksum += bench::digest(message.template get<protocol::market_status>().value()); }
        if constexpr (requires { message.template get<protocol::status_flag>(); }) { checksum += bench::digest(message.template get<protocol::status_flag>().value()); }
        if constexpr (requires { message.template get<protocol::short_selling_status>(); }) { checksum += bench::digest(message.template get<protocol::short_selling_status>().value()); }
        if constexpr (requires { message.template get<protocol::pricing_method>(); }) { checksum += bench::digest(message.template get<protocol::pricing_method>().value()); }
        if constexpr (requires { message.template get<protocol::book_center_price>(); }) { checksum += bench::digest(message.template get<protocol::book_center_price>().value()); }
    }

    void operator()(const protocol::execution_summary_message& message) {
        if constexpr (requires { message.template get<protocol::time_microseconds>(); }) { checksum += bench::digest(message.template get<protocol::time_microseconds>().value()); }
        if constexpr (requires { message.template get<protocol::triggered_side>(); }) { checksum += bench::digest(message.template get<protocol::triggered_side>().value()); }
        if constexpr (requires { message.template get<protocol::total_volume>(); }) { checksum += bench::digest(message.template get<protocol::total_volume>().value()); }
        if constexpr (requires { message.template get<protocol::total_invalidation>(); }) { checksum += bench::digest(message.template get<protocol::total_invalidation>().value()); }
        if constexpr (requires { message.template get<protocol::last_price>(); }) { checksum += bench::digest(message.template get<protocol::last_price>().value()); }
        if constexpr (requires { message.template get<protocol::match_id>(); }) { checksum += bench::digest(message.template get<protocol::match_id>().value()); }
        if constexpr (requires { message.template get<protocol::best_offer>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::best_offer>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::best_offer>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::best_bid>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::best_bid>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::best_bid>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::add_order_message& message) {
        if constexpr (requires { message.template get<protocol::time_microseconds>(); }) { checksum += bench::digest(message.template get<protocol::time_microseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_condition>(); }) { checksum += bench::digest(message.template get<protocol::order_condition>().value()); }
        if constexpr (requires { message.template get<protocol::modification_flag>(); }) { checksum += bench::digest(message.template get<protocol::modification_flag>().value()); }
    }

    void operator()(const protocol::order_executed_message& message) {
        if constexpr (requires { message.template get<protocol::time_microseconds>(); }) { checksum += bench::digest(message.template get<protocol::time_microseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += bench::digest(message.template get<protocol::volume>().value()); }
        if constexpr (requires { message.template get<protocol::match_id>(); }) { checksum += bench::digest(message.template get<protocol::match_id>().value()); }
    }

    void operator()(const protocol::order_executed_with_price_message& message) {
        if constexpr (requires { message.template get<protocol::time_microseconds>(); }) { checksum += bench::digest(message.template get<protocol::time_microseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += bench::digest(message.template get<protocol::volume>().value()); }
        if constexpr (requires { message.template get<protocol::match_id>(); }) { checksum += bench::digest(message.template get<protocol::match_id>().value()); }
        if constexpr (requires { message.template get<protocol::execution_price>(); }) { checksum += bench::digest(message.template get<protocol::execution_price>().value()); }
        if constexpr (requires { message.template get<protocol::adopted_pricing_method>(); }) { checksum += bench::digest(message.template get<protocol::adopted_pricing_method>().value()); }
    }

    void operator()(const protocol::order_delete_message& message) {
        if constexpr (requires { message.template get<protocol::time_microseconds>(); }) { checksum += bench::digest(message.template get<protocol::time_microseconds>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::modification_flag>(); }) { checksum += bench::digest(message.template get<protocol::modification_flag>().value()); }
    }

    void operator()(const protocol::reset_message& message) {
        if constexpr (requires { message.template get<protocol::reset_start_end_flag>(); }) { checksum += bench::digest(message.template get<protocol::reset_start_end_flag>().value()); }
    }

    void operator()(const protocol::communication_control_message& message) {
        if constexpr (requires { message.template get<protocol::test_mode_flag>(); }) { checksum += bench::digest(message.template get<protocol::test_mode_flag>().value()); }
        if constexpr (requires { message.template get<protocol::communication_start_end_flag>(); }) { checksum += bench::digest(message.template get<protocol::communication_start_end_flag>().value()); }
    }
};

// The values the Tmp reading reads from one datagram, folded into a checksum. A datagram it cannot read
// is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_udp_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Jpx.TseEquities.MarketByOrder.Flex.v1.1", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
