#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

// match_sub_type
struct match_sub_type {

    enum class enum_type : std::uint8_t {
        opening_auction = 1,
        closing_auction = 2,
        intraday_auction = 3,
        circuit_breaker_auction = 4,
        ipo_auction = 5,
        no_value = 0xFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Circuit Breaker Auction", enum_type::circuit_breaker_auction},
        {"Closing Auction", enum_type::closing_auction},
        {"Intraday Auction", enum_type::intraday_auction},
        {"Ipo Auction", enum_type::ipo_auction},
        {"No Value", enum_type::no_value},
        {"Opening Auction", enum_type::opening_auction}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::opening_auction: return "Opening Auction";
            case enum_type::closing_auction: return "Closing Auction";
            case enum_type::intraday_auction: return "Intraday Auction";
            case enum_type::circuit_breaker_auction: return "Circuit Breaker Auction";
            case enum_type::ipo_auction: return "Ipo Auction";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "match_sub_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<match_sub_type::enum_type>;
    using storage_type = result_type;

    constexpr match_sub_type()
     : value{ enum_type{} } {}

    constexpr match_sub_type(enum_type v)
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
            set(static_cast<enum_type>(0xFF));
    }

  protected:
    enum_type value;
};
}
