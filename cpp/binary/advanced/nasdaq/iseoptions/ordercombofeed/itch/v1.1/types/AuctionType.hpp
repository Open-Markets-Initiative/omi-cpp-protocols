#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// auction_type
struct auction_type {

    enum class enum_type : char {
        exposure = 'E',
        facilitation = 'C',
        solicitation = 'S',
        pim = 'P'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Exposure", enum_type::exposure},
        {"Facilitation", enum_type::facilitation},
        {"Pim", enum_type::pim},
        {"Solicitation", enum_type::solicitation}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::exposure: return "Exposure";
            case enum_type::facilitation: return "Facilitation";
            case enum_type::solicitation: return "Solicitation";
            case enum_type::pim: return "Pim";
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

    static constexpr const char* name = "auction_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<auction_type::enum_type>;
    using storage_type = result_type;

    constexpr auction_type()
     : value{ enum_type{} } {}

    constexpr auction_type(enum_type v)
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
            set(enum_type::pim);
    }

  protected:
    enum_type value;
};
}
