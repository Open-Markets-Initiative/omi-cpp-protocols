// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/ListingMarket.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// listing_market
struct listing_market {

    enum class enum_type : char {
        tsx = 'T',
        tsx_venture = 'V',
        tsx_na_vex = 'N',
        nasdaq = 'Q',
        nyse = 'S',
        nyse_mkt = 'M',
        no_market = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Nasdaq", enum_type::nasdaq},
        {"No Market", enum_type::no_market},
        {"Nyse", enum_type::nyse},
        {"Nyse Mkt", enum_type::nyse_mkt},
        {"Tsx", enum_type::tsx},
        {"Tsx Na Vex", enum_type::tsx_na_vex},
        {"Tsx Venture", enum_type::tsx_venture}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::tsx: return "Tsx";
            case enum_type::tsx_venture: return "Tsx Venture";
            case enum_type::tsx_na_vex: return "Tsx Na Vex";
            case enum_type::nasdaq: return "Nasdaq";
            case enum_type::nyse: return "Nyse";
            case enum_type::nyse_mkt: return "Nyse Mkt";
            case enum_type::no_market: return "No Market";
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
            set(enum_type::no_market);
    }

  protected:
    enum_type value;
};
}
