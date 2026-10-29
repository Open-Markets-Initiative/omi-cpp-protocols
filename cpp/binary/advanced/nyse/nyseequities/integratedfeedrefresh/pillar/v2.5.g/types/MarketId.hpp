#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::integratedfeedrefresh::pillar::v2_5_g {

// market_id
struct market_id {

    enum class enum_type : std::uint16_t {
        nyse_equities = 1,
        nyse_arca_equities = 3,
        nyse_arca_options = 4,
        nyse_bonds = 5,
        nyse_american_options = 8,
        nyse_american_equities = 9,
        nyse_national_equities = 10,
        nyse_texas_equities = 11
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"Nyse American Equities", enum_type::nyse_american_equities},
        {"Nyse American Options", enum_type::nyse_american_options},
        {"Nyse Arca Equities", enum_type::nyse_arca_equities},
        {"Nyse Arca Options", enum_type::nyse_arca_options},
        {"Nyse Bonds", enum_type::nyse_bonds},
        {"Nyse Equities", enum_type::nyse_equities},
        {"Nyse National Equities", enum_type::nyse_national_equities},
        {"Nyse Texas Equities", enum_type::nyse_texas_equities}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nyse_equities: return "Nyse Equities";
            case enum_type::nyse_arca_equities: return "Nyse Arca Equities";
            case enum_type::nyse_arca_options: return "Nyse Arca Options";
            case enum_type::nyse_bonds: return "Nyse Bonds";
            case enum_type::nyse_american_options: return "Nyse American Options";
            case enum_type::nyse_american_equities: return "Nyse American Equities";
            case enum_type::nyse_national_equities: return "Nyse National Equities";
            case enum_type::nyse_texas_equities: return "Nyse Texas Equities";
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

    static constexpr const char* name = "market_id";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<market_id::enum_type>;
    using storage_type = result_type;

    constexpr market_id()
     : value{ enum_type{} } {}

    constexpr market_id(enum_type v)
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
            set(enum_type::nyse_texas_equities);
    }

  protected:
    enum_type value;
};
}
