#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// customer_firm_indicator
struct customer_firm_indicator {

    enum class enum_type : char {
        customer = 'C',
        firm_joint = 'F',
        on_floor = 'M',
        professional = 'P',
        broker_dealer_non_registered = 'B'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Broker Dealer Non Registered", enum_type::broker_dealer_non_registered},
        {"Customer", enum_type::customer},
        {"Firm Joint", enum_type::firm_joint},
        {"On Floor", enum_type::on_floor},
        {"Professional", enum_type::professional}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::customer: return "Customer";
            case enum_type::firm_joint: return "Firm Joint";
            case enum_type::on_floor: return "On Floor";
            case enum_type::professional: return "Professional";
            case enum_type::broker_dealer_non_registered: return "Broker Dealer Non Registered";
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

    static constexpr const char* name = "customer_firm_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<customer_firm_indicator::enum_type>;
    using storage_type = result_type;

    constexpr customer_firm_indicator()
     : value{ enum_type{} } {}

    constexpr customer_firm_indicator(enum_type v)
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
            set(enum_type::broker_dealer_non_registered);
    }

  protected:
    enum_type value;
};
}
