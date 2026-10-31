// Nyse.NyseEquities.ImbalancesFeed.Xdp.v2.1.f benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/nyseequities/imbalancesfeed/xdp/v2.1.f.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/nyse/nyseequities/imbalancesfeed/xdp/v2.1.f/nyse_nyseequities_imbalancesfeed_xdp_v2_1_f.hpp"

// Nyse NyseEquities ImbalancesFeed Xdp 2.1.f: the reading of its packets, through its Template Meta Programming header
namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

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

// Refresh Header Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_refresh_header_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& refresh_header_message_section_1_ = tmp::read<refresh_header_message_section_1>(data + offset, bound - offset, handler); offset += refresh_header_message_section_1::size;
    if (static_cast<bool>(tmp::rule(refresh_header_message_section_1_.template get<current_refresh_pkt>()) == 1)) {
        offset += tmp::take<full_refresh_header>(data + offset, bound - offset, handler);
    }
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& sequence_number_reset_message_ = tmp::read<sequence_number_reset_message>(data + offset, bound - offset, handler); offset += sequence_number_reset_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 3)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& symbol_index_mapping_message_ = tmp::read<symbol_index_mapping_message>(data + offset, bound - offset, handler); offset += symbol_index_mapping_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 10)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& retransmission_request_message_ = tmp::read<retransmission_request_message>(data + offset, bound - offset, handler); offset += retransmission_request_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 11)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& request_response_message_ = tmp::read<request_response_message>(data + offset, bound - offset, handler); offset += request_response_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 12)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& heartbeat_response_message_ = tmp::read<heartbeat_response_message>(data + offset, bound - offset, handler); offset += heartbeat_response_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 13)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& symbol_index_mapping_request_message_ = tmp::read<symbol_index_mapping_request_message>(data + offset, bound - offset, handler); offset += symbol_index_mapping_request_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 15)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& refresh_request_message_ = tmp::read<refresh_request_message>(data + offset, bound - offset, handler); offset += refresh_request_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 31)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& message_unavailable_message_ = tmp::read<message_unavailable_message>(data + offset, bound - offset, handler); offset += message_unavailable_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 32)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& symbol_clear_message_ = tmp::read<symbol_clear_message>(data + offset, bound - offset, handler); offset += symbol_clear_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 34)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& security_status_message_ = tmp::read<security_status_message>(data + offset, bound - offset, handler); offset += security_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 35)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_refresh_header_message(data + offset, bound - offset, handler);
        tmp::call(handler, refresh_header_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 105)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& imbalance_message_ = tmp::read<imbalance_message>(data + offset, bound - offset, handler); offset += imbalance_message::size;
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
    bound = static_cast<std::size_t>(tmp::rule(message_header_.template get<message_size>()));
    tmp::require(bound, length);
    offset += parse_payload(data + offset, bound - offset, handler, message_header_.template get<message_type>());
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


} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f

namespace protocol = ::nyse::nyseequities::imbalancesfeed::xdp::v2_1_f;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::packet_size>(); }) { checksum += bench::digest(header.template get<protocol::packet_size>().value()); }
        if constexpr (requires { header.template get<protocol::delivery_flag>(); }) { checksum += bench::digest(header.template get<protocol::delivery_flag>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { checksum += bench::digest(header.template get<protocol::message_count>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { checksum += bench::digest(header.template get<protocol::sequence_number>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::message_size>(); }) { checksum += bench::digest(header.template get<protocol::message_size>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { checksum += bench::digest(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::sequence_number_reset_message& message) {
        if constexpr (requires { message.template get<protocol::source_time>(); }) { checksum += bench::digest(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { checksum += bench::digest(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { checksum += bench::digest(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { checksum += bench::digest(message.template get<protocol::channel_id>().value()); }
    }

    void operator()(const protocol::symbol_index_mapping_message& message) {
        if constexpr (requires { message.template get<protocol::symbol_index>(); }) { checksum += bench::digest(message.template get<protocol::symbol_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::market_id>(); }) { checksum += bench::digest(message.template get<protocol::market_id>().value()); }
        if constexpr (requires { message.template get<protocol::system_id>(); }) { checksum += bench::digest(message.template get<protocol::system_id>().value()); }
        if constexpr (requires { message.template get<protocol::exchange_code>(); }) { checksum += bench::digest(message.template get<protocol::exchange_code>().value()); }
        if constexpr (requires { message.template get<protocol::price_scale_code>(); }) { checksum += bench::digest(message.template get<protocol::price_scale_code>().value()); }
        if constexpr (requires { message.template get<protocol::security_type>(); }) { checksum += bench::digest(message.template get<protocol::security_type>().value()); }
        if constexpr (requires { message.template get<protocol::lot_size>(); }) { checksum += bench::digest(message.template get<protocol::lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::prev_close_price>(); }) { checksum += bench::digest(message.template get<protocol::prev_close_price>().value()); }
        if constexpr (requires { message.template get<protocol::prev_close_volume>(); }) { checksum += bench::digest(message.template get<protocol::prev_close_volume>().value()); }
        if constexpr (requires { message.template get<protocol::price_resolution>(); }) { checksum += bench::digest(message.template get<protocol::price_resolution>().value()); }
        if constexpr (requires { message.template get<protocol::round_lot>(); }) { checksum += bench::digest(message.template get<protocol::round_lot>().value()); }
        if constexpr (requires { message.template get<protocol::mpv>(); }) { checksum += bench::digest(message.template get<protocol::mpv>().value()); }
        if constexpr (requires { message.template get<protocol::unit_of_trade>(); }) { checksum += bench::digest(message.template get<protocol::unit_of_trade>().value()); }
    }

    void operator()(const protocol::retransmission_request_message& message) {
        if constexpr (requires { message.template get<protocol::begin_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::begin_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::end_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::end_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::source_id>(); }) { checksum += bench::digest(message.template get<protocol::source_id>().value()); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { checksum += bench::digest(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { checksum += bench::digest(message.template get<protocol::channel_id>().value()); }
    }

    void operator()(const protocol::request_response_message& message) {
        if constexpr (requires { message.template get<protocol::request_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::request_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::begin_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::begin_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::end_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::end_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::source_id>(); }) { checksum += bench::digest(message.template get<protocol::source_id>().value()); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { checksum += bench::digest(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { checksum += bench::digest(message.template get<protocol::channel_id>().value()); }
        if constexpr (requires { message.template get<protocol::status>(); }) { checksum += bench::digest(message.template get<protocol::status>().value()); }
    }

    void operator()(const protocol::heartbeat_response_message& message) {
        if constexpr (requires { message.template get<protocol::source_id>(); }) { checksum += bench::digest(message.template get<protocol::source_id>().value()); }
    }

    void operator()(const protocol::symbol_index_mapping_request_message& message) {
        if constexpr (requires { message.template get<protocol::symbol_index>(); }) { checksum += bench::digest(message.template get<protocol::symbol_index>().value()); }
        if constexpr (requires { message.template get<protocol::source_id>(); }) { checksum += bench::digest(message.template get<protocol::source_id>().value()); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { checksum += bench::digest(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { checksum += bench::digest(message.template get<protocol::channel_id>().value()); }
        if constexpr (requires { message.template get<protocol::retransmit_method>(); }) { checksum += bench::digest(message.template get<protocol::retransmit_method>().value()); }
    }

    void operator()(const protocol::refresh_request_message& message) {
        if constexpr (requires { message.template get<protocol::symbol_index>(); }) { checksum += bench::digest(message.template get<protocol::symbol_index>().value()); }
        if constexpr (requires { message.template get<protocol::source_id>(); }) { checksum += bench::digest(message.template get<protocol::source_id>().value()); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { checksum += bench::digest(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { checksum += bench::digest(message.template get<protocol::channel_id>().value()); }
    }

    void operator()(const protocol::message_unavailable_message& message) {
        if constexpr (requires { message.template get<protocol::begin_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::begin_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::end_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::end_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { checksum += bench::digest(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { checksum += bench::digest(message.template get<protocol::channel_id>().value()); }
    }

    void operator()(const protocol::symbol_clear_message& message) {
        if constexpr (requires { message.template get<protocol::source_time>(); }) { checksum += bench::digest(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { checksum += bench::digest(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_index>(); }) { checksum += bench::digest(message.template get<protocol::symbol_index>().value()); }
        if constexpr (requires { message.template get<protocol::next_source_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::next_source_seq_num>().value()); }
    }

    void operator()(const protocol::security_status_message& message) {
        if constexpr (requires { message.template get<protocol::source_time>(); }) { checksum += bench::digest(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { checksum += bench::digest(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_index>(); }) { checksum += bench::digest(message.template get<protocol::symbol_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { checksum += bench::digest(message.template get<protocol::security_status>().value()); }
        if constexpr (requires { message.template get<protocol::halt_condition>(); }) { checksum += bench::digest(message.template get<protocol::halt_condition>().value()); }
        if constexpr (requires { message.template get<protocol::price_1>(); }) { checksum += bench::digest(message.template get<protocol::price_1>().value()); }
        if constexpr (requires { message.template get<protocol::price_2>(); }) { checksum += bench::digest(message.template get<protocol::price_2>().value()); }
        if constexpr (requires { message.template get<protocol::ssr_triggering_exchange_id>(); }) { checksum += bench::digest(message.template get<protocol::ssr_triggering_exchange_id>().value()); }
        if constexpr (requires { message.template get<protocol::ssr_triggering_volume>(); }) { checksum += bench::digest(message.template get<protocol::ssr_triggering_volume>().value()); }
        if constexpr (requires { message.template get<protocol::time>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::time>().value()) != 0x0U ? bench::digest(message.template get<protocol::time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::ssr_state>(); }) { checksum += bench::digest(message.template get<protocol::ssr_state>().value()); }
        if constexpr (requires { message.template get<protocol::market_state>(); }) { checksum += bench::digest(message.template get<protocol::market_state>().value()); }
        if constexpr (requires { message.template get<protocol::session_state>(); }) { checksum += bench::digest(message.template get<protocol::session_state>().value()); }
    }

    void operator()(const protocol::refresh_header_message&) {
    }

    void operator()(const protocol::imbalance_message& message) {
        if constexpr (requires { message.template get<protocol::source_time>(); }) { checksum += bench::digest(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { checksum += bench::digest(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_index>(); }) { checksum += bench::digest(message.template get<protocol::symbol_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::reference_price>(); }) { checksum += bench::digest(message.template get<protocol::reference_price>().value()); }
        if constexpr (requires { message.template get<protocol::paired_qty>(); }) { checksum += bench::digest(message.template get<protocol::paired_qty>().value()); }
        if constexpr (requires { message.template get<protocol::total_imbalance_qty>(); }) { checksum += bench::digest(message.template get<protocol::total_imbalance_qty>().value()); }
        if constexpr (requires { message.template get<protocol::market_imbalance_qty>(); }) { checksum += bench::digest(message.template get<protocol::market_imbalance_qty>().value()); }
        if constexpr (requires { message.template get<protocol::auction_time>(); }) { checksum += bench::digest(message.template get<protocol::auction_time>().value()); }
        if constexpr (requires { message.template get<protocol::auction_type>(); }) { checksum += bench::digest(message.template get<protocol::auction_type>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_side>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_side>().value()); }
        if constexpr (requires { message.template get<protocol::continuous_book_clearing_price>(); }) { checksum += bench::digest(message.template get<protocol::continuous_book_clearing_price>().value()); }
        if constexpr (requires { message.template get<protocol::closing_only_clearing_price>(); }) { checksum += bench::digest(message.template get<protocol::closing_only_clearing_price>().value()); }
        if constexpr (requires { message.template get<protocol::ssr_filing_price>(); }) { checksum += bench::digest(message.template get<protocol::ssr_filing_price>().value()); }
        if constexpr (requires { message.template get<protocol::indicative_match_price>(); }) { checksum += bench::digest(message.template get<protocol::indicative_match_price>().value()); }
        if constexpr (requires { message.template get<protocol::upper_collar>(); }) { checksum += bench::digest(message.template get<protocol::upper_collar>().value()); }
        if constexpr (requires { message.template get<protocol::lower_collar>(); }) { checksum += bench::digest(message.template get<protocol::lower_collar>().value()); }
        if constexpr (requires { message.template get<protocol::auction_status>(); }) { checksum += bench::digest(message.template get<protocol::auction_status>().value()); }
        if constexpr (requires { message.template get<protocol::freeze_status>(); }) { checksum += bench::digest(message.template get<protocol::freeze_status>().value()); }
        if constexpr (requires { message.template get<protocol::num_extensions>(); }) { checksum += bench::digest(message.template get<protocol::num_extensions>().value()); }
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
    return bench::run("Nyse.NyseEquities.ImbalancesFeed.Xdp.v2.1.f", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
