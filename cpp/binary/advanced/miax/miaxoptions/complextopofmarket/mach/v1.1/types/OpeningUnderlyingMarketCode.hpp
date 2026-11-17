// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: types/OpeningUnderlyingMarketCode.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// opening_underlying_market_code
struct opening_underlying_market_code {

    enum class enum_type : char {
        nyse_amex = 'A',
        nasdaq_omx_bx = 'B',
        nse = 'C',
        finra_adf = 'D',
        market_independent = 'E',
        ise = 'I',
        edga = 'J',
        edgx = 'K',
        cse = 'M',
        nyse_euronext = 'N',
        nyse_arca = 'P',
        nasdaq_omx_utp = 'Q',
        nasdaq_omx_cta = 'T',
        iex = 'V',
        nasdaq_omx_phlx = 'X',
        bats_y = 'Y',
        bats = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 17> from_string_map = {{
        {"Bats", enum_type::bats},
        {"Bats Y", enum_type::bats_y},
        {"Cse", enum_type::cse},
        {"Edga", enum_type::edga},
        {"Edgx", enum_type::edgx},
        {"Finra Adf", enum_type::finra_adf},
        {"Iex", enum_type::iex},
        {"Ise", enum_type::ise},
        {"Market Independent", enum_type::market_independent},
        {"Nasdaq Omx Bx", enum_type::nasdaq_omx_bx},
        {"Nasdaq Omx Cta", enum_type::nasdaq_omx_cta},
        {"Nasdaq Omx Phlx", enum_type::nasdaq_omx_phlx},
        {"Nasdaq Omx Utp", enum_type::nasdaq_omx_utp},
        {"Nse", enum_type::nse},
        {"Nyse Amex", enum_type::nyse_amex},
        {"Nyse Arca", enum_type::nyse_arca},
        {"Nyse Euronext", enum_type::nyse_euronext}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nyse_amex: return "Nyse Amex";
            case enum_type::nasdaq_omx_bx: return "Nasdaq Omx Bx";
            case enum_type::nse: return "Nse";
            case enum_type::finra_adf: return "Finra Adf";
            case enum_type::market_independent: return "Market Independent";
            case enum_type::ise: return "Ise";
            case enum_type::edga: return "Edga";
            case enum_type::edgx: return "Edgx";
            case enum_type::cse: return "Cse";
            case enum_type::nyse_euronext: return "Nyse Euronext";
            case enum_type::nyse_arca: return "Nyse Arca";
            case enum_type::nasdaq_omx_utp: return "Nasdaq Omx Utp";
            case enum_type::nasdaq_omx_cta: return "Nasdaq Omx Cta";
            case enum_type::iex: return "Iex";
            case enum_type::nasdaq_omx_phlx: return "Nasdaq Omx Phlx";
            case enum_type::bats_y: return "Bats Y";
            case enum_type::bats: return "Bats";
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

    static constexpr const char* name = "opening_underlying_market_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<opening_underlying_market_code::enum_type>;
    using storage_type = result_type;

    constexpr opening_underlying_market_code()
     : value{ enum_type{} } {}

    constexpr opening_underlying_market_code(enum_type v)
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
            set(enum_type::bats);
    }

  protected:
    enum_type value;
};
}
