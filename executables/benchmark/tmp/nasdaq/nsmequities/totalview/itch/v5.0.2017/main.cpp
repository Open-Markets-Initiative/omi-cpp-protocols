// Nasdaq.NsmEquities.TotalView.Itch.v5.0.2017 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/totalview/itch/v5.0.2017.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/nasdaq/nsmequities/totalview/itch/v5.0.2017/nasdaq_nsmequities_totalview_itch_v5_0_2017.hpp"

// Nasdaq NsmEquities TotalView Itch 5.0.2017: the reading of its packets, through its Template Meta Programming header
namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

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
        [[maybe_unused]] const auto& retail_interest_message_ = tmp::read<retail_interest_message>(data + offset, bound - offset, handler); offset += retail_interest_message::size;
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
        [[maybe_unused]] const auto& retail_interest_message_ = tmp::read<retail_interest_message>(data + offset, bound - offset, handler); offset += retail_interest_message::size;
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
        [[maybe_unused]] const auto& retail_interest_message_ = tmp::read<retail_interest_message>(data + offset, bound - offset, handler); offset += retail_interest_message::size;
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
        tmp::call(handler, server_heartbeat{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(server_packet_type_) == 'Z')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, end_of_session{});
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
        tmp::call(handler, client_heartbeat{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(client_packet_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, logout_request{});
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


} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v5_0_2017;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::session>(); }) { checksum += bench::digest(header.template get<protocol::session>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { checksum += bench::digest(header.template get<protocol::sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { checksum += bench::digest(header.template get<protocol::message_count>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::message_length>(); }) { checksum += bench::digest(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { checksum += bench::digest(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::system_event_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::event_code>(); }) { checksum += bench::digest(message.template get<protocol::event_code>().value()); }
    }

    void operator()(const protocol::stock_directory_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::market_category>(); }) { checksum += bench::digest(message.template get<protocol::market_category>().value()); }
        if constexpr (requires { message.template get<protocol::financial_status_indicator>(); }) { checksum += bench::digest(message.template get<protocol::financial_status_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::round_lot_size>(); }) { checksum += bench::digest(message.template get<protocol::round_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::round_lots_only>(); }) { checksum += bench::digest(message.template get<protocol::round_lots_only>().value()); }
        if constexpr (requires { message.template get<protocol::issue_classification>(); }) { checksum += bench::digest(message.template get<protocol::issue_classification>().value()); }
        if constexpr (requires { message.template get<protocol::issue_sub_type>(); }) { checksum += bench::digest(message.template get<protocol::issue_sub_type>().value()); }
        if constexpr (requires { message.template get<protocol::authenticity>(); }) { checksum += bench::digest(message.template get<protocol::authenticity>().value()); }
        if constexpr (requires { message.template get<protocol::short_sale_threshold_indicator>(); }) { checksum += bench::digest(message.template get<protocol::short_sale_threshold_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::ipo_flag>(); }) { checksum += bench::digest(message.template get<protocol::ipo_flag>().value()); }
        if constexpr (requires { message.template get<protocol::luld_reference_price_tier>(); }) { checksum += bench::digest(message.template get<protocol::luld_reference_price_tier>().value()); }
        if constexpr (requires { message.template get<protocol::etp_flag>(); }) { checksum += bench::digest(message.template get<protocol::etp_flag>().value()); }
        if constexpr (requires { message.template get<protocol::etp_leverage_factor>(); }) { checksum += bench::digest(message.template get<protocol::etp_leverage_factor>().value()); }
        if constexpr (requires { message.template get<protocol::inverse_indicator>(); }) { checksum += bench::digest(message.template get<protocol::inverse_indicator>().value()); }
    }

    void operator()(const protocol::stock_trading_action_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::trading_state>(); }) { checksum += bench::digest(message.template get<protocol::trading_state>().value()); }
        if constexpr (requires { message.template get<protocol::reserved>(); }) { checksum += bench::digest(message.template get<protocol::reserved>().value()); }
        if constexpr (requires { message.template get<protocol::reason_code>(); }) { checksum += bench::digest(message.template get<protocol::reason_code>().value()); }
    }

    void operator()(const protocol::reg_sho_short_sale_price_test_restricted_indicator_message& message) {
        if constexpr (requires { message.template get<protocol::locate_code>(); }) { checksum += bench::digest(message.template get<protocol::locate_code>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::reg_sho_action>(); }) { checksum += bench::digest(message.template get<protocol::reg_sho_action>().value()); }
    }

    void operator()(const protocol::market_participant_position_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::mpid>(); }) { checksum += bench::digest(message.template get<protocol::mpid>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::primary_market_maker>(); }) { checksum += bench::digest(message.template get<protocol::primary_market_maker>().value()); }
        if constexpr (requires { message.template get<protocol::market_maker_mode>(); }) { checksum += bench::digest(message.template get<protocol::market_maker_mode>().value()); }
        if constexpr (requires { message.template get<protocol::market_participant_state>(); }) { checksum += bench::digest(message.template get<protocol::market_participant_state>().value()); }
    }

    void operator()(const protocol::mwcb_decline_level_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::level_1>(); }) { checksum += bench::digest(message.template get<protocol::level_1>().value()); }
        if constexpr (requires { message.template get<protocol::level_2>(); }) { checksum += bench::digest(message.template get<protocol::level_2>().value()); }
        if constexpr (requires { message.template get<protocol::level_3>(); }) { checksum += bench::digest(message.template get<protocol::level_3>().value()); }
    }

    void operator()(const protocol::mwcb_status_level_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::breached_level>(); }) { checksum += bench::digest(message.template get<protocol::breached_level>().value()); }
    }

    void operator()(const protocol::ipo_quoting_period_update& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::ipo_quotation_release_time>(); }) { checksum += bench::digest(message.template get<protocol::ipo_quotation_release_time>().value()); }
        if constexpr (requires { message.template get<protocol::ipo_quotation_release_qualifier>(); }) { checksum += bench::digest(message.template get<protocol::ipo_quotation_release_qualifier>().value()); }
        if constexpr (requires { message.template get<protocol::ipo_price>(); }) { checksum += bench::digest(message.template get<protocol::ipo_price>().value()); }
    }

    void operator()(const protocol::luld_auction_collar_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::auction_collar_reference_price>(); }) { checksum += bench::digest(message.template get<protocol::auction_collar_reference_price>().value()); }
        if constexpr (requires { message.template get<protocol::upper_auction_collar_price>(); }) { checksum += bench::digest(message.template get<protocol::upper_auction_collar_price>().value()); }
        if constexpr (requires { message.template get<protocol::lower_auction_collar_price>(); }) { checksum += bench::digest(message.template get<protocol::lower_auction_collar_price>().value()); }
        if constexpr (requires { message.template get<protocol::auction_collar_extension>(); }) { checksum += bench::digest(message.template get<protocol::auction_collar_extension>().value()); }
    }

    void operator()(const protocol::add_order_no_mpid_attribution_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::buy_sell_indicator>(); }) { checksum += bench::digest(message.template get<protocol::buy_sell_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::shares>(); }) { checksum += bench::digest(message.template get<protocol::shares>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::add_order_with_mpid_attribution_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::buy_sell_indicator>(); }) { checksum += bench::digest(message.template get<protocol::buy_sell_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::shares>(); }) { checksum += bench::digest(message.template get<protocol::shares>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::attribution>(); }) { checksum += bench::digest(message.template get<protocol::attribution>().value()); }
    }

    void operator()(const protocol::order_executed_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::executed_shares>(); }) { checksum += bench::digest(message.template get<protocol::executed_shares>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
    }

    void operator()(const protocol::order_executed_with_price_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::executed_shares>(); }) { checksum += bench::digest(message.template get<protocol::executed_shares>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
        if constexpr (requires { message.template get<protocol::printable>(); }) { checksum += bench::digest(message.template get<protocol::printable>().value()); }
        if constexpr (requires { message.template get<protocol::execution_price>(); }) { checksum += bench::digest(message.template get<protocol::execution_price>().value()); }
    }

    void operator()(const protocol::order_cancel_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::canceled_shares>(); }) { checksum += bench::digest(message.template get<protocol::canceled_shares>().value()); }
    }

    void operator()(const protocol::order_delete_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
    }

    void operator()(const protocol::order_replace_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::original_order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::original_order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::new_order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::new_order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::shares>(); }) { checksum += bench::digest(message.template get<protocol::shares>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::non_cross_trade_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_reference_number>(); }) { checksum += bench::digest(message.template get<protocol::order_reference_number>().value()); }
        if constexpr (requires { message.template get<protocol::buy_sell_indicator>(); }) { checksum += bench::digest(message.template get<protocol::buy_sell_indicator>().value()); }
        if constexpr (requires { message.template get<protocol::shares>(); }) { checksum += bench::digest(message.template get<protocol::shares>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
    }

    void operator()(const protocol::cross_trade_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::cross_shares>(); }) { checksum += bench::digest(message.template get<protocol::cross_shares>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::cross_price>(); }) { checksum += bench::digest(message.template get<protocol::cross_price>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { checksum += bench::digest(message.template get<protocol::cross_type>().value()); }
    }

    void operator()(const protocol::broken_trade_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::match_number>(); }) { checksum += bench::digest(message.template get<protocol::match_number>().value()); }
    }

    void operator()(const protocol::net_order_imbalance_indicator_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::paired_shares>(); }) { checksum += bench::digest(message.template get<protocol::paired_shares>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_shares>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_shares>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_direction>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_direction>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::far_price>(); }) { checksum += bench::digest(message.template get<protocol::far_price>().value()); }
        if constexpr (requires { message.template get<protocol::near_price>(); }) { checksum += bench::digest(message.template get<protocol::near_price>().value()); }
        if constexpr (requires { message.template get<protocol::current_reference_price>(); }) { checksum += bench::digest(message.template get<protocol::current_reference_price>().value()); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { checksum += bench::digest(message.template get<protocol::cross_type>().value()); }
        if constexpr (requires { message.template get<protocol::price_variation_indicator>(); }) { checksum += bench::digest(message.template get<protocol::price_variation_indicator>().value()); }
    }

    void operator()(const protocol::retail_interest_message& message) {
        if constexpr (requires { message.template get<protocol::stock_locate>(); }) { checksum += bench::digest(message.template get<protocol::stock_locate>().value()); }
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { checksum += bench::digest(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { checksum += bench::digest(message.template get<protocol::stock>().value()); }
        if constexpr (requires { message.template get<protocol::interest_flag>(); }) { checksum += bench::digest(message.template get<protocol::interest_flag>().value()); }
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
    return bench::run("Nasdaq.NsmEquities.TotalView.Itch.v5.0.2017", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
