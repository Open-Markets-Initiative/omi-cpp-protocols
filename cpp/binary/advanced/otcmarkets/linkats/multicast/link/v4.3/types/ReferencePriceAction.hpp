// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/ReferencePriceAction.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// reference_price_action
struct reference_price_action {

    enum class enum_type : std::uint8_t {
        add = 2,
        delete_value = 3,
        spin = 4
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Add", enum_type::add},
        {"Delete", enum_type::delete_value},
        {"Spin", enum_type::spin}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::add: return "Add";
            case enum_type::delete_value: return "Delete";
            case enum_type::spin: return "Spin";
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

    static constexpr const char* name = "reference_price_action";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<reference_price_action::enum_type>;
    using storage_type = result_type;

    constexpr reference_price_action()
     : value{ enum_type{} } {}

    constexpr reference_price_action(enum_type v)
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
            set(enum_type::spin);
    }

  protected:
    enum_type value;
};
}
