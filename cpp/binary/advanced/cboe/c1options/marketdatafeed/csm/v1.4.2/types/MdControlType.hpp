#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// md_control_type
struct md_control_type {

    enum class enum_type : std::uint8_t {
        start_of_summary = 0,
        end_of_summary = 1,
        start_of_settlement = 2,
        end_of_settlement = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"End Of Settlement", enum_type::end_of_settlement},
        {"End Of Summary", enum_type::end_of_summary},
        {"Start Of Settlement", enum_type::start_of_settlement},
        {"Start Of Summary", enum_type::start_of_summary}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::start_of_summary: return "Start Of Summary";
            case enum_type::end_of_summary: return "End Of Summary";
            case enum_type::start_of_settlement: return "Start Of Settlement";
            case enum_type::end_of_settlement: return "End Of Settlement";
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

    static constexpr const char* name = "md_control_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_control_type::enum_type>;
    using storage_type = result_type;

    constexpr md_control_type()
     : value{ enum_type{} } {}

    constexpr md_control_type(enum_type v)
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
            set(enum_type::end_of_settlement);
    }

  protected:
    enum_type value;
};
}
