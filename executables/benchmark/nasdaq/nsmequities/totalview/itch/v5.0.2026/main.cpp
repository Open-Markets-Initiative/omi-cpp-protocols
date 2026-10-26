// Nasdaq.NsmEquities.TotalView.Itch.v5.0.2026 benchmark.
//
// Reads a capture's datagrams into memory, then times reading them: every datagram parsed by the
// reading below, over the types and structs of the Tmp header, and every field of every message
// read through get<Field>() and folded into a checksum, so no read can be skipped. Each figure is
// the best of the passes asked for.

#include <algorithm>
#include <bit>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <map>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "cpp/binary/tmp/nasdaq/nsmequities/totalview/itch/v5.0.2026/nasdaq_nsmequities_totalview_itch_v5_0_2026.hpp"

// Nasdaq NsmEquities TotalView Itch 5.0.2026: the reading of its packets, through its Template Meta Programming header
namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

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
    if (static_cast<bool>(tmp::rule(message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_event_message_ = tmp::read<system_event_message>(data + offset, bound - offset, handler); offset += system_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& stock_directory_message_ = tmp::read<stock_directory_message>(data + offset, bound - offset, handler); offset += stock_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& stock_trading_action_message_ = tmp::read<stock_trading_action_message>(data + offset, bound - offset, handler); offset += stock_trading_action_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Y')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reg_sho_short_sale_price_test_restricted_indicator_message_ = tmp::read<reg_sho_short_sale_price_test_restricted_indicator_message>(data + offset, bound - offset, handler); offset += reg_sho_short_sale_price_test_restricted_indicator_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& market_participant_position_message_ = tmp::read<market_participant_position_message>(data + offset, bound - offset, handler); offset += market_participant_position_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'V')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& mwcb_decline_level_message_ = tmp::read<mwcb_decline_level_message>(data + offset, bound - offset, handler); offset += mwcb_decline_level_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'W')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& mwcb_status_level_message_ = tmp::read<mwcb_status_level_message>(data + offset, bound - offset, handler); offset += mwcb_status_level_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'K')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& ipo_quoting_period_update_ = tmp::read<ipo_quoting_period_update>(data + offset, bound - offset, handler); offset += ipo_quoting_period_update::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'J')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& luld_auction_collar_message_ = tmp::read<luld_auction_collar_message>(data + offset, bound - offset, handler); offset += luld_auction_collar_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'h')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& operational_halt_message_ = tmp::read<operational_halt_message>(data + offset, bound - offset, handler); offset += operational_halt_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_no_mpid_attribution_message_ = tmp::read<add_order_no_mpid_attribution_message>(data + offset, bound - offset, handler); offset += add_order_no_mpid_attribution_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'F')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_with_mpid_attribution_message_ = tmp::read<add_order_with_mpid_attribution_message>(data + offset, bound - offset, handler); offset += add_order_with_mpid_attribution_message::size;
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
    if (static_cast<bool>(tmp::rule(message_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_cancel_message_ = tmp::read<order_cancel_message>(data + offset, bound - offset, handler); offset += order_cancel_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_delete_message_ = tmp::read<order_delete_message>(data + offset, bound - offset, handler); offset += order_delete_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'U')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_replace_message_ = tmp::read<order_replace_message>(data + offset, bound - offset, handler); offset += order_replace_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& non_cross_trade_message_ = tmp::read<non_cross_trade_message>(data + offset, bound - offset, handler); offset += non_cross_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& cross_trade_message_ = tmp::read<cross_trade_message>(data + offset, bound - offset, handler); offset += cross_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& broken_trade_message_ = tmp::read<broken_trade_message>(data + offset, bound - offset, handler); offset += broken_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'I')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& net_order_imbalance_indicator_message_ = tmp::read<net_order_imbalance_indicator_message>(data + offset, bound - offset, handler); offset += net_order_imbalance_indicator_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'N')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& retail_price_improvement_indicator_message_ = tmp::read<retail_price_improvement_indicator_message>(data + offset, bound - offset, handler); offset += retail_price_improvement_indicator_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& direct_listing_with_capital_raise_price_discovery_message_ = tmp::read<direct_listing_with_capital_raise_price_discovery_message>(data + offset, bound - offset, handler); offset += direct_listing_with_capital_raise_price_discovery_message::size;
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
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_length>()))) + 2);
    tmp::require(bound, length);
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_length>()))) - 1);
        tmp::require(offset + size, bound);
        parse_payload(data + offset, size, handler, message_header_.template get<message_type>());
        offset += size;
    }
    return bound;
}

// Messages: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_messages([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_count& message_count_) {
    if (static_cast<bool>(tmp::rule(message_count_) == 0)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, heartbeat{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_count_) == 65535)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, end_of_session{});
        return offset;
    }
    {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            std::size_t count = static_cast<std::size_t>(tmp::rule(message_count_));
            while (count-- > 0) {
                offset += parse_message(data + offset, bound - offset, handler);
            }
        }
        return offset;
    }
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
    offset += parse_messages(data + offset, bound - offset, handler, packet_header_.template get<message_count>());
    return offset;
}

// Sequenced Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_sequenced_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const sequenced_message_type& sequenced_message_type_) {
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_event_message_ = tmp::read<system_event_message>(data + offset, bound - offset, handler); offset += system_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& stock_directory_message_ = tmp::read<stock_directory_message>(data + offset, bound - offset, handler); offset += stock_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& stock_trading_action_message_ = tmp::read<stock_trading_action_message>(data + offset, bound - offset, handler); offset += stock_trading_action_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'Y')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reg_sho_short_sale_price_test_restricted_indicator_message_ = tmp::read<reg_sho_short_sale_price_test_restricted_indicator_message>(data + offset, bound - offset, handler); offset += reg_sho_short_sale_price_test_restricted_indicator_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& market_participant_position_message_ = tmp::read<market_participant_position_message>(data + offset, bound - offset, handler); offset += market_participant_position_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'V')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& mwcb_decline_level_message_ = tmp::read<mwcb_decline_level_message>(data + offset, bound - offset, handler); offset += mwcb_decline_level_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'W')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& mwcb_status_level_message_ = tmp::read<mwcb_status_level_message>(data + offset, bound - offset, handler); offset += mwcb_status_level_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'K')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& ipo_quoting_period_update_ = tmp::read<ipo_quoting_period_update>(data + offset, bound - offset, handler); offset += ipo_quoting_period_update::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'J')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& luld_auction_collar_message_ = tmp::read<luld_auction_collar_message>(data + offset, bound - offset, handler); offset += luld_auction_collar_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'h')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& operational_halt_message_ = tmp::read<operational_halt_message>(data + offset, bound - offset, handler); offset += operational_halt_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_no_mpid_attribution_message_ = tmp::read<add_order_no_mpid_attribution_message>(data + offset, bound - offset, handler); offset += add_order_no_mpid_attribution_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'F')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_with_mpid_attribution_message_ = tmp::read<add_order_with_mpid_attribution_message>(data + offset, bound - offset, handler); offset += add_order_with_mpid_attribution_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'E')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_executed_message_ = tmp::read<order_executed_message>(data + offset, bound - offset, handler); offset += order_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_executed_with_price_message_ = tmp::read<order_executed_with_price_message>(data + offset, bound - offset, handler); offset += order_executed_with_price_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_cancel_message_ = tmp::read<order_cancel_message>(data + offset, bound - offset, handler); offset += order_cancel_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_delete_message_ = tmp::read<order_delete_message>(data + offset, bound - offset, handler); offset += order_delete_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'U')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_replace_message_ = tmp::read<order_replace_message>(data + offset, bound - offset, handler); offset += order_replace_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& non_cross_trade_message_ = tmp::read<non_cross_trade_message>(data + offset, bound - offset, handler); offset += non_cross_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'Q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& cross_trade_message_ = tmp::read<cross_trade_message>(data + offset, bound - offset, handler); offset += cross_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& broken_trade_message_ = tmp::read<broken_trade_message>(data + offset, bound - offset, handler); offset += broken_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'I')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& net_order_imbalance_indicator_message_ = tmp::read<net_order_imbalance_indicator_message>(data + offset, bound - offset, handler); offset += net_order_imbalance_indicator_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'N')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& retail_price_improvement_indicator_message_ = tmp::read<retail_price_improvement_indicator_message>(data + offset, bound - offset, handler); offset += retail_price_improvement_indicator_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(sequenced_message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& direct_listing_with_capital_raise_price_discovery_message_ = tmp::read<direct_listing_with_capital_raise_price_discovery_message>(data + offset, bound - offset, handler); offset += direct_listing_with_capital_raise_price_discovery_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Sequenced Data Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_sequenced_data_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const packet_length& packet_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& sequenced_data_packet_section_1_ = tmp::read<sequenced_data_packet_section_1>(data + offset, bound - offset, handler); offset += sequenced_data_packet_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(packet_length_))) - 2);
        tmp::require(offset + size, bound);
        parse_sequenced_message(data + offset, size, handler, sequenced_data_packet_section_1_.template get<sequenced_message_type>());
        offset += size;
    }
    return offset;
}

// Debug Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_debug_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const packet_length& packet_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(packet_length_))) - 1);
        tmp::require(offset + size, bound);
        tmp::call(handler, debug_text{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Server Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_server_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const server_packet_type& server_packet_type_, const packet_length& packet_length_) {
    if (static_cast<bool>(tmp::rule(server_packet_type_) == '+')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_debug_packet(data + offset, bound - offset, handler, packet_length_);
        tmp::call(handler, debug_packet{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(server_packet_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& login_accepted_packet_ = tmp::read<login_accepted_packet>(data + offset, bound - offset, handler); offset += login_accepted_packet::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(server_packet_type_) == 'J')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& login_rejected_packet_ = tmp::read<login_rejected_packet>(data + offset, bound - offset, handler); offset += login_rejected_packet::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(server_packet_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(packet_length_))) - 1);
            tmp::require(offset + size, bound);
            parse_sequenced_data_packet(data + offset, size, handler, packet_length_);
            offset += size;
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(server_packet_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, server_heartbeat_packet{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(server_packet_type_) == 'Z')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, end_of_session_packet{});
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Server Soup Bin Tcp Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_server_soup_bin_tcp_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& server_packet_header_ = tmp::read<server_packet_header>(data + offset, bound - offset, handler); offset += server_packet_header::size;
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(server_packet_header_.template get<packet_length>()))) + 2);
    tmp::require(bound, length);
    offset += parse_server_payload(data + offset, bound - offset, handler, server_packet_header_.template get<server_packet_type>(), server_packet_header_.template get<packet_length>());
    return bound;
}

// Server Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_server_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    while (offset < bound) {
        if (bound - offset < 0 + packet_length::size) { return offset; }
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(tmp::at<packet_length>(data + offset + 0)))) + 2);
        if (bound - offset < size) { return offset; }
        parse_server_soup_bin_tcp_packet(data + offset, size, handler);
        offset += size;
    }
    return offset;
}

// Unsequenced Data Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_unsequenced_data_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const packet_length& packet_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& unsequenced_data_packet_section_1_ = tmp::read<unsequenced_data_packet_section_1>(data + offset, bound - offset, handler); offset += unsequenced_data_packet_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(packet_length_))) - 2);
        tmp::require(offset + size, bound);
        tmp::call(handler, unsequenced_message{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Client Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_client_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const client_packet_type& client_packet_type_, const packet_length& packet_length_) {
    if (static_cast<bool>(tmp::rule(client_packet_type_) == '+')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_debug_packet(data + offset, bound - offset, handler, packet_length_);
        tmp::call(handler, debug_packet{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(client_packet_type_) == 'L')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& login_request_packet_ = tmp::read<login_request_packet>(data + offset, bound - offset, handler); offset += login_request_packet::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(client_packet_type_) == 'U')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(packet_length_))) - 1);
            tmp::require(offset + size, bound);
            parse_unsequenced_data_packet(data + offset, size, handler, packet_length_);
            tmp::call(handler, unsequenced_data_packet{});
            offset += size;
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(client_packet_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, client_heartbeat_packet{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(client_packet_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, logout_request_packet{});
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Client Soup Bin Tcp Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_client_soup_bin_tcp_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& client_packet_header_ = tmp::read<client_packet_header>(data + offset, bound - offset, handler); offset += client_packet_header::size;
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(client_packet_header_.template get<packet_length>()))) + 2);
    tmp::require(bound, length);
    offset += parse_client_payload(data + offset, bound - offset, handler, client_packet_header_.template get<client_packet_type>(), client_packet_header_.template get<packet_length>());
    return bound;
}

// Client Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_client_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    while (offset < bound) {
        if (bound - offset < 0 + packet_length::size) { return offset; }
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(tmp::at<packet_length>(data + offset + 0)))) + 2);
        if (bound - offset < size) { return offset; }
        parse_client_soup_bin_tcp_packet(data + offset, size, handler);
        offset += size;
    }
    return offset;
}


} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v5_0_2026;

namespace {

using clock = std::chrono::steady_clock;

// A value folded into the checksum, whatever its type
template <typename T>
std::uint64_t digest(const T& value) {
    if constexpr (std::is_enum_v<T>) { return static_cast<std::uint64_t>(std::to_underlying(value)); }
    else if constexpr (std::is_same_v<T, bool>) { return value ? 1u : 0u; }
    else if constexpr (std::is_integral_v<T>) { return static_cast<std::uint64_t>(value); }
    else if constexpr (std::is_floating_point_v<T>) { return std::bit_cast<std::uint64_t>(static_cast<double>(value)); }
    else if constexpr (std::is_same_v<T, std::string_view>) { return value.size() + (value.empty() ? 0u : static_cast<unsigned char>(value.front())); }
    else { return value.size() + (value.empty() ? 0u : std::to_integer<std::uint64_t>(value.front())); }
}

template <typename Struct, typename... Fields>
std::uint64_t fold(const Struct& value, protocol::tmp::list<Fields...>);

// A field read through its value; a struct within a struct read field by field
template <typename Field>
std::uint64_t read(const Field& field) {
    if constexpr (requires { typename Field::fields; }) { return fold(field, typename Field::fields{}); }
    else { return digest(field.value()); }
}

// Every field of a struct, each asked for by its type
template <typename Struct, typename... Fields>
std::uint64_t fold(const Struct& value, protocol::tmp::list<Fields...>) {
    return (std::uint64_t{ 0 } + ... + read(value.template get<Fields>()));
}

// Every field of a message, or nothing for a message of no fields
template <typename Message>
std::uint64_t every(const Message& message) {
    if constexpr (requires { typename Message::fields; }) { return fold(message, typename Message::fields{}); }
    else { return 0; }
}

// Is a type the reader hands over a message, not a header or a field?
template <typename T>
constexpr bool is_message = requires { requires T::is_message; };

// Is a type the reader hands over a section of a message no struct lies over?
template <typename T>
constexpr bool is_section = requires { requires T::is_section; };

// The whole read: every message of every datagram, every field of it. A message no struct lies
// over is handed over a section at a time, then announced: its sections' fields are read as they
// come, and the message is counted once.
struct Reading {
    std::uint64_t checksum = 0;
    std::size_t messages = 0;

    template <typename T>
    void operator()(const T& value) {
        if constexpr (is_message<T>) {
            ++messages;
            checksum += every(value);
        }
        else if constexpr (is_section<T>) {
            checksum += every(value);
        }
    }
};

// The messages of one type: how many, where those with fields lie, and how to read every field of them
struct Gathered {
    std::size_t count = 0;
    std::vector<const std::byte*> at;
    std::uint64_t (*run)(const std::vector<const std::byte*>&) = nullptr;
};

template <typename Message>
std::uint64_t run(const std::vector<const std::byte*>& at) {
    std::uint64_t checksum = 0;
    for (const std::byte* bytes : at) { checksum += every(*reinterpret_cast<const Message*>(bytes)); }
    return checksum;
}

// Gathers every message by its type, untimed. A message no struct lies over - one the reader parses
// field by field and then announces - has no bytes of its own to gather; it is only counted.
struct Census {
    std::map<std::string_view, Gathered> types;

    template <typename T>
    void operator()(const T& value) {
        if constexpr (is_message<T>) {
            auto& gathered = types[T::name];
            ++gathered.count;
            if constexpr (requires { typename T::fields; }) {
                gathered.at.push_back(reinterpret_cast<const std::byte*>(&value));
                gathered.run = &run<T>;
            }
        }
    }
};

// The best of the passes, in nanoseconds
template <typename Pass>
double best(int passes, Pass pass) {
    double fastest = 0;
    for (int index = 0; index < passes; ++index) {
        const auto start = clock::now();
        pass();
        const double took = std::chrono::duration<double, std::nano>(clock::now() - start).count();
        if (index == 0 || took < fastest) { fastest = took; }
    }
    return fastest;
}

}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: %s <capture.pcap> [passes]\n", argv[0]);
        return 2;
    }

    const int passes = argc > 2 ? std::max(1, std::atoi(argv[2])) : 10;

    // the capture's datagrams, held in memory so only the reading is timed
    std::vector<std::byte> bytes;
    std::vector<std::pair<std::size_t, std::size_t>> datagrams;
    {
        std::vector<std::pair<std::string, std::int64_t>> sources;
        sources.emplace_back(argv[1], 0);
        packet::PcapIterator captures(sources);

        while (captures.advance()) {
            const packet::Frame frame(captures.data(), captures.length());
            if (!frame.valid() || !frame.is_udp()) { continue; }
            datagrams.emplace_back(bytes.size(), frame.payload_len);
            bytes.insert(bytes.end(), frame.payload, frame.payload + frame.payload_len);
        }
    }

    // untimed: which datagrams parse, and every message gathered by its type
    Census census;
    std::vector<std::pair<std::size_t, std::size_t>> read;
    std::size_t failed = 0;
    std::size_t length = 0;

    for (const auto& [offset, size] : datagrams) {
        try {
            protocol::parse_packet(bytes.data() + offset, size, census);
            read.emplace_back(offset, size);
            length += size;
        } catch (const std::exception&) {
            ++failed;
        }
    }

    // timed: the whole read
    Reading reading;
    const double whole = best(passes, [&] {
        reading = Reading{};
        for (const auto& [offset, size] : read) { protocol::parse_packet(bytes.data() + offset, size, reading); }
    });

    std::printf("Nasdaq.NsmEquities.TotalView.Itch.v5.0.2026\n");
    std::printf("  %zu datagrams read, %zu did not parse; %zu bytes, %zu messages\n", read.size(), failed, length, reading.messages);
    std::printf("  whole read, best of %d: %.3f ms, %.1f ns/datagram, %.1f ns/message, %.2f M messages/s, %.1f MB/s\n",
        passes, whole / 1e6,
        read.empty() ? 0.0 : whole / static_cast<double>(read.size()),
        reading.messages == 0 ? 0.0 : whole / static_cast<double>(reading.messages),
        whole == 0 ? 0.0 : static_cast<double>(reading.messages) / whole * 1e3,
        whole == 0 ? 0.0 : static_cast<double>(length) / whole * 1e3);
    std::printf("  checksum %016llx\n", static_cast<unsigned long long>(reading.checksum));

    // timed: each message type's field reads on their own
    std::printf("  every field of each message type, best of %d:\n", passes);
    for (const auto& [name, gathered] : census.types) {
        if (gathered.run == nullptr) {
            std::printf("    %-48.*s %10zu  (read field by field in the whole read)\n",
                static_cast<int>(name.size()), name.data(), gathered.count);
            continue;
        }

        std::uint64_t checksum = 0;
        const double took = best(passes, [&] { checksum = gathered.run(gathered.at); });
        std::printf("    %-48.*s %10zu  %8.2f ns/message  (checksum %016llx)\n",
            static_cast<int>(name.size()), name.data(), gathered.count,
            gathered.at.empty() ? 0.0 : took / static_cast<double>(gathered.at.size()),
            static_cast<unsigned long long>(checksum));
    }

    return failed == 0 ? 0 : 1;
}
