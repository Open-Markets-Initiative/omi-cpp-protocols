#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// settl_price_type
struct settl_price_type {

    enum class enum_type : std::uint8_t {
        final_value = 1,
        theoretical = 2,
        updated = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Final", enum_type::final_value},
        {"Theoretical", enum_type::theoretical},
        {"Updated", enum_type::updated}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::final_value: return "Final";
            case enum_type::theoretical: return "Theoretical";
            case enum_type::updated: return "Updated";
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

    static constexpr const char* name = "settl_price_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<settl_price_type::enum_type>;
    using storage_type = result_type;

    constexpr settl_price_type()
     : value{ enum_type::final_value } {}

    constexpr settl_price_type(enum_type v)
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
            set(enum_type::updated);
    }

  protected:
    enum_type value;
};
}
