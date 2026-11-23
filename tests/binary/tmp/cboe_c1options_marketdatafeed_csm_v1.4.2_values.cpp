// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2 canonical values, through the Tmp header: every value the Tmp reading hands
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
#include "cpp/binary/tmp/cboe/c1options/marketdatafeed/csm/v1.4.2/cboe_c1options_marketdatafeed_csm_v1_4_2.hpp"

// Cboe C1Options MarketDataFeed Csm 1.4.2: the reading of its packets, through its Template Meta Programming header
namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

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

// Summary Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_summary_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& summary_message_section_1_ = tmp::read<summary_message_section_1>(data + offset, bound - offset, handler); offset += summary_message_section_1::size;
    tmp::call(handler, summary_message_section_1_.template get<net_chg_prev_day>());
    tmp::call(handler, summary_message_section_1_.template get<underlying_px>());
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(summary_message_section_1_.template get<no_entries>()));
        while (count-- > 0) {
            offset += tmp::take<summary_md_entry>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Settlement Value Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_settlement_value_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& settlement_value_message_section_1_ = tmp::read<settlement_value_message_section_1>(data + offset, bound - offset, handler); offset += settlement_value_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(settlement_value_message_section_1_.template get<no_entries>()));
        while (count-- > 0) {
            offset += tmp::take<settlement_value_md_entry>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Symbol: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_symbol([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& symbol_section_1_ = tmp::read<symbol_section_1>(data + offset, bound - offset, handler); offset += symbol_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(tmp::rule(symbol_section_1_.template get<symbol_length>()));
        tmp::require(offset + size, bound);
        tmp::call(handler, symbol_text{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Index Value Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_index_value_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    offset += parse_symbol(data + offset, bound - offset, handler);
    [[maybe_unused]] const auto& index_value_message_section_1_ = tmp::read<index_value_message_section_1>(data + offset, bound - offset, handler); offset += index_value_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(index_value_message_section_1_.template get<no_entries>()));
        while (count-- > 0) {
            offset += tmp::take<index_value_md_entry>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Trade Condition: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_trade_condition([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& trade_condition_section_1_ = tmp::read<trade_condition_section_1>(data + offset, bound - offset, handler); offset += trade_condition_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(tmp::rule(trade_condition_section_1_.template get<trade_condition_length>()));
        tmp::require(offset + size, bound);
        tmp::call(handler, trade_condition_text{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Ticker Md Entry: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_ticker_md_entry([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& ticker_md_entry_section_1_ = tmp::read<ticker_md_entry_section_1>(data + offset, bound - offset, handler); offset += ticker_md_entry_section_1::size;
    tmp::call(handler, ticker_md_entry_section_1_.template get<md_entry_px>());
    offset += parse_trade_condition(data + offset, bound - offset, handler);
    return offset;
}

// Ticker Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_ticker_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& ticker_message_section_1_ = tmp::read<ticker_message_section_1>(data + offset, bound - offset, handler); offset += ticker_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(ticker_message_section_1_.template get<no_entries>()));
        while (count-- > 0) {
            offset += parse_ticker_md_entry(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Recap Update Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_recap_update_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& recap_update_message_section_1_ = tmp::read<recap_update_message_section_1>(data + offset, bound - offset, handler); offset += recap_update_message_section_1::size;
    tmp::call(handler, recap_update_message_section_1_.template get<prev_close_px>());
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(recap_update_message_section_1_.template get<no_entries>()));
        while (count-- > 0) {
            offset += tmp::take<recap_update_md_entry>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Current Market Update Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_current_market_update_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& current_market_update_message_section_1_ = tmp::read<current_market_update_message_section_1>(data + offset, bound - offset, handler); offset += current_market_update_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(current_market_update_message_section_1_.template get<no_entries>()));
        while (count-- > 0) {
            offset += tmp::take<md_entry>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Market Data Refresh Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_market_data_refresh_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& market_data_refresh_message_section_1_ = tmp::read<market_data_refresh_message_section_1>(data + offset, bound - offset, handler); offset += market_data_refresh_message_section_1::size;
    tmp::call(handler, market_data_refresh_message_section_1_.template get<prev_close_px>());
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(market_data_refresh_message_section_1_.template get<no_entries>()));
        while (count-- > 0) {
            offset += tmp::take<md_entry>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Current Market Refresh Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_current_market_refresh_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& current_market_refresh_message_section_1_ = tmp::read<current_market_refresh_message_section_1>(data + offset, bound - offset, handler); offset += current_market_refresh_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(current_market_refresh_message_section_1_.template get<no_entries>()));
        while (count-- > 0) {
            offset += tmp::take<md_entry>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Underlying Type: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_underlying_type([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& underlying_type_section_1_ = tmp::read<underlying_type_section_1>(data + offset, bound - offset, handler); offset += underlying_type_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(tmp::rule(underlying_type_section_1_.template get<underlying_type_length>()));
        tmp::require(offset + size, bound);
        tmp::call(handler, underlying_type_text{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Underlying Symbol: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_underlying_symbol([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& underlying_symbol_section_1_ = tmp::read<underlying_symbol_section_1>(data + offset, bound - offset, handler); offset += underlying_symbol_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(tmp::rule(underlying_symbol_section_1_.template get<underlying_symbol_length>()));
        tmp::require(offset + size, bound);
        tmp::call(handler, underlying_symbol_text{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Currency Code: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_currency_code([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& currency_code_section_1_ = tmp::read<currency_code_section_1>(data + offset, bound - offset, handler); offset += currency_code_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(tmp::rule(currency_code_section_1_.template get<currency_code_length>()));
        tmp::require(offset + size, bound);
        tmp::call(handler, currency_code_text{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Target Location Id: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_target_location_id([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& target_location_id_section_1_ = tmp::read<target_location_id_section_1>(data + offset, bound - offset, handler); offset += target_location_id_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(tmp::rule(target_location_id_section_1_.template get<target_location_id_length>()));
        tmp::require(offset + size, bound);
        tmp::call(handler, target_location_id_text{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Security Type: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_security_type([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& security_type_section_1_ = tmp::read<security_type_section_1>(data + offset, bound - offset, handler); offset += security_type_section_1::size;
    {
        const std::size_t size = static_cast<std::size_t>(tmp::rule(security_type_section_1_.template get<security_type_length>()));
        tmp::require(offset + size, bound);
        tmp::call(handler, security_type_text{ data + offset, size });
        offset += size;
    }
    return offset;
}

// Security Definition Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_security_definition_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    offset += parse_security_type(data + offset, bound - offset, handler);
    [[maybe_unused]] const auto& security_definition_message_section_1_ = tmp::read<security_definition_message_section_1>(data + offset, bound - offset, handler); offset += security_definition_message_section_1::size;
    offset += parse_symbol(data + offset, bound - offset, handler);
    offset += parse_target_location_id(data + offset, bound - offset, handler);
    [[maybe_unused]] const auto& security_definition_message_section_2_ = tmp::read<security_definition_message_section_2>(data + offset, bound - offset, handler); offset += security_definition_message_section_2::size;
    tmp::call(handler, security_definition_message_section_2_.template get<strike_price>());
    tmp::call(handler, security_definition_message_section_2_.template get<minimum_strike_price_fraction>());
    tmp::call(handler, security_definition_message_section_2_.template get<max_strike_price>());
    tmp::call(handler, security_definition_message_section_2_.template get<premium_break_point>());
    tmp::call(handler, security_definition_message_section_2_.template get<minimum_above_premium_fraction>());
    tmp::call(handler, security_definition_message_section_2_.template get<minimum_below_premium_fraction>());
    offset += parse_currency_code(data + offset, bound - offset, handler);
    offset += parse_underlying_symbol(data + offset, bound - offset, handler);
    offset += parse_underlying_type(data + offset, bound - offset, handler);
    [[maybe_unused]] const auto& security_definition_message_section_3_ = tmp::read<security_definition_message_section_3>(data + offset, bound - offset, handler); offset += security_definition_message_section_3::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(security_definition_message_section_3_.template get<no_legs>()));
        while (count-- > 0) {
            offset += tmp::take<security_definition_leg>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const template_id& template_id_) {
    if (static_cast<bool>(tmp::rule(template_id_) == 13)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_security_definition_message(data + offset, bound - offset, handler);
        tmp::call(handler, security_definition_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 11)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_current_market_refresh_message(data + offset, bound - offset, handler);
        tmp::call(handler, current_market_refresh_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 20)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_market_data_refresh_message(data + offset, bound - offset, handler);
        tmp::call(handler, market_data_refresh_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 12)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_current_market_update_message(data + offset, bound - offset, handler);
        tmp::call(handler, current_market_update_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 21)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_recap_update_message(data + offset, bound - offset, handler);
        tmp::call(handler, recap_update_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 14)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_ticker_message(data + offset, bound - offset, handler);
        tmp::call(handler, ticker_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 15)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& expected_opening_price_and_size_message_ = tmp::read<expected_opening_price_and_size_message>(data + offset, bound - offset, handler); offset += expected_opening_price_and_size_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 22)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_index_value_message(data + offset, bound - offset, handler);
        tmp::call(handler, index_value_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 23)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_settlement_value_message(data + offset, bound - offset, handler);
        tmp::call(handler, settlement_value_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 24)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_summary_message(data + offset, bound - offset, handler);
        tmp::call(handler, summary_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 25)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& market_data_control_message_ = tmp::read<market_data_control_message>(data + offset, bound - offset, handler); offset += market_data_control_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 16)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, heartbeat_message{});
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
    bound = static_cast<std::size_t>(tmp::rule(message_header_.template get<message_length>()));
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
        std::size_t count = static_cast<std::size_t>(tmp::rule(packet_header_.template get<message_count>()));
        while (count-- > 0) {
            offset += parse_message(data + offset, bound - offset, handler);
        }
    }
    return offset;
}


} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2

namespace protocol = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

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
        if constexpr (requires { header.template get<protocol::version>(); }) { values["packet.packetheader.version"] = canonical::number(header.template get<protocol::version>().value()); }
        if constexpr (requires { header.template get<protocol::packet_length>(); }) { values["packet.packetheader.packetlength"] = canonical::number(header.template get<protocol::packet_length>().value()); }
        if constexpr (requires { header.template get<protocol::sending_time>(); }) { values["packet.packetheader.sendingtime"] = canonical::number(header.template get<protocol::sending_time>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { values["packet.packetheader.messagecount"] = canonical::number(header.template get<protocol::message_count>().value()); }
        if constexpr (requires { header.template get<protocol::first_msg_seq_num>(); }) { values["packet.packetheader.firstmsgseqnum"] = canonical::number(header.template get<protocol::first_msg_seq_num>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::message_length>(); }) { values[entry + ".messageheader.messagelength"] = canonical::number(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::template_id>(); }) { values[entry + ".messageheader.templateid"] = canonical::number(header.template get<protocol::template_id>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(header.template get<protocol::message_type>().value())); }
        if constexpr (requires { header.template get<protocol::msg_seq_num>(); }) { values[entry + ".messageheader.msgseqnum"] = canonical::number(header.template get<protocol::msg_seq_num>().value()); }
    }

    void operator()(const protocol::security_definition_message&) {
        values[entry + ".payload"] = "packet.message.payload.securitydefinitionmessage";
    }

    void operator()(const protocol::current_market_refresh_message&) {
        values[entry + ".payload"] = "packet.message.payload.currentmarketrefreshmessage";
    }

    void operator()(const protocol::market_data_refresh_message&) {
        values[entry + ".payload"] = "packet.message.payload.marketdatarefreshmessage";
    }

    void operator()(const protocol::current_market_update_message&) {
        values[entry + ".payload"] = "packet.message.payload.currentmarketupdatemessage";
    }

    void operator()(const protocol::recap_update_message&) {
        values[entry + ".payload"] = "packet.message.payload.recapupdatemessage";
    }

    void operator()(const protocol::ticker_message&) {
        values[entry + ".payload"] = "packet.message.payload.tickermessage";
    }

    void operator()(const protocol::expected_opening_price_and_size_message& message) {
        values[entry + ".payload"] = "packet.message.payload.expectedopeningpriceandsizemessage";
        if constexpr (requires { message.template get<protocol::class_key>(); }) { values[entry + ".payload.expectedopeningpriceandsizemessage.classkey"] = canonical::number(message.template get<protocol::class_key>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.expectedopeningpriceandsizemessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::eop>().template get<protocol::eop_exponent>(); }) { values[entry + ".payload.expectedopeningpriceandsizemessage.eop.eopexponent"] = canonical::number(message.template get<protocol::eop>().template get<protocol::eop_exponent>().value()); }
        if constexpr (requires { message.template get<protocol::eop>().template get<protocol::eop_mantissa>(); }) { values[entry + ".payload.expectedopeningpriceandsizemessage.eop.eopmantissa"] = canonical::number(message.template get<protocol::eop>().template get<protocol::eop_mantissa>().value()); }
        if constexpr (requires { message.template get<protocol::eos>(); }) { values[entry + ".payload.expectedopeningpriceandsizemessage.eos"] = canonical::number(message.template get<protocol::eos>().value()); }
        if constexpr (requires { message.template get<protocol::eop_type>(); }) { values[entry + ".payload.expectedopeningpriceandsizemessage.eoptype"] = canonical::number(message.template get<protocol::eop_type>().value()); }
        if constexpr (requires { message.template get<protocol::legal_market>(); }) { values[entry + ".payload.expectedopeningpriceandsizemessage.legalmarket"] = canonical::number(message.template get<protocol::legal_market>().value()); }
    }

    void operator()(const protocol::index_value_message&) {
        values[entry + ".payload"] = "packet.message.payload.indexvaluemessage";
    }

    void operator()(const protocol::settlement_value_message&) {
        values[entry + ".payload"] = "packet.message.payload.settlementvaluemessage";
    }

    void operator()(const protocol::summary_message&) {
        values[entry + ".payload"] = "packet.message.payload.summarymessage";
    }

    void operator()(const protocol::market_data_control_message& message) {
        values[entry + ".payload"] = "packet.message.payload.marketdatacontrolmessage";
        if constexpr (requires { message.template get<protocol::md_control_type>(); }) { values[entry + ".payload.marketdatacontrolmessage.mdcontroltype"] = canonical::number(message.template get<protocol::md_control_type>().value()); }
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
    std::printf("== Cboe.C1Options.MarketDataFeed.Csm.v1.4.2 (tmp values)\n");
    int failures = 0;
    failures += check("CurrentMarketRefreshMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/CurrentMarketRefreshMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/CurrentMarketRefreshMessage.values");
    failures += check("CurrentMarketUpdateMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/CurrentMarketUpdateMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/CurrentMarketUpdateMessage.values");
    failures += check("HeartbeatMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/HeartbeatMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/HeartbeatMessage.values");
    failures += check("MarketDataRefreshMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/MarketDataRefreshMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/MarketDataRefreshMessage.values");
    failures += check("RecapUpdateMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/RecapUpdateMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/RecapUpdateMessage.values");
    failures += check("SecurityDefinitionMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/SecurityDefinitionMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/SecurityDefinitionMessage.values");
    failures += check("TickerMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/TickerMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/TickerMessage.values");
    return failures == 0 ? 0 : 1;
}
