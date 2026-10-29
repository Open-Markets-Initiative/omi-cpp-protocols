// Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/amexoptions/deepfeed/xdp/v1.3.a.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/nyse/amexoptions/deepfeed/xdp/v1.3.a/nyse_amexoptions_deepfeed_xdp_v1_3_a.hpp"

// Nyse AmexOptions DeepFeed Xdp 1.3.a: the reading of its packets, through its Template Meta Programming header
namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

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
    if (static_cast<bool>(tmp::rule(message_type_) == 403)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& outright_market_depth_buy_message_ = tmp::read<outright_market_depth_buy_message>(data + offset, bound - offset, handler); offset += outright_market_depth_buy_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 405)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& outright_market_depth_sell_message_ = tmp::read<outright_market_depth_sell_message>(data + offset, bound - offset, handler); offset += outright_market_depth_sell_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 419)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& underlying_status_message_ = tmp::read<underlying_status_message>(data + offset, bound - offset, handler); offset += underlying_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 421)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& outright_series_status_message_ = tmp::read<outright_series_status_message>(data + offset, bound - offset, handler); offset += outright_series_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 503)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& refresh_outright_market_depth_buy_message_ = tmp::read<refresh_outright_market_depth_buy_message>(data + offset, bound - offset, handler); offset += refresh_outright_market_depth_buy_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 505)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& refresh_outright_market_depth_sell_message_ = tmp::read<refresh_outright_market_depth_sell_message>(data + offset, bound - offset, handler); offset += refresh_outright_market_depth_sell_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 435)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& underlying_index_mapping_message_ = tmp::read<underlying_index_mapping_message>(data + offset, bound - offset, handler); offset += underlying_index_mapping_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 437)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& series_index_mapping_message_ = tmp::read<series_index_mapping_message>(data + offset, bound - offset, handler); offset += series_index_mapping_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 455)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& stream_id_message_ = tmp::read<stream_id_message>(data + offset, bound - offset, handler); offset += stream_id_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& sequence_number_reset_message_ = tmp::read<sequence_number_reset_message>(data + offset, bound - offset, handler); offset += sequence_number_reset_message::size;
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


} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a

namespace protocol = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

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

    void operator()(const protocol::outright_market_depth_buy_message& message) {
        if constexpr (requires { message.template get<protocol::source_time>(); }) { checksum += bench::digest(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_ns>(); }) { checksum += bench::digest(message.template get<protocol::source_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { checksum += bench::digest(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_price>(); }) { checksum += bench::digest(message.template get<protocol::first_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_price>(); }) { checksum += bench::digest(message.template get<protocol::second_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_price>(); }) { checksum += bench::digest(message.template get<protocol::third_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_volume>(); }) { checksum += bench::digest(message.template get<protocol::first_level_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_volume>(); }) { checksum += bench::digest(message.template get<protocol::second_level_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_volume>(); }) { checksum += bench::digest(message.template get<protocol::third_level_volume>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { checksum += bench::digest(message.template get<protocol::quote_condition>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_customer_volume>(); }) { checksum += bench::digest(message.template get<protocol::first_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_customer_volume>(); }) { checksum += bench::digest(message.template get<protocol::second_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_customer_volume>(); }) { checksum += bench::digest(message.template get<protocol::third_level_customer_volume>().value()); }
    }

    void operator()(const protocol::outright_market_depth_sell_message& message) {
        if constexpr (requires { message.template get<protocol::source_time>(); }) { checksum += bench::digest(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_ns>(); }) { checksum += bench::digest(message.template get<protocol::source_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { checksum += bench::digest(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_price>(); }) { checksum += bench::digest(message.template get<protocol::first_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_price>(); }) { checksum += bench::digest(message.template get<protocol::second_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_price>(); }) { checksum += bench::digest(message.template get<protocol::third_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::first_volume>(); }) { checksum += bench::digest(message.template get<protocol::first_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_volume>(); }) { checksum += bench::digest(message.template get<protocol::second_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_volume>(); }) { checksum += bench::digest(message.template get<protocol::third_volume>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { checksum += bench::digest(message.template get<protocol::quote_condition>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_customer_volume>(); }) { checksum += bench::digest(message.template get<protocol::first_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_customer_volume>(); }) { checksum += bench::digest(message.template get<protocol::second_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_customer_volume>(); }) { checksum += bench::digest(message.template get<protocol::third_level_customer_volume>().value()); }
    }

    void operator()(const protocol::underlying_status_message& message) {
        if constexpr (requires { message.template get<protocol::source_time>(); }) { checksum += bench::digest(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { checksum += bench::digest(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_index>(); }) { checksum += bench::digest(message.template get<protocol::underlying_index>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::underlying_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { checksum += bench::digest(message.template get<protocol::security_status>().value()); }
        if constexpr (requires { message.template get<protocol::halt_condition>(); }) { checksum += bench::digest(message.template get<protocol::halt_condition>().value()); }
    }

    void operator()(const protocol::outright_series_status_message& message) {
        if constexpr (requires { message.template get<protocol::source_time>(); }) { checksum += bench::digest(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { checksum += bench::digest(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { checksum += bench::digest(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { checksum += bench::digest(message.template get<protocol::security_status>().value()); }
        if constexpr (requires { message.template get<protocol::halt_condition>(); }) { checksum += bench::digest(message.template get<protocol::halt_condition>().value()); }
    }

    void operator()(const protocol::refresh_outright_market_depth_buy_message& message) {
        if constexpr (requires { message.template get<protocol::source_time>(); }) { checksum += bench::digest(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_ns>(); }) { checksum += bench::digest(message.template get<protocol::source_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { checksum += bench::digest(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_price>(); }) { checksum += bench::digest(message.template get<protocol::first_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_price>(); }) { checksum += bench::digest(message.template get<protocol::second_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_price>(); }) { checksum += bench::digest(message.template get<protocol::third_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::first_volume>(); }) { checksum += bench::digest(message.template get<protocol::first_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_volume>(); }) { checksum += bench::digest(message.template get<protocol::second_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_volume>(); }) { checksum += bench::digest(message.template get<protocol::third_volume>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { checksum += bench::digest(message.template get<protocol::quote_condition>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_customer_volume>(); }) { checksum += bench::digest(message.template get<protocol::first_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_customer_volume>(); }) { checksum += bench::digest(message.template get<protocol::second_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_customer_volume>(); }) { checksum += bench::digest(message.template get<protocol::third_level_customer_volume>().value()); }
    }

    void operator()(const protocol::refresh_outright_market_depth_sell_message& message) {
        if constexpr (requires { message.template get<protocol::source_time>(); }) { checksum += bench::digest(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { checksum += bench::digest(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { checksum += bench::digest(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_price>(); }) { checksum += bench::digest(message.template get<protocol::first_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_price>(); }) { checksum += bench::digest(message.template get<protocol::second_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_price>(); }) { checksum += bench::digest(message.template get<protocol::third_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::first_volume>(); }) { checksum += bench::digest(message.template get<protocol::first_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_volume>(); }) { checksum += bench::digest(message.template get<protocol::second_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_volume>(); }) { checksum += bench::digest(message.template get<protocol::third_volume>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { checksum += bench::digest(message.template get<protocol::quote_condition>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_customer_volume>(); }) { checksum += bench::digest(message.template get<protocol::first_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_customer_volume>(); }) { checksum += bench::digest(message.template get<protocol::second_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_customer_volume>(); }) { checksum += bench::digest(message.template get<protocol::third_level_customer_volume>().value()); }
    }

    void operator()(const protocol::underlying_index_mapping_message& message) {
        if constexpr (requires { message.template get<protocol::underlying_index>(); }) { checksum += bench::digest(message.template get<protocol::underlying_index>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_symbol>(); }) { checksum += bench::digest(message.template get<protocol::underlying_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { checksum += bench::digest(message.template get<protocol::channel_id>().value()); }
        if constexpr (requires { message.template get<protocol::market_id>(); }) { checksum += bench::digest(message.template get<protocol::market_id>().value()); }
        if constexpr (requires { message.template get<protocol::system_id>(); }) { checksum += bench::digest(message.template get<protocol::system_id>().value()); }
        if constexpr (requires { message.template get<protocol::exchange_code>(); }) { checksum += bench::digest(message.template get<protocol::exchange_code>().value()); }
        if constexpr (requires { message.template get<protocol::price_scale_code>(); }) { checksum += bench::digest(message.template get<protocol::price_scale_code>().value()); }
        if constexpr (requires { message.template get<protocol::security_type>(); }) { checksum += bench::digest(message.template get<protocol::security_type>().value()); }
        if constexpr (requires { message.template get<protocol::price_resolution>(); }) { checksum += bench::digest(message.template get<protocol::price_resolution>().value()); }
    }

    void operator()(const protocol::series_index_mapping_message& message) {
        if constexpr (requires { message.template get<protocol::series_index>(); }) { checksum += bench::digest(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { checksum += bench::digest(message.template get<protocol::channel_id>().value()); }
        if constexpr (requires { message.template get<protocol::market_id>(); }) { checksum += bench::digest(message.template get<protocol::market_id>().value()); }
        if constexpr (requires { message.template get<protocol::system_id>(); }) { checksum += bench::digest(message.template get<protocol::system_id>().value()); }
        if constexpr (requires { message.template get<protocol::stream_id>(); }) { checksum += bench::digest(message.template get<protocol::stream_id>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_index>(); }) { checksum += bench::digest(message.template get<protocol::underlying_index>().value()); }
        if constexpr (requires { message.template get<protocol::contract_multiplier>(); }) { checksum += bench::digest(message.template get<protocol::contract_multiplier>().value()); }
        if constexpr (requires { message.template get<protocol::maturity_date>(); }) { checksum += bench::digest(message.template get<protocol::maturity_date>().value()); }
        if constexpr (requires { message.template get<protocol::put_or_call>(); }) { checksum += bench::digest(message.template get<protocol::put_or_call>().value()); }
        if constexpr (requires { message.template get<protocol::strike_price>(); }) { checksum += bench::digest(message.template get<protocol::strike_price>().value()); }
        if constexpr (requires { message.template get<protocol::price_scale_code>(); }) { checksum += bench::digest(message.template get<protocol::price_scale_code>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_symbol>(); }) { checksum += bench::digest(message.template get<protocol::underlying_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::option_symbol_root>(); }) { checksum += bench::digest(message.template get<protocol::option_symbol_root>().value()); }
        if constexpr (requires { message.template get<protocol::group_id>(); }) { checksum += bench::digest(message.template get<protocol::group_id>().value()); }
    }

    void operator()(const protocol::stream_id_message& message) {
        if constexpr (requires { message.template get<protocol::stream_id>(); }) { checksum += bench::digest(message.template get<protocol::stream_id>().value()); }
    }

    void operator()(const protocol::sequence_number_reset_message& message) {
        if constexpr (requires { message.template get<protocol::source_time>(); }) { checksum += bench::digest(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { checksum += bench::digest(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { checksum += bench::digest(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { checksum += bench::digest(message.template get<protocol::channel_id>().value()); }
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
    return bench::run("Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
