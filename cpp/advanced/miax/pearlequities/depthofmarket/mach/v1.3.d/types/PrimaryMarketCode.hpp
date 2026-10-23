#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// primary_market_code
struct primary_market_code {

    enum class enum_type : char {
        nyse_american = 'A',
        nasdaq_texas = 'B',
        nyse_national = 'C',
        texas_stock_exchange = 'F',
        n24x_exchange = 'G',
        miax_pearl_equities = 'H',
        nasdaq_ise = 'I',
        cboe_edga_exchange = 'J',
        cboe_edgx_exchange = 'K',
        long_term_stock_exchange = 'L',
        nyse_texas = 'M',
        new_york_stock_exchange = 'N',
        nyse_arca = 'P',
        nasdaq = 'Q',
        members_exchange = 'U',
        investors_exchange = 'V',
        cboe_stock_exchange = 'W',
        nasdaq_phlx = 'X',
        cboe_byx_exchange = 'Y',
        cboe_bzx_exchange = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 20> from_string_map = {{
        {"Cboe Byx Exchange", enum_type::cboe_byx_exchange},
        {"Cboe Bzx Exchange", enum_type::cboe_bzx_exchange},
        {"Cboe Edga Exchange", enum_type::cboe_edga_exchange},
        {"Cboe Edgx Exchange", enum_type::cboe_edgx_exchange},
        {"Cboe Stock Exchange", enum_type::cboe_stock_exchange},
        {"Investors Exchange", enum_type::investors_exchange},
        {"Long Term Stock Exchange", enum_type::long_term_stock_exchange},
        {"Members Exchange", enum_type::members_exchange},
        {"Miax Pearl Equities", enum_type::miax_pearl_equities},
        {"N24X Exchange", enum_type::n24x_exchange},
        {"Nasdaq", enum_type::nasdaq},
        {"Nasdaq Ise", enum_type::nasdaq_ise},
        {"Nasdaq Phlx", enum_type::nasdaq_phlx},
        {"Nasdaq Texas", enum_type::nasdaq_texas},
        {"New York Stock Exchange", enum_type::new_york_stock_exchange},
        {"Nyse American", enum_type::nyse_american},
        {"Nyse Arca", enum_type::nyse_arca},
        {"Nyse National", enum_type::nyse_national},
        {"Nyse Texas", enum_type::nyse_texas},
        {"Texas Stock Exchange", enum_type::texas_stock_exchange}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nyse_american: return "Nyse American";
            case enum_type::nasdaq_texas: return "Nasdaq Texas";
            case enum_type::nyse_national: return "Nyse National";
            case enum_type::texas_stock_exchange: return "Texas Stock Exchange";
            case enum_type::n24x_exchange: return "N24X Exchange";
            case enum_type::miax_pearl_equities: return "Miax Pearl Equities";
            case enum_type::nasdaq_ise: return "Nasdaq Ise";
            case enum_type::cboe_edga_exchange: return "Cboe Edga Exchange";
            case enum_type::cboe_edgx_exchange: return "Cboe Edgx Exchange";
            case enum_type::long_term_stock_exchange: return "Long Term Stock Exchange";
            case enum_type::nyse_texas: return "Nyse Texas";
            case enum_type::new_york_stock_exchange: return "New York Stock Exchange";
            case enum_type::nyse_arca: return "Nyse Arca";
            case enum_type::nasdaq: return "Nasdaq";
            case enum_type::members_exchange: return "Members Exchange";
            case enum_type::investors_exchange: return "Investors Exchange";
            case enum_type::cboe_stock_exchange: return "Cboe Stock Exchange";
            case enum_type::nasdaq_phlx: return "Nasdaq Phlx";
            case enum_type::cboe_byx_exchange: return "Cboe Byx Exchange";
            case enum_type::cboe_bzx_exchange: return "Cboe Bzx Exchange";
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

    static constexpr const char* name = "primary_market_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<primary_market_code::enum_type>;
    using storage_type = result_type;

    constexpr primary_market_code()
     : value{ enum_type{} } {}

    constexpr primary_market_code(enum_type v)
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
            set(enum_type::cboe_bzx_exchange);
    }

  protected:
    enum_type value;
};
}
