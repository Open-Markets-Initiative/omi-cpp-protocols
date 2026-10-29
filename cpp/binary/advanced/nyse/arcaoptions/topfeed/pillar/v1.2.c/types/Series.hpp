#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// series
struct series {

    enum class enum_type : char {
        cube = 'a',
        occ = 'c',
        floor_trade = 'e',
        other_outright_series = 'I',
        iso_sweep = 'S',
        after_90_seconds = 'D',
        other_complex_orders = 'f',
        complex_cube = 'g',
        complex_qcc_order = 'H',
        complex_floor_order = 'i',
        complex_order_trading_with_the_outright_series = 'j',
        complex_order_to_outright_series_orderfloor_trade = 'm',
        complex_order_with_stock_to_complex_order_with_stock_floor_trade = 'p',
        complex_order_with_stock_to_outright_series_order_floor_trade = 's'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 14> from_string_map = {{
        {"After 90 Seconds", enum_type::after_90_seconds},
        {"Complex Cube", enum_type::complex_cube},
        {"Complex Floor Order", enum_type::complex_floor_order},
        {"Complex Order To Outright Series Orderfloor Trade", enum_type::complex_order_to_outright_series_orderfloor_trade},
        {"Complex Order Trading With The Outright Series", enum_type::complex_order_trading_with_the_outright_series},
        {"Complex Order With Stock To Complex Order With Stock Floor Trade", enum_type::complex_order_with_stock_to_complex_order_with_stock_floor_trade},
        {"Complex Order With Stock To Outright Series Order Floor Trade", enum_type::complex_order_with_stock_to_outright_series_order_floor_trade},
        {"Complex Qcc Order", enum_type::complex_qcc_order},
        {"Cube", enum_type::cube},
        {"Floor Trade", enum_type::floor_trade},
        {"Iso Sweep", enum_type::iso_sweep},
        {"Occ", enum_type::occ},
        {"Other Complex Orders", enum_type::other_complex_orders},
        {"Other Outright Series", enum_type::other_outright_series}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::cube: return "Cube";
            case enum_type::occ: return "Occ";
            case enum_type::floor_trade: return "Floor Trade";
            case enum_type::other_outright_series: return "Other Outright Series";
            case enum_type::iso_sweep: return "Iso Sweep";
            case enum_type::after_90_seconds: return "After 90 Seconds";
            case enum_type::other_complex_orders: return "Other Complex Orders";
            case enum_type::complex_cube: return "Complex Cube";
            case enum_type::complex_qcc_order: return "Complex Qcc Order";
            case enum_type::complex_floor_order: return "Complex Floor Order";
            case enum_type::complex_order_trading_with_the_outright_series: return "Complex Order Trading With The Outright Series";
            case enum_type::complex_order_to_outright_series_orderfloor_trade: return "Complex Order To Outright Series Orderfloor Trade";
            case enum_type::complex_order_with_stock_to_complex_order_with_stock_floor_trade: return "Complex Order With Stock To Complex Order With Stock Floor Trade";
            case enum_type::complex_order_with_stock_to_outright_series_order_floor_trade: return "Complex Order With Stock To Outright Series Order Floor Trade";
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

    static constexpr const char* name = "series";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<series::enum_type>;
    using storage_type = result_type;

    constexpr series()
     : value{ enum_type{} } {}

    constexpr series(enum_type v)
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
            set(enum_type::complex_order_with_stock_to_outright_series_order_floor_trade);
    }

  protected:
    enum_type value;
};
}
