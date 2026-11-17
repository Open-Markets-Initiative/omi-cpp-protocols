// Bse.BseIndia.Eobi.Fbe.v1.4 canonical values, through the Tmp header: every value the Tmp reading hands
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
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::appl_seq_num>(); }) { values["packet.packetheader.applseqnum"] = canonical::number(header.template get<protocol::appl_seq_num>().value()); }
        if constexpr (requires { header.template get<protocol::market_segment_id>(); }) { values["packet.packetheader.marketsegmentid"] = canonical::number(header.template get<protocol::market_segment_id>().value()); }
        if constexpr (requires { header.template get<protocol::partition_id>(); }) { values["packet.packetheader.partitionid"] = canonical::number(header.template get<protocol::partition_id>().value()); }
        if constexpr (requires { header.template get<protocol::completion_indicator>(); }) { values["packet.packetheader.completionindicator"] = canonical::number(header.template get<protocol::completion_indicator>().value()); }
        if constexpr (requires { header.template get<protocol::appl_seq_reset_indicator>(); }) { values["packet.packetheader.applseqresetindicator"] = canonical::number(header.template get<protocol::appl_seq_reset_indicator>().value()); }
        if constexpr (requires { header.template get<protocol::transact_time>(); }) { values["packet.packetheader.transacttime"] = canonical::number(header.template get<protocol::transact_time>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::body_len>(); }) { values[entry + ".messageheader.bodylen"] = canonical::number(header.template get<protocol::body_len>().value()); }
        if constexpr (requires { header.template get<protocol::template_id>(); }) { values[entry + ".messageheader.templateid"] = canonical::number(header.template get<protocol::template_id>().value()); }
        if constexpr (requires { header.template get<protocol::msg_seq_num>(); }) { values[entry + ".messageheader.msgseqnum"] = canonical::number(header.template get<protocol::msg_seq_num>().value()); }
    }

    void operator()(const protocol::heartbeat_message& message) {
        values[entry + ".payload"] = "packet.message.payload.heartbeatmessage";
        if constexpr (requires { message.template get<protocol::last_msg_seq_num_processed>(); }) { values[entry + ".payload.heartbeatmessage.lastmsgseqnumprocessed"] = canonical::number(message.template get<protocol::last_msg_seq_num_processed>().value()); }
    }

    void operator()(const protocol::product_summary_message& message) {
        values[entry + ".payload"] = "packet.message.payload.productsummarymessage";
        if constexpr (requires { message.template get<protocol::last_msg_seq_num_processed>(); }) { values[entry + ".payload.productsummarymessage.lastmsgseqnumprocessed"] = canonical::number(message.template get<protocol::last_msg_seq_num_processed>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { values[entry + ".payload.productsummarymessage.tradingsessionid"] = canonical::number(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_sub_id>(); }) { values[entry + ".payload.productsummarymessage.tradingsessionsubid"] = canonical::number(message.template get<protocol::trading_session_sub_id>().value()); }
        if constexpr (requires { message.template get<protocol::trad_ses_status>(); }) { values[entry + ".payload.productsummarymessage.tradsesstatus"] = canonical::number(message.template get<protocol::trad_ses_status>().value()); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { values[entry + ".payload.productsummarymessage.fastmarketindicator"] = canonical::number(message.template get<protocol::fast_market_indicator>().value()); }
    }

    void operator()(const protocol::snapshot_order_message&) {
        values[entry + ".payload"] = "packet.message.payload.snapshotordermessage";
    }

    void operator()(const protocol::instrument_summary_message& message) {
        values[entry + ".payload"] = "packet.message.payload.instrumentsummarymessage";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.instrumentsummarymessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_update_time>(); }) { values[entry + ".payload.instrumentsummarymessage.lastupdatetime"] = canonical::number(message.template get<protocol::last_update_time>().value()); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_execution_time>(); }) { values[entry + ".payload.instrumentsummarymessage.trdregtsexecutiontime"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_execution_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_execution_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::tot_no_orders>(); }) { values[entry + ".payload.instrumentsummarymessage.totnoorders"] = canonical::number(message.template get<protocol::tot_no_orders>().value()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { values[entry + ".payload.instrumentsummarymessage.securitystatus"] = canonical::number(message.template get<protocol::security_status>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { values[entry + ".payload.instrumentsummarymessage.securitytradingstatus"] = canonical::number(message.template get<protocol::security_trading_status>().value()); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { values[entry + ".payload.instrumentsummarymessage.fastmarketindicator"] = canonical::number(message.template get<protocol::fast_market_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::no_md_entries>(); }) { values[entry + ".payload.instrumentsummarymessage.nomdentries"] = canonical::number(message.template get<protocol::no_md_entries>().value()); }
        if constexpr (requires { message.template get<protocol::trade_volume>(); }) { values[entry + ".payload.instrumentsummarymessage.tradevolume"] = canonical::number(message.template get<protocol::trade_volume>().value()); }
        if constexpr (requires { message.template get<protocol::no_of_trades>(); }) { values[entry + ".payload.instrumentsummarymessage.nooftrades"] = canonical::number(message.template get<protocol::no_of_trades>().value()); }
    }

    void operator()(const protocol::auction_best_bid_offer_message& message) {
        values[entry + ".payload"] = "packet.message.payload.auctionbestbidoffermessage";
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.auctionbestbidoffermessage.transacttime"] = canonical::number(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.auctionbestbidoffermessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::bid_px>(); }) { values[entry + ".payload.auctionbestbidoffermessage.bidpx"] = (static_cast<std::uint64_t>(message.template get<protocol::bid_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::bid_px>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::offer_px>(); }) { values[entry + ".payload.auctionbestbidoffermessage.offerpx"] = (static_cast<std::uint64_t>(message.template get<protocol::offer_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::offer_px>().value(), -6) : canonical::absent()); }
    }

    void operator()(const protocol::auction_clearing_price_message& message) {
        values[entry + ".payload"] = "packet.message.payload.auctionclearingpricemessage";
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.auctionclearingpricemessage.transacttime"] = canonical::number(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.auctionclearingpricemessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { values[entry + ".payload.auctionclearingpricemessage.lastpx"] = canonical::scaled(message.template get<protocol::last_px>().value(), -6); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.auctionclearingpricemessage.lastqty"] = canonical::number(message.template get<protocol::last_qty>().value()); }
    }

    void operator()(const protocol::top_of_book_message& message) {
        values[entry + ".payload"] = "packet.message.payload.topofbookmessage";
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.topofbookmessage.transacttime"] = canonical::number(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.topofbookmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::bid_px>(); }) { values[entry + ".payload.topofbookmessage.bidpx"] = (static_cast<std::uint64_t>(message.template get<protocol::bid_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::bid_px>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::offer_px>(); }) { values[entry + ".payload.topofbookmessage.offerpx"] = (static_cast<std::uint64_t>(message.template get<protocol::offer_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::offer_px>().value(), -6) : canonical::absent()); }
    }

    void operator()(const protocol::order_add_message& message) {
        values[entry + ".payload"] = "packet.message.payload.orderaddmessage";
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_in>(); }) { values[entry + ".payload.orderaddmessage.trdregtstimein"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_in>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_time_in>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.orderaddmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
    }

    void operator()(const protocol::order_modify_message& message) {
        values[entry + ".payload"] = "packet.message.payload.ordermodifymessage";
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_in>(); }) { values[entry + ".payload.ordermodifymessage.trdregtstimein"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_in>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_time_in>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_prev_time_priority>(); }) { values[entry + ".payload.ordermodifymessage.trdregtsprevtimepriority"] = canonical::number(message.template get<protocol::trd_reg_ts_prev_time_priority>().value()); }
        if constexpr (requires { message.template get<protocol::prev_price>(); }) { values[entry + ".payload.ordermodifymessage.prevprice"] = canonical::scaled(message.template get<protocol::prev_price>().value(), -6); }
        if constexpr (requires { message.template get<protocol::prev_display_qty>(); }) { values[entry + ".payload.ordermodifymessage.prevdisplayqty"] = canonical::number(message.template get<protocol::prev_display_qty>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.ordermodifymessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
    }

    void operator()(const protocol::order_modify_same_priority_message& message) {
        values[entry + ".payload"] = "packet.message.payload.ordermodifysameprioritymessage";
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_in>(); }) { values[entry + ".payload.ordermodifysameprioritymessage.trdregtstimein"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_in>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_time_in>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.ordermodifysameprioritymessage.transacttime"] = canonical::number(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::prev_display_qty>(); }) { values[entry + ".payload.ordermodifysameprioritymessage.prevdisplayqty"] = canonical::number(message.template get<protocol::prev_display_qty>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.ordermodifysameprioritymessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
    }

    void operator()(const protocol::order_delete_message& message) {
        values[entry + ".payload"] = "packet.message.payload.orderdeletemessage";
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_in>(); }) { values[entry + ".payload.orderdeletemessage.trdregtstimein"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_time_in>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_time_in>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.orderdeletemessage.transacttime"] = canonical::number(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.orderdeletemessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
    }

    void operator()(const protocol::order_mass_delete_message& message) {
        values[entry + ".payload"] = "packet.message.payload.ordermassdeletemessage";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.ordermassdeletemessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.ordermassdeletemessage.transacttime"] = canonical::number(message.template get<protocol::transact_time>().value()); }
    }

    void operator()(const protocol::partial_order_execution_message& message) {
        values[entry + ".payload"] = "packet.message.payload.partialorderexecutionmessage";
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.partialorderexecutionmessage.side"] = canonical::number(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.partialorderexecutionmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -6); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_priority>(); }) { values[entry + ".payload.partialorderexecutionmessage.trdregtstimepriority"] = canonical::number(message.template get<protocol::trd_reg_ts_time_priority>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.partialorderexecutionmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { values[entry + ".payload.partialorderexecutionmessage.trdmatchid"] = canonical::number(message.template get<protocol::trd_match_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.partialorderexecutionmessage.lastqty"] = canonical::number(message.template get<protocol::last_qty>().value()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { values[entry + ".payload.partialorderexecutionmessage.lastpx"] = canonical::scaled(message.template get<protocol::last_px>().value(), -6); }
    }

    void operator()(const protocol::full_order_execution_message& message) {
        values[entry + ".payload"] = "packet.message.payload.fullorderexecutionmessage";
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.fullorderexecutionmessage.side"] = canonical::number(message.template get<protocol::side>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.fullorderexecutionmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -6); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_time_priority>(); }) { values[entry + ".payload.fullorderexecutionmessage.trdregtstimepriority"] = canonical::number(message.template get<protocol::trd_reg_ts_time_priority>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.fullorderexecutionmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { values[entry + ".payload.fullorderexecutionmessage.trdmatchid"] = canonical::number(message.template get<protocol::trd_match_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.fullorderexecutionmessage.lastqty"] = canonical::number(message.template get<protocol::last_qty>().value()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { values[entry + ".payload.fullorderexecutionmessage.lastpx"] = canonical::scaled(message.template get<protocol::last_px>().value(), -6); }
    }

    void operator()(const protocol::trade_reversal_message& message) {
        values[entry + ".payload"] = "packet.message.payload.tradereversalmessage";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.tradereversalmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.tradereversalmessage.transacttime"] = canonical::number(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::trd_match_id>(); }) { values[entry + ".payload.tradereversalmessage.trdmatchid"] = canonical::number(message.template get<protocol::trd_match_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.tradereversalmessage.lastqty"] = canonical::number(message.template get<protocol::last_qty>().value()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { values[entry + ".payload.tradereversalmessage.lastpx"] = canonical::scaled(message.template get<protocol::last_px>().value(), -6); }
        if constexpr (requires { message.template get<protocol::trd_reg_ts_execution_time>(); }) { values[entry + ".payload.tradereversalmessage.trdregtsexecutiontime"] = (static_cast<std::uint64_t>(message.template get<protocol::trd_reg_ts_execution_time>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::trd_reg_ts_execution_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::no_md_entries>(); }) { values[entry + ".payload.tradereversalmessage.nomdentries"] = canonical::number(message.template get<protocol::no_md_entries>().value()); }
    }

    void operator()(const protocol::execution_summary_message& message) {
        values[entry + ".payload"] = "packet.message.payload.executionsummarymessage";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.executionsummarymessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::aggressor_timestamp>(); }) { values[entry + ".payload.executionsummarymessage.aggressortimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::aggressor_timestamp>().value()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message.template get<protocol::aggressor_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::exec_id>(); }) { values[entry + ".payload.executionsummarymessage.execid"] = canonical::number(message.template get<protocol::exec_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_qty>(); }) { values[entry + ".payload.executionsummarymessage.lastqty"] = canonical::number(message.template get<protocol::last_qty>().value()); }
        if constexpr (requires { message.template get<protocol::aggressor_side>(); }) { values[entry + ".payload.executionsummarymessage.aggressorside"] = canonical::number(message.template get<protocol::aggressor_side>().value()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { values[entry + ".payload.executionsummarymessage.tradecondition"] = (static_cast<std::uint8_t>(message.template get<protocol::trade_condition>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::trade_condition>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { values[entry + ".payload.executionsummarymessage.lastpx"] = canonical::scaled(message.template get<protocol::last_px>().value(), -6); }
        if constexpr (requires { message.template get<protocol::resting_hidden_qty>(); }) { values[entry + ".payload.executionsummarymessage.restinghiddenqty"] = (static_cast<std::uint64_t>(message.template get<protocol::resting_hidden_qty>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::resting_hidden_qty>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::instrument_info_message& message) {
        values[entry + ".payload"] = "packet.message.payload.instrumentinfomessage";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.instrumentinfomessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::close_price>(); }) { values[entry + ".payload.instrumentinfomessage.closeprice"] = (static_cast<std::uint64_t>(message.template get<protocol::close_price>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::close_price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::prev_close_price>(); }) { values[entry + ".payload.instrumentinfomessage.prevcloseprice"] = (static_cast<std::uint64_t>(message.template get<protocol::prev_close_price>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::prev_close_price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::upper_ckt_limit>(); }) { values[entry + ".payload.instrumentinfomessage.uppercktlimit"] = (static_cast<std::uint64_t>(message.template get<protocol::upper_ckt_limit>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::upper_ckt_limit>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::lower_ckt_limit>(); }) { values[entry + ".payload.instrumentinfomessage.lowercktlimit"] = (static_cast<std::uint64_t>(message.template get<protocol::lower_ckt_limit>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::lower_ckt_limit>().value(), -6) : canonical::absent()); }
    }

    void operator()(const protocol::lpp_range_message& message) {
        values[entry + ".payload"] = "packet.message.payload.lpprangemessage";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.lpprangemessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::upper_exec_limit>(); }) { values[entry + ".payload.lpprangemessage.upperexeclimit"] = canonical::scaled(message.template get<protocol::upper_exec_limit>().value(), -6); }
        if constexpr (requires { message.template get<protocol::lower_exec_limit>(); }) { values[entry + ".payload.lpprangemessage.lowerexeclimit"] = canonical::scaled(message.template get<protocol::lower_exec_limit>().value(), -6); }
    }

    void operator()(const protocol::product_state_change_message& message) {
        values[entry + ".payload"] = "packet.message.payload.productstatechangemessage";
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { values[entry + ".payload.productstatechangemessage.tradingsessionid"] = canonical::number(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_sub_id>(); }) { values[entry + ".payload.productstatechangemessage.tradingsessionsubid"] = canonical::number(message.template get<protocol::trading_session_sub_id>().value()); }
        if constexpr (requires { message.template get<protocol::trad_ses_status>(); }) { values[entry + ".payload.productstatechangemessage.tradsesstatus"] = canonical::number(message.template get<protocol::trad_ses_status>().value()); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { values[entry + ".payload.productstatechangemessage.fastmarketindicator"] = canonical::number(message.template get<protocol::fast_market_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.productstatechangemessage.transacttime"] = canonical::number(message.template get<protocol::transact_time>().value()); }
    }

    void operator()(const protocol::instrument_state_change_message& message) {
        values[entry + ".payload"] = "packet.message.payload.instrumentstatechangemessage";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.instrumentstatechangemessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { values[entry + ".payload.instrumentstatechangemessage.securitystatus"] = canonical::number(message.template get<protocol::security_status>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { values[entry + ".payload.instrumentstatechangemessage.securitytradingstatus"] = canonical::number(message.template get<protocol::security_trading_status>().value()); }
        if constexpr (requires { message.template get<protocol::fast_market_indicator>(); }) { values[entry + ".payload.instrumentstatechangemessage.fastmarketindicator"] = canonical::number(message.template get<protocol::fast_market_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.instrumentstatechangemessage.transacttime"] = canonical::number(message.template get<protocol::transact_time>().value()); }
    }

    void operator()(const protocol::add_complex_instrument_message& message) {
        values[entry + ".payload"] = "packet.message.payload.addcomplexinstrumentmessage";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.addcomplexinstrumentmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.addcomplexinstrumentmessage.transacttime"] = canonical::number(message.template get<protocol::transact_time>().value()); }
        if constexpr (requires { message.template get<protocol::security_sub_type>(); }) { values[entry + ".payload.addcomplexinstrumentmessage.securitysubtype"] = (static_cast<std::uint32_t>(message.template get<protocol::security_sub_type>().value()) != 0x080000000U ? canonical::number(message.template get<protocol::security_sub_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::product_complex>(); }) { values[entry + ".payload.addcomplexinstrumentmessage.productcomplex"] = canonical::number(message.template get<protocol::product_complex>().value()); }
        if constexpr (requires { message.template get<protocol::implied_market_indicator>(); }) { values[entry + ".payload.addcomplexinstrumentmessage.impliedmarketindicator"] = canonical::number(message.template get<protocol::implied_market_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::no_legs>(); }) { values[entry + ".payload.addcomplexinstrumentmessage.nolegs"] = canonical::number(message.template get<protocol::no_legs>().value()); }
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
    std::printf("== Bse.BseIndia.Eobi.Fbe.v1.4 (tmp values)\n");
    int failures = 0;
    failures += check("ExecutionSummaryMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/ExecutionSummaryMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/ExecutionSummaryMessage.values");
    failures += check("FullOrderExecutionMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/FullOrderExecutionMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/FullOrderExecutionMessage.values");
    failures += check("HeartbeatMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/HeartbeatMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/HeartbeatMessage.values");
    failures += check("InstrumentInfoMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/InstrumentInfoMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/InstrumentInfoMessage.values");
    failures += check("InstrumentStateChangeMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/InstrumentStateChangeMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/InstrumentStateChangeMessage.values");
    failures += check("LppRangeMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/LppRangeMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/LppRangeMessage.values");
    failures += check("OrderAddMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/OrderAddMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/OrderAddMessage.values");
    failures += check("OrderDeleteMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/OrderDeleteMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/OrderDeleteMessage.values");
    failures += check("OrderModifyMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/OrderModifyMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/OrderModifyMessage.values");
    failures += check("PartialOrderExecutionMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/PartialOrderExecutionMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/PartialOrderExecutionMessage.values");
    failures += check("ProductStateChangeMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/ProductStateChangeMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/ProductStateChangeMessage.values");
    return failures == 0 ? 0 : 1;
}
