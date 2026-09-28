#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// opt_payout_type
struct opt_payout_type {

    enum class enum_type : std::uint8_t {
        vanilla = 1,
        capped = 2,
        binary = 3,
        no_value = 0
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Binary", enum_type::binary},
        {"Capped", enum_type::capped},
        {"No Value", enum_type::no_value},
        {"Vanilla", enum_type::vanilla}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::vanilla: return "Vanilla";
            case enum_type::capped: return "Capped";
            case enum_type::binary: return "Binary";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "opt_payout_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<opt_payout_type::enum_type>;
    using storage_type = result_type;

    constexpr opt_payout_type()
     : value{ enum_type::vanilla } {}

    constexpr opt_payout_type(enum_type v)
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
            set(static_cast<enum_type>(0));
    }

  protected:
    enum_type value;
};
}
