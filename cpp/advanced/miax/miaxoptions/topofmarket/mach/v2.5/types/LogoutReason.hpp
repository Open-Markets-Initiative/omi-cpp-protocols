#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// logout_reason
struct logout_reason {

    enum class enum_type : char {
        graceful_logout = ' ',
        bad_packet = 'B',
        timed_out = 'L',
        application_terminating_connection = 'A'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Application Terminating Connection", enum_type::application_terminating_connection},
        {"Bad Packet", enum_type::bad_packet},
        {"Graceful Logout", enum_type::graceful_logout},
        {"Timed Out", enum_type::timed_out}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::graceful_logout: return "Graceful Logout";
            case enum_type::bad_packet: return "Bad Packet";
            case enum_type::timed_out: return "Timed Out";
            case enum_type::application_terminating_connection: return "Application Terminating Connection";
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

    static constexpr const char* name = "logout_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<logout_reason::enum_type>;
    using storage_type = result_type;

    constexpr logout_reason()
     : value{ enum_type{} } {}

    constexpr logout_reason(enum_type v)
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
            set(enum_type::application_terminating_connection);
    }

  protected:
    enum_type value;
};
}
