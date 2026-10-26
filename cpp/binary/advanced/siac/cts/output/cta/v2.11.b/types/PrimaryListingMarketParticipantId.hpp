#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// primary_listing_market_participant_id
struct primary_listing_market_participant_id {

    enum class enum_type : char {
        primary_listing_market_participant_id_not_applicable = ' ',
        nyse_american = 'A',
        nasdaq_bx = 'B',
        nyse_national = 'C',
        finra_adf = 'D',
        texas_stock_exchange = 'F',
        n24x = 'G',
        miax_pearl = 'H',
        ise = 'I',
        cboe_edga = 'J',
        cboe_edgx = 'K',
        ltse = 'L',
        nyse_texas = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'T',
        members_exchange = 'U',
        iex = 'V',
        cbsx = 'W',
        nasdaq_omx_psx = 'X',
        cboe_byx = 'Y',
        cboe_bzx = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 22> from_string_map = {{
        {"Cboe Byx", enum_type::cboe_byx},
        {"Cboe Bzx", enum_type::cboe_bzx},
        {"Cboe Edga", enum_type::cboe_edga},
        {"Cboe Edgx", enum_type::cboe_edgx},
        {"Cbsx", enum_type::cbsx},
        {"Finra Adf", enum_type::finra_adf},
        {"Iex", enum_type::iex},
        {"Ise", enum_type::ise},
        {"Ltse", enum_type::ltse},
        {"Members Exchange", enum_type::members_exchange},
        {"Miax Pearl", enum_type::miax_pearl},
        {"N24X", enum_type::n24x},
        {"Nasdaq", enum_type::nasdaq},
        {"Nasdaq Bx", enum_type::nasdaq_bx},
        {"Nasdaq Omx Psx", enum_type::nasdaq_omx_psx},
        {"Nyse", enum_type::nyse},
        {"Nyse American", enum_type::nyse_american},
        {"Nyse Arca", enum_type::nyse_arca},
        {"Nyse National", enum_type::nyse_national},
        {"Nyse Texas", enum_type::nyse_texas},
        {"Primary Listing Market Participant Id Not Applicable", enum_type::primary_listing_market_participant_id_not_applicable},
        {"Texas Stock Exchange", enum_type::texas_stock_exchange}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::primary_listing_market_participant_id_not_applicable: return "Primary Listing Market Participant Id Not Applicable";
            case enum_type::nyse_american: return "Nyse American";
            case enum_type::nasdaq_bx: return "Nasdaq Bx";
            case enum_type::nyse_national: return "Nyse National";
            case enum_type::finra_adf: return "Finra Adf";
            case enum_type::texas_stock_exchange: return "Texas Stock Exchange";
            case enum_type::n24x: return "N24X";
            case enum_type::miax_pearl: return "Miax Pearl";
            case enum_type::ise: return "Ise";
            case enum_type::cboe_edga: return "Cboe Edga";
            case enum_type::cboe_edgx: return "Cboe Edgx";
            case enum_type::ltse: return "Ltse";
            case enum_type::nyse_texas: return "Nyse Texas";
            case enum_type::nyse: return "Nyse";
            case enum_type::nyse_arca: return "Nyse Arca";
            case enum_type::nasdaq: return "Nasdaq";
            case enum_type::members_exchange: return "Members Exchange";
            case enum_type::iex: return "Iex";
            case enum_type::cbsx: return "Cbsx";
            case enum_type::nasdaq_omx_psx: return "Nasdaq Omx Psx";
            case enum_type::cboe_byx: return "Cboe Byx";
            case enum_type::cboe_bzx: return "Cboe Bzx";
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

    static constexpr const char* name = "primary_listing_market_participant_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<primary_listing_market_participant_id::enum_type>;
    using storage_type = result_type;

    constexpr primary_listing_market_participant_id()
     : value{ enum_type{} } {}

    constexpr primary_listing_market_participant_id(enum_type v)
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
            set(enum_type::cboe_bzx);
    }

  protected:
    enum_type value;
};
}
