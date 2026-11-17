// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/Tier.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// tier
struct tier {

    enum class enum_type : std::uint8_t {
        no_tier = 0,
        otcqxus_premier = 1,
        otcqxus = 2,
        otcqx_international_premier = 5,
        otcqx_international = 6,
        otcqb = 10,
        otcbb_only = 11,
        pink_current = 20,
        pink_limited = 21,
        pink_no_information = 22,
        grey_market = 30,
        expert_market = 40,
        otc_bonds = 50
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 13> from_string_map = {{
        {"Expert Market", enum_type::expert_market},
        {"Grey Market", enum_type::grey_market},
        {"No Tier", enum_type::no_tier},
        {"Otc Bonds", enum_type::otc_bonds},
        {"Otcbb Only", enum_type::otcbb_only},
        {"Otcqb", enum_type::otcqb},
        {"Otcqx International", enum_type::otcqx_international},
        {"Otcqx International Premier", enum_type::otcqx_international_premier},
        {"Otcqxus", enum_type::otcqxus},
        {"Otcqxus Premier", enum_type::otcqxus_premier},
        {"Pink Current", enum_type::pink_current},
        {"Pink Limited", enum_type::pink_limited},
        {"Pink No Information", enum_type::pink_no_information}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_tier: return "No Tier";
            case enum_type::otcqxus_premier: return "Otcqxus Premier";
            case enum_type::otcqxus: return "Otcqxus";
            case enum_type::otcqx_international_premier: return "Otcqx International Premier";
            case enum_type::otcqx_international: return "Otcqx International";
            case enum_type::otcqb: return "Otcqb";
            case enum_type::otcbb_only: return "Otcbb Only";
            case enum_type::pink_current: return "Pink Current";
            case enum_type::pink_limited: return "Pink Limited";
            case enum_type::pink_no_information: return "Pink No Information";
            case enum_type::grey_market: return "Grey Market";
            case enum_type::expert_market: return "Expert Market";
            case enum_type::otc_bonds: return "Otc Bonds";
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

    static constexpr const char* name = "tier";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<tier::enum_type>;
    using storage_type = result_type;

    constexpr tier()
     : value{ enum_type{} } {}

    constexpr tier(enum_type v)
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
            set(enum_type::otc_bonds);
    }

  protected:
    enum_type value;
};
}
