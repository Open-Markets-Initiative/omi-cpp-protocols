#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::opra::output::obi::v6_2 {

// control_message_type
struct control_message_type {

    enum class enum_type : char {
        start_of_day = 'C',
        start_of_summary = 'E',
        end_of_summary = 'F',
        end_of_day = 'J',
        reset_block_sequence_number = 'K',
        start_of_open_interest = 'L',
        end_of_open_interest = 'M',
        line_integrity = 'N',
        disaster_recovery_data_center_activation = 'P'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Disaster Recovery Data Center Activation", enum_type::disaster_recovery_data_center_activation},
        {"End Of Day", enum_type::end_of_day},
        {"End Of Open Interest", enum_type::end_of_open_interest},
        {"End Of Summary", enum_type::end_of_summary},
        {"Line Integrity", enum_type::line_integrity},
        {"Reset Block Sequence Number", enum_type::reset_block_sequence_number},
        {"Start Of Day", enum_type::start_of_day},
        {"Start Of Open Interest", enum_type::start_of_open_interest},
        {"Start Of Summary", enum_type::start_of_summary}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::start_of_day: return "Start Of Day";
            case enum_type::start_of_summary: return "Start Of Summary";
            case enum_type::end_of_summary: return "End Of Summary";
            case enum_type::end_of_day: return "End Of Day";
            case enum_type::reset_block_sequence_number: return "Reset Block Sequence Number";
            case enum_type::start_of_open_interest: return "Start Of Open Interest";
            case enum_type::end_of_open_interest: return "End Of Open Interest";
            case enum_type::line_integrity: return "Line Integrity";
            case enum_type::disaster_recovery_data_center_activation: return "Disaster Recovery Data Center Activation";
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

    static constexpr const char* name = "control_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<control_message_type::enum_type>;
    using storage_type = result_type;

    constexpr control_message_type()
     : value{ enum_type{} } {}

    constexpr control_message_type(enum_type v)
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
            set(enum_type::disaster_recovery_data_center_activation);
    }

  protected:
    enum_type value;
};
}
