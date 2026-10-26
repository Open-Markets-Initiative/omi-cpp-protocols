#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// financial_product
struct financial_product {

    enum class enum_type : std::uint8_t {
        option = 1,
        forward = 2,
        future = 3,
        fra = 4,
        cash = 5,
        payment = 6,
        exchange_rate = 7,
        interest_rate_swap = 8,
        repo = 9,
        synthetic_box_leg_or_reference = 10,
        combination = 11,
        guarantee = 12,
        otc_general = 13,
        equity_warrant = 14,
        security_lending = 15
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 15> from_string_map = {{
        {"Cash", enum_type::cash},
        {"Combination", enum_type::combination},
        {"Equity Warrant", enum_type::equity_warrant},
        {"Exchange Rate", enum_type::exchange_rate},
        {"Forward", enum_type::forward},
        {"Fra", enum_type::fra},
        {"Future", enum_type::future},
        {"Guarantee", enum_type::guarantee},
        {"Interest Rate Swap", enum_type::interest_rate_swap},
        {"Option", enum_type::option},
        {"Otc General", enum_type::otc_general},
        {"Payment", enum_type::payment},
        {"Repo", enum_type::repo},
        {"Security Lending", enum_type::security_lending},
        {"Synthetic Box Leg Or Reference", enum_type::synthetic_box_leg_or_reference}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::option: return "Option";
            case enum_type::forward: return "Forward";
            case enum_type::future: return "Future";
            case enum_type::fra: return "Fra";
            case enum_type::cash: return "Cash";
            case enum_type::payment: return "Payment";
            case enum_type::exchange_rate: return "Exchange Rate";
            case enum_type::interest_rate_swap: return "Interest Rate Swap";
            case enum_type::repo: return "Repo";
            case enum_type::synthetic_box_leg_or_reference: return "Synthetic Box Leg Or Reference";
            case enum_type::combination: return "Combination";
            case enum_type::guarantee: return "Guarantee";
            case enum_type::otc_general: return "Otc General";
            case enum_type::equity_warrant: return "Equity Warrant";
            case enum_type::security_lending: return "Security Lending";
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

    static constexpr const char* name = "financial_product";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<financial_product::enum_type>;
    using storage_type = result_type;

    constexpr financial_product()
     : value{ enum_type{} } {}

    constexpr financial_product(enum_type v)
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
            set(enum_type::security_lending);
    }

  protected:
    enum_type value;
};
}
