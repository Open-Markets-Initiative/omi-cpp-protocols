#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// listing_market
struct listing_market {

    enum class enum_type : char {
        tsx = 'T',
        venture = 'V',
        cse = 'C',
        neo = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Cse", enum_type::cse},
        {"Neo", enum_type::neo},
        {"Tsx", enum_type::tsx},
        {"Venture", enum_type::venture}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::tsx: return "Tsx";
            case enum_type::venture: return "Venture";
            case enum_type::cse: return "Cse";
            case enum_type::neo: return "Neo";
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

    static constexpr const char* name = "listing_market";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<listing_market::enum_type>;
    using storage_type = result_type;

    constexpr listing_market()
     : value{ enum_type{} } {}

    constexpr listing_market(enum_type v)
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
            set(enum_type::neo);
    }

  protected:
    enum_type value;
};
}
