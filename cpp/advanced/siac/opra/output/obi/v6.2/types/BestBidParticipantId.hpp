#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::opra::output::obi::v6_2 {

// best_bid_participant_id
struct best_bid_participant_id {

    enum class enum_type : char {
        nyse_american = 'A',
        boston_options_exchange = 'B',
        cboe_options_exchange = 'C',
        miax_emerald = 'D',
        cboe_edgx_options = 'E',
        nasdaq_gemx = 'H',
        nasdaq_ise = 'I',
        nasdaq_mrx = 'J',
        miami_international_securities_exchange = 'M',
        nyse_arca = 'N',
        options_price_reporting_authority = 'O',
        miax_pearl = 'P',
        nasdaq_options_market = 'Q',
        nasdaq_bx_options = 'T',
        cboe_c_2_options = 'W',
        nasdaq_phlx = 'X',
        cboe_bzx_options_exchange = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 17> from_string_map = {{
        {"Boston Options Exchange", enum_type::boston_options_exchange},
        {"Cboe Bzx Options Exchange", enum_type::cboe_bzx_options_exchange},
        {"Cboe C 2 Options", enum_type::cboe_c_2_options},
        {"Cboe Edgx Options", enum_type::cboe_edgx_options},
        {"Cboe Options Exchange", enum_type::cboe_options_exchange},
        {"Miami International Securities Exchange", enum_type::miami_international_securities_exchange},
        {"Miax Emerald", enum_type::miax_emerald},
        {"Miax Pearl", enum_type::miax_pearl},
        {"Nasdaq Bx Options", enum_type::nasdaq_bx_options},
        {"Nasdaq Gemx", enum_type::nasdaq_gemx},
        {"Nasdaq Ise", enum_type::nasdaq_ise},
        {"Nasdaq Mrx", enum_type::nasdaq_mrx},
        {"Nasdaq Options Market", enum_type::nasdaq_options_market},
        {"Nasdaq Phlx", enum_type::nasdaq_phlx},
        {"Nyse American", enum_type::nyse_american},
        {"Nyse Arca", enum_type::nyse_arca},
        {"Options Price Reporting Authority", enum_type::options_price_reporting_authority}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nyse_american: return "Nyse American";
            case enum_type::boston_options_exchange: return "Boston Options Exchange";
            case enum_type::cboe_options_exchange: return "Cboe Options Exchange";
            case enum_type::miax_emerald: return "Miax Emerald";
            case enum_type::cboe_edgx_options: return "Cboe Edgx Options";
            case enum_type::nasdaq_gemx: return "Nasdaq Gemx";
            case enum_type::nasdaq_ise: return "Nasdaq Ise";
            case enum_type::nasdaq_mrx: return "Nasdaq Mrx";
            case enum_type::miami_international_securities_exchange: return "Miami International Securities Exchange";
            case enum_type::nyse_arca: return "Nyse Arca";
            case enum_type::options_price_reporting_authority: return "Options Price Reporting Authority";
            case enum_type::miax_pearl: return "Miax Pearl";
            case enum_type::nasdaq_options_market: return "Nasdaq Options Market";
            case enum_type::nasdaq_bx_options: return "Nasdaq Bx Options";
            case enum_type::cboe_c_2_options: return "Cboe C 2 Options";
            case enum_type::nasdaq_phlx: return "Nasdaq Phlx";
            case enum_type::cboe_bzx_options_exchange: return "Cboe Bzx Options Exchange";
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

    static constexpr const char* name = "best_bid_participant_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<best_bid_participant_id::enum_type>;
    using storage_type = result_type;

    constexpr best_bid_participant_id()
     : value{ enum_type{} } {}

    constexpr best_bid_participant_id(enum_type v)
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
            set(enum_type::cboe_bzx_options_exchange);
    }

  protected:
    enum_type value;
};
}
