#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// authenticity
struct authenticity {

    enum class enum_type : char {
        live_production = 'P',
        test = 'T'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Live Production", enum_type::live_production},
        {"Test", enum_type::test}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::live_production: return "Live Production";
            case enum_type::test: return "Test";
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

    static constexpr const char* name = "authenticity";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<authenticity::enum_type>;
    using storage_type = result_type;

    constexpr authenticity()
     : value{ enum_type::live_production } {}

    constexpr authenticity(enum_type v)
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
            set(enum_type::test);
    }

  protected:
    enum_type value;
};
}
