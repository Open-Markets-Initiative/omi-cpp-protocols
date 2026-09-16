#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// financial_status_indicator
struct financial_status_indicator {

    enum class enum_type : char {
        deficient = 'D',
        delinquent = 'E',
        bankrupt = 'Q',
        suspended = 'S',
        deficient_and_bankrupt = 'G',
        deficient_and_delinquent = 'H',
        delinquent_and_bankrupt = 'J',
        deficient_delinquent_and_bankrupt = 'K',
        creations_and_redemptions_suspended = 'C',
        normal = 'N',
        not_available = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 11> from_string_map = {{
        {"Bankrupt", enum_type::bankrupt},
        {"Creations And Redemptions Suspended", enum_type::creations_and_redemptions_suspended},
        {"Deficient", enum_type::deficient},
        {"Deficient And Bankrupt", enum_type::deficient_and_bankrupt},
        {"Deficient And Delinquent", enum_type::deficient_and_delinquent},
        {"Deficient Delinquent And Bankrupt", enum_type::deficient_delinquent_and_bankrupt},
        {"Delinquent", enum_type::delinquent},
        {"Delinquent And Bankrupt", enum_type::delinquent_and_bankrupt},
        {"Normal", enum_type::normal},
        {"Not Available", enum_type::not_available},
        {"Suspended", enum_type::suspended}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::deficient: return "Deficient";
            case enum_type::delinquent: return "Delinquent";
            case enum_type::bankrupt: return "Bankrupt";
            case enum_type::suspended: return "Suspended";
            case enum_type::deficient_and_bankrupt: return "Deficient And Bankrupt";
            case enum_type::deficient_and_delinquent: return "Deficient And Delinquent";
            case enum_type::delinquent_and_bankrupt: return "Delinquent And Bankrupt";
            case enum_type::deficient_delinquent_and_bankrupt: return "Deficient Delinquent And Bankrupt";
            case enum_type::creations_and_redemptions_suspended: return "Creations And Redemptions Suspended";
            case enum_type::normal: return "Normal";
            case enum_type::not_available: return "Not Available";
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
     : value{ enum_type::deficient } {}

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
            set(enum_type::not_available);
    }

  protected:
    enum_type value;
};
}
