#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// status_action
struct status_action {

    enum class enum_type : std::uint16_t {
        none = 0,
        pre_open = 1,
        pre_cross = 2,
        quoting = 3,
        cross = 4,
        rotation = 5,
        new_price_indication = 6,
        trading = 7,
        halt = 8,
        pause = 9,
        suspend = 10,
        pre_close = 11,
        close = 12,
        post_close = 13,
        ssr_change = 14,
        not_available_for_trading = 15
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 16> from_string_map = {{
        {"Close", enum_type::close},
        {"Cross", enum_type::cross},
        {"Halt", enum_type::halt},
        {"New Price Indication", enum_type::new_price_indication},
        {"None", enum_type::none},
        {"Not Available For Trading", enum_type::not_available_for_trading},
        {"Pause", enum_type::pause},
        {"Post Close", enum_type::post_close},
        {"Pre Close", enum_type::pre_close},
        {"Pre Cross", enum_type::pre_cross},
        {"Pre Open", enum_type::pre_open},
        {"Quoting", enum_type::quoting},
        {"Rotation", enum_type::rotation},
        {"Ssr Change", enum_type::ssr_change},
        {"Suspend", enum_type::suspend},
        {"Trading", enum_type::trading}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::none: return "None";
            case enum_type::pre_open: return "Pre Open";
            case enum_type::pre_cross: return "Pre Cross";
            case enum_type::quoting: return "Quoting";
            case enum_type::cross: return "Cross";
            case enum_type::rotation: return "Rotation";
            case enum_type::new_price_indication: return "New Price Indication";
            case enum_type::trading: return "Trading";
            case enum_type::halt: return "Halt";
            case enum_type::pause: return "Pause";
            case enum_type::suspend: return "Suspend";
            case enum_type::pre_close: return "Pre Close";
            case enum_type::close: return "Close";
            case enum_type::post_close: return "Post Close";
            case enum_type::ssr_change: return "Ssr Change";
            case enum_type::not_available_for_trading: return "Not Available For Trading";
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

    static constexpr const char* name = "status_action";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<status_action::enum_type>;
    using storage_type = result_type;

    constexpr status_action()
     : value{ enum_type{} } {}

    constexpr status_action(enum_type v)
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
            set(enum_type::not_available_for_trading);
    }

  protected:
    enum_type value;
};
}
