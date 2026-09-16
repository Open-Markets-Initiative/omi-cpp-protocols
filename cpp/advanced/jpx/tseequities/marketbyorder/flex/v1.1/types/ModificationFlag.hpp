#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// modification_flag
struct modification_flag {

    enum class enum_type : std::uint8_t {
        cancel_order_or_modification_order_that_changes_time_priority = 0,
        modification_order_that_does_not_change_time_priority = 1
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Cancel Order Or Modification Order That Changes Time Priority", enum_type::cancel_order_or_modification_order_that_changes_time_priority},
        {"Modification Order That Does Not Change Time Priority", enum_type::modification_order_that_does_not_change_time_priority}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::cancel_order_or_modification_order_that_changes_time_priority: return "Cancel Order Or Modification Order That Changes Time Priority";
            case enum_type::modification_order_that_does_not_change_time_priority: return "Modification Order That Does Not Change Time Priority";
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

    static constexpr const char* name = "modification_flag";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<modification_flag::enum_type>;
    using storage_type = result_type;

    constexpr modification_flag()
     : value{ enum_type::cancel_order_or_modification_order_that_changes_time_priority } {}

    constexpr modification_flag(enum_type v)
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
            set(enum_type::modification_order_that_does_not_change_time_priority);
    }

  protected:
    enum_type value;
};
}
