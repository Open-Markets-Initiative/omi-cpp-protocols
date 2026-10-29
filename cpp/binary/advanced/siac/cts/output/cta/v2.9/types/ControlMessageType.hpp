#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_9 {

// control_message_type
struct control_message_type {

    enum class enum_type : char {
        start_of_day_message = 'A',
        reset_block_sequence_number_message = 'L',
        disaster_recovery_data_center_activation_message = 'P',
        line_integrity_message = 'T',
        end_of_day_message = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Disaster Recovery Data Center Activation Message", enum_type::disaster_recovery_data_center_activation_message},
        {"End Of Day Message", enum_type::end_of_day_message},
        {"Line Integrity Message", enum_type::line_integrity_message},
        {"Reset Block Sequence Number Message", enum_type::reset_block_sequence_number_message},
        {"Start Of Day Message", enum_type::start_of_day_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::start_of_day_message: return "Start Of Day Message";
            case enum_type::reset_block_sequence_number_message: return "Reset Block Sequence Number Message";
            case enum_type::disaster_recovery_data_center_activation_message: return "Disaster Recovery Data Center Activation Message";
            case enum_type::line_integrity_message: return "Line Integrity Message";
            case enum_type::end_of_day_message: return "End Of Day Message";
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
            set(enum_type::end_of_day_message);
    }

  protected:
    enum_type value;
};
}
