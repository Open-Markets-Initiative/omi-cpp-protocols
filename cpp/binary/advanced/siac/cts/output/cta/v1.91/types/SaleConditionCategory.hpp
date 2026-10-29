#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v1_91 {

// sale_condition_category
struct sale_condition_category {

    enum class enum_type : char {
        not_applicable = ' ',
        category_1 = '1',
        category_2 = '2',
        category_3 = '3',
        category_4 = '4'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Category 1", enum_type::category_1},
        {"Category 2", enum_type::category_2},
        {"Category 3", enum_type::category_3},
        {"Category 4", enum_type::category_4},
        {"Not Applicable", enum_type::not_applicable}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::category_1: return "Category 1";
            case enum_type::category_2: return "Category 2";
            case enum_type::category_3: return "Category 3";
            case enum_type::category_4: return "Category 4";
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

    static constexpr const char* name = "sale_condition_category";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<sale_condition_category::enum_type>;
    using storage_type = result_type;

    constexpr sale_condition_category()
     : value{ enum_type{} } {}

    constexpr sale_condition_category(enum_type v)
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
            set(enum_type::category_4);
    }

  protected:
    enum_type value;
};
}
