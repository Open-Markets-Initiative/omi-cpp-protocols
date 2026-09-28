#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// news_source
struct news_source {

    enum class enum_type : std::uint8_t {
        other = 0,
        dcm = 1,
        bbmnet = 2,
        market_surveillance = 3,
        internet = 4,
        dpr_ve = 5,
        mkt_ops_fx_agency = 19,
        mkt_ops_derivatives_agency = 20,
        over_the_counter_news_agency = 11,
        electronic_purchase_exchange = 13,
        cblc_news_agency = 14,
        bovespa_index_agency = 15,
        bovespa_institutional_agency = 16,
        mkt_ops_equities_agency = 17,
        bovespa_companies_agency = 18
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 15> from_string_map = {{
        {"Bbmnet", enum_type::bbmnet},
        {"Bovespa Companies Agency", enum_type::bovespa_companies_agency},
        {"Bovespa Index Agency", enum_type::bovespa_index_agency},
        {"Bovespa Institutional Agency", enum_type::bovespa_institutional_agency},
        {"Cblc News Agency", enum_type::cblc_news_agency},
        {"Dcm", enum_type::dcm},
        {"Dpr Ve", enum_type::dpr_ve},
        {"Electronic Purchase Exchange", enum_type::electronic_purchase_exchange},
        {"Internet", enum_type::internet},
        {"Market Surveillance", enum_type::market_surveillance},
        {"Mkt Ops Derivatives Agency", enum_type::mkt_ops_derivatives_agency},
        {"Mkt Ops Equities Agency", enum_type::mkt_ops_equities_agency},
        {"Mkt Ops Fx Agency", enum_type::mkt_ops_fx_agency},
        {"Other", enum_type::other},
        {"Over The Counter News Agency", enum_type::over_the_counter_news_agency}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::other: return "Other";
            case enum_type::dcm: return "Dcm";
            case enum_type::bbmnet: return "Bbmnet";
            case enum_type::market_surveillance: return "Market Surveillance";
            case enum_type::internet: return "Internet";
            case enum_type::dpr_ve: return "Dpr Ve";
            case enum_type::mkt_ops_fx_agency: return "Mkt Ops Fx Agency";
            case enum_type::mkt_ops_derivatives_agency: return "Mkt Ops Derivatives Agency";
            case enum_type::over_the_counter_news_agency: return "Over The Counter News Agency";
            case enum_type::electronic_purchase_exchange: return "Electronic Purchase Exchange";
            case enum_type::cblc_news_agency: return "Cblc News Agency";
            case enum_type::bovespa_index_agency: return "Bovespa Index Agency";
            case enum_type::bovespa_institutional_agency: return "Bovespa Institutional Agency";
            case enum_type::mkt_ops_equities_agency: return "Mkt Ops Equities Agency";
            case enum_type::bovespa_companies_agency: return "Bovespa Companies Agency";
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

    static constexpr const char* name = "news_source";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<news_source::enum_type>;
    using storage_type = result_type;

    constexpr news_source()
     : value{ enum_type::other } {}

    constexpr news_source(enum_type v)
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
            set(enum_type::bovespa_companies_agency);
    }

  protected:
    enum_type value;
};
}
