// Eurex.T7.Eobi.Fbe.v15.0: main.cpp
// Eurex.T7.Eobi.Fbe.v15.0 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/eurex/t7/eobi/fbe/v15.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/eurex/t7/eobi/fbe/v15.0/eurex_t7_eobi_fbe_v15_0.hpp"

// Eurex T7 Eobi Fbe 15.0: the reading of its packets, through its Template Meta Programming header
namespace eurex::t7::eobi::fbe::v15_0 {

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

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const template_id& template_id_) {
    if (static_cast<bool>(tmp::rule(template_id_) == 13400)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_complex_instrument_ = tmp::read<add_complex_instrument>(data + offset, bound - offset, handler); offset += add_complex_instrument::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13401)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_flexible_instrument_ = tmp::read<add_flexible_instrument>(data + offset, bound - offset, handler); offset += add_flexible_instrument::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13402)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_scaled_simple_instrument_ = tmp::read<add_scaled_simple_instrument>(data + offset, bound - offset, handler); offset += add_scaled_simple_instrument::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13500)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& auction_bbo_ = tmp::read<auction_bbo>(data + offset, bound - offset, handler); offset += auction_bbo::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13501)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& auction_clearing_price_ = tmp::read<auction_clearing_price>(data + offset, bound - offset, handler); offset += auction_clearing_price::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13502)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& cross_request_ = tmp::read<cross_request>(data + offset, bound - offset, handler); offset += cross_request::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13202)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& execution_summary_ = tmp::read<execution_summary>(data + offset, bound - offset, handler); offset += execution_summary::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13104)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& full_order_execution_ = tmp::read<full_order_execution>(data + offset, bound - offset, handler); offset += full_order_execution::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13001)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& heartbeat_ = tmp::read<heartbeat>(data + offset, bound - offset, handler); offset += heartbeat::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13301)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& instrument_state_change_ = tmp::read<instrument_state_change>(data + offset, bound - offset, handler); offset += instrument_state_change::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13601)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& instrument_summary_ = tmp::read<instrument_summary>(data + offset, bound - offset, handler); offset += instrument_summary::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13302)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& mass_instrument_state_change_ = tmp::read<mass_instrument_state_change>(data + offset, bound - offset, handler); offset += mass_instrument_state_change::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13100)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_add_ = tmp::read<order_add>(data + offset, bound - offset, handler); offset += order_add::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13102)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_delete_ = tmp::read<order_delete>(data + offset, bound - offset, handler); offset += order_delete::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13103)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_mass_delete_ = tmp::read<order_mass_delete>(data + offset, bound - offset, handler); offset += order_mass_delete::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13101)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_modify_ = tmp::read<order_modify>(data + offset, bound - offset, handler); offset += order_modify::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13106)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_modify_same_prio_ = tmp::read<order_modify_same_prio>(data + offset, bound - offset, handler); offset += order_modify_same_prio::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13105)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& partial_order_execution_ = tmp::read<partial_order_execution>(data + offset, bound - offset, handler); offset += partial_order_execution::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13300)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& product_state_change_ = tmp::read<product_state_change>(data + offset, bound - offset, handler); offset += product_state_change::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13600)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& product_summary_ = tmp::read<product_summary>(data + offset, bound - offset, handler); offset += product_summary::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13503)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& quote_request_ = tmp::read<quote_request>(data + offset, bound - offset, handler); offset += quote_request::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13602)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& snapshot_order_ = tmp::read<snapshot_order>(data + offset, bound - offset, handler); offset += snapshot_order::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13203)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& tes_trade_report_ = tmp::read<tes_trade_report>(data + offset, bound - offset, handler); offset += tes_trade_report::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13504)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& top_of_book_ = tmp::read<top_of_book>(data + offset, bound - offset, handler); offset += top_of_book::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13201)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_report_ = tmp::read<trade_report>(data + offset, bound - offset, handler); offset += trade_report::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13200)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_reversal_ = tmp::read<trade_reversal>(data + offset, bound - offset, handler); offset += trade_reversal::size;
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
    [[maybe_unused]] const auto& message_header_comp_ = tmp::read<message_header_comp>(data + offset, bound - offset, handler); offset += message_header_comp::size;
    bound = static_cast<std::size_t>(tmp::rule(message_header_comp_.template get<body_len>()));
    tmp::require(bound, length);
    offset += parse_payload(data + offset, bound - offset, handler, message_header_comp_.template get<template_id>());
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


} // namespace eurex::t7::eobi::fbe::v15_0

namespace protocol = ::eurex::t7::eobi::fbe::v15_0;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::eobi_header>().template get<protocol::body_len>(); }) { checksum += (static_cast<std::uint16_t>(header.template get<protocol::eobi_header>().template get<protocol::body_len>().value()) != 0x0FFFFU ? bench::digest(header.template get<protocol::eobi_header>().template get<protocol::body_len>().value()) : std::uint64_t{0}); }
        if constexpr (requires { header.template get<protocol::eobi_header>().template get<protocol::template_id>(); }) { checksum += (static_cast<std::uint16_t>(header.template get<protocol::eobi_header>().template get<protocol::template_id>().value()) != 0x0FFFFU ? bench::digest(header.template get<protocol::eobi_header>().template get<protocol::template_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { header.template get<protocol::eobi_header>().template get<protocol::msg_seq_num>(); }) { checksum += (static_cast<std::uint32_t>(header.template get<protocol::eobi_header>().template get<protocol::msg_seq_num>().value()) != 0x0FFFFFFFFU ? bench::digest(header.template get<protocol::eobi_header>().template get<protocol::msg_seq_num>().value()) : std::uint64_t{0}); }
        if constexpr (requires { header.template get<protocol::appl_seq_num>(); }) { checksum += (static_cast<std::uint32_t>(header.template get<protocol::appl_seq_num>().value()) != 0x0FFFFFFFFU ? bench::digest(header.template get<protocol::appl_seq_num>().value()) : std::uint64_t{0}); }
        if constexpr (requires { header.template get<protocol::market_segment_id>(); }) { checksum += (static_cast<std::uint32_t>(header.template get<protocol::market_segment_id>().value()) != 0x080000000U ? bench::digest(header.template get<protocol::market_segment_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { header.template get<protocol::partition_id>(); }) { checksum += (static_cast<std::uint8_t>(header.template get<protocol::partition_id>().value()) != 0x0FFU ? bench::digest(header.template get<protocol::partition_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { header.template get<protocol::completion_indicator>(); }) { checksum += (static_cast<std::uint8_t>(header.template get<protocol::completion_indicator>().value()) != 0x0FFU ? bench::digest(header.template get<protocol::completion_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { header.template get<protocol::appl_seq_reset_indicator>(); }) { checksum += (static_cast<std::uint8_t>(header.template get<protocol::appl_seq_reset_indicator>().value()) != 0x0FFU ? bench::digest(header.template get<protocol::appl_seq_reset_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { header.template get<protocol::dscp>(); }) { checksum += (static_cast<std::uint8_t>(header.template get<protocol::dscp>().value()) != 0x0FFU ? bench::digest(header.template get<protocol::dscp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { header.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(header.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(header.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::message_header_comp& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::body_len>(); }) { checksum += (static_cast<std::uint16_t>(header.template get<protocol::body_len>().value()) != 0x0FFFFU ? bench::digest(header.template get<protocol::body_len>().value()) : std::uint64_t{0}); }
        if constexpr (requires { header.template get<protocol::template_id>(); }) { checksum += (static_cast<std::uint16_t>(header.template get<protocol::template_id>().value()) != 0x0FFFFU ? bench::digest(header.template get<protocol::template_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { header.template get<protocol::msg_seq_num>(); }) { checksum += (static_cast<std::uint32_t>(header.template get<protocol::msg_seq_num>().value()) != 0x0FFFFFFFFU ? bench::digest(header.template get<protocol::msg_seq_num>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::add_complex_instrument& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_sub_type>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::security_sub_type>().value()) != 0x080000000U ? bench::digest(message.template get<protocol::security_sub_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::product_complex>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::product_complex>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::product_complex>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::implied_market_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::implied_market_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::implied_market_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::quantity_scaling_factor>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::quantity_scaling_factor>().value()) != 0x0FFFFU ? bench::digest(message.template get<protocol::quantity_scaling_factor>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::leg_ratio_multiplier>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::leg_ratio_multiplier>().value()) != 0x0FFFFFFFFU ? bench::digest(message.template get<protocol::leg_ratio_multiplier>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::no_legs>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::no_legs>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::no_legs>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_fragment>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::last_fragment>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::last_fragment>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::add_flexible_instrument& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::put_or_call>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::put_or_call>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::put_or_call>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::exercise_style>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::exercise_style>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::exercise_style>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::settl_method>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::settl_method>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::settl_method>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::maturity_date>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::maturity_date>().value()) != 0x0FFFFFFFFU ? bench::digest(message.template get<protocol::maturity_date>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::strike_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::strike_price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::strike_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::opt_attribute>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::opt_attribute>().value()) != 0x0FFFFFFFFU ? bench::digest(message.template get<protocol::opt_attribute>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::contract_date>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::contract_date>().value()) != 0x0FFFFFFFFU ? bench::digest(message.template get<protocol::contract_date>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_reference_data_supplement>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::security_reference_data_supplement>().value()) != 0x0FFFFFFFFU ? bench::digest(message.template get<protocol::security_reference_data_supplement>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::add_scaled_simple_instrument& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::quantity_scaling_factor>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::quantity_scaling_factor>().value()) != 0x0FFFFU ? bench::digest(message.template get<protocol::quantity_scaling_factor>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::related_instrument_grp_comp>().template get<protocol::related_security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::related_instrument_grp_comp>().template get<protocol::related_security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::related_instrument_grp_comp>().template get<protocol::related_security_id>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::auction_bbo& message) {
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::bid_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::bid_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::bid_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::offer_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::offer_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::offer_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::bid_size>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::bid_size>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::bid_size>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::offer_size>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::offer_size>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::offer_size>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::potential_security_trading_event>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::potential_security_trading_event>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::potential_security_trading_event>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::bid_ord_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::bid_ord_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::bid_ord_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::offer_ord_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::offer_ord_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::offer_ord_type>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::auction_clearing_price& message) {
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::imbalance_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::imbalance_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::imbalance_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_trading_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_trading_status>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::potential_security_trading_event>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::potential_security_trading_event>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::potential_security_trading_event>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::cross_request& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::side>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::side>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::cross_request_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::cross_request_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::cross_request_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::input_source>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::input_source>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::input_source>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::execution_summary& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::request_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::request_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::request_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::exec_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::exec_id>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::exec_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::aggressor_side>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::aggressor_side>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::aggressor_side>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::trade_condition>().value()) != 0x0FFFFU ? bench::digest(message.template get<protocol::trade_condition>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_hhi_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::trading_hhi_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::trading_hhi_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::remaining_order_details_comp>().template get<protocol::trd_reg_ts_prev_time_priority>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::remaining_order_details_comp>().template get<protocol::trd_reg_ts_prev_time_priority>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::remaining_order_details_comp>().template get<protocol::trd_reg_ts_prev_time_priority>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::remaining_order_details_comp>().template get<protocol::display_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::remaining_order_details_comp>().template get<protocol::display_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::remaining_order_details_comp>().template get<protocol::display_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::remaining_order_details_comp>().template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::remaining_order_details_comp>().template get<protocol::price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::remaining_order_details_comp>().template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::resting_hidden_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::resting_hidden_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::resting_hidden_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::resting_cxl_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::resting_cxl_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::resting_cxl_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::aggressor_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::aggressor_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::aggressor_time>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::full_order_execution& message) {
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::side>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::side>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::ord_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::ord_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::ord_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::algorithmic_trade_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::algorithmic_trade_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::algorithmic_trade_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::hhi_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::hhi_indicator>().value()) != 0x080U ? bench::digest(message.template get<protocol::hhi_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trd_match_id>().value()) != 0x0FFFFFFFFU ? bench::digest(message.template get<protocol::trd_match_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_priority>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_priority>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::trd_reg_ts_time_priority>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_px>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::heartbeat& message) {
        if constexpr (requires { message.template get<protocol::last_msg_seq_num_processed>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::last_msg_seq_num_processed>().value()) != 0x0FFFFFFFFU ? bench::digest(message.template get<protocol::last_msg_seq_num_processed>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::instrument_state_change& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_status>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_trading_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_trading_status>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::market_condition>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::market_condition>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::market_condition>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::fast_market_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::fast_market_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_trading_event>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_trading_event>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_trading_event>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::sold_out_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::sold_out_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::sold_out_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::high_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::high_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::high_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::low_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::low_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::low_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::tes_security_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::tes_security_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::tes_security_status>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::instrument_summary& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_update_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_update_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::last_update_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_execution_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_execution_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::trd_reg_ts_execution_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::tot_no_orders>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::tot_no_orders>().value()) != 0x0FFFFU ? bench::digest(message.template get<protocol::tot_no_orders>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_status>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_trading_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_trading_status>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::market_condition>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::market_condition>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::market_condition>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::fast_market_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::fast_market_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_trading_event>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_trading_event>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_trading_event>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::sold_out_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::sold_out_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::sold_out_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::high_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::high_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::high_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::low_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::low_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::low_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::product_complex>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::product_complex>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::product_complex>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::no_md_entries>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::no_md_entries>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::no_md_entries>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::tes_security_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::tes_security_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::tes_security_status>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::mass_instrument_state_change& message) {
        if constexpr (requires { message.template get<protocol::instrument_scope_product_complex>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::instrument_scope_product_complex>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::instrument_scope_product_complex>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_mass_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_mass_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_mass_status>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_mass_trading_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_mass_trading_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_mass_trading_status>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::mass_market_condition>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::mass_market_condition>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::mass_market_condition>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::fast_market_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::fast_market_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_mass_trading_event>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_mass_trading_event>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_mass_trading_event>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::mass_sold_out_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::mass_sold_out_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::mass_sold_out_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::tes_security_mass_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::tes_security_mass_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::tes_security_mass_status>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_fragment>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::last_fragment>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::last_fragment>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::no_related_sym>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::no_related_sym>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::no_related_sym>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_add& message) {
        if constexpr (requires { message.template get<protocol::request_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::request_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::request_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::display_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::display_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::display_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::side>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::side>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::side>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::ord_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::ord_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::ord_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>().value()) != 0x080U ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::price>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_delete& message) {
        if constexpr (requires { message.template get<protocol::request_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::request_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::request_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::display_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::display_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::display_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::side>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::side>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::side>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::ord_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::ord_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::ord_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>().value()) != 0x080U ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::price>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_mass_delete& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_modify& message) {
        if constexpr (requires { message.template get<protocol::request_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::request_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::request_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_prev_time_priority>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_prev_time_priority>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::trd_reg_ts_prev_time_priority>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::prev_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::prev_price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::prev_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::prev_display_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::prev_display_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::prev_display_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::display_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::display_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::display_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::side>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::side>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::side>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::ord_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::ord_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::ord_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>().value()) != 0x080U ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::prev_price_hhi_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::prev_price_hhi_indicator>().value()) != 0x080U ? bench::digest(message.template get<protocol::prev_price_hhi_indicator>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_modify_same_prio& message) {
        if constexpr (requires { message.template get<protocol::request_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::request_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::request_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::prev_display_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::prev_display_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::prev_display_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::display_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::display_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::display_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::side>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::side>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::side>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::ord_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::ord_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::ord_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>().value()) != 0x080U ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::price>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::partial_order_execution& message) {
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::side>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::side>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::ord_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::ord_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::ord_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::algorithmic_trade_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::algorithmic_trade_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::algorithmic_trade_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::hhi_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::hhi_indicator>().value()) != 0x080U ? bench::digest(message.template get<protocol::hhi_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trd_match_id>().value()) != 0x0FFFFFFFFU ? bench::digest(message.template get<protocol::trd_match_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_priority>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_priority>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::trd_reg_ts_time_priority>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_px>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::product_state_change& message) {
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::trading_session_id>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::trading_session_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_session_sub_id>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::trading_session_sub_id>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::trading_session_sub_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trad_ses_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::trad_ses_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::trad_ses_status>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::market_condition>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::market_condition>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::market_condition>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::fast_market_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::fast_market_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::tes_trad_ses_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::tes_trad_ses_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::tes_trad_ses_status>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::product_summary& message) {
        if constexpr (requires { message.template get<protocol::last_msg_seq_num_processed>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::last_msg_seq_num_processed>().value()) != 0x0FFFFFFFFU ? bench::digest(message.template get<protocol::last_msg_seq_num_processed>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::trading_session_id>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::trading_session_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_session_sub_id>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::trading_session_sub_id>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::trading_session_sub_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trad_ses_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::trad_ses_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::trad_ses_status>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::market_condition>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::market_condition>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::market_condition>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::fast_market_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::fast_market_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::tes_trad_ses_status>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::tes_trad_ses_status>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::tes_trad_ses_status>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::quote_request& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::side>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::side>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::snapshot_order& message) {
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::trd_reg_ts_time_priority>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::display_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::display_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::display_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::side>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::side>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::side>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::ord_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::ord_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::ord_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>().value()) != 0x080U ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::hhi_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_details_comp>().template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_details_comp>().template get<protocol::price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::order_details_comp>().template get<protocol::price>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::tes_trade_report& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trd_match_id>().value()) != 0x0FFFFFFFFU ? bench::digest(message.template get<protocol::trd_match_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_type>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::trd_type>().value()) != 0x0FFFFU ? bench::digest(message.template get<protocol::trd_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::trade_condition>().value()) != 0x0FFFFU ? bench::digest(message.template get<protocol::trade_condition>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::multi_leg_reporting_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::multi_leg_reporting_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::multi_leg_reporting_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::multi_leg_price_model>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::multi_leg_price_model>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::multi_leg_price_model>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::non_disclosed_trade_volume>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::non_disclosed_trade_volume>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::non_disclosed_trade_volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trans_bkd_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trans_bkd_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::trans_bkd_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::number_of_buy_sides>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::number_of_buy_sides>().value()) != 0x0FFFFU ? bench::digest(message.template get<protocol::number_of_buy_sides>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::number_of_sell_sides>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::number_of_sell_sides>().value()) != 0x0FFFFU ? bench::digest(message.template get<protocol::number_of_sell_sides>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::top_of_book& message) {
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::bid_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::bid_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::bid_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::offer_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::offer_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::offer_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::bid_size>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::bid_size>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::bid_size>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::offer_size>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::offer_size>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::offer_size>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::number_of_buy_orders>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::number_of_buy_orders>().value()) != 0x0FFFFU ? bench::digest(message.template get<protocol::number_of_buy_orders>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::number_of_sell_orders>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::number_of_sell_orders>().value()) != 0x0FFFFU ? bench::digest(message.template get<protocol::number_of_sell_orders>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::trade_report& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trd_match_id>().value()) != 0x0FFFFFFFFU ? bench::digest(message.template get<protocol::trd_match_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::match_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::match_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::match_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::match_sub_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::match_sub_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::match_sub_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::algorithmic_trade_indicator>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::algorithmic_trade_indicator>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::algorithmic_trade_indicator>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::trade_condition>().value()) != 0x0FFFFU ? bench::digest(message.template get<protocol::trade_condition>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::trade_reversal& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::security_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::last_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_execution_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_execution_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::trd_reg_ts_execution_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trd_match_id>().value()) != 0x0FFFFFFFFU ? bench::digest(message.template get<protocol::trd_match_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::trade_condition>().value()) != 0x0FFFFU ? bench::digest(message.template get<protocol::trade_condition>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_origin_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::md_origin_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::md_origin_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::no_md_entries>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::no_md_entries>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::no_md_entries>().value()) : std::uint64_t{0}); }
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
    return bench::run("Eurex.T7.Eobi.Fbe.v15.0", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
