#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// market_condition
struct market_condition {

    enum class enum_type : char {
        normal_auction_market = ' ',
        crossed_market = 'A',
        locked_market = 'B'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Crossed Market", enum_type::crossed_market},
        {"Locked Market", enum_type::locked_market},
        {"Normal Auction Market", enum_type::normal_auction_market}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::normal_auction_market: return "Normal Auction Market";
            case enum_type::crossed_market: return "Crossed Market";
            case enum_type::locked_market: return "Locked Market";
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

    static constexpr const char* name = "market_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<market_condition::enum_type>;
    using storage_type = result_type;

    constexpr market_condition()
     : value{ enum_type{} } {}

    constexpr market_condition(enum_type v)
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
            set(enum_type::locked_market);
    }

  protected:
    enum_type value;
};
}
