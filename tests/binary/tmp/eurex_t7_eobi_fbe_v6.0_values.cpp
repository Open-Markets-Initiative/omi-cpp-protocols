// Eurex.T7.Eobi.Fbe.v6.0 canonical values, through the Tmp header: every value the Tmp reading hands
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
#include "cpp/binary/tmp/eurex/t7/eobi/fbe/v6.0/eurex_t7_eobi_fbe_v6_0.hpp"

// Eurex T7 Eobi Fbe 6.0: the reading of its packets, through its Template Meta Programming header
namespace eurex::t7::eobi::fbe::v6_0 {

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


} // namespace eurex::t7::eobi::fbe::v6_0

namespace protocol = ::eurex::t7::eobi::fbe::v6_0;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::appl_seq_num>(); }) { values["packet.packetheader.applseqnum"] = (static_cast<std::uint32_t>(header.template get<protocol::appl_seq_num>().value()) != 0x0FFFFFFFFU ? canonical::number(header.template get<protocol::appl_seq_num>().value()) : canonical::absent()); }
        if constexpr (requires { header.template get<protocol::market_segment_id>(); }) { values["packet.packetheader.marketsegmentid"] = (static_cast<std::uint32_t>(header.template get<protocol::market_segment_id>().value()) != 0x080000000U ? canonical::number(header.template get<protocol::market_segment_id>().value()) : canonical::absent()); }
        if constexpr (requires { header.template get<protocol::partition_id>(); }) { values["packet.packetheader.partitionid"] = (static_cast<std::uint8_t>(header.template get<protocol::partition_id>().value()) != 0x0FFU ? canonical::number(header.template get<protocol::partition_id>().value()) : canonical::absent()); }
        if constexpr (requires { header.template get<protocol::completion_indicator>(); }) { values["packet.packetheader.completionindicator"] = (static_cast<std::uint8_t>(header.template get<protocol::completion_indicator>().value()) != 0x0FFU ? canonical::number(header.template get<protocol::completion_indicator>().value()) : canonical::absent()); }
        if constexpr (requires { header.template get<protocol::appl_seq_reset_indicator>(); }) { values["packet.packetheader.applseqresetindicator"] = (static_cast<std::uint8_t>(header.template get<protocol::appl_seq_reset_indicator>().value()) != 0x0FFU ? canonical::number(header.template get<protocol::appl_seq_reset_indicator>().value()) : canonical::absent()); }
        if constexpr (requires { header.template get<protocol::transact_time>(); }) { values["packet.packetheader.transacttime"] = (static_cast<std::uint64_t>(header.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(header.template get<protocol::transact_time>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::message_header_comp& header) {
        entry = "packet.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::body_len>(); }) { values[entry + ".messageheadercomp.bodylen"] = (static_cast<std::uint16_t>(header.template get<protocol::body_len>().value()) != 0x0FFFFU ? canonical::number(header.template get<protocol::body_len>().value()) : canonical::absent()); }
        if constexpr (requires { header.template get<protocol::template_id>(); }) { values[entry + ".messageheadercomp.templateid"] = (static_cast<std::uint16_t>(header.template get<protocol::template_id>().value()) != 0x0FFFFU ? canonical::number(header.template get<protocol::template_id>().value()) : canonical::absent()); }
        if constexpr (requires { header.template get<protocol::msg_seq_num>(); }) { values[entry + ".messageheadercomp.msgseqnum"] = (static_cast<std::uint32_t>(header.template get<protocol::msg_seq_num>().value()) != 0x0FFFFFFFFU ? canonical::number(header.template get<protocol::msg_seq_num>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::add_complex_instrument& message) {
        values[entry + ".payload"] = "packet.message.payload.addcomplexinstrument";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.addcomplexinstrument.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.addcomplexinstrument.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_sub_type>(); }) { values[entry + ".payload.addcomplexinstrument.securitysubtype"] = (static_cast<std::uint32_t>(message.template get<protocol::security_sub_type>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::security_sub_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::product_complex>(); }) { values[entry + ".payload.addcomplexinstrument.productcomplex"] = (static_cast<std::uint8_t>(message.template get<protocol::product_complex>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::product_complex>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::implied_market_indicator>(); }) { values[entry + ".payload.addcomplexinstrument.impliedmarketindicator"] = (static_cast<std::uint8_t>(message.template get<protocol::implied_market_indicator>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::implied_market_indicator>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::no_legs>(); }) { values[entry + ".payload.addcomplexinstrument.nolegs"] = (static_cast<std::uint8_t>(message.template get<protocol::no_legs>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::no_legs>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::auction_bbo& message) {
        values[entry + ".payload"] = "packet.message.payload.auctionbbo";
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.auctionbbo.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.auctionbbo.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::bid_px>(); }) { values[entry + ".payload.auctionbbo.bidpx"] = (static_cast<std::uint64_t>(message.template get<protocol::bid_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::bid_px>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::offer_px>(); }) { values[entry + ".payload.auctionbbo.offerpx"] = (static_cast<std::uint64_t>(message.template get<protocol::offer_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::offer_px>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::bid_size>(); }) { values[entry + ".payload.auctionbbo.bidsize"] = (static_cast<std::uint32_t>(message.template get<protocol::bid_size>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::bid_size>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::offer_size>(); }) { values[entry + ".payload.auctionbbo.offersize"] = (static_cast<std::uint32_t>(message.template get<protocol::offer_size>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::offer_size>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::potential_security_trading_event>(); }) { values[entry + ".payload.auctionbbo.potentialsecuritytradingevent"] = (static_cast<std::uint8_t>(message.template get<protocol::potential_security_trading_event>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::potential_security_trading_event>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::auction_clearing_price& message) {
        values[entry + ".payload"] = "packet.message.payload.auctionclearingprice";
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.auctionclearingprice.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.auctionclearingprice.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { values[entry + ".payload.auctionclearingprice.lastpx"] = (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::last_px>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.auctionclearingprice.lastqty"] = (static_cast<std::uint32_t>(message.template get<protocol::last_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::last_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::imbalance_qty>(); }) { values[entry + ".payload.auctionclearingprice.imbalanceqty"] = (static_cast<std::uint32_t>(message.template get<protocol::imbalance_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::imbalance_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { values[entry + ".payload.auctionclearingprice.securitytradingstatus"] = (static_cast<std::uint8_t>(message.template get<protocol::security_trading_status>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::security_trading_status>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::potential_security_trading_event>(); }) { values[entry + ".payload.auctionclearingprice.potentialsecuritytradingevent"] = (static_cast<std::uint8_t>(message.template get<protocol::potential_security_trading_event>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::potential_security_trading_event>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::cross_request& message) {
        values[entry + ".payload"] = "packet.message.payload.crossrequest";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.crossrequest.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.crossrequest.lastqty"] = (static_cast<std::uint32_t>(message.template get<protocol::last_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::last_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.crossrequest.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::execution_summary& message) {
        values[entry + ".payload"] = "packet.message.payload.executionsummary";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.executionsummary.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::aggressor_time>(); }) { values[entry + ".payload.executionsummary.aggressortime"] = (static_cast<std::uint64_t>(message.template get<protocol::aggressor_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::aggressor_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::request_time>(); }) { values[entry + ".payload.executionsummary.requesttime"] = (static_cast<std::uint64_t>(message.template get<protocol::request_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::request_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::exec_id>(); }) { values[entry + ".payload.executionsummary.execid"] = (static_cast<std::uint64_t>(message.template get<protocol::exec_id>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::exec_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.executionsummary.lastqty"] = (static_cast<std::uint32_t>(message.template get<protocol::last_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::last_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::aggressor_side>(); }) { values[entry + ".payload.executionsummary.aggressorside"] = (static_cast<std::uint8_t>(message.template get<protocol::aggressor_side>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::aggressor_side>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { values[entry + ".payload.executionsummary.tradecondition"] = (static_cast<std::uint8_t>(message.template get<protocol::trade_condition>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::trade_condition>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { values[entry + ".payload.executionsummary.lastpx"] = (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::last_px>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::resting_hidden_qty>(); }) { values[entry + ".payload.executionsummary.restinghiddenqty"] = (static_cast<std::uint32_t>(message.template get<protocol::resting_hidden_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::resting_hidden_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::resting_cxl_qty>(); }) { values[entry + ".payload.executionsummary.restingcxlqty"] = (static_cast<std::uint32_t>(message.template get<protocol::resting_cxl_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::resting_cxl_qty>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::full_order_execution& message) {
        values[entry + ".payload"] = "packet.message.payload.fullorderexecution";
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.fullorderexecution.side"] = (static_cast<std::uint8_t>(message.template get<protocol::side>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::side>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::ord_type>(); }) { values[entry + ".payload.fullorderexecution.ordtype"] = (static_cast<std::uint8_t>(message.template get<protocol::ord_type>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::ord_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::algorithmic_trade_indicator>(); }) { values[entry + ".payload.fullorderexecution.algorithmictradeindicator"] = (static_cast<std::uint8_t>(message.template get<protocol::algorithmic_trade_indicator>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::algorithmic_trade_indicator>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.fullorderexecution.price"] = (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::price>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_priority>(); }) { values[entry + ".payload.fullorderexecution.trdregtstimepriority"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_priority>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_time_priority>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.fullorderexecution.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { values[entry + ".payload.fullorderexecution.trdmatchid"] = (static_cast<std::uint32_t>(message.template get<protocol::trd_match_id>().value()) != 0x0FFFFFFFFU ? canonical::number(message.template get<protocol::trd_match_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.fullorderexecution.lastqty"] = (static_cast<std::uint32_t>(message.template get<protocol::last_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::last_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { values[entry + ".payload.fullorderexecution.lastpx"] = (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::last_px>().value(), -8) : canonical::absent()); }
    }

    void operator()(const protocol::heartbeat& message) {
        values[entry + ".payload"] = "packet.message.payload.heartbeat";
        if constexpr (requires { message.template get<protocol::last_msg_seq_num_processed>(); }) { values[entry + ".payload.heartbeat.lastmsgseqnumprocessed"] = (static_cast<std::uint32_t>(message.template get<protocol::last_msg_seq_num_processed>().value()) != 0x0FFFFFFFFU ? canonical::number(message.template get<protocol::last_msg_seq_num_processed>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::instrument_state_change& message) {
        values[entry + ".payload"] = "packet.message.payload.instrumentstatechange";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.instrumentstatechange.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { values[entry + ".payload.instrumentstatechange.securitystatus"] = (static_cast<std::uint8_t>(message.template get<protocol::security_status>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::security_status>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { values[entry + ".payload.instrumentstatechange.securitytradingstatus"] = (static_cast<std::uint8_t>(message.template get<protocol::security_trading_status>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::security_trading_status>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::market_condition>(); }) { values[entry + ".payload.instrumentstatechange.marketcondition"] = (static_cast<std::uint8_t>(message.template get<protocol::market_condition>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::market_condition>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { values[entry + ".payload.instrumentstatechange.fastmarketindicator"] = (static_cast<std::uint8_t>(message.template get<protocol::fast_market_indicator>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::fast_market_indicator>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_trading_event>(); }) { values[entry + ".payload.instrumentstatechange.securitytradingevent"] = (static_cast<std::uint8_t>(message.template get<protocol::security_trading_event>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::security_trading_event>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.instrumentstatechange.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::instrument_summary& message) {
        values[entry + ".payload"] = "packet.message.payload.instrumentsummary";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.instrumentsummary.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_update_time>(); }) { values[entry + ".payload.instrumentsummary.lastupdatetime"] = (static_cast<std::uint64_t>(message.template get<protocol::last_update_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::last_update_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_execution_time>(); }) { values[entry + ".payload.instrumentsummary.trdregtsexecutiontime"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_execution_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_execution_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::tot_no_orders>(); }) { values[entry + ".payload.instrumentsummary.totnoorders"] = (static_cast<std::uint16_t>(message.template get<protocol::tot_no_orders>().value()) != 0x0FFFFU ? canonical::number(message.template get<protocol::tot_no_orders>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { values[entry + ".payload.instrumentsummary.securitystatus"] = (static_cast<std::uint8_t>(message.template get<protocol::security_status>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::security_status>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { values[entry + ".payload.instrumentsummary.securitytradingstatus"] = (static_cast<std::uint8_t>(message.template get<protocol::security_trading_status>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::security_trading_status>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::market_condition>(); }) { values[entry + ".payload.instrumentsummary.marketcondition"] = (static_cast<std::uint8_t>(message.template get<protocol::market_condition>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::market_condition>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { values[entry + ".payload.instrumentsummary.fastmarketindicator"] = (static_cast<std::uint8_t>(message.template get<protocol::fast_market_indicator>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::fast_market_indicator>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_trading_event>(); }) { values[entry + ".payload.instrumentsummary.securitytradingevent"] = (static_cast<std::uint8_t>(message.template get<protocol::security_trading_event>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::security_trading_event>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::no_md_entries>(); }) { values[entry + ".payload.instrumentsummary.nomdentries"] = (static_cast<std::uint8_t>(message.template get<protocol::no_md_entries>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::no_md_entries>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::order_add& message) {
        values[entry + ".payload"] = "packet.message.payload.orderadd";
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_in>(); }) { values[entry + ".payload.orderadd.trdregtstimein"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_in>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_time_in>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.orderadd.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::order_delete& message) {
        values[entry + ".payload"] = "packet.message.payload.orderdelete";
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_in>(); }) { values[entry + ".payload.orderdelete.trdregtstimein"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_in>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_time_in>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.orderdelete.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.orderdelete.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::order_mass_delete& message) {
        values[entry + ".payload"] = "packet.message.payload.ordermassdelete";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.ordermassdelete.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.ordermassdelete.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::order_modify& message) {
        values[entry + ".payload"] = "packet.message.payload.ordermodify";
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_in>(); }) { values[entry + ".payload.ordermodify.trdregtstimein"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_in>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_time_in>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_prev_time_priority>(); }) { values[entry + ".payload.ordermodify.trdregtsprevtimepriority"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_prev_time_priority>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_prev_time_priority>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::prev_price>(); }) { values[entry + ".payload.ordermodify.prevprice"] = (static_cast<std::uint64_t>(message.template get<protocol::prev_price>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::prev_price>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::prev_display_qty>(); }) { values[entry + ".payload.ordermodify.prevdisplayqty"] = (static_cast<std::uint32_t>(message.template get<protocol::prev_display_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::prev_display_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.ordermodify.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::order_modify_same_prio& message) {
        values[entry + ".payload"] = "packet.message.payload.ordermodifysameprio";
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_in>(); }) { values[entry + ".payload.ordermodifysameprio.trdregtstimein"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_in>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_time_in>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.ordermodifysameprio.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::prev_display_qty>(); }) { values[entry + ".payload.ordermodifysameprio.prevdisplayqty"] = (static_cast<std::uint32_t>(message.template get<protocol::prev_display_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::prev_display_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.ordermodifysameprio.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::partial_order_execution& message) {
        values[entry + ".payload"] = "packet.message.payload.partialorderexecution";
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.partialorderexecution.side"] = (static_cast<std::uint8_t>(message.template get<protocol::side>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::side>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::ord_type>(); }) { values[entry + ".payload.partialorderexecution.ordtype"] = (static_cast<std::uint8_t>(message.template get<protocol::ord_type>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::ord_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::algorithmic_trade_indicator>(); }) { values[entry + ".payload.partialorderexecution.algorithmictradeindicator"] = (static_cast<std::uint8_t>(message.template get<protocol::algorithmic_trade_indicator>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::algorithmic_trade_indicator>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.partialorderexecution.price"] = (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::price>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_priority>(); }) { values[entry + ".payload.partialorderexecution.trdregtstimepriority"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_priority>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_time_priority>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.partialorderexecution.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { values[entry + ".payload.partialorderexecution.trdmatchid"] = (static_cast<std::uint32_t>(message.template get<protocol::trd_match_id>().value()) != 0x0FFFFFFFFU ? canonical::number(message.template get<protocol::trd_match_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.partialorderexecution.lastqty"] = (static_cast<std::uint32_t>(message.template get<protocol::last_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::last_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { values[entry + ".payload.partialorderexecution.lastpx"] = (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::last_px>().value(), -8) : canonical::absent()); }
    }

    void operator()(const protocol::product_state_change& message) {
        values[entry + ".payload"] = "packet.message.payload.productstatechange";
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { values[entry + ".payload.productstatechange.tradingsessionid"] = (static_cast<std::uint8_t>(message.template get<protocol::trading_session_id>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::trading_session_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_session_sub_id>(); }) { values[entry + ".payload.productstatechange.tradingsessionsubid"] = (static_cast<std::uint8_t>(message.template get<protocol::trading_session_sub_id>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::trading_session_sub_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trad_ses_status>(); }) { values[entry + ".payload.productstatechange.tradsesstatus"] = (static_cast<std::uint8_t>(message.template get<protocol::trad_ses_status>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::trad_ses_status>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::market_condition>(); }) { values[entry + ".payload.productstatechange.marketcondition"] = (static_cast<std::uint8_t>(message.template get<protocol::market_condition>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::market_condition>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { values[entry + ".payload.productstatechange.fastmarketindicator"] = (static_cast<std::uint8_t>(message.template get<protocol::fast_market_indicator>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::fast_market_indicator>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.productstatechange.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::product_summary& message) {
        values[entry + ".payload"] = "packet.message.payload.productsummary";
        if constexpr (requires { message.template get<protocol::last_msg_seq_num_processed>(); }) { values[entry + ".payload.productsummary.lastmsgseqnumprocessed"] = (static_cast<std::uint32_t>(message.template get<protocol::last_msg_seq_num_processed>().value()) != 0x0FFFFFFFFU ? canonical::number(message.template get<protocol::last_msg_seq_num_processed>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { values[entry + ".payload.productsummary.tradingsessionid"] = (static_cast<std::uint8_t>(message.template get<protocol::trading_session_id>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::trading_session_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_session_sub_id>(); }) { values[entry + ".payload.productsummary.tradingsessionsubid"] = (static_cast<std::uint8_t>(message.template get<protocol::trading_session_sub_id>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::trading_session_sub_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trad_ses_status>(); }) { values[entry + ".payload.productsummary.tradsesstatus"] = (static_cast<std::uint8_t>(message.template get<protocol::trad_ses_status>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::trad_ses_status>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::market_condition>(); }) { values[entry + ".payload.productsummary.marketcondition"] = (static_cast<std::uint8_t>(message.template get<protocol::market_condition>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::market_condition>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { values[entry + ".payload.productsummary.fastmarketindicator"] = (static_cast<std::uint8_t>(message.template get<protocol::fast_market_indicator>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::fast_market_indicator>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::quote_request& message) {
        values[entry + ".payload"] = "packet.message.payload.quoterequest";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.quoterequest.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.quoterequest.lastqty"] = (static_cast<std::uint32_t>(message.template get<protocol::last_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::last_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.quoterequest.side"] = (static_cast<std::uint8_t>(message.template get<protocol::side>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::side>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.quoterequest.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::snapshot_order&) {
        values[entry + ".payload"] = "packet.message.payload.snapshotorder";
    }

    void operator()(const protocol::top_of_book& message) {
        values[entry + ".payload"] = "packet.message.payload.topofbook";
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.topofbook.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.topofbook.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::bid_px>(); }) { values[entry + ".payload.topofbook.bidpx"] = (static_cast<std::uint64_t>(message.template get<protocol::bid_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::bid_px>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::offer_px>(); }) { values[entry + ".payload.topofbook.offerpx"] = (static_cast<std::uint64_t>(message.template get<protocol::offer_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::offer_px>().value(), -8) : canonical::absent()); }
    }

    void operator()(const protocol::trade_report& message) {
        values[entry + ".payload"] = "packet.message.payload.tradereport";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.tradereport.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.tradereport.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { values[entry + ".payload.tradereport.trdmatchid"] = (static_cast<std::uint32_t>(message.template get<protocol::trd_match_id>().value()) != 0x0FFFFFFFFU ? canonical::number(message.template get<protocol::trd_match_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.tradereport.lastqty"] = (static_cast<std::uint32_t>(message.template get<protocol::last_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::last_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { values[entry + ".payload.tradereport.lastpx"] = (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::last_px>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::match_type>(); }) { values[entry + ".payload.tradereport.matchtype"] = (static_cast<std::uint8_t>(message.template get<protocol::match_type>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::match_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::match_sub_type>(); }) { values[entry + ".payload.tradereport.matchsubtype"] = (static_cast<std::uint8_t>(message.template get<protocol::match_sub_type>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::match_sub_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::algorithmic_trade_indicator>(); }) { values[entry + ".payload.tradereport.algorithmictradeindicator"] = (static_cast<std::uint8_t>(message.template get<protocol::algorithmic_trade_indicator>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::algorithmic_trade_indicator>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { values[entry + ".payload.tradereport.tradecondition"] = (static_cast<std::uint8_t>(message.template get<protocol::trade_condition>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::trade_condition>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::trade_reversal& message) {
        values[entry + ".payload"] = "packet.message.payload.tradereversal";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.tradereversal.securityid"] = (static_cast<std::uint64_t>(message.template get<protocol::security_id>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::security_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.tradereversal.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { values[entry + ".payload.tradereversal.trdmatchid"] = (static_cast<std::uint32_t>(message.template get<protocol::trd_match_id>().value()) != 0x0FFFFFFFFU ? canonical::number(message.template get<protocol::trd_match_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.tradereversal.lastqty"] = (static_cast<std::uint32_t>(message.template get<protocol::last_qty>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::last_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { values[entry + ".payload.tradereversal.lastpx"] = (static_cast<std::uint64_t>(message.template get<protocol::last_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::last_px>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_execution_time>(); }) { values[entry + ".payload.tradereversal.trdregtsexecutiontime"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_execution_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_execution_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { values[entry + ".payload.tradereversal.tradecondition"] = (static_cast<std::uint8_t>(message.template get<protocol::trade_condition>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::trade_condition>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::no_md_entries>(); }) { values[entry + ".payload.tradereversal.nomdentries"] = (static_cast<std::uint8_t>(message.template get<protocol::no_md_entries>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::no_md_entries>().value()) : canonical::absent()); }
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
    std::printf("== Eurex.T7.Eobi.Fbe.v6.0 (tmp values)\n");
    int failures = 0;
    failures += check("FullOrderExecution", "Eurex/T7.Eobi.Fbe.v6.0/FullOrderExecution.pcap", "eurex/t7/eobi/fbe/v6.0/FullOrderExecution.values");
    failures += check("Heartbeat", "Eurex/T7.Eobi.Fbe.v6.0/Heartbeat.pcap", "eurex/t7/eobi/fbe/v6.0/Heartbeat.values");
    failures += check("InstrumentSummary", "Eurex/T7.Eobi.Fbe.v6.0/InstrumentSummary.pcap", "eurex/t7/eobi/fbe/v6.0/InstrumentSummary.values");
    failures += check("OrderAdd", "Eurex/T7.Eobi.Fbe.v6.0/OrderAdd.pcap", "eurex/t7/eobi/fbe/v6.0/OrderAdd.values");
    failures += check("OrderModify", "Eurex/T7.Eobi.Fbe.v6.0/OrderModify.pcap", "eurex/t7/eobi/fbe/v6.0/OrderModify.values");
    failures += check("ProductSummary", "Eurex/T7.Eobi.Fbe.v6.0/ProductSummary.pcap", "eurex/t7/eobi/fbe/v6.0/ProductSummary.values");
    failures += check("SnapshotOrder", "Eurex/T7.Eobi.Fbe.v6.0/SnapshotOrder.pcap", "eurex/t7/eobi/fbe/v6.0/SnapshotOrder.values");
    return failures == 0 ? 0 : 1;
}
