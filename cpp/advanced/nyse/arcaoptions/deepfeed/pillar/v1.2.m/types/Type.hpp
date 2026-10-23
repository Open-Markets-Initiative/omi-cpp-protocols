#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// type
struct type {

    enum class enum_type : char {
        bold_outright_only = 'B',
        coa_complex_only = 'C',
        flex_price_improvement_cube = 'F',
        flex_aon_solicitation_cube = 'L',
        price_improvement_cube = 'P',
        aon_solicitation_cube = 'S'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Aon Solicitation Cube", enum_type::aon_solicitation_cube},
        {"Bold Outright Only", enum_type::bold_outright_only},
        {"Coa Complex Only", enum_type::coa_complex_only},
        {"Flex Aon Solicitation Cube", enum_type::flex_aon_solicitation_cube},
        {"Flex Price Improvement Cube", enum_type::flex_price_improvement_cube},
        {"Price Improvement Cube", enum_type::price_improvement_cube}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::bold_outright_only: return "Bold Outright Only";
            case enum_type::coa_complex_only: return "Coa Complex Only";
            case enum_type::flex_price_improvement_cube: return "Flex Price Improvement Cube";
            case enum_type::flex_aon_solicitation_cube: return "Flex Aon Solicitation Cube";
            case enum_type::price_improvement_cube: return "Price Improvement Cube";
            case enum_type::aon_solicitation_cube: return "Aon Solicitation Cube";
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
            set(enum_type::aon_solicitation_cube);
    }

  protected:
    enum_type value;
};
}
