#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// stype_in
struct stype_in {

    enum class enum_type : std::uint8_t {
        instrument_id = 0,
        raw_symbol = 1,
        smart = 2,
        continuous = 3,
        parent = 4,
        nasdaq_symbol = 5,
        cms_symbol = 6,
        isin = 7,
        us_code = 8,
        bbg_comp_id = 9,
        bbg_comp_ticker = 10,
        figi = 11,
        figi_ticker = 12,
        listing_id = 13,
        issuer_id = 14,
        security_id = 15,
        no_value = 255
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 17> from_string_map = {{
        {"Bbg Comp Id", enum_type::bbg_comp_id},
        {"Bbg Comp Ticker", enum_type::bbg_comp_ticker},
        {"Cms Symbol", enum_type::cms_symbol},
        {"Continuous", enum_type::continuous},
        {"Figi", enum_type::figi},
        {"Figi Ticker", enum_type::figi_ticker},
        {"Instrument Id", enum_type::instrument_id},
        {"Isin", enum_type::isin},
        {"Issuer Id", enum_type::issuer_id},
        {"Listing Id", enum_type::listing_id},
        {"Nasdaq Symbol", enum_type::nasdaq_symbol},
        {"No Value", enum_type::no_value},
        {"Parent", enum_type::parent},
        {"Raw Symbol", enum_type::raw_symbol},
        {"Security Id", enum_type::security_id},
        {"Smart", enum_type::smart},
        {"Us Code", enum_type::us_code}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::instrument_id: return "Instrument Id";
            case enum_type::raw_symbol: return "Raw Symbol";
            case enum_type::smart: return "Smart";
            case enum_type::continuous: return "Continuous";
            case enum_type::parent: return "Parent";
            case enum_type::nasdaq_symbol: return "Nasdaq Symbol";
            case enum_type::cms_symbol: return "Cms Symbol";
            case enum_type::isin: return "Isin";
            case enum_type::us_code: return "Us Code";
            case enum_type::bbg_comp_id: return "Bbg Comp Id";
            case enum_type::bbg_comp_ticker: return "Bbg Comp Ticker";
            case enum_type::figi: return "Figi";
            case enum_type::figi_ticker: return "Figi Ticker";
            case enum_type::listing_id: return "Listing Id";
            case enum_type::issuer_id: return "Issuer Id";
            case enum_type::security_id: return "Security Id";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "stype_in";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<stype_in::enum_type>;
    using storage_type = result_type;

    constexpr stype_in()
     : value{ static_cast<enum_type>(255) } {}

    constexpr stype_in(enum_type v)
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
            set(static_cast<enum_type>(255));
    }

  protected:
    enum_type value;
};
}
