#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// open_close_settl_flag
struct open_close_settl_flag {

    enum class enum_type : std::uint8_t {
        daily = 0,
        session = 1,
        expected_entry = 3,
        entry_from_previous_business_day = 4,
        theoretical_price = 5
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Daily", enum_type::daily},
        {"Entry From Previous Business Day", enum_type::entry_from_previous_business_day},
        {"Expected Entry", enum_type::expected_entry},
        {"Session", enum_type::session},
        {"Theoretical Price", enum_type::theoretical_price}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::daily: return "Daily";
            case enum_type::session: return "Session";
            case enum_type::expected_entry: return "Expected Entry";
            case enum_type::entry_from_previous_business_day: return "Entry From Previous Business Day";
            case enum_type::theoretical_price: return "Theoretical Price";
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

    static constexpr const char* name = "open_close_settl_flag";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<open_close_settl_flag::enum_type>;
    using storage_type = result_type;

    constexpr open_close_settl_flag()
     : value{ enum_type::daily } {}

    constexpr open_close_settl_flag(enum_type v)
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
            set(enum_type::theoretical_price);
    }

  protected:
    enum_type value;
};
}
