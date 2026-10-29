#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// order_classification
struct order_classification {

    enum class enum_type : char {
        non_hft = '1',
        hft_market_making_strategy = '3',
        hft_arbitrage_strategy = '4',
        hft_directional_strategy = '5',
        hft_other_strategy = '6'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Hft Arbitrage Strategy", enum_type::hft_arbitrage_strategy},
        {"Hft Directional Strategy", enum_type::hft_directional_strategy},
        {"Hft Market Making Strategy", enum_type::hft_market_making_strategy},
        {"Hft Other Strategy", enum_type::hft_other_strategy},
        {"Non Hft", enum_type::non_hft}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::non_hft: return "Non Hft";
            case enum_type::hft_market_making_strategy: return "Hft Market Making Strategy";
            case enum_type::hft_arbitrage_strategy: return "Hft Arbitrage Strategy";
            case enum_type::hft_directional_strategy: return "Hft Directional Strategy";
            case enum_type::hft_other_strategy: return "Hft Other Strategy";
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

    static constexpr const char* name = "order_classification";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<order_classification::enum_type>;
    using storage_type = result_type;

    constexpr order_classification()
     : value{ enum_type{} } {}

    constexpr order_classification(enum_type v)
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
            set(enum_type::hft_other_strategy);
    }

  protected:
    enum_type value;
};
}
