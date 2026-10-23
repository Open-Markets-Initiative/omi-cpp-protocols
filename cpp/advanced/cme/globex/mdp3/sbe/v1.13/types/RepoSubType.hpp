#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// repo_sub_type
struct repo_sub_type {

    enum class enum_type : std::uint8_t {
        special = 0,
        gc = 1,
        gc_for_dbv = 2
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Gc", enum_type::gc},
        {"Gc For Dbv", enum_type::gc_for_dbv},
        {"Special", enum_type::special}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::special: return "Special";
            case enum_type::gc: return "Gc";
            case enum_type::gc_for_dbv: return "Gc For Dbv";
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

    static constexpr const char* name = "repo_sub_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<repo_sub_type::enum_type>;
    using storage_type = result_type;

    constexpr repo_sub_type()
     : value{ enum_type{} } {}

    constexpr repo_sub_type(enum_type v)
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
            set(enum_type::gc_for_dbv);
    }

  protected:
    enum_type value;
};
}
