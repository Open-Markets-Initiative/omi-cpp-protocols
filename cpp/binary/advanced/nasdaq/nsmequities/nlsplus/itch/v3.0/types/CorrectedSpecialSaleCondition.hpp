#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// corrected_special_sale_condition
struct corrected_special_sale_condition {

    enum class enum_type : char {
        acquisition = 'A',
        bunched = 'B',
        distribution = 'D',
        price_variation_transaction = 'H',
        nasdaq_official_close_price = 'M',
        prior_reference_price = 'P',
        nasdaq_official_opening_price = 'Q',
        split_trade = 'S',
        contingent_trade = 'V',
        average_price_trade = 'W',
        cross_trade = 'X',
        odd_lot_execution = 'o',
        odd_lot_cross_execution = 'x',
        not_applicable = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 14> from_string_map = {{
        {"Acquisition", enum_type::acquisition},
        {"Average Price Trade", enum_type::average_price_trade},
        {"Bunched", enum_type::bunched},
        {"Contingent Trade", enum_type::contingent_trade},
        {"Cross Trade", enum_type::cross_trade},
        {"Distribution", enum_type::distribution},
        {"Nasdaq Official Close Price", enum_type::nasdaq_official_close_price},
        {"Nasdaq Official Opening Price", enum_type::nasdaq_official_opening_price},
        {"Not Applicable", enum_type::not_applicable},
        {"Odd Lot Cross Execution", enum_type::odd_lot_cross_execution},
        {"Odd Lot Execution", enum_type::odd_lot_execution},
        {"Price Variation Transaction", enum_type::price_variation_transaction},
        {"Prior Reference Price", enum_type::prior_reference_price},
        {"Split Trade", enum_type::split_trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::acquisition: return "Acquisition";
            case enum_type::bunched: return "Bunched";
            case enum_type::distribution: return "Distribution";
            case enum_type::price_variation_transaction: return "Price Variation Transaction";
            case enum_type::nasdaq_official_close_price: return "Nasdaq Official Close Price";
            case enum_type::prior_reference_price: return "Prior Reference Price";
            case enum_type::nasdaq_official_opening_price: return "Nasdaq Official Opening Price";
            case enum_type::split_trade: return "Split Trade";
            case enum_type::contingent_trade: return "Contingent Trade";
            case enum_type::average_price_trade: return "Average Price Trade";
            case enum_type::cross_trade: return "Cross Trade";
            case enum_type::odd_lot_execution: return "Odd Lot Execution";
            case enum_type::odd_lot_cross_execution: return "Odd Lot Cross Execution";
            case enum_type::not_applicable: return "Not Applicable";
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

    static constexpr const char* name = "corrected_special_sale_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<corrected_special_sale_condition::enum_type>;
    using storage_type = result_type;

    constexpr corrected_special_sale_condition()
     : value{ enum_type{} } {}

    constexpr corrected_special_sale_condition(enum_type v)
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
            set(enum_type::not_applicable);
    }

  protected:
    enum_type value;
};
}
