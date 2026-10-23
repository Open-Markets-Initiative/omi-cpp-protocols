#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// unsequenced_message_type
struct unsequenced_message_type {

    enum class enum_type : char {
        refresh_request_message = 'R',
        refresh_response_message = 'r',
        end_of_refresh_notification_message = 'E'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"End Of Refresh Notification Message", enum_type::end_of_refresh_notification_message},
        {"Refresh Request Message", enum_type::refresh_request_message},
        {"Refresh Response Message", enum_type::refresh_response_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::refresh_request_message: return "Refresh Request Message";
            case enum_type::refresh_response_message: return "Refresh Response Message";
            case enum_type::end_of_refresh_notification_message: return "End Of Refresh Notification Message";
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

    static constexpr const char* name = "unsequenced_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<unsequenced_message_type::enum_type>;
    using storage_type = result_type;

    constexpr unsequenced_message_type()
     : value{ enum_type{} } {}

    constexpr unsequenced_message_type(enum_type v)
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
            set(enum_type::end_of_refresh_notification_message);
    }

  protected:
    enum_type value;
};
}
