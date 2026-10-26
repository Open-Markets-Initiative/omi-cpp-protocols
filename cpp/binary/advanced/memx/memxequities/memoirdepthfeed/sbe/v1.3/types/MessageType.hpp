#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// message_type
struct message_type {

    enum class enum_type : std::uint8_t {
        heartbeat_message = 0,
        session_shutdown_message = 1,
        sequenced_message = 2
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Heartbeat Message", enum_type::heartbeat_message},
        {"Sequenced Message", enum_type::sequenced_message},
        {"Session Shutdown Message", enum_type::session_shutdown_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::heartbeat_message: return "Heartbeat Message";
            case enum_type::session_shutdown_message: return "Session Shutdown Message";
            case enum_type::sequenced_message: return "Sequenced Message";
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

    static constexpr const char* name = "message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<message_type::enum_type>;
    using storage_type = result_type;

    constexpr message_type()
     : value{ enum_type{} } {}

    constexpr message_type(enum_type v)
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
            set(enum_type::sequenced_message);
    }

  protected:
    enum_type value;
};
}
