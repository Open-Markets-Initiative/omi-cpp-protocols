#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

// security_event
struct security_event {

    enum class enum_type : char {
        opening_process_complete = 'O',
        closing_process_complete = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Closing Process Complete", enum_type::closing_process_complete},
        {"Opening Process Complete", enum_type::opening_process_complete}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::opening_process_complete: return "Opening Process Complete";
            case enum_type::closing_process_complete: return "Closing Process Complete";
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

    static constexpr const char* name = "security_event";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_event::enum_type>;
    using storage_type = result_type;

    constexpr security_event()
     : value{ enum_type::opening_process_complete } {}

    constexpr security_event(enum_type v)
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
            set(enum_type::closing_process_complete);
    }

  protected:
    enum_type value;
};
}
