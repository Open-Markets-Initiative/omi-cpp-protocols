#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// opening_underlying_market_code
struct opening_underlying_market_code {

    enum class enum_type : char {
        nyse_amex = 'A',
        nasdaq_omx_bx = 'B',
        national_stock_exchange = 'C',
        finra_adf = 'D',
        market_independent = 'E',
        miax_pearl_equities = 'H',
        international_securities_exchange = 'I',
        edga_exchange_inc = 'J',
        edgx_exchange_inc = 'K',
        ltse = 'L',
        chicago_stock_exchange = 'M',
        nyse_euronext = 'N',
        nyse_arca_exchange = 'P',
        nasdaq_omx_utp = 'Q',
        nasdaq_omx_cta = 'T',
        memx = 'U',
        iex = 'V',
        cboe_stock_exchange = 'W',
        nasdaq_omx_phlx = 'X',
        bats_y = 'Y',
        bats = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 21> from_string_map = {{
        {"Bats", enum_type::bats},
        {"Bats Y", enum_type::bats_y},
        {"Cboe Stock Exchange", enum_type::cboe_stock_exchange},
        {"Chicago Stock Exchange", enum_type::chicago_stock_exchange},
        {"Edga Exchange Inc", enum_type::edga_exchange_inc},
        {"Edgx Exchange Inc", enum_type::edgx_exchange_inc},
        {"Finra Adf", enum_type::finra_adf},
        {"Iex", enum_type::iex},
        {"International Securities Exchange", enum_type::international_securities_exchange},
        {"Ltse", enum_type::ltse},
        {"Market Independent", enum_type::market_independent},
        {"Memx", enum_type::memx},
        {"Miax Pearl Equities", enum_type::miax_pearl_equities},
        {"Nasdaq Omx Bx", enum_type::nasdaq_omx_bx},
        {"Nasdaq Omx Cta", enum_type::nasdaq_omx_cta},
        {"Nasdaq Omx Phlx", enum_type::nasdaq_omx_phlx},
        {"Nasdaq Omx Utp", enum_type::nasdaq_omx_utp},
        {"National Stock Exchange", enum_type::national_stock_exchange},
        {"Nyse Amex", enum_type::nyse_amex},
        {"Nyse Arca Exchange", enum_type::nyse_arca_exchange},
        {"Nyse Euronext", enum_type::nyse_euronext}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nyse_amex: return "Nyse Amex";
            case enum_type::nasdaq_omx_bx: return "Nasdaq Omx Bx";
            case enum_type::national_stock_exchange: return "National Stock Exchange";
            case enum_type::finra_adf: return "Finra Adf";
            case enum_type::market_independent: return "Market Independent";
            case enum_type::miax_pearl_equities: return "Miax Pearl Equities";
            case enum_type::international_securities_exchange: return "International Securities Exchange";
            case enum_type::edga_exchange_inc: return "Edga Exchange Inc";
            case enum_type::edgx_exchange_inc: return "Edgx Exchange Inc";
            case enum_type::ltse: return "Ltse";
            case enum_type::chicago_stock_exchange: return "Chicago Stock Exchange";
            case enum_type::nyse_euronext: return "Nyse Euronext";
            case enum_type::nyse_arca_exchange: return "Nyse Arca Exchange";
            case enum_type::nasdaq_omx_utp: return "Nasdaq Omx Utp";
            case enum_type::nasdaq_omx_cta: return "Nasdaq Omx Cta";
            case enum_type::memx: return "Memx";
            case enum_type::iex: return "Iex";
            case enum_type::cboe_stock_exchange: return "Cboe Stock Exchange";
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
