#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// md_update_action
struct md_update_action {

    enum class enum_type : std::uint8_t {
        new_value = 0,
        change = 1,
        delete_value = 2,
        delete_thru = 3,
        delete_from = 4,
        overlay = 5
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Change", enum_type::change},
        {"Delete", enum_type::delete_value},
        {"Delete From", enum_type::delete_from},
        {"Delete Thru", enum_type::delete_thru},
        {"New", enum_type::new_value},
        {"Overlay", enum_type::overlay}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::new_value: return "New";
            case enum_type::change: return "Change";
            case enum_type::delete_value: return "Delete";
            case enum_type::delete_thru: return "Delete Thru";
            case enum_type::delete_from: return "Delete From";
            case enum_type::overlay: return "Overlay";
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

    static constexpr const char* name = "md_update_action";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_update_action::enum_type>;
    using storage_type = result_type;

    constexpr md_update_action()
     : value{ enum_type::new_value } {}

    constexpr md_update_action(enum_type v)
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
            set(enum_type::overlay);
    }

  protected:
    enum_type value;
};
}
