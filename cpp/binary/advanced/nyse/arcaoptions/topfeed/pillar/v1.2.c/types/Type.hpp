#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// type
struct type {

    enum class enum_type : char {
        price_improvement = 'P',
        facilitation = 'F',
        solicitation = 'S',
        bold = 'B',
        coa = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Bold", enum_type::bold},
        {"Coa", enum_type::coa},
        {"Facilitation", enum_type::facilitation},
        {"Price Improvement", enum_type::price_improvement},
        {"Solicitation", enum_type::solicitation}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::price_improvement: return "Price Improvement";
            case enum_type::facilitation: return "Facilitation";
            case enum_type::solicitation: return "Solicitation";
            case enum_type::bold: return "Bold";
            case enum_type::coa: return "Coa";
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

    static constexpr const char* name = "type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<type::enum_type>;
    using storage_type = result_type;

    constexpr type()
     : value{ enum_type{} } {}

    constexpr type(enum_type v)
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
            set(enum_type::coa);
    }

  protected:
    enum_type value;
};
}
