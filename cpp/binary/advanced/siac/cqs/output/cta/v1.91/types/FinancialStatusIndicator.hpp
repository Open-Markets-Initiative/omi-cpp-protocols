#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// financial_status_indicator
struct financial_status_indicator {

    enum class enum_type : char {
        financial_status_not_applicable = '0',
        bankrupt = '1',
        below_continuing_listing_standards = '2',
        bankrupt_and_below_continuing_listing_standards = '3',
        late_filing = '4',
        bankrupt_and_late_filing = '5',
        below_continuing_listing_standards_and_late_filing = '6',
        bankrupt_below_continuing_listing_standards_and_late_filing = '7',
        creations_suspended = '8',
        redemptions_suspended = '9',
        liquidation = 'A'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 11> from_string_map = {{
        {"Bankrupt", enum_type::bankrupt},
        {"Bankrupt And Below Continuing Listing Standards", enum_type::bankrupt_and_below_continuing_listing_standards},
        {"Bankrupt And Late Filing", enum_type::bankrupt_and_late_filing},
        {"Bankrupt Below Continuing Listing Standards And Late Filing", enum_type::bankrupt_below_continuing_listing_standards_and_late_filing},
        {"Below Continuing Listing Standards", enum_type::below_continuing_listing_standards},
        {"Below Continuing Listing Standards And Late Filing", enum_type::below_continuing_listing_standards_and_late_filing},
        {"Creations Suspended", enum_type::creations_suspended},
        {"Financial Status Not Applicable", enum_type::financial_status_not_applicable},
        {"Late Filing", enum_type::late_filing},
        {"Liquidation", enum_type::liquidation},
        {"Redemptions Suspended", enum_type::redemptions_suspended}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::financial_status_not_applicable: return "Financial Status Not Applicable";
            case enum_type::bankrupt: return "Bankrupt";
            case enum_type::below_continuing_listing_standards: return "Below Continuing Listing Standards";
            case enum_type::bankrupt_and_below_continuing_listing_standards: return "Bankrupt And Below Continuing Listing Standards";
            case enum_type::late_filing: return "Late Filing";
            case enum_type::bankrupt_and_late_filing: return "Bankrupt And Late Filing";
            case enum_type::below_continuing_listing_standards_and_late_filing: return "Below Continuing Listing Standards And Late Filing";
            case enum_type::bankrupt_below_continuing_listing_standards_and_late_filing: return "Bankrupt Below Continuing Listing Standards And Late Filing";
            case enum_type::creations_suspended: return "Creations Suspended";
            case enum_type::redemptions_suspended: return "Redemptions Suspended";
            case enum_type::liquidation: return "Liquidation";
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

    static constexpr const char* name = "financial_status_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<financial_status_indicator::enum_type>;
    using storage_type = result_type;

    constexpr financial_status_indicator()
     : value{ enum_type{} } {}

    constexpr financial_status_indicator(enum_type v)
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
            set(enum_type::liquidation);
    }

  protected:
    enum_type value;
};
}
