#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

// match_type
struct match_type {

    enum class enum_type : std::uint8_t {
        confirmed_trade_report = 3,
        cross_auction = 5,
        call_auction = 7,
        liquidity_improvement_cross = 13,
        continuous_auction = 14,
        no_value = 0xFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Call Auction", enum_type::call_auction},
        {"Confirmed Trade Report", enum_type::confirmed_trade_report},
        {"Continuous Auction", enum_type::continuous_auction},
        {"Cross Auction", enum_type::cross_auction},
        {"Liquidity Improvement Cross", enum_type::liquidity_improvement_cross},
        {"No Value", enum_type::no_value}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::confirmed_trade_report: return "Confirmed Trade Report";
            case enum_type::cross_auction: return "Cross Auction";
            case enum_type::call_auction: return "Call Auction";
            case enum_type::liquidity_improvement_cross: return "Liquidity Improvement Cross";
            case enum_type::continuous_auction: return "Continuous Auction";
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

    static constexpr const char* name = "match_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<match_type::enum_type>;
    using storage_type = result_type;

    constexpr match_type()
     : value{ enum_type{} } {}

    constexpr match_type(enum_type v)
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
