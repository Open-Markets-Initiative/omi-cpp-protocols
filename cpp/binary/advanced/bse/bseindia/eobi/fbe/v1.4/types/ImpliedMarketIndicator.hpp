#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// implied_market_indicator
struct implied_market_indicator {

    enum class enum_type : std::uint8_t {
        not_implied = 0,
        implied_in_out = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Implied In Out", enum_type::implied_in_out},
        {"Not Implied", enum_type::not_implied}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_implied: return "Not Implied";
            case enum_type::implied_in_out: return "Implied In Out";
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

    static constexpr const char* name = "implied_market_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<implied_market_indicator::enum_type>;
    using storage_type = result_type;

    constexpr implied_market_indicator()
     : value{ enum_type{} } {}

    constexpr implied_market_indicator(enum_type v)
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
            set(enum_type::implied_in_out);
    }

  protected:
    enum_type value;
};
}
