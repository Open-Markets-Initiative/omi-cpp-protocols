// B3.B3Derivatives.BinaryUmdf.Sbe.v1.6: types/DatedDate.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// dated_date
struct dated_date {

    enum class enum_type : std::int32_t {
        no_value = 0,
        no_end_date = 2932896
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"No End Date", enum_type::no_end_date},
        {"No Value", enum_type::no_value}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_value: return "No Value";
            case enum_type::no_end_date: return "No End Date";
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

    static constexpr const char* name = "dated_date";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = true;
    static constexpr enum_type null_value = static_cast<enum_type>(0);

    using result_type = std::optional<dated_date::enum_type>;
    using storage_type = result_type;

    constexpr dated_date()
     : value{ static_cast<enum_type>(0) } {}

    constexpr dated_date(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        const enum_type held = value;
        return held == null_value ? std::nullopt : result_type{held};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        set(null_value);
    }

  protected:
    enum_type value;
};
}
