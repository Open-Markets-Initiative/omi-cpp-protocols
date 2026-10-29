#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// cross_type
struct cross_type {

    enum class enum_type : char {
        early_opening = 'E',
        opening = 'O',
        reopening = '5',
        closing = '6'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Closing", enum_type::closing},
        {"Early Opening", enum_type::early_opening},
        {"Opening", enum_type::opening},
        {"Reopening", enum_type::reopening}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::early_opening: return "Early Opening";
            case enum_type::opening: return "Opening";
            case enum_type::reopening: return "Reopening";
            case enum_type::closing: return "Closing";
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

    static constexpr const char* name = "cross_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<cross_type::enum_type>;
    using storage_type = result_type;

    constexpr cross_type()
     : value{ enum_type{} } {}

    constexpr cross_type(enum_type v)
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
            set(enum_type::closing);
    }

  protected:
    enum_type value;
};
}
