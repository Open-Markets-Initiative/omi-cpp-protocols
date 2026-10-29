#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// trading_session_id
struct trading_session_id {

    enum class enum_type : std::uint8_t {
        regular_day_session = 1,
        non_regular_session = 6,
        no_value = 0
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"No Value", enum_type::no_value},
        {"Non Regular Session", enum_type::non_regular_session},
        {"Regular Day Session", enum_type::regular_day_session}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular_day_session: return "Regular Day Session";
            case enum_type::non_regular_session: return "Non Regular Session";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "trading_session_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trading_session_id::enum_type>;
    using storage_type = result_type;

    constexpr trading_session_id()
     : value{ enum_type{} } {}

    constexpr trading_session_id(enum_type v)
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
            set(static_cast<enum_type>(0));
    }

  protected:
    enum_type value;
};
}
