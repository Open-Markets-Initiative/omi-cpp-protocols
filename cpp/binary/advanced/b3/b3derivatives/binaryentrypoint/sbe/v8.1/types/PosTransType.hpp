#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// pos_trans_type
struct pos_trans_type {

    enum class enum_type : std::uint8_t {
        exercise = 1,
        automatic_exercise = 105,
        exercise_not_automatic = 106
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Automatic Exercise", enum_type::automatic_exercise},
        {"Exercise", enum_type::exercise},
        {"Exercise Not Automatic", enum_type::exercise_not_automatic}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::exercise: return "Exercise";
            case enum_type::automatic_exercise: return "Automatic Exercise";
            case enum_type::exercise_not_automatic: return "Exercise Not Automatic";
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

    static constexpr const char* name = "pos_trans_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<pos_trans_type::enum_type>;
    using storage_type = result_type;

    constexpr pos_trans_type()
     : value{ enum_type{} } {}

    constexpr pos_trans_type(enum_type v)
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
            set(enum_type::exercise_not_automatic);
    }

  protected:
    enum_type value;
};
}
