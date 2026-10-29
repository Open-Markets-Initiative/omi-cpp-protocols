#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// event_code
struct event_code {

    enum class enum_type : char {
        start_of_messages = 'O',
        start_of_system_hours = 'S',
        start_of_opening_process = 'Q',
        start_of_normal_hours_closing_process = 'N',
        start_of_late_hours_closing_process = 'L',
        end_of_system_hours = 'E',
        end_of_messages = 'C',
        end_of_wco_early_closing = 'W'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"End Of Messages", enum_type::end_of_messages},
        {"End Of System Hours", enum_type::end_of_system_hours},
        {"End Of Wco Early Closing", enum_type::end_of_wco_early_closing},
        {"Start Of Late Hours Closing Process", enum_type::start_of_late_hours_closing_process},
        {"Start Of Messages", enum_type::start_of_messages},
        {"Start Of Normal Hours Closing Process", enum_type::start_of_normal_hours_closing_process},
        {"Start Of Opening Process", enum_type::start_of_opening_process},
        {"Start Of System Hours", enum_type::start_of_system_hours}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::start_of_messages: return "Start Of Messages";
            case enum_type::start_of_system_hours: return "Start Of System Hours";
            case enum_type::start_of_opening_process: return "Start Of Opening Process";
            case enum_type::start_of_normal_hours_closing_process: return "Start Of Normal Hours Closing Process";
            case enum_type::start_of_late_hours_closing_process: return "Start Of Late Hours Closing Process";
            case enum_type::end_of_system_hours: return "End Of System Hours";
            case enum_type::end_of_messages: return "End Of Messages";
            case enum_type::end_of_wco_early_closing: return "End Of Wco Early Closing";
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
            set(enum_type::end_of_wco_early_closing);
    }

  protected:
    enum_type value;
};
}
