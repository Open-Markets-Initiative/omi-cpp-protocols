// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/ReportingStatus.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// reporting_status
struct reporting_status {

    enum class enum_type : char {
        alternative_reporting = 'A',
        bank_thrift = 'B',
        sec_reporting = 'F',
        international_reporting = 'G',
        insurance_company = 'I',
        no_reporting = 'N',
        other_reporting = 'O',
        finra_reporting = 'R',
        sec_investment_company = 'V',
        sec_reg_a = 'W'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 10> from_string_map = {{
        {"Alternative Reporting", enum_type::alternative_reporting},
        {"Bank Thrift", enum_type::bank_thrift},
        {"Finra Reporting", enum_type::finra_reporting},
        {"Insurance Company", enum_type::insurance_company},
        {"International Reporting", enum_type::international_reporting},
        {"No Reporting", enum_type::no_reporting},
        {"Other Reporting", enum_type::other_reporting},
        {"Sec Investment Company", enum_type::sec_investment_company},
        {"Sec Reg A", enum_type::sec_reg_a},
        {"Sec Reporting", enum_type::sec_reporting}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::alternative_reporting: return "Alternative Reporting";
            case enum_type::bank_thrift: return "Bank Thrift";
            case enum_type::sec_reporting: return "Sec Reporting";
            case enum_type::international_reporting: return "International Reporting";
            case enum_type::insurance_company: return "Insurance Company";
            case enum_type::no_reporting: return "No Reporting";
            case enum_type::other_reporting: return "Other Reporting";
            case enum_type::finra_reporting: return "Finra Reporting";
            case enum_type::sec_investment_company: return "Sec Investment Company";
            case enum_type::sec_reg_a: return "Sec Reg A";
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

    static constexpr const char* name = "reporting_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<reporting_status::enum_type>;
    using storage_type = result_type;

    constexpr reporting_status()
     : value{ enum_type{} } {}

    constexpr reporting_status(enum_type v)
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
            set(enum_type::sec_reg_a);
    }

  protected:
    enum_type value;
};
}
