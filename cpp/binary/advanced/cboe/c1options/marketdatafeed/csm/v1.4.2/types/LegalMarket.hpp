#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// legal_market
struct legal_market {

    enum class enum_type : std::uint8_t {
        not_a_legal_market = 0,
        legal_market = 1
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Legal Market", enum_type::legal_market},
        {"Not A Legal Market", enum_type::not_a_legal_market}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_a_legal_market: return "Not A Legal Market";
            case enum_type::legal_market: return "Legal Market";
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

    static constexpr const char* name = "legal_market";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<legal_market::enum_type>;
    using storage_type = result_type;

    constexpr legal_market()
     : value{ enum_type{} } {}

    constexpr legal_market(enum_type v)
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
            set(enum_type::legal_market);
    }

  protected:
    enum_type value;
};
}
