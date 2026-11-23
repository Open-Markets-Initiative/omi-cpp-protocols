// B3.B3Derivatives.BinaryUmdf.Sbe.v1.8: types/IssueDate.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// issue_date
struct issue_date {

    enum class enum_type : std::int32_t {
        no_end_date = 2932896
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 1> from_string_map = {{
        {"No End Date", enum_type::no_end_date}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
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

    static constexpr const char* name = "issue_date";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<issue_date::enum_type>;
    using storage_type = result_type;

    constexpr issue_date()
     : value{ enum_type{} } {}

    constexpr issue_date(enum_type v)
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
            set(enum_type::no_end_date);
    }

  protected:
    enum_type value;
};
}
