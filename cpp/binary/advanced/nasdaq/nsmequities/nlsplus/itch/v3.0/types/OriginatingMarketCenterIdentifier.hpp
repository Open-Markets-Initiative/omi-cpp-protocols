#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// originating_market_center_identifier
struct originating_market_center_identifier {

    enum class enum_type : char {
        nasdaq = 'Q',
        trf_carteret = 'L',
        trf_chicago = '2',
        bx = 'B',
        psx = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Bx", enum_type::bx},
        {"Nasdaq", enum_type::nasdaq},
        {"Psx", enum_type::psx},
        {"Trf Carteret", enum_type::trf_carteret},
        {"Trf Chicago", enum_type::trf_chicago}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nasdaq: return "Nasdaq";
            case enum_type::trf_carteret: return "Trf Carteret";
            case enum_type::trf_chicago: return "Trf Chicago";
            case enum_type::bx: return "Bx";
            case enum_type::psx: return "Psx";
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

    static constexpr const char* name = "originating_market_center_identifier";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<originating_market_center_identifier::enum_type>;
    using storage_type = result_type;

    constexpr originating_market_center_identifier()
     : value{ enum_type{} } {}

    constexpr originating_market_center_identifier(enum_type v)
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
            set(enum_type::psx);
    }

  protected:
    enum_type value;
};
}
