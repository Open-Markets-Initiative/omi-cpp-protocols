#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// session_state
struct session_state {

    enum class enum_type : char {
        pre_open = 'P',
        opened = 'O',
        regulatory_halt = 'R',
        halted = 'H',
        closed = 'C',
        maintenance = 'M'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Closed", enum_type::closed},
        {"Halted", enum_type::halted},
        {"Maintenance", enum_type::maintenance},
        {"Opened", enum_type::opened},
        {"Pre Open", enum_type::pre_open},
        {"Regulatory Halt", enum_type::regulatory_halt}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::pre_open: return "Pre Open";
            case enum_type::opened: return "Opened";
            case enum_type::regulatory_halt: return "Regulatory Halt";
            case enum_type::halted: return "Halted";
            case enum_type::closed: return "Closed";
            case enum_type::maintenance: return "Maintenance";
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

    static constexpr const char* name = "session_state";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<session_state::enum_type>;
    using storage_type = result_type;

    constexpr session_state()
     : value{ enum_type{} } {}

    constexpr session_state(enum_type v)
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
            set(enum_type::maintenance);
    }

  protected:
    enum_type value;
};
}
