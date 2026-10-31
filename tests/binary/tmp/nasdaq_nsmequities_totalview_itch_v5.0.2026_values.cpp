// Nasdaq.NsmEquities.TotalView.Itch.v5.0.2026 canonical values, through the Tmp header: every value the Tmp reading hands
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

// File Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_file_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
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

// File Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_file_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& message_header_ = tmp::read<message_header>(data + offset, bound - offset, handler); offset += message_header::size;
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_length>()))) + 2);
    tmp::require(bound, length);
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_length>()))) - 1);
        tmp::require(offset + size, bound);
        parse_file_payload(data + offset, size, handler, message_header_.template get<message_type>());
        offset += size;
    }
    return bound;
}

// File: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_file([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    while (offset < bound) {
        if (bound - offset < 0 + message_length::size) { return offset; }
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(tmp::at<message_length>(data + offset + 0)))) + 2);
        if (bound - offset < size) { return offset; }
        parse_file_message(data + offset, size, handler);
        offset += size;
    }
    return offset;
}

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

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::session>(); }) { values["packet.packetheader.session"] = canonical::text(std::string(header.template get<protocol::session>().value()), '\0', false); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { values["packet.packetheader.sequencenumber"] = canonical::number(header.template get<protocol::sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { values["packet.packetheader.messagecount"] = canonical::number(header.template get<protocol::message_count>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.messages.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::message_length>(); }) { values[entry + ".messageheader.messagelength"] = canonical::number(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(header.template get<protocol::message_type>().value())); }
    }

    void operator()(const protocol::system_event_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.systemeventmessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.systemeventmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::event_code>(); }) { values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message.template get<protocol::event_code>().value()), ' ', false); }
    }

    void operator()(const protocol::stock_directory_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.stockdirectorymessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.stockdirectorymessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.stockdirectorymessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.stockdirectorymessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::market_category>(); }) { values[entry + ".payload.stockdirectorymessage.marketcategory"] = canonical::text(canonical::character(message.template get<protocol::market_category>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::financial_status_indicator>(); }) { values[entry + ".payload.stockdirectorymessage.financialstatusindicator"] = canonical::text(canonical::character(message.template get<protocol::financial_status_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::round_lot_size>(); }) { values[entry + ".payload.stockdirectorymessage.roundlotsize"] = canonical::number(message.template get<protocol::round_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::round_lots_only>(); }) { values[entry + ".payload.stockdirectorymessage.roundlotsonly"] = canonical::text(canonical::character(message.template get<protocol::round_lots_only>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_classification>(); }) { values[entry + ".payload.stockdirectorymessage.issueclassification"] = canonical::text(canonical::character(message.template get<protocol::issue_classification>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_sub_type>(); }) { values[entry + ".payload.stockdirectorymessage.issuesubtype"] = canonical::text(std::string(message.template get<protocol::issue_sub_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::authenticity>(); }) { values[entry + ".payload.stockdirectorymessage.authenticity"] = canonical::text(canonical::character(message.template get<protocol::authenticity>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::short_sale_threshold_indicator>(); }) { values[entry + ".payload.stockdirectorymessage.shortsalethresholdindicator"] = canonical::text(canonical::character(message.template get<protocol::short_sale_threshold_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::ipo_flag>(); }) { values[entry + ".payload.stockdirectorymessage.ipoflag"] = canonical::text(canonical::character(message.template get<protocol::ipo_flag>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::luld_reference_price_tier>(); }) { values[entry + ".payload.stockdirectorymessage.luldreferencepricetier"] = canonical::text(canonical::character(message.template get<protocol::luld_reference_price_tier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::etp_flag>(); }) { values[entry + ".payload.stockdirectorymessage.etpflag"] = canonical::text(canonical::character(message.template get<protocol::etp_flag>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::etp_leverage_factor>(); }) { values[entry + ".payload.stockdirectorymessage.etpleveragefactor"] = canonical::number(message.template get<protocol::etp_leverage_factor>().value()); }
        if constexpr (requires { message.template get<protocol::inverse_indicator>(); }) { values[entry + ".payload.stockdirectorymessage.inverseindicator"] = canonical::text(canonical::character(message.template get<protocol::inverse_indicator>().value()), ' ', false); }
    }

    void operator()(const protocol::stock_trading_action_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.stocktradingactionmessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.stocktradingactionmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.stocktradingactionmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.stocktradingactionmessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trading_state>(); }) { values[entry + ".payload.stocktradingactionmessage.tradingstate"] = canonical::text(canonical::character(message.template get<protocol::trading_state>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reserved>(); }) { values[entry + ".payload.stocktradingactionmessage.reserved"] = canonical::text(canonical::character(message.template get<protocol::reserved>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reason_code>(); }) { values[entry + ".payload.stocktradingactionmessage.reasoncode"] = canonical::text(std::string(message.template get<protocol::reason_code>().value()), ' ', false); }
    }

    void operator()(const protocol::reg_sho_short_sale_price_test_restricted_indicator_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.regshoshortsalepricetestrestrictedindicatormessage";
        if constexpr (requires { message.template get<protocol::locate_code>(); }) { values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.locatecode"] = canonical::number(message.template get<protocol::locate_code>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reg_sho_action>(); }) { values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.regshoaction"] = canonical::text(canonical::character(message.template get<protocol::reg_sho_action>().value()), ' ', false); }
    }

    void operator()(const protocol::market_participant_position_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.marketparticipantpositionmessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.marketparticipantpositionmessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.marketparticipantpositionmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.marketparticipantpositionmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::mpid>(); }) { values[entry + ".payload.marketparticipantpositionmessage.mpid"] = canonical::text(std::string(message.template get<protocol::mpid>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.marketparticipantpositionmessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::primary_market_maker>(); }) { values[entry + ".payload.marketparticipantpositionmessage.primarymarketmaker"] = canonical::text(canonical::character(message.template get<protocol::primary_market_maker>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::market_maker_mode>(); }) { values[entry + ".payload.marketparticipantpositionmessage.marketmakermode"] = canonical::text(canonical::character(message.template get<protocol::market_maker_mode>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::market_participant_state>(); }) { values[entry + ".payload.marketparticipantpositionmessage.marketparticipantstate"] = canonical::text(canonical::character(message.template get<protocol::market_participant_state>().value()), ' ', false); }
    }

    void operator()(const protocol::mwcb_decline_level_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.mwcbdeclinelevelmessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::level_1>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.level1"] = canonical::scaled(message.template get<protocol::level_1>().value(), -8); }
        if constexpr (requires { message.template get<protocol::level_2>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.level2"] = canonical::scaled(message.template get<protocol::level_2>().value(), -8); }
        if constexpr (requires { message.template get<protocol::level_3>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.level3"] = canonical::scaled(message.template get<protocol::level_3>().value(), -8); }
    }

    void operator()(const protocol::mwcb_status_level_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.mwcbstatuslevelmessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.mwcbstatuslevelmessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.mwcbstatuslevelmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.mwcbstatuslevelmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::breached_level>(); }) { values[entry + ".payload.mwcbstatuslevelmessage.breachedlevel"] = canonical::text(canonical::character(message.template get<protocol::breached_level>().value()), ' ', false); }
    }

    void operator()(const protocol::ipo_quoting_period_update& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.ipoquotingperiodupdate";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.ipoquotingperiodupdate.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.ipoquotingperiodupdate.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.ipoquotingperiodupdate.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.ipoquotingperiodupdate.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::ipo_quotation_release_time>(); }) { values[entry + ".payload.ipoquotingperiodupdate.ipoquotationreleasetime"] = canonical::number(message.template get<protocol::ipo_quotation_release_time>().value()); }
        if constexpr (requires { message.template get<protocol::ipo_quotation_release_qualifier>(); }) { values[entry + ".payload.ipoquotingperiodupdate.ipoquotationreleasequalifier"] = canonical::text(canonical::character(message.template get<protocol::ipo_quotation_release_qualifier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::ipo_price>(); }) { values[entry + ".payload.ipoquotingperiodupdate.ipoprice"] = canonical::scaled(message.template get<protocol::ipo_price>().value(), -4); }
    }

    void operator()(const protocol::luld_auction_collar_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.luldauctioncollarmessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.luldauctioncollarmessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.luldauctioncollarmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.luldauctioncollarmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.luldauctioncollarmessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::auction_collar_reference_price>(); }) { values[entry + ".payload.luldauctioncollarmessage.auctioncollarreferenceprice"] = canonical::scaled(message.template get<protocol::auction_collar_reference_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::upper_auction_collar_price>(); }) { values[entry + ".payload.luldauctioncollarmessage.upperauctioncollarprice"] = canonical::scaled(message.template get<protocol::upper_auction_collar_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::lower_auction_collar_price>(); }) { values[entry + ".payload.luldauctioncollarmessage.lowerauctioncollarprice"] = canonical::scaled(message.template get<protocol::lower_auction_collar_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::auction_collar_extension>(); }) { values[entry + ".payload.luldauctioncollarmessage.auctioncollarextension"] = canonical::number(message.template get<protocol::auction_collar_extension>().value()); }
    }

    void operator()(const protocol::operational_halt_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.operationalhaltmessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.operationalhaltmessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.operationalhaltmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.operationalhaltmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.operationalhaltmessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::market_code>(); }) { values[entry + ".payload.operationalhaltmessage.marketcode"] = canonical::text(canonical::character(message.template get<protocol::market_code>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::operational_halt_action>(); }) { values[entry + ".payload.operationalhaltmessage.operationalhaltaction"] = canonical::text(canonical::character(message.template get<protocol::operational_halt_action>().value()), ' ', false); }
    }

    void operator()(const protocol::add_order_no_mpid_attribution_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.addordernompidattributionmessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.addordernompidattributionmessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.addordernompidattributionmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.addordernompidattributionmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { values[entry + ".payload.addordernompidattributionmessage.orderreferencenumber"] = canonical::number(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::buy_sell_indicator>(); }) { values[entry + ".payload.addordernompidattributionmessage.buysellindicator"] = canonical::text(canonical::character(message.template get<protocol::buy_sell_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::shares>(); }) { values[entry + ".payload.addordernompidattributionmessage.shares"] = canonical::number(message.template get<protocol::shares>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.addordernompidattributionmessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.addordernompidattributionmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -4); }
    }

    void operator()(const protocol::add_order_with_mpid_attribution_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.addorderwithmpidattributionmessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.addorderwithmpidattributionmessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.addorderwithmpidattributionmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.addorderwithmpidattributionmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { values[entry + ".payload.addorderwithmpidattributionmessage.orderreferencenumber"] = canonical::number(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::buy_sell_indicator>(); }) { values[entry + ".payload.addorderwithmpidattributionmessage.buysellindicator"] = canonical::text(canonical::character(message.template get<protocol::buy_sell_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::shares>(); }) { values[entry + ".payload.addorderwithmpidattributionmessage.shares"] = canonical::number(message.template get<protocol::shares>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.addorderwithmpidattributionmessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.addorderwithmpidattributionmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::attribution>(); }) { values[entry + ".payload.addorderwithmpidattributionmessage.attribution"] = canonical::text(std::string(message.template get<protocol::attribution>().value()), ' ', false); }
    }

    void operator()(const protocol::order_executed_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.orderexecutedmessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.orderexecutedmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.orderexecutedmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { values[entry + ".payload.orderexecutedmessage.orderreferencenumber"] = canonical::number(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::executed_shares>(); }) { values[entry + ".payload.orderexecutedmessage.executedshares"] = canonical::number(message.template get<protocol::executed_shares>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { values[entry + ".payload.orderexecutedmessage.matchnumber"] = canonical::number(message.template get<protocol::match_number>().value()); }
    }

    void operator()(const protocol::order_executed_with_price_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedwithpricemessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.orderreferencenumber"] = canonical::number(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::executed_shares>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.executedshares"] = canonical::number(message.template get<protocol::executed_shares>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.matchnumber"] = canonical::number(message.template get<protocol::match_number>().value()); }
        if constexpr (requires { message.template get<protocol::printable>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.printable"] = canonical::text(canonical::character(message.template get<protocol::printable>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::execution_price>(); }) { values[entry + ".payload.orderexecutedwithpricemessage.executionprice"] = canonical::scaled(message.template get<protocol::execution_price>().value(), -4); }
    }

    void operator()(const protocol::order_cancel_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.ordercancelmessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.ordercancelmessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.ordercancelmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.ordercancelmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { values[entry + ".payload.ordercancelmessage.orderreferencenumber"] = canonical::number(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::canceled_shares>(); }) { values[entry + ".payload.ordercancelmessage.canceledshares"] = canonical::number(message.template get<protocol::canceled_shares>().value()); }
    }

    void operator()(const protocol::order_delete_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderdeletemessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.orderdeletemessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.orderdeletemessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.orderdeletemessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { values[entry + ".payload.orderdeletemessage.orderreferencenumber"] = canonical::number(message.template get<protocol::order_reference_number>().value()); }
    }

    void operator()(const protocol::order_replace_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderreplacemessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.orderreplacemessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.orderreplacemessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.orderreplacemessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::original_order_reference_number>(); }) { values[entry + ".payload.orderreplacemessage.originalorderreferencenumber"] = canonical::number(message.template get<protocol::original_order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::new_order_reference_number>(); }) { values[entry + ".payload.orderreplacemessage.neworderreferencenumber"] = canonical::number(message.template get<protocol::new_order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::shares>(); }) { values[entry + ".payload.orderreplacemessage.shares"] = canonical::number(message.template get<protocol::shares>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.orderreplacemessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -4); }
    }

    void operator()(const protocol::non_cross_trade_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.noncrosstrademessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.noncrosstrademessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.noncrosstrademessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.noncrosstrademessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { values[entry + ".payload.noncrosstrademessage.orderreferencenumber"] = canonical::number(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::buy_sell_indicator>(); }) { values[entry + ".payload.noncrosstrademessage.buysellindicator"] = canonical::text(canonical::character(message.template get<protocol::buy_sell_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::shares>(); }) { values[entry + ".payload.noncrosstrademessage.shares"] = canonical::number(message.template get<protocol::shares>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.noncrosstrademessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.noncrosstrademessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { values[entry + ".payload.noncrosstrademessage.matchnumber"] = canonical::number(message.template get<protocol::match_number>().value()); }
    }

    void operator()(const protocol::cross_trade_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.crosstrademessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.crosstrademessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.crosstrademessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.crosstrademessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::cross_shares>(); }) { values[entry + ".payload.crosstrademessage.crossshares"] = canonical::number(message.template get<protocol::cross_shares>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.crosstrademessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::cross_price>(); }) { values[entry + ".payload.crosstrademessage.crossprice"] = canonical::scaled(message.template get<protocol::cross_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { values[entry + ".payload.crosstrademessage.matchnumber"] = canonical::number(message.template get<protocol::match_number>().value()); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { values[entry + ".payload.crosstrademessage.crosstype"] = canonical::text(canonical::character(message.template get<protocol::cross_type>().value()), ' ', false); }
    }

    void operator()(const protocol::broken_trade_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.brokentrademessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.brokentrademessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.brokentrademessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.brokentrademessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { values[entry + ".payload.brokentrademessage.matchnumber"] = canonical::number(message.template get<protocol::match_number>().value()); }
    }

    void operator()(const protocol::net_order_imbalance_indicator_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.netorderimbalanceindicatormessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.netorderimbalanceindicatormessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.netorderimbalanceindicatormessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.netorderimbalanceindicatormessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::paired_shares>(); }) { values[entry + ".payload.netorderimbalanceindicatormessage.pairedshares"] = canonical::number(message.template get<protocol::paired_shares>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_shares>(); }) { values[entry + ".payload.netorderimbalanceindicatormessage.imbalanceshares"] = canonical::number(message.template get<protocol::imbalance_shares>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_direction>(); }) { values[entry + ".payload.netorderimbalanceindicatormessage.imbalancedirection"] = canonical::text(canonical::character(message.template get<protocol::imbalance_direction>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.netorderimbalanceindicatormessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::far_price>(); }) { values[entry + ".payload.netorderimbalanceindicatormessage.farprice"] = canonical::scaled(message.template get<protocol::far_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::near_price>(); }) { values[entry + ".payload.netorderimbalanceindicatormessage.nearprice"] = canonical::scaled(message.template get<protocol::near_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::current_reference_price>(); }) { values[entry + ".payload.netorderimbalanceindicatormessage.currentreferenceprice"] = canonical::scaled(message.template get<protocol::current_reference_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { values[entry + ".payload.netorderimbalanceindicatormessage.crosstype"] = canonical::text(canonical::character(message.template get<protocol::cross_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price_variation_indicator>(); }) { values[entry + ".payload.netorderimbalanceindicatormessage.pricevariationindicator"] = canonical::text(canonical::character(message.template get<protocol::price_variation_indicator>().value()), ' ', false); }
    }

    void operator()(const protocol::retail_price_improvement_indicator_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.retailpriceimprovementindicatormessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.retailpriceimprovementindicatormessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.retailpriceimprovementindicatormessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.retailpriceimprovementindicatormessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.retailpriceimprovementindicatormessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::interest_flag>(); }) { values[entry + ".payload.retailpriceimprovementindicatormessage.interestflag"] = canonical::text(canonical::character(message.template get<protocol::interest_flag>().value()), ' ', false); }
    }

    void operator()(const protocol::direct_listing_with_capital_raise_price_discovery_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.directlistingwithcapitalraisepricediscoverymessage";
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.stocklocate"] = canonical::number(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::open_eligibility_status>(); }) { values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.openeligibilitystatus"] = canonical::text(canonical::character(message.template get<protocol::open_eligibility_status>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::minimum_allowable_price>(); }) { values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.minimumallowableprice"] = canonical::scaled(message.template get<protocol::minimum_allowable_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::maximum_allowable_price>(); }) { values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.maximumallowableprice"] = canonical::scaled(message.template get<protocol::maximum_allowable_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::near_execution_price>(); }) { values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.nearexecutionprice"] = canonical::scaled(message.template get<protocol::near_execution_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::near_execution_time>(); }) { values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.nearexecutiontime"] = canonical::number(message.template get<protocol::near_execution_time>().value()); }
        if constexpr (requires { message.template get<protocol::lower_price_range_collar>(); }) { values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.lowerpricerangecollar"] = canonical::scaled(message.template get<protocol::lower_price_range_collar>().value(), -4); }
        if constexpr (requires { message.template get<protocol::upper_price_range_collar>(); }) { values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.upperpricerangecollar"] = canonical::scaled(message.template get<protocol::upper_price_range_collar>().value(), -4); }
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
    std::printf("== Nasdaq.NsmEquities.TotalView.Itch.v5.0.2026 (tmp values)\n");
    int failures = 0;
    failures += check("AddOrderNoMpidAttributionMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/AddOrderNoMpidAttributionMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/AddOrderNoMpidAttributionMessage.values");
    failures += check("AddOrderWithMpidAttributionMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/AddOrderWithMpidAttributionMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/AddOrderWithMpidAttributionMessage.values");
    failures += check("CrossTradeMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/CrossTradeMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/CrossTradeMessage.values");
    failures += check("LuldAuctionCollarMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/LuldAuctionCollarMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/LuldAuctionCollarMessage.values");
    failures += check("MarketParticipantPositionMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/MarketParticipantPositionMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/MarketParticipantPositionMessage.values");
    failures += check("NetOrderImbalanceIndicatorMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/NetOrderImbalanceIndicatorMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/NetOrderImbalanceIndicatorMessage.values");
    failures += check("NonCrossTradeMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/NonCrossTradeMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/NonCrossTradeMessage.values");
    failures += check("OrderCancelMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/OrderCancelMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/OrderCancelMessage.values");
    failures += check("OrderDeleteMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/OrderDeleteMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/OrderDeleteMessage.values");
    failures += check("OrderExecutedMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/OrderExecutedMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/OrderExecutedMessage.values");
    failures += check("OrderExecutedWithPriceMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/OrderExecutedWithPriceMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/OrderExecutedWithPriceMessage.values");
    failures += check("OrderReplaceMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/OrderReplaceMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/OrderReplaceMessage.values");
    failures += check("RegShoShortSalePriceTestRestrictedIndicatorMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/RegShoShortSalePriceTestRestrictedIndicatorMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/RegShoShortSalePriceTestRestrictedIndicatorMessage.values");
    failures += check("StockDirectoryMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/StockDirectoryMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/StockDirectoryMessage.values");
    failures += check("StockTradingActionMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/StockTradingActionMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/StockTradingActionMessage.values");
    failures += check("SystemEventMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2026/SystemEventMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2026/SystemEventMessage.values");
    return failures == 0 ? 0 : 1;
}
