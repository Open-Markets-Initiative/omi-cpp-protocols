#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// security_update_action
struct security_update_action {

    enum class enum_type : char {
        add = 'A',
        delete_value = 'D',
        modify = 'M'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Add", enum_type::add},
        {"Delete", enum_type::delete_value},
        {"Modify", enum_type::modify}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::add: return "Add";
            case enum_type::delete_value: return "Delete";
            case enum_type::modify: return "Modify";
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

    static constexpr const char* name = "security_update_action";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_update_action::enum_type>;
    using storage_type = result_type;

    constexpr security_update_action()
     : value{ enum_type::add } {}

    constexpr security_update_action(enum_type v)
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
            set(enum_type::modify);
    }

  protected:
    enum_type value;
};
}
