#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// symbol_status
struct symbol_status {

    enum class enum_type : char {
        active = ' ',
        suspended = 'S',
        inactive = 'a',
        halt = 'H'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Active", enum_type::active},
        {"Halt", enum_type::halt},
        {"Inactive", enum_type::inactive},
        {"Suspended", enum_type::suspended}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::active: return "Active";
            case enum_type::suspended: return "Suspended";
            case enum_type::inactive: return "Inactive";
            case enum_type::halt: return "Halt";
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

    static constexpr const char* name = "symbol_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<symbol_status::enum_type>;
    using storage_type = result_type;

    constexpr symbol_status()
     : value{ enum_type{} } {}

    constexpr symbol_status(enum_type v)
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
            set(enum_type::halt);
    }

  protected:
    enum_type value;
};
}
