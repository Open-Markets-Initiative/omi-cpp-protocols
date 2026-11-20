// B3.B3Derivatives.BinaryUmdf.Sbe.v1.6: types/ExerciseStyle.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// exercise_style
struct exercise_style {

    enum class enum_type : std::uint8_t {
        european = 0,
        american = 1,
        no_value = 255
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"American", enum_type::american},
        {"European", enum_type::european},
        {"No Value", enum_type::no_value}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::european: return "European";
            case enum_type::american: return "American";
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

    static constexpr const char* name = "exercise_style";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = true;
    static constexpr enum_type null_value = static_cast<enum_type>(255);

    using result_type = std::optional<exercise_style::enum_type>;
    using storage_type = result_type;

    constexpr exercise_style()
     : value{ static_cast<enum_type>(255) } {}

    constexpr exercise_style(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        const enum_type held = value;
        return held == null_value ? std::nullopt : result_type{held};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        set(null_value);
    }

  protected:
    enum_type value;
};
}
