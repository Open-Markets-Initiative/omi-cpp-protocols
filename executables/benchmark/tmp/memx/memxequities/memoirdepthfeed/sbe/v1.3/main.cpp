// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3: main.cpp
// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/memx/memxequities/memoirdepthfeed/sbe/v1.3.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/memx/memxequities/memoirdepthfeed/sbe/v1.3/memx_memxequities_memoirdepthfeed_sbe_v1_3.hpp"

// Memx MemxEquities MemoirDepthFeed Sbe 1.3: the reading of its packets, through its Template Meta Programming header
namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

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
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const template_id& template_id_, const block_length& block_length_) {
    if (static_cast<bool>(tmp::rule(template_id_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<instrument_directory_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 2)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<reg_sho_restriction_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 3)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<security_trading_status_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 5)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<trading_session_status_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 10)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<order_added_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 11)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<order_deleted_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 12)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<order_reduced_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<order_executed_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 14)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<trade_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 15)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<broken_trade_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 16)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<corrected_trade_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 18)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<clear_book_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 100)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<snapshot_complete_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Sbe Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_sbe_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& sbe_header_ = tmp::read<sbe_header>(data + offset, bound - offset, handler); offset += sbe_header::size;
    offset += parse_payload(data + offset, bound - offset, handler, sbe_header_.template get<template_id>(), sbe_header_.template get<block_length>());
    return offset;
}

// Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& message_section_1_ = tmp::read<message_section_1>(data + offset, bound - offset, handler); offset += message_section_1::size;
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_section_1_.template get<message_length>()))) + 2);
    tmp::require(bound, length);
    offset += parse_sbe_message(data + offset, bound - offset, handler);
    return bound;
}

// Sequenced Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_sequenced_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& sequenced_message_section_1_ = tmp::read<sequenced_message_section_1>(data + offset, bound - offset, handler); offset += sequenced_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(sequenced_message_section_1_.template get<message_count>()));
        while (count-- > 0) {
            offset += parse_message(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Sequenced Messages: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_sequenced_messages([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 0)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, heartbeat{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, session_shutdown{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 2)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_sequenced_message(data + offset, bound - offset, handler);
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& common_header_ = tmp::read<common_header>(data + offset, bound - offset, handler); offset += common_header::size;
    offset += parse_sequenced_messages(data + offset, bound - offset, handler, common_header_.template get<message_type>());
    return offset;
}


} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3

namespace protocol = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::sequenced_message&) {
    }

    void operator()(const protocol::sbe_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::block_length>(); }) { checksum += bench::digest(header.template get<protocol::block_length>().value()); }
        if constexpr (requires { header.template get<protocol::template_id>(); }) { checksum += bench::digest(header.template get<protocol::template_id>().value()); }
        if constexpr (requires { header.template get<protocol::schema_id>(); }) { checksum += bench::digest(header.template get<protocol::schema_id>().value()); }
        if constexpr (requires { header.template get<protocol::version>(); }) { checksum += bench::digest(header.template get<protocol::version>().value()); }
    }

    void operator()(const protocol::instrument_directory_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_sfx>(); }) { checksum += bench::digest(message.template get<protocol::symbol_sfx>().value()); }
        if constexpr (requires { message.template get<protocol::round_lot>(); }) { checksum += bench::digest(message.template get<protocol::round_lot>().value()); }
        if constexpr (requires { message.template get<protocol::is_test_symbol>(); }) { checksum += bench::digest(message.template get<protocol::is_test_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::mpv>(); }) { checksum += bench::digest(message.template get<protocol::mpv>().value()); }
    }

    void operator()(const protocol::reg_sho_restriction_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::short_sale_restriction>(); }) { checksum += bench::digest(message.template get<protocol::short_sale_restriction>().value()); }
    }

    void operator()(const protocol::security_trading_status_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { checksum += bench::digest(message.template get<protocol::security_trading_status>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_status_reason>(); }) { checksum += bench::digest(message.template get<protocol::security_trading_status_reason>().value()); }
    }

    void operator()(const protocol::trading_session_status_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session>(); }) { checksum += bench::digest(message.template get<protocol::trading_session>().value()); }
    }

    void operator()(const protocol::order_added_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::order_deleted_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
    }

    void operator()(const protocol::order_reduced_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
    }

    void operator()(const protocol::order_executed_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::trade_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { checksum += bench::digest(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::broken_trade_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::original_quantity>(); }) { checksum += bench::digest(message.template get<protocol::original_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::original_price>(); }) { checksum += bench::digest(message.template get<protocol::original_price>().value()); }
    }

    void operator()(const protocol::corrected_trade_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::original_quantity>(); }) { checksum += bench::digest(message.template get<protocol::original_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::original_price>(); }) { checksum += bench::digest(message.template get<protocol::original_price>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_quantity>(); }) { checksum += bench::digest(message.template get<protocol::corrected_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_price>(); }) { checksum += bench::digest(message.template get<protocol::corrected_price>().value()); }
    }

    void operator()(const protocol::clear_book_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
    }

    void operator()(const protocol::snapshot_complete_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::as_of_sequence_number>(); }) { checksum += bench::digest(message.template get<protocol::as_of_sequence_number>().value()); }
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
    return bench::run("Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
