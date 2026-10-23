#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// reg_sho_action
struct reg_sho_action {

    enum class enum_type : char {
        no_price_test = '0',
        restriction_in_effect = '1',
        restriction_remains = '2'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"No Price Test", enum_type::no_price_test},
        {"Restriction In Effect", enum_type::restriction_in_effect},
        {"Restriction Remains", enum_type::restriction_remains}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_price_test: return "No Price Test";
            case enum_type::restriction_in_effect: return "Restriction In Effect";
            case enum_type::restriction_remains: return "Restriction Remains";
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

    static constexpr const char* name = "reg_sho_action";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<reg_sho_action::enum_type>;
    using storage_type = result_type;

    constexpr reg_sho_action()
     : value{ enum_type{} } {}

    constexpr reg_sho_action(enum_type v)
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
            set(enum_type::restriction_remains);
    }

  protected:
    enum_type value;
};
}
