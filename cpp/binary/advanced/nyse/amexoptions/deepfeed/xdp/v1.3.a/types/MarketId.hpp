#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// market_id
struct market_id {

    enum class enum_type : std::uint16_t {
        nyse_cash = 1,
        europe_cash = 2,
        nyse_arca_cash = 3,
        nyse_arca_options = 4,
        nyse_arca_bonds = 5,
        arca_edge = 6,
        liffe = 7,
        nyse_american_options = 8,
        nyse_mkt_cash = 9
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Arca Edge", enum_type::arca_edge},
        {"Europe Cash", enum_type::europe_cash},
        {"Liffe", enum_type::liffe},
        {"Nyse American Options", enum_type::nyse_american_options},
        {"Nyse Arca Bonds", enum_type::nyse_arca_bonds},
        {"Nyse Arca Cash", enum_type::nyse_arca_cash},
        {"Nyse Arca Options", enum_type::nyse_arca_options},
        {"Nyse Cash", enum_type::nyse_cash},
        {"Nyse Mkt Cash", enum_type::nyse_mkt_cash}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nyse_cash: return "Nyse Cash";
            case enum_type::europe_cash: return "Europe Cash";
            case enum_type::nyse_arca_cash: return "Nyse Arca Cash";
            case enum_type::nyse_arca_options: return "Nyse Arca Options";
            case enum_type::nyse_arca_bonds: return "Nyse Arca Bonds";
            case enum_type::arca_edge: return "Arca Edge";
            case enum_type::liffe: return "Liffe";
            case enum_type::nyse_american_options: return "Nyse American Options";
            case enum_type::nyse_mkt_cash: return "Nyse Mkt Cash";
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

    static constexpr const char* name = "market_id";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<market_id::enum_type>;
    using storage_type = result_type;

    constexpr market_id()
     : value{ enum_type{} } {}

    constexpr market_id(enum_type v)
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
            set(enum_type::nyse_mkt_cash);
    }

  protected:
    enum_type value;
};
}
