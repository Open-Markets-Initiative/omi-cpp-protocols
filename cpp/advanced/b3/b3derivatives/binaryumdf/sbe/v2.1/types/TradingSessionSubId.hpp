#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// trading_session_sub_id
struct trading_session_sub_id {

    enum class enum_type : std::uint8_t {
        pause = 2,
        close = 4,
        open = 17,
        forbidden = 18,
        unknown_or_invalid = 20,
        reserved = 21,
        final_closing_call = 101
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Close", enum_type::close},
        {"Final Closing Call", enum_type::final_closing_call},
        {"Forbidden", enum_type::forbidden},
        {"Open", enum_type::open},
        {"Pause", enum_type::pause},
        {"Reserved", enum_type::reserved},
        {"Unknown Or Invalid", enum_type::unknown_or_invalid}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::pause: return "Pause";
            case enum_type::close: return "Close";
            case enum_type::open: return "Open";
            case enum_type::forbidden: return "Forbidden";
            case enum_type::unknown_or_invalid: return "Unknown Or Invalid";
            case enum_type::reserved: return "Reserved";
            case enum_type::final_closing_call: return "Final Closing Call";
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

    static constexpr const char* name = "trading_session_sub_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trading_session_sub_id::enum_type>;
    using storage_type = result_type;

    constexpr trading_session_sub_id()
     : value{ enum_type::pause } {}

    constexpr trading_session_sub_id(enum_type v)
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
            set(enum_type::final_closing_call);
    }

  protected:
    enum_type value;
};
}
