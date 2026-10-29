#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// trading_session_id
struct trading_session_id {

    enum class enum_type : std::uint8_t {
        day = 1,
        morning = 3,
        evening = 5,
        holiday = 7
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Day", enum_type::day},
        {"Evening", enum_type::evening},
        {"Holiday", enum_type::holiday},
        {"Morning", enum_type::morning}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::day: return "Day";
            case enum_type::morning: return "Morning";
            case enum_type::evening: return "Evening";
            case enum_type::holiday: return "Holiday";
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
            set(enum_type::holiday);
    }

  protected:
    enum_type value;
};
}
