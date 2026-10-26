#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// event_code
struct event_code {

    enum class enum_type : char {
        start_of_transmissions = 'O',
        start_of_system_hours = 'S',
        start_of_market_hours = 'Q',
        end_of_market_hours = 'M',
        end_of_system_hours = 'E',
        end_of_transmissions = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"End Of Market Hours", enum_type::end_of_market_hours},
        {"End Of System Hours", enum_type::end_of_system_hours},
        {"End Of Transmissions", enum_type::end_of_transmissions},
        {"Start Of Market Hours", enum_type::start_of_market_hours},
        {"Start Of System Hours", enum_type::start_of_system_hours},
        {"Start Of Transmissions", enum_type::start_of_transmissions}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::start_of_transmissions: return "Start Of Transmissions";
            case enum_type::start_of_system_hours: return "Start Of System Hours";
            case enum_type::start_of_market_hours: return "Start Of Market Hours";
            case enum_type::end_of_market_hours: return "End Of Market Hours";
            case enum_type::end_of_system_hours: return "End Of System Hours";
            case enum_type::end_of_transmissions: return "End Of Transmissions";
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

    static constexpr const char* name = "event_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<event_code::enum_type>;
    using storage_type = result_type;

    constexpr event_code()
     : value{ enum_type{} } {}

    constexpr event_code(enum_type v)
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
            set(enum_type::end_of_transmissions);
    }

  protected:
    enum_type value;
};
}
