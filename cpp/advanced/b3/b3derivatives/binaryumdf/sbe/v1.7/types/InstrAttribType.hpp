#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// instr_attrib_type
struct instr_attrib_type {

    enum class enum_type : std::uint8_t {
        trade_type_eligibility = 24,
        gtd_gtc_eligibility = 34
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Gtd Gtc Eligibility", enum_type::gtd_gtc_eligibility},
        {"Trade Type Eligibility", enum_type::trade_type_eligibility}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::trade_type_eligibility: return "Trade Type Eligibility";
            case enum_type::gtd_gtc_eligibility: return "Gtd Gtc Eligibility";
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

    static constexpr const char* name = "instr_attrib_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<instr_attrib_type::enum_type>;
    using storage_type = result_type;

    constexpr instr_attrib_type()
     : value{ enum_type::trade_type_eligibility } {}

    constexpr instr_attrib_type(enum_type v)
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
            set(enum_type::gtd_gtc_eligibility);
    }

  protected:
    enum_type value;
};
}
