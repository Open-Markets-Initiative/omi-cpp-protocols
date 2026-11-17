// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: types/MessageType.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// message_type
struct message_type {

    enum class enum_type : char {
        system_time_message = '1',
        series_update = 'P',
        complex_strategy_definition_message = 'C',
        system_state_message = 'S',
        compact_complex_top_of_market_bid_message = 'b',
        compact_complex_top_of_market_offer_message = 'o',
        wide_complex_top_of_market_bid_message = 'e',
        wide_complex_top_of_market_offer_message = 'f',
        compact_complex_double_sided_top_of_market_message = 'm',
        wide_complex_double_sided_top_of_market_message = 'w',
        strategy_trade_message = 't',
        underlying_trading_status_message = 'H'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 12> from_string_map = {{
        {"Compact Complex Double Sided Top Of Market Message", enum_type::compact_complex_double_sided_top_of_market_message},
        {"Compact Complex Top Of Market Bid Message", enum_type::compact_complex_top_of_market_bid_message},
        {"Compact Complex Top Of Market Offer Message", enum_type::compact_complex_top_of_market_offer_message},
        {"Complex Strategy Definition Message", enum_type::complex_strategy_definition_message},
        {"Series Update", enum_type::series_update},
        {"Strategy Trade Message", enum_type::strategy_trade_message},
        {"System State Message", enum_type::system_state_message},
        {"System Time Message", enum_type::system_time_message},
        {"Underlying Trading Status Message", enum_type::underlying_trading_status_message},
        {"Wide Complex Double Sided Top Of Market Message", enum_type::wide_complex_double_sided_top_of_market_message},
        {"Wide Complex Top Of Market Bid Message", enum_type::wide_complex_top_of_market_bid_message},
        {"Wide Complex Top Of Market Offer Message", enum_type::wide_complex_top_of_market_offer_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::system_time_message: return "System Time Message";
            case enum_type::series_update: return "Series Update";
            case enum_type::complex_strategy_definition_message: return "Complex Strategy Definition Message";
            case enum_type::system_state_message: return "System State Message";
            case enum_type::compact_complex_top_of_market_bid_message: return "Compact Complex Top Of Market Bid Message";
            case enum_type::compact_complex_top_of_market_offer_message: return "Compact Complex Top Of Market Offer Message";
            case enum_type::wide_complex_top_of_market_bid_message: return "Wide Complex Top Of Market Bid Message";
            case enum_type::wide_complex_top_of_market_offer_message: return "Wide Complex Top Of Market Offer Message";
            case enum_type::compact_complex_double_sided_top_of_market_message: return "Compact Complex Double Sided Top Of Market Message";
            case enum_type::wide_complex_double_sided_top_of_market_message: return "Wide Complex Double Sided Top Of Market Message";
            case enum_type::strategy_trade_message: return "Strategy Trade Message";
            case enum_type::underlying_trading_status_message: return "Underlying Trading Status Message";
            default: return "unknown";
        }
    }

    static constexpr std::optional<enum_type> from_string(std::string_view str) {
        auto it = std::lower_bound(
            from_string_map.begin(),
            from_string_map.end(),
            str,
            [](const auto& pair, std::string_view s) { return pair.first < s; }
        );
        if (it != from_string_map.end() && it->first == str) {
            return it->second;
        }
        return std::nullopt;
    }

    static constexpr const char* name = "message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<message_type::enum_type>;
    using storage_type = result_type;

    constexpr message_type()
     : value{ enum_type{} } {}

    constexpr message_type(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(enum_type::underlying_trading_status_message);
    }

  protected:
    enum_type value;
};
}
