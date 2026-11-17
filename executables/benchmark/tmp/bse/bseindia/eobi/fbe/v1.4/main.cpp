// Bse.BseIndia.Eobi.Fbe.v1.4: main.cpp
// Bse.BseIndia.Eobi.Fbe.v1.4 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/bse/bseindia/eobi/fbe/v1.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/bse/bseindia/eobi/fbe/v1.4/bse_bseindia_eobi_fbe_v1_4.hpp"

// Bse BseIndia Eobi Fbe 1.4: the reading of its packets, through its Template Meta Programming header
namespace bse::bseindia::eobi::fbe::v1_4 {

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
    if (static_cast<bool>(tmp::rule(template_id_) == 13001)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& heartbeat_message_ = tmp::read<heartbeat_message>(data + offset, bound - offset, handler); offset += heartbeat_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13600)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& product_summary_message_ = tmp::read<product_summary_message>(data + offset, bound - offset, handler); offset += product_summary_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13602)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& snapshot_order_message_ = tmp::read<snapshot_order_message>(data + offset, bound - offset, handler); offset += snapshot_order_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13601)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& instrument_summary_message_ = tmp::read<instrument_summary_message>(data + offset, bound - offset, handler); offset += instrument_summary_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13500)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& auction_best_bid_offer_message_ = tmp::read<auction_best_bid_offer_message>(data + offset, bound - offset, handler); offset += auction_best_bid_offer_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13501)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& auction_clearing_price_message_ = tmp::read<auction_clearing_price_message>(data + offset, bound - offset, handler); offset += auction_clearing_price_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13504)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& top_of_book_message_ = tmp::read<top_of_book_message>(data + offset, bound - offset, handler); offset += top_of_book_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13100)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_add_message_ = tmp::read<order_add_message>(data + offset, bound - offset, handler); offset += order_add_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13101)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_modify_message_ = tmp::read<order_modify_message>(data + offset, bound - offset, handler); offset += order_modify_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13106)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_modify_same_priority_message_ = tmp::read<order_modify_same_priority_message>(data + offset, bound - offset, handler); offset += order_modify_same_priority_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13102)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_delete_message_ = tmp::read<order_delete_message>(data + offset, bound - offset, handler); offset += order_delete_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13103)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_mass_delete_message_ = tmp::read<order_mass_delete_message>(data + offset, bound - offset, handler); offset += order_mass_delete_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13105)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& partial_order_execution_message_ = tmp::read<partial_order_execution_message>(data + offset, bound - offset, handler); offset += partial_order_execution_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13104)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& full_order_execution_message_ = tmp::read<full_order_execution_message>(data + offset, bound - offset, handler); offset += full_order_execution_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13200)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_reversal_message_ = tmp::read<trade_reversal_message>(data + offset, bound - offset, handler); offset += trade_reversal_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13202)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& execution_summary_message_ = tmp::read<execution_summary_message>(data + offset, bound - offset, handler); offset += execution_summary_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13203)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& instrument_info_message_ = tmp::read<instrument_info_message>(data + offset, bound - offset, handler); offset += instrument_info_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13204)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& lpp_range_message_ = tmp::read<lpp_range_message>(data + offset, bound - offset, handler); offset += lpp_range_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13300)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& product_state_change_message_ = tmp::read<product_state_change_message>(data + offset, bound - offset, handler); offset += product_state_change_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13301)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& instrument_state_change_message_ = tmp::read<instrument_state_change_message>(data + offset, bound - offset, handler); offset += instrument_state_change_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 13400)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_complex_instrument_message_ = tmp::read<add_complex_instrument_message>(data + offset, bound - offset, handler); offset += add_complex_instrument_message::size;
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
    bound = static_cast<std::size_t>(tmp::rule(message_header_.template get<body_len>()));
    tmp::require(bound, length);
    offset += parse_payload(data + offset, bound - offset, handler, message_header_.template get<template_id>());
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


} // namespace bse::bseindia::eobi::fbe::v1_4

namespace protocol = ::bse::bseindia::eobi::fbe::v1_4;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::appl_seq_num>(); }) { checksum += bench::digest(header.template get<protocol::appl_seq_num>().value()); }
        if constexpr (requires { header.template get<protocol::market_segment_id>(); }) { checksum += bench::digest(header.template get<protocol::market_segment_id>().value()); }
        if constexpr (requires { header.template get<protocol::partition_id>(); }) { checksum += bench::digest(header.template get<protocol::partition_id>().value()); }
        if constexpr (requires { header.template get<protocol::completion_indicator>(); }) { checksum += bench::digest(header.template get<protocol::completion_indicator>().value()); }
        if constexpr (requires { header.template get<protocol::appl_seq_reset_indicator>(); }) { checksum += bench::digest(header.template get<protocol::appl_seq_reset_indicator>().value()); }
        if constexpr (requires { header.template get<protocol::transact_time>(); }) { checksum += bench::digest(header.template get<protocol::transact_time>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::body_len>(); }) { checksum += bench::digest(header.template get<protocol::body_len>().value()); }
        if constexpr (requires { header.template get<protocol::template_id>(); }) { checksum += bench::digest(header.template get<protocol::template_id>().value()); }
        if constexpr (requires { header.template get<protocol::msg_seq_num>(); }) { checksum += bench::digest(header.template get<protocol::msg_seq_num>().value()); }
    }

    void operator()(const protocol::heartbeat_message& message) {
        if constexpr (requires { message.template get<protocol::last_msg_seq_num_processed>(); }) { checksum += bench::digest(message.template get<protocol::last_msg_seq_num_processed>().value()); }
    }

    void operator()(const protocol::product_summary_message& message) {
        if constexpr (requires { message.template get<protocol::last_msg_seq_num_processed>(); }) { checksum += bench::digest(message.template get<protocol::last_msg_seq_num_processed>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { checksum += bench::digest(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_sub_id>(); }) { checksum += bench::digest(message.template get<protocol::trading_session_sub_id>().value()); }
        if constexpr (requires { message.template get<protocol::trad_ses_status>(); }) { checksum += bench::digest(message.template get<protocol::trad_ses_status>().value()); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { checksum += bench::digest(message.template get<protocol::fast_market_indicator>().value()); }
    }

    void operator()(const protocol::snapshot_order_message&) {
    }

    void operator()(const protocol::instrument_summary_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_update_time>(); }) { checksum += bench::digest(message.template get<protocol::last_update_time>().value()); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_execution_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_execution_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::trd_reg_ts_execution_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::tot_no_orders>(); }) { checksum += bench::digest(message.template get<protocol::tot_no_orders>().value()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { checksum += bench::digest(message.template get<protocol::security_status>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { checksum += bench::digest(message.template get<protocol::security_trading_status>().value()); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { checksum += bench::digest(message.template get<protocol::fast_market_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::no_md_entries>(); }) { checksum += bench::digest(message.template get<protocol::no_md_entries>().value()); }
        if constexpr (requires { message.template get<protocol::trade_volume>(); }) { checksum += bench::digest(message.template get<protocol::trade_volume>().value()); }
        if constexpr (requires { message.template get<protocol::no_of_trades>(); }) { checksum += bench::digest(message.template get<protocol::no_of_trades>().value()); }
    }

    void operator()(const protocol::auction_best_bid_offer_message& message) {
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += bench::digest(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::bid_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::bid_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::bid_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::offer_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::offer_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::offer_px>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::auction_clearing_price_message& message) {
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += bench::digest(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += bench::digest(message.template get<protocol::last_px>().value()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += bench::digest(message.template get<protocol::last_qty>().value()); }
    }

    void operator()(const protocol::top_of_book_message& message) {
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += bench::digest(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::bid_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::bid_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::bid_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::offer_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::offer_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::offer_px>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_add_message& message) {
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_in>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_in>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::trd_reg_ts_time_in>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
    }

    void operator()(const protocol::order_modify_message& message) {
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_in>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_in>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::trd_reg_ts_time_in>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_prev_time_priority>(); }) { checksum += bench::digest(message.template get<protocol::trd_reg_ts_prev_time_priority>().value()); }
        if constexpr (requires { message.template get<protocol::prev_price>(); }) { checksum += bench::digest(message.template get<protocol::prev_price>().value()); }
        if constexpr (requires { message.template get<protocol::prev_display_qty>(); }) { checksum += bench::digest(message.template get<protocol::prev_display_qty>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
    }

    void operator()(const protocol::order_modify_same_priority_message& message) {
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_in>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_in>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::trd_reg_ts_time_in>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += bench::digest(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::prev_display_qty>(); }) { checksum += bench::digest(message.template get<protocol::prev_display_qty>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
    }

    void operator()(const protocol::order_delete_message& message) {
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_in>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_in>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::trd_reg_ts_time_in>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += bench::digest(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
    }

    void operator()(const protocol::order_mass_delete_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += bench::digest(message.template get<protocol::transact_time>().value()); }
    }

    void operator()(const protocol::partial_order_execution_message& message) {
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_priority>(); }) { checksum += bench::digest(message.template get<protocol::trd_reg_ts_time_priority>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { checksum += bench::digest(message.template get<protocol::trd_match_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += bench::digest(message.template get<protocol::last_qty>().value()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += bench::digest(message.template get<protocol::last_px>().value()); }
    }

    void operator()(const protocol::full_order_execution_message& message) {
        if constexpr (requires { message.template get<protocol::side>(); }) { checksum += bench::digest(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_priority>(); }) { checksum += bench::digest(message.template get<protocol::trd_reg_ts_time_priority>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { checksum += bench::digest(message.template get<protocol::trd_match_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += bench::digest(message.template get<protocol::last_qty>().value()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += bench::digest(message.template get<protocol::last_px>().value()); }
    }

    void operator()(const protocol::trade_reversal_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += bench::digest(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { checksum += bench::digest(message.template get<protocol::trd_match_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += bench::digest(message.template get<protocol::last_qty>().value()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += bench::digest(message.template get<protocol::last_px>().value()); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_execution_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_execution_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::trd_reg_ts_execution_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::no_md_entries>(); }) { checksum += bench::digest(message.template get<protocol::no_md_entries>().value()); }
    }

    void operator()(const protocol::execution_summary_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::aggressor_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::aggressor_timestamp>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message.template get<protocol::aggressor_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::exec_id>(); }) { checksum += bench::digest(message.template get<protocol::exec_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { checksum += bench::digest(message.template get<protocol::last_qty>().value()); }
        if constexpr (requires { message.template get<protocol::aggressor_side>(); }) { checksum += bench::digest(message.template get<protocol::aggressor_side>().value()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::trade_condition>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::trade_condition>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += bench::digest(message.template get<protocol::last_px>().value()); }
        if constexpr (requires { message.template get<protocol::resting_hidden_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::resting_hidden_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::resting_hidden_qty>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::instrument_info_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::close_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::close_price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::close_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::prev_close_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::prev_close_price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::prev_close_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::upper_ckt_limit>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::upper_ckt_limit>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::upper_ckt_limit>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::lower_ckt_limit>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::lower_ckt_limit>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::lower_ckt_limit>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::lpp_range_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::upper_exec_limit>(); }) { checksum += bench::digest(message.template get<protocol::upper_exec_limit>().value()); }
        if constexpr (requires { message.template get<protocol::lower_exec_limit>(); }) { checksum += bench::digest(message.template get<protocol::lower_exec_limit>().value()); }
    }

    void operator()(const protocol::product_state_change_message& message) {
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { checksum += bench::digest(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_sub_id>(); }) { checksum += bench::digest(message.template get<protocol::trading_session_sub_id>().value()); }
        if constexpr (requires { message.template get<protocol::trad_ses_status>(); }) { checksum += bench::digest(message.template get<protocol::trad_ses_status>().value()); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { checksum += bench::digest(message.template get<protocol::fast_market_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += bench::digest(message.template get<protocol::transact_time>().value()); }
    }

    void operator()(const protocol::instrument_state_change_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { checksum += bench::digest(message.template get<protocol::security_status>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { checksum += bench::digest(message.template get<protocol::security_trading_status>().value()); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { checksum += bench::digest(message.template get<protocol::fast_market_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += bench::digest(message.template get<protocol::transact_time>().value()); }
    }

    void operator()(const protocol::add_complex_instrument_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += bench::digest(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::security_sub_type>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::security_sub_type>().value()) != 0x080000000U ? bench::digest(message.template get<protocol::security_sub_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::product_complex>(); }) { checksum += bench::digest(message.template get<protocol::product_complex>().value()); }
        if constexpr (requires { message.template get<protocol::implied_market_indicator>(); }) { checksum += bench::digest(message.template get<protocol::implied_market_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::no_legs>(); }) { checksum += bench::digest(message.template get<protocol::no_legs>().value()); }
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
    return bench::run("Bse.BseIndia.Eobi.Fbe.v1.4", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
