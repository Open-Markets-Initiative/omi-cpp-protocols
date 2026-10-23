#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// tick
struct tick {

    enum class enum_type : char {
        tick_not_applicable = ' ',
        up_tick = '1',
        down_tick = '2',
        zero_up_tick = '3',
        zero_down_tick = '4'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Down Tick", enum_type::down_tick},
        {"Tick Not Applicable", enum_type::tick_not_applicable},
        {"Up Tick", enum_type::up_tick},
        {"Zero Down Tick", enum_type::zero_down_tick},
        {"Zero Up Tick", enum_type::zero_up_tick}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::tick_not_applicable: return "Tick Not Applicable";
            case enum_type::up_tick: return "Up Tick";
            case enum_type::down_tick: return "Down Tick";
            case enum_type::zero_up_tick: return "Zero Up Tick";
            case enum_type::zero_down_tick: return "Zero Down Tick";
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

    static constexpr const char* name = "tick";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<tick::enum_type>;
    using storage_type = result_type;

    constexpr tick()
     : value{ enum_type{} } {}

    constexpr tick(enum_type v)
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
            set(enum_type::zero_down_tick);
    }

  protected:
    enum_type value;
};
}
