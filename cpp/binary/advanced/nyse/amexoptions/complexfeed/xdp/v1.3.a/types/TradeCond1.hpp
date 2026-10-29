#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// trade_cond_1
struct trade_cond_1 {

    enum class enum_type : char {
        regular_trade = ' ',
        late_report = 'I',
        floor_trade = 'R',
        so_sweep_trade = 'S'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Floor Trade", enum_type::floor_trade},
        {"Late Report", enum_type::late_report},
        {"Regular Trade", enum_type::regular_trade},
        {"So Sweep Trade", enum_type::so_sweep_trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular_trade: return "Regular Trade";
            case enum_type::late_report: return "Late Report";
            case enum_type::floor_trade: return "Floor Trade";
            case enum_type::so_sweep_trade: return "So Sweep Trade";
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

    static constexpr const char* name = "trade_cond_1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_cond_1::enum_type>;
    using storage_type = result_type;

    constexpr trade_cond_1()
     : value{ enum_type{} } {}

    constexpr trade_cond_1(enum_type v)
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
            set(enum_type::so_sweep_trade);
    }

  protected:
    enum_type value;
};
}
