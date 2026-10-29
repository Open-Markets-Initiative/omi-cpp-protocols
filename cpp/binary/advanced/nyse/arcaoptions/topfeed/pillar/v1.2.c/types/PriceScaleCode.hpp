#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// price_scale_code
struct price_scale_code {

    enum class enum_type : std::uint8_t {
        low_priced_securities = 6,
        medium_priced_securities = 4,
        high_priced_securities = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"High Priced Securities", enum_type::high_priced_securities},
        {"Low Priced Securities", enum_type::low_priced_securities},
        {"Medium Priced Securities", enum_type::medium_priced_securities}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::low_priced_securities: return "Low Priced Securities";
            case enum_type::medium_priced_securities: return "Medium Priced Securities";
            case enum_type::high_priced_securities: return "High Priced Securities";
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

    static constexpr const char* name = "price_scale_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<price_scale_code::enum_type>;
    using storage_type = result_type;

    constexpr price_scale_code()
     : value{ enum_type{} } {}

    constexpr price_scale_code(enum_type v)
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
            set(enum_type::high_priced_securities);
    }

  protected:
    enum_type value;
};
}
