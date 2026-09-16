#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// order_condition
struct order_condition {

    enum class enum_type : std::uint8_t {
        nonconditional = 0,
        onopen = 2,
        onclose = 4,
        funari = 6
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Funari", enum_type::funari},
        {"Nonconditional", enum_type::nonconditional},
        {"Onclose", enum_type::onclose},
        {"Onopen", enum_type::onopen}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nonconditional: return "Nonconditional";
            case enum_type::onopen: return "Onopen";
            case enum_type::onclose: return "Onclose";
            case enum_type::funari: return "Funari";
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

    static constexpr const char* name = "order_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<order_condition::enum_type>;
    using storage_type = result_type;

    constexpr order_condition()
     : value{ enum_type::nonconditional } {}

    constexpr order_condition(enum_type v)
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
            set(enum_type::funari);
    }

  protected:
    enum_type value;
};
}
