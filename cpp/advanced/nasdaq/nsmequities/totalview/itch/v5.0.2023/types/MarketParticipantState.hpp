#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// market_participant_state
struct market_participant_state {

    enum class enum_type : char {
        active = 'A',
        excused = 'E',
        withdrawn = 'W',
        suspended = 'S',
        deleted = 'D'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Active", enum_type::active},
        {"Deleted", enum_type::deleted},
        {"Excused", enum_type::excused},
        {"Suspended", enum_type::suspended},
        {"Withdrawn", enum_type::withdrawn}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::active: return "Active";
            case enum_type::excused: return "Excused";
            case enum_type::withdrawn: return "Withdrawn";
            case enum_type::suspended: return "Suspended";
            case enum_type::deleted: return "Deleted";
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

    static constexpr const char* name = "market_participant_state";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<market_participant_state::enum_type>;
    using storage_type = result_type;

    constexpr market_participant_state()
     : value{ enum_type::active } {}

    constexpr market_participant_state(enum_type v)
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
            set(enum_type::deleted);
    }

  protected:
    enum_type value;
};
}
