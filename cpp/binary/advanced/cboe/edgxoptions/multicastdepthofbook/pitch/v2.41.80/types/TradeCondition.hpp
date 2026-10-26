#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// trade_condition
struct trade_condition {

    enum class enum_type : char {
        single_leg_auction_non_iso_cboe_auction_types_include_aim_sam = 'a',
        single_leg_auction_iso_cboe_auction_types_are_aim_iso_sam_iso = 'b',
        single_leg_cross_non_iso_cboe_auction_types_include_cust_to_cust_aim_qcc = 'c',
        single_leg_cross_iso_cboe_order_type_is_cust_to_cust_aim_iso = 'd',
        single_leg_floor_trade = 'e',
        complex_to_complex_electronic_trade = 'f',
        complex_auction_trade = 'g',
        complex_cross = 'h',
        complex_electronic_trade_against_single_legs = 'j',
        complex_with_stock_options_auction_trade = 'k',
        complex_floor_trade_against_single_legs = 'm',
        complex_with_stock_electronic_trade = 'n',
        complex_with_stock_cross = 'o',
        complex_with_stock_floor_trade = 'p',
        complex_floor_trade_of_proprietary_products_marked_as_combo_order = 't',
        multilateral_compression_trade_of_proprietary_products = 'u',
        extended_hours_trade = 'v',
        electronic_trade = 'I',
        cabinet_order = 'K',
        future_options_auction_trade_electronic_execution_of_a_multi_leg_futureoptions_order_traded_in_a_two_sided_auction = 'M',
        future_options_auto_electronic_trade_electronic_execution_of_a_multi_leg_futureoptions_order_traded_on_the_complex_book_or_in_a_coa = 'N',
        future_options_cross_electronic_execution_of_a_multi_leg_futureoptions_order_traded_in_a_two_sided_crossing_mechanism_that_does_not_go_through_an_exposure_period = 'P',
        opening_trade = 'O',
        iso = 'S'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 24> from_string_map = {{
        {"Cabinet Order", enum_type::cabinet_order},
        {"Complex Auction Trade", enum_type::complex_auction_trade},
        {"Complex Cross", enum_type::complex_cross},
        {"Complex Electronic Trade Against Single Legs", enum_type::complex_electronic_trade_against_single_legs},
        {"Complex Floor Trade Against Single Legs", enum_type::complex_floor_trade_against_single_legs},
        {"Complex Floor Trade Of Proprietary Products Marked As Combo Order", enum_type::complex_floor_trade_of_proprietary_products_marked_as_combo_order},
        {"Complex To Complex Electronic Trade", enum_type::complex_to_complex_electronic_trade},
        {"Complex With Stock Cross", enum_type::complex_with_stock_cross},
        {"Complex With Stock Electronic Trade", enum_type::complex_with_stock_electronic_trade},
        {"Complex With Stock Floor Trade", enum_type::complex_with_stock_floor_trade},
        {"Complex With Stock Options Auction Trade", enum_type::complex_with_stock_options_auction_trade},
        {"Electronic Trade", enum_type::electronic_trade},
        {"Extended Hours Trade", enum_type::extended_hours_trade},
        {"Future Options Auction Trade Electronic Execution Of A Multi Leg Futureoptions Order Traded In A Two Sided Auction", enum_type::future_options_auction_trade_electronic_execution_of_a_multi_leg_futureoptions_order_traded_in_a_two_sided_auction},
        {"Future Options Auto Electronic Trade Electronic Execution Of A Multi Leg Futureoptions Order Traded On The Complex Book Or In A Coa", enum_type::future_options_auto_electronic_trade_electronic_execution_of_a_multi_leg_futureoptions_order_traded_on_the_complex_book_or_in_a_coa},
        {"Future Options Cross Electronic Execution Of A Multi Leg Futureoptions Order Traded In A Two Sided Crossing Mechanism That Does Not Go Through An Exposure Period", enum_type::future_options_cross_electronic_execution_of_a_multi_leg_futureoptions_order_traded_in_a_two_sided_crossing_mechanism_that_does_not_go_through_an_exposure_period},
        {"Iso", enum_type::iso},
        {"Multilateral Compression Trade Of Proprietary Products", enum_type::multilateral_compression_trade_of_proprietary_products},
        {"Opening Trade", enum_type::opening_trade},
        {"Single Leg Auction Iso Cboe Auction Types Are Aim Iso Sam Iso", enum_type::single_leg_auction_iso_cboe_auction_types_are_aim_iso_sam_iso},
        {"Single Leg Auction Non Iso Cboe Auction Types Include Aim Sam", enum_type::single_leg_auction_non_iso_cboe_auction_types_include_aim_sam},
        {"Single Leg Cross Iso Cboe Order Type Is Cust To Cust Aim Iso", enum_type::single_leg_cross_iso_cboe_order_type_is_cust_to_cust_aim_iso},
        {"Single Leg Cross Non Iso Cboe Auction Types Include Cust To Cust Aim Qcc", enum_type::single_leg_cross_non_iso_cboe_auction_types_include_cust_to_cust_aim_qcc},
        {"Single Leg Floor Trade", enum_type::single_leg_floor_trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::single_leg_auction_non_iso_cboe_auction_types_include_aim_sam: return "Single Leg Auction Non Iso Cboe Auction Types Include Aim Sam";
            case enum_type::single_leg_auction_iso_cboe_auction_types_are_aim_iso_sam_iso: return "Single Leg Auction Iso Cboe Auction Types Are Aim Iso Sam Iso";
            case enum_type::single_leg_cross_non_iso_cboe_auction_types_include_cust_to_cust_aim_qcc: return "Single Leg Cross Non Iso Cboe Auction Types Include Cust To Cust Aim Qcc";
            case enum_type::single_leg_cross_iso_cboe_order_type_is_cust_to_cust_aim_iso: return "Single Leg Cross Iso Cboe Order Type Is Cust To Cust Aim Iso";
            case enum_type::single_leg_floor_trade: return "Single Leg Floor Trade";
            case enum_type::complex_to_complex_electronic_trade: return "Complex To Complex Electronic Trade";
            case enum_type::complex_auction_trade: return "Complex Auction Trade";
            case enum_type::complex_cross: return "Complex Cross";
            case enum_type::complex_electronic_trade_against_single_legs: return "Complex Electronic Trade Against Single Legs";
            case enum_type::complex_with_stock_options_auction_trade: return "Complex With Stock Options Auction Trade";
            case enum_type::complex_floor_trade_against_single_legs: return "Complex Floor Trade Against Single Legs";
            case enum_type::complex_with_stock_electronic_trade: return "Complex With Stock Electronic Trade";
            case enum_type::complex_with_stock_cross: return "Complex With Stock Cross";
            case enum_type::complex_with_stock_floor_trade: return "Complex With Stock Floor Trade";
            case enum_type::complex_floor_trade_of_proprietary_products_marked_as_combo_order: return "Complex Floor Trade Of Proprietary Products Marked As Combo Order";
            case enum_type::multilateral_compression_trade_of_proprietary_products: return "Multilateral Compression Trade Of Proprietary Products";
            case enum_type::extended_hours_trade: return "Extended Hours Trade";
            case enum_type::electronic_trade: return "Electronic Trade";
            case enum_type::cabinet_order: return "Cabinet Order";
            case enum_type::future_options_auction_trade_electronic_execution_of_a_multi_leg_futureoptions_order_traded_in_a_two_sided_auction: return "Future Options Auction Trade Electronic Execution Of A Multi Leg Futureoptions Order Traded In A Two Sided Auction";
            case enum_type::future_options_auto_electronic_trade_electronic_execution_of_a_multi_leg_futureoptions_order_traded_on_the_complex_book_or_in_a_coa: return "Future Options Auto Electronic Trade Electronic Execution Of A Multi Leg Futureoptions Order Traded On The Complex Book Or In A Coa";
            case enum_type::future_options_cross_electronic_execution_of_a_multi_leg_futureoptions_order_traded_in_a_two_sided_crossing_mechanism_that_does_not_go_through_an_exposure_period: return "Future Options Cross Electronic Execution Of A Multi Leg Futureoptions Order Traded In A Two Sided Crossing Mechanism That Does Not Go Through An Exposure Period";
            case enum_type::opening_trade: return "Opening Trade";
            case enum_type::iso: return "Iso";
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

    static constexpr const char* name = "trade_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_condition::enum_type>;
    using storage_type = result_type;

    constexpr trade_condition()
     : value{ enum_type{} } {}

    constexpr trade_condition(enum_type v)
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
            set(enum_type::iso);
    }

  protected:
    enum_type value;
};
}
