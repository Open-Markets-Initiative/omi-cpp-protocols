#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// md_volume_type
struct md_volume_type {

    enum class enum_type : std::uint8_t {
        total_limit = 0,
        customer_limit = 1,
        total_contingency_all_or_none = 2,
        customer_contingency_all_or_none = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Customer Contingency All Or None", enum_type::customer_contingency_all_or_none},
        {"Customer Limit", enum_type::customer_limit},
        {"Total Contingency All Or None", enum_type::total_contingency_all_or_none},
        {"Total Limit", enum_type::total_limit}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::total_limit: return "Total Limit";
            case enum_type::customer_limit: return "Customer Limit";
            case enum_type::total_contingency_all_or_none: return "Total Contingency All Or None";
            case enum_type::customer_contingency_all_or_none: return "Customer Contingency All Or None";
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

    static constexpr const char* name = "md_volume_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_volume_type::enum_type>;
    using storage_type = result_type;

    constexpr md_volume_type()
     : value{ enum_type{} } {}

    constexpr md_volume_type(enum_type v)
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
            set(enum_type::customer_contingency_all_or_none);
    }

  protected:
    enum_type value;
};
}
