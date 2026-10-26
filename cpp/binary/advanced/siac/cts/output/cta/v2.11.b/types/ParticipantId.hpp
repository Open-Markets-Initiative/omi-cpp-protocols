#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// participant_id
struct participant_id {

    enum class enum_type : char {
        nyse_american_llc_nyse_american = 'A',
        nasdaq_omx_bx_inc_nasdaq_omx_bx = 'B',
        nyse_national_inc_nyse_national = 'C',
        finra_alternative_display_facility_adf = 'D',
        texas_stock_exchange_llc_txse = 'F',
        n24x_national_exchange_llc_24x = 'G',
        miax_pearl_exchange_llc_miax = 'H',
        international_securities_exchange_llc_ise = 'I',
        cboe_edga_exchange_inc_cboe_edga = 'J',
        cboe_edgx_exchange_inc_cboe_edgx = 'K',
        long_term_stock_exchange_inc_ltse = 'L',
        nyse_texas_inc_nyse_texas = 'M',
        new_york_stock_exchange_llc_nyse = 'N',
        nyse_arca_inc_nyse_arca = 'P',
        consolidated_tape_system_cts = 'S',
        nasdaq_stock_market_llc_nasdaq = 'T',
        members_exchange_llc_memx = 'U',
        investors_exchange_llc_iex = 'V',
        cboe_stock_exchange_inc_cbsx = 'W',
        nasdaq_omx_psx_inc_nasdaq_omx_psx = 'X',
        cboe_byx_exchange_inc_cboe_byx = 'Y',
        cboe_bzx_exchange_inc_cboe_bzx = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 22> from_string_map = {{
        {"Cboe Byx Exchange Inc Cboe Byx", enum_type::cboe_byx_exchange_inc_cboe_byx},
        {"Cboe Bzx Exchange Inc Cboe Bzx", enum_type::cboe_bzx_exchange_inc_cboe_bzx},
        {"Cboe Edga Exchange Inc Cboe Edga", enum_type::cboe_edga_exchange_inc_cboe_edga},
        {"Cboe Edgx Exchange Inc Cboe Edgx", enum_type::cboe_edgx_exchange_inc_cboe_edgx},
        {"Cboe Stock Exchange Inc Cbsx", enum_type::cboe_stock_exchange_inc_cbsx},
        {"Consolidated Tape System Cts", enum_type::consolidated_tape_system_cts},
        {"Finra Alternative Display Facility Adf", enum_type::finra_alternative_display_facility_adf},
        {"International Securities Exchange Llc Ise", enum_type::international_securities_exchange_llc_ise},
        {"Investors Exchange Llc Iex", enum_type::investors_exchange_llc_iex},
        {"Long Term Stock Exchange Inc Ltse", enum_type::long_term_stock_exchange_inc_ltse},
        {"Members Exchange Llc Memx", enum_type::members_exchange_llc_memx},
        {"Miax Pearl Exchange Llc Miax", enum_type::miax_pearl_exchange_llc_miax},
        {"N24X National Exchange LLC 24X", enum_type::n24x_national_exchange_llc_24x},
        {"Nasdaq Omx Bx Inc Nasdaq Omx Bx", enum_type::nasdaq_omx_bx_inc_nasdaq_omx_bx},
        {"Nasdaq Omx Psx Inc Nasdaq Omx Psx", enum_type::nasdaq_omx_psx_inc_nasdaq_omx_psx},
        {"Nasdaq Stock Market Llc Nasdaq", enum_type::nasdaq_stock_market_llc_nasdaq},
        {"New York Stock Exchange Llc Nyse", enum_type::new_york_stock_exchange_llc_nyse},
        {"Nyse American Llc Nyse American", enum_type::nyse_american_llc_nyse_american},
        {"Nyse Arca Inc Nyse Arca", enum_type::nyse_arca_inc_nyse_arca},
        {"Nyse National Inc Nyse National", enum_type::nyse_national_inc_nyse_national},
        {"Nyse Texas Inc Nyse Texas", enum_type::nyse_texas_inc_nyse_texas},
        {"Texas Stock Exchange Llc Txse", enum_type::texas_stock_exchange_llc_txse}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nyse_american_llc_nyse_american: return "Nyse American Llc Nyse American";
            case enum_type::nasdaq_omx_bx_inc_nasdaq_omx_bx: return "Nasdaq Omx Bx Inc Nasdaq Omx Bx";
            case enum_type::nyse_national_inc_nyse_national: return "Nyse National Inc Nyse National";
            case enum_type::finra_alternative_display_facility_adf: return "Finra Alternative Display Facility Adf";
            case enum_type::texas_stock_exchange_llc_txse: return "Texas Stock Exchange Llc Txse";
            case enum_type::n24x_national_exchange_llc_24x: return "N24X National Exchange LLC 24X";
            case enum_type::miax_pearl_exchange_llc_miax: return "Miax Pearl Exchange Llc Miax";
            case enum_type::international_securities_exchange_llc_ise: return "International Securities Exchange Llc Ise";
            case enum_type::cboe_edga_exchange_inc_cboe_edga: return "Cboe Edga Exchange Inc Cboe Edga";
            case enum_type::cboe_edgx_exchange_inc_cboe_edgx: return "Cboe Edgx Exchange Inc Cboe Edgx";
            case enum_type::long_term_stock_exchange_inc_ltse: return "Long Term Stock Exchange Inc Ltse";
            case enum_type::nyse_texas_inc_nyse_texas: return "Nyse Texas Inc Nyse Texas";
            case enum_type::new_york_stock_exchange_llc_nyse: return "New York Stock Exchange Llc Nyse";
            case enum_type::nyse_arca_inc_nyse_arca: return "Nyse Arca Inc Nyse Arca";
            case enum_type::consolidated_tape_system_cts: return "Consolidated Tape System Cts";
            case enum_type::nasdaq_stock_market_llc_nasdaq: return "Nasdaq Stock Market Llc Nasdaq";
            case enum_type::members_exchange_llc_memx: return "Members Exchange Llc Memx";
            case enum_type::investors_exchange_llc_iex: return "Investors Exchange Llc Iex";
            case enum_type::cboe_stock_exchange_inc_cbsx: return "Cboe Stock Exchange Inc Cbsx";
            case enum_type::nasdaq_omx_psx_inc_nasdaq_omx_psx: return "Nasdaq Omx Psx Inc Nasdaq Omx Psx";
            case enum_type::cboe_byx_exchange_inc_cboe_byx: return "Cboe Byx Exchange Inc Cboe Byx";
            case enum_type::cboe_bzx_exchange_inc_cboe_bzx: return "Cboe Bzx Exchange Inc Cboe Bzx";
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

    static constexpr const char* name = "participant_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<participant_id::enum_type>;
    using storage_type = result_type;

    constexpr participant_id()
     : value{ enum_type{} } {}

    constexpr participant_id(enum_type v)
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
            set(enum_type::cboe_bzx_exchange_inc_cboe_bzx);
    }

  protected:
    enum_type value;
};
}
