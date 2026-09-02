#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

// short_sale_price_test_status
struct short_sale_price_test_status {

    enum class enum_type : std::uint8_t {
        not_in_effect = 0,
        in_effect = 1
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"In Effect", enum_type::in_effect},
        {"Not In Effect", enum_type::not_in_effect}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_in_effect: return "Not In Effect";
            case enum_type::in_effect: return "In Effect";
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

    static constexpr const char* name = "short_sale_price_test_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<short_sale_price_test_status::enum_type>;
    using storage_type = result_type;

    constexpr short_sale_price_test_status()
     : value{ enum_type::not_in_effect } {}

    constexpr short_sale_price_test_status(enum_type v)
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
            set(enum_type::in_effect);
    }

  protected:
    enum_type value;
};
}
