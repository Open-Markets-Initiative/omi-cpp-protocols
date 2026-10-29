#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_9 {

// summary_message_type
struct summary_message_type {

    enum class enum_type : char {
        consolidated_start_of_day_summary_message = 'A',
        participant_start_of_day_summary_message = 'B',
        consolidated_end_of_day_summary_message = 'C',
        participant_end_of_day_summary_message = 'D'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Consolidated End Of Day Summary Message", enum_type::consolidated_end_of_day_summary_message},
        {"Consolidated Start Of Day Summary Message", enum_type::consolidated_start_of_day_summary_message},
        {"Participant End Of Day Summary Message", enum_type::participant_end_of_day_summary_message},
        {"Participant Start Of Day Summary Message", enum_type::participant_start_of_day_summary_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::consolidated_start_of_day_summary_message: return "Consolidated Start Of Day Summary Message";
            case enum_type::participant_start_of_day_summary_message: return "Participant Start Of Day Summary Message";
            case enum_type::consolidated_end_of_day_summary_message: return "Consolidated End Of Day Summary Message";
            case enum_type::participant_end_of_day_summary_message: return "Participant End Of Day Summary Message";
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

    static constexpr const char* name = "summary_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<summary_message_type::enum_type>;
    using storage_type = result_type;

    constexpr summary_message_type()
     : value{ enum_type{} } {}

    constexpr summary_message_type(enum_type v)
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
            set(enum_type::participant_end_of_day_summary_message);
    }

  protected:
    enum_type value;
};
}
