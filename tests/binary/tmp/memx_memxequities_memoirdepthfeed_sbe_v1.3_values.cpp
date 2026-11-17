// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 canonical values, through the Tmp header: every value the Tmp reading hands
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
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::sequenced_message&) {
    }

    void operator()(const protocol::sbe_header& header) {
        entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::block_length>(); }) { values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(header.template get<protocol::block_length>().value()); }
        if constexpr (requires { header.template get<protocol::template_id>(); }) { values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(header.template get<protocol::template_id>().value()); }
        if constexpr (requires { header.template get<protocol::schema_id>(); }) { values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(header.template get<protocol::schema_id>().value()); }
        if constexpr (requires { header.template get<protocol::version>(); }) { values[entry + ".sbemessage.sbeheader.version"] = canonical::number(header.template get<protocol::version>().value()); }
    }

    void operator()(const protocol::instrument_directory_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.instrumentdirectorymessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.instrumentdirectorymessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".sbemessage.payload.instrumentdirectorymessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".sbemessage.payload.instrumentdirectorymessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::symbol_sfx>(); }) { values[entry + ".sbemessage.payload.instrumentdirectorymessage.symbolsfx"] = canonical::text(std::string(message.template get<protocol::symbol_sfx>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::round_lot>(); }) { values[entry + ".sbemessage.payload.instrumentdirectorymessage.roundlot"] = canonical::number(message.template get<protocol::round_lot>().value()); }
        if constexpr (requires { message.template get<protocol::is_test_symbol>(); }) { values[entry + ".sbemessage.payload.instrumentdirectorymessage.istestsymbol"] = canonical::number(message.template get<protocol::is_test_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::mpv>(); }) { values[entry + ".sbemessage.payload.instrumentdirectorymessage.mpv"] = canonical::scaled(message.template get<protocol::mpv>().value(), -6); }
    }

    void operator()(const protocol::reg_sho_restriction_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.regshorestrictionmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.regshorestrictionmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".sbemessage.payload.regshorestrictionmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::short_sale_restriction>(); }) { values[entry + ".sbemessage.payload.regshorestrictionmessage.shortsalerestriction"] = canonical::number(message.template get<protocol::short_sale_restriction>().value()); }
    }

    void operator()(const protocol::security_trading_status_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.securitytradingstatusmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.securitytradingstatusmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".sbemessage.payload.securitytradingstatusmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { values[entry + ".sbemessage.payload.securitytradingstatusmessage.securitytradingstatus"] = canonical::text(canonical::character(message.template get<protocol::security_trading_status>().value())); }
        if constexpr (requires { message.template get<protocol::security_trading_status_reason>(); }) { values[entry + ".sbemessage.payload.securitytradingstatusmessage.securitytradingstatusreason"] = canonical::text(canonical::character(message.template get<protocol::security_trading_status_reason>().value())); }
    }

    void operator()(const protocol::trading_session_status_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.tradingsessionstatusmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.tradingsessionstatusmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session>(); }) { values[entry + ".sbemessage.payload.tradingsessionstatusmessage.tradingsession"] = canonical::text(canonical::character(message.template get<protocol::trading_session>().value())); }
    }

    void operator()(const protocol::order_added_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderaddedmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.orderaddedmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".sbemessage.payload.orderaddedmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".sbemessage.payload.orderaddedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".sbemessage.payload.orderaddedmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value())); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".sbemessage.payload.orderaddedmessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".sbemessage.payload.orderaddedmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -6); }
    }

    void operator()(const protocol::order_deleted_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderdeletedmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.orderdeletedmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".sbemessage.payload.orderdeletedmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".sbemessage.payload.orderdeletedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
    }

    void operator()(const protocol::order_reduced_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderreducedmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.orderreducedmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".sbemessage.payload.orderreducedmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".sbemessage.payload.orderreducedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".sbemessage.payload.orderreducedmessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
    }

    void operator()(const protocol::order_executed_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderexecutedmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.orderexecutedmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".sbemessage.payload.orderexecutedmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".sbemessage.payload.orderexecutedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".sbemessage.payload.orderexecutedmessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".sbemessage.payload.orderexecutedmessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".sbemessage.payload.orderexecutedmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -6); }
    }

    void operator()(const protocol::trade_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.trademessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.trademessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".sbemessage.payload.trademessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".sbemessage.payload.trademessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity>(); }) { values[entry + ".sbemessage.payload.trademessage.quantity"] = canonical::number(message.template get<protocol::quantity>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".sbemessage.payload.trademessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -6); }
    }

    void operator()(const protocol::broken_trade_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.brokentrademessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.brokentrademessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".sbemessage.payload.brokentrademessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".sbemessage.payload.brokentrademessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::original_quantity>(); }) { values[entry + ".sbemessage.payload.brokentrademessage.originalquantity"] = canonical::number(message.template get<protocol::original_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::original_price>(); }) { values[entry + ".sbemessage.payload.brokentrademessage.originalprice"] = canonical::scaled(message.template get<protocol::original_price>().value(), -6); }
    }

    void operator()(const protocol::corrected_trade_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.correctedtrademessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.correctedtrademessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".sbemessage.payload.correctedtrademessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".sbemessage.payload.correctedtrademessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::original_quantity>(); }) { values[entry + ".sbemessage.payload.correctedtrademessage.originalquantity"] = canonical::number(message.template get<protocol::original_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::original_price>(); }) { values[entry + ".sbemessage.payload.correctedtrademessage.originalprice"] = canonical::scaled(message.template get<protocol::original_price>().value(), -6); }
        if constexpr (requires { message.template get<protocol::corrected_quantity>(); }) { values[entry + ".sbemessage.payload.correctedtrademessage.correctedquantity"] = canonical::number(message.template get<protocol::corrected_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::corrected_price>(); }) { values[entry + ".sbemessage.payload.correctedtrademessage.correctedprice"] = canonical::scaled(message.template get<protocol::corrected_price>().value(), -6); }
    }

    void operator()(const protocol::clear_book_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.clearbookmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.clearbookmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".sbemessage.payload.clearbookmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
    }

    void operator()(const protocol::snapshot_complete_message& message) {
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.snapshotcompletemessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".sbemessage.payload.snapshotcompletemessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::as_of_sequence_number>(); }) { values[entry + ".sbemessage.payload.snapshotcompletemessage.asofsequencenumber"] = canonical::number(message.template get<protocol::as_of_sequence_number>().value()); }
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
    std::printf("== Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 (tmp values)\n");
    int failures = 0;
    failures += check("Heartbeat", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/Heartbeat.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/Heartbeat.values");
    failures += check("InstrumentDirectoryMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/InstrumentDirectoryMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/InstrumentDirectoryMessage.values");
    failures += check("OrderAddedMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/OrderAddedMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/OrderAddedMessage.values");
    failures += check("OrderDeletedMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/OrderDeletedMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/OrderDeletedMessage.values");
    failures += check("OrderExecutedMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/OrderExecutedMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/OrderExecutedMessage.values");
    failures += check("OrderReducedMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/OrderReducedMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/OrderReducedMessage.values");
    failures += check("RegShoRestrictionMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/RegShoRestrictionMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/RegShoRestrictionMessage.values");
    failures += check("SecurityTradingStatusMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/SecurityTradingStatusMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/SecurityTradingStatusMessage.values");
    failures += check("SessionShutdown", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/SessionShutdown.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/SessionShutdown.values");
    failures += check("TradeMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/TradeMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/TradeMessage.values");
    failures += check("TradingSessionStatusMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/TradingSessionStatusMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/TradingSessionStatusMessage.values");
    return failures == 0 ? 0 : 1;
}
