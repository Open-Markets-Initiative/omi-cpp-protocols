// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SpinType.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// spin_type
struct spin_type {

    enum class enum_type : std::uint8_t {
        reference = 1,
        market_data = 2,
        opening = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Market Data", enum_type::market_data},
        {"Opening", enum_type::opening},
        {"Reference", enum_type::reference}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::reference: return "Reference";
            case enum_type::market_data: return "Market Data";
            case enum_type::opening: return "Opening";
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

    static constexpr const char* name = "spin_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<spin_type::enum_type>;
    using storage_type = result_type;

    constexpr spin_type()
     : value{ enum_type{} } {}

    constexpr spin_type(enum_type v)
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
            set(enum_type::opening);
    }

  protected:
    enum_type value;
};
}
