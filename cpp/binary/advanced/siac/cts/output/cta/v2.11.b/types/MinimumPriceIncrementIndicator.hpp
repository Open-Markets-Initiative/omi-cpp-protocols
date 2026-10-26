#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// minimum_price_increment_indicator
struct minimum_price_increment_indicator {

    enum class enum_type : char {
        penny_mpi_001 = '1',
        half_penny_mpi_0005 = '2'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Half Penny Mpi 0.005", enum_type::half_penny_mpi_0005},
        {"Penny Mpi 0.01", enum_type::penny_mpi_001}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::penny_mpi_001: return "Penny Mpi 0.01";
            case enum_type::half_penny_mpi_0005: return "Half Penny Mpi 0.005";
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

    static constexpr const char* name = "minimum_price_increment_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<minimum_price_increment_indicator::enum_type>;
    using storage_type = result_type;

    constexpr minimum_price_increment_indicator()
     : value{ enum_type{} } {}

    constexpr minimum_price_increment_indicator(enum_type v)
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
            set(enum_type::half_penny_mpi_0005);
    }

  protected:
    enum_type value;
};
}
