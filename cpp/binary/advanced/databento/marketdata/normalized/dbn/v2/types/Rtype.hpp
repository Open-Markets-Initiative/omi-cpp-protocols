// Databento.MarketData.Normalized.Dbn.v2: types/Rtype.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// rtype
struct rtype {

    enum class enum_type : std::uint8_t {
        market_by_price_0 = 0,
        market_by_price_1 = 1,
        market_by_price_10 = 10,
        ohlcv_deprecated = 17,
        status = 18,
        instrument_definition = 19,
        imbalance = 20,
        error = 21,
        symbol_mapping = 22,
        system = 23,
        statistics = 24,
        ohlcv_1_second = 32,
        ohlcv_1_minute = 33,
        ohlcv_1_hour = 34,
        ohlcv_1_day = 35,
        ohlcv_end_of_day = 36,
        market_by_order = 160,
        consolidated_market_by_price_1 = 177,
        consolidated_bbo_1_second = 192,
        consolidated_bbo_1_minute = 193,
        trade_with_consolidated_bbo = 194,
        bbo_1_second = 195,
        bbo_1_minute = 196
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 23> from_string_map = {{
        {"Bbo 1 Minute", enum_type::bbo_1_minute},
        {"Bbo 1 Second", enum_type::bbo_1_second},
        {"Consolidated Bbo 1 Minute", enum_type::consolidated_bbo_1_minute},
        {"Consolidated Bbo 1 Second", enum_type::consolidated_bbo_1_second},
        {"Consolidated Market By Price 1", enum_type::consolidated_market_by_price_1},
        {"Error", enum_type::error},
        {"Imbalance", enum_type::imbalance},
        {"Instrument Definition", enum_type::instrument_definition},
        {"Market By Order", enum_type::market_by_order},
        {"Market By Price 0", enum_type::market_by_price_0},
        {"Market By Price 1", enum_type::market_by_price_1},
        {"Market By Price 10", enum_type::market_by_price_10},
        {"Ohlcv 1 Day", enum_type::ohlcv_1_day},
        {"Ohlcv 1 Hour", enum_type::ohlcv_1_hour},
        {"Ohlcv 1 Minute", enum_type::ohlcv_1_minute},
        {"Ohlcv 1 Second", enum_type::ohlcv_1_second},
        {"Ohlcv Deprecated", enum_type::ohlcv_deprecated},
        {"Ohlcv End Of Day", enum_type::ohlcv_end_of_day},
        {"Statistics", enum_type::statistics},
        {"Status", enum_type::status},
        {"Symbol Mapping", enum_type::symbol_mapping},
        {"System", enum_type::system},
        {"Trade With Consolidated Bbo", enum_type::trade_with_consolidated_bbo}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::market_by_price_0: return "Market By Price 0";
            case enum_type::market_by_price_1: return "Market By Price 1";
            case enum_type::market_by_price_10: return "Market By Price 10";
            case enum_type::ohlcv_deprecated: return "Ohlcv Deprecated";
            case enum_type::status: return "Status";
            case enum_type::instrument_definition: return "Instrument Definition";
            case enum_type::imbalance: return "Imbalance";
            case enum_type::error: return "Error";
            case enum_type::symbol_mapping: return "Symbol Mapping";
            case enum_type::system: return "System";
            case enum_type::statistics: return "Statistics";
            case enum_type::ohlcv_1_second: return "Ohlcv 1 Second";
            case enum_type::ohlcv_1_minute: return "Ohlcv 1 Minute";
            case enum_type::ohlcv_1_hour: return "Ohlcv 1 Hour";
            case enum_type::ohlcv_1_day: return "Ohlcv 1 Day";
            case enum_type::ohlcv_end_of_day: return "Ohlcv End Of Day";
            case enum_type::market_by_order: return "Market By Order";
            case enum_type::consolidated_market_by_price_1: return "Consolidated Market By Price 1";
            case enum_type::consolidated_bbo_1_second: return "Consolidated Bbo 1 Second";
            case enum_type::consolidated_bbo_1_minute: return "Consolidated Bbo 1 Minute";
            case enum_type::trade_with_consolidated_bbo: return "Trade With Consolidated Bbo";
            case enum_type::bbo_1_second: return "Bbo 1 Second";
            case enum_type::bbo_1_minute: return "Bbo 1 Minute";
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

    static constexpr const char* name = "rtype";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<rtype::enum_type>;
    using storage_type = result_type;

    constexpr rtype()
     : value{ enum_type{} } {}

    constexpr rtype(enum_type v)
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
            set(enum_type::bbo_1_minute);
    }

  protected:
    enum_type value;
};
}
