#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// system_status
struct system_status {

    enum class enum_type : char {
        start_of_system_hours = 'S',
        end_of_system_hours = 'C',
        start_of_test_session = '1',
        end_of_test_session = '2'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"End Of System Hours", enum_type::end_of_system_hours},
        {"End Of Test Session", enum_type::end_of_test_session},
        {"Start Of System Hours", enum_type::start_of_system_hours},
        {"Start Of Test Session", enum_type::start_of_test_session}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::start_of_system_hours: return "Start Of System Hours";
            case enum_type::end_of_system_hours: return "End Of System Hours";
            case enum_type::start_of_test_session: return "Start Of Test Session";
            case enum_type::end_of_test_session: return "End Of Test Session";
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

    static constexpr const char* name = "system_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<system_status::enum_type>;
    using storage_type = result_type;

    constexpr system_status()
     : value{ enum_type{} } {}

    constexpr system_status(enum_type v)
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
            set(enum_type::end_of_test_session);
    }

  protected:
    enum_type value;
};
}
