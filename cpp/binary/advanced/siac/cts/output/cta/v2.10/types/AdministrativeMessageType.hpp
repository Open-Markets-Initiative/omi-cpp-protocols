#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_10 {

// administrative_message_type
struct administrative_message_type {

    enum class enum_type : char {
        start_of_end_of_day_message = 'A',
        end_of_end_of_day_message = 'B',
        start_of_start_of_day_message = 'C',
        end_of_start_of_day_message = 'D'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"End Of End Of Day Message", enum_type::end_of_end_of_day_message},
        {"End Of Start Of Day Message", enum_type::end_of_start_of_day_message},
        {"Start Of End Of Day Message", enum_type::start_of_end_of_day_message},
        {"Start Of Start Of Day Message", enum_type::start_of_start_of_day_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::start_of_end_of_day_message: return "Start Of End Of Day Message";
            case enum_type::end_of_end_of_day_message: return "End Of End Of Day Message";
            case enum_type::start_of_start_of_day_message: return "Start Of Start Of Day Message";
            case enum_type::end_of_start_of_day_message: return "End Of Start Of Day Message";
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

    static constexpr const char* name = "administrative_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<administrative_message_type::enum_type>;
    using storage_type = result_type;

    constexpr administrative_message_type()
     : value{ enum_type{} } {}

    constexpr administrative_message_type(enum_type v)
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
            set(enum_type::end_of_start_of_day_message);
    }

  protected:
    enum_type value;
};
}
