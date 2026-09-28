#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// security_id_source
struct security_id_source {

    enum class enum_type : char {
        isin = '4',
        exchange_symbol = '8'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Exchange Symbol", enum_type::exchange_symbol},
        {"Isin", enum_type::isin}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::isin: return "Isin";
            case enum_type::exchange_symbol: return "Exchange Symbol";
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

    static constexpr const char* name = "security_id_source";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_id_source::enum_type>;
    using storage_type = result_type;

    constexpr security_id_source()
     : value{ enum_type::isin } {}

    constexpr security_id_source(enum_type v)
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
            set(enum_type::exchange_symbol);
    }

  protected:
    enum_type value;
};
}
