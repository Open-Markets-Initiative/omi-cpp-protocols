#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// alloc_report_type
struct alloc_report_type {

    enum class enum_type : char {
        request_to_intermediary = '8'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 1> from_string_map = {{
        {"Request To Intermediary", enum_type::request_to_intermediary}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::request_to_intermediary: return "Request To Intermediary";
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

    static constexpr const char* name = "alloc_report_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<alloc_report_type::enum_type>;
    using storage_type = result_type;

    constexpr alloc_report_type()
     : value{ enum_type{} } {}

    constexpr alloc_report_type(enum_type v)
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
            set(enum_type::request_to_intermediary);
    }

  protected:
    enum_type value;
};
}
