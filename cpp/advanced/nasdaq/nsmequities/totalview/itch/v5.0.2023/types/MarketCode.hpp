#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// market_code
struct market_code {

    enum class enum_type : char {
        nasdaq = 'Q',
        nasdaq_texas = 'B',
        psx = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Nasdaq", enum_type::nasdaq},
        {"Nasdaq Texas", enum_type::nasdaq_texas},
        {"Psx", enum_type::psx}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nasdaq: return "Nasdaq";
            case enum_type::nasdaq_texas: return "Nasdaq Texas";
            case enum_type::psx: return "Psx";
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

    static constexpr const char* name = "market_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<market_code::enum_type>;
    using storage_type = result_type;

    constexpr market_code()
     : value{ enum_type::nasdaq } {}

    constexpr market_code(enum_type v)
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
            set(enum_type::psx);
    }

  protected:
    enum_type value;
};
}
