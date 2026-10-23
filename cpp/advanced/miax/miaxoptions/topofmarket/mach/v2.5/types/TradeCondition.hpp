#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// trade_condition
struct trade_condition {

    enum class enum_type : char {
        regular = ' ',
        cancel_of_trade_previously_reported_other_than_as_the_last_or_opening = 'A',
        late_and_is_out_of_sequence = 'B',
        cancel_of_the_last_reported_trade = 'C',
        late_and_is_in_correct_sequence = 'D',
        cancel_of_the_first_reported_trade = 'E',
        late_report_of_the_opening_trade_and_is_out_of_sequence = 'F',
        cancel_of_the_only_reported_trade = 'G',
        late_report_of_the_opening_trade_and_is_in_correct_sequence = 'H',
        auto_value = 'I',
        reopening_of_an_option = 'J',
        reserved_K = 'K',
        a_buy_and_a_sell_in_the_same_class = 'L',
        a_buy_and_a_sell_in_a_put_and_a_call = 'M',
        reserved_N = 'N',
        reserved_O = 'O',
        buy_or_sell_of_a_call_or_put = 'P',
        buy_of_a_call_and_a_sell_of_a_put_for_the_same_underlying_stock_or_index = 'Q',
        execution_of_an_order_which_was_stopped_at_a_price_that_did_not_constitute_a_trade_through_on_another_market_at_the_time_of_the_stop = 'R',
        execution_of_an_iso_order = 'S',
        reserved_T = 'T',
        trade_through_exempt = 'X',
        paired_prime = 'a',
        iso_paired_prime = 'b',
        prime_customer_to_customer_cross_or_prime_qcc = 'c',
        reserved_d = 'd',
        reserved_e = 'e',
        complex_transaction_that_is_not_complex_stock_tied_and_does_not_involve_legging = 'f',
        complex_prime_transaction_that_is_not_complex_stock_tied_and_does_not_involve_legging = 'g',
        complex_prime_customer_to_customer_cross_or_complex_prime_qcc_transaction_that_is_not_complex_stock_tied = 'h',
        reserved_i = 'i',
        complex_legging_transaction_that_is_not_complex_stock_tied = 'j',
        complex_prime_stock_tied_transaction_that_does_not_involve_legging = 'k',
        complex_prime_legging_transaction_that_is_not_complex_stock_tied = 'l',
        reserved_m = 'm',
        complex_stock_tied_transaction_that_does_not_involve_legging = 'n',
        complex_customer_to_customer_cross_stock_tied_or_complex_qcc_stock_tied_transaction = 'o',
        reserved_p = 'p',
        reserved_q = 'q',
        reserved_r = 'r',
        reserved_s = 's',
        reserved_t = 't'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 42> from_string_map = {{
        {"A Buy And A Sell In A Put And A Call", enum_type::a_buy_and_a_sell_in_a_put_and_a_call},
        {"A Buy And A Sell In The Same Class", enum_type::a_buy_and_a_sell_in_the_same_class},
        {"Auto", enum_type::auto_value},
        {"Buy Of A Call And A Sell Of A Put For The Same Underlying Stock Or Index", enum_type::buy_of_a_call_and_a_sell_of_a_put_for_the_same_underlying_stock_or_index},
        {"Buy Or Sell Of A Call Or Put", enum_type::buy_or_sell_of_a_call_or_put},
        {"Cancel Of The First Reported Trade", enum_type::cancel_of_the_first_reported_trade},
        {"Cancel Of The Last Reported Trade", enum_type::cancel_of_the_last_reported_trade},
        {"Cancel Of The Only Reported Trade", enum_type::cancel_of_the_only_reported_trade},
        {"Cancel Of Trade Previously Reported Other Than As The Last Or Opening", enum_type::cancel_of_trade_previously_reported_other_than_as_the_last_or_opening},
        {"Complex Customer To Customer Cross Stock Tied Or Complex Qcc Stock Tied Transaction", enum_type::complex_customer_to_customer_cross_stock_tied_or_complex_qcc_stock_tied_transaction},
        {"Complex Legging Transaction That Is Not Complex Stock Tied", enum_type::complex_legging_transaction_that_is_not_complex_stock_tied},
        {"Complex Prime Customer To Customer Cross Or Complex Prime Qcc Transaction That Is Not Complex Stock Tied", enum_type::complex_prime_customer_to_customer_cross_or_complex_prime_qcc_transaction_that_is_not_complex_stock_tied},
        {"Complex Prime Legging Transaction That Is Not Complex Stock Tied", enum_type::complex_prime_legging_transaction_that_is_not_complex_stock_tied},
        {"Complex Prime Stock Tied Transaction That Does Not Involve Legging", enum_type::complex_prime_stock_tied_transaction_that_does_not_involve_legging},
        {"Complex Prime Transaction That Is Not Complex Stock Tied And Does Not Involve Legging", enum_type::complex_prime_transaction_that_is_not_complex_stock_tied_and_does_not_involve_legging},
        {"Complex Stock Tied Transaction That Does Not Involve Legging", enum_type::complex_stock_tied_transaction_that_does_not_involve_legging},
        {"Complex Transaction That Is Not Complex Stock Tied And Does Not Involve Legging", enum_type::complex_transaction_that_is_not_complex_stock_tied_and_does_not_involve_legging},
        {"Execution Of An Iso Order", enum_type::execution_of_an_iso_order},
        {"Execution Of An Order Which Was Stopped At A Price That Did Not Constitute A Trade Through On Another Market At The Time Of The Stop", enum_type::execution_of_an_order_which_was_stopped_at_a_price_that_did_not_constitute_a_trade_through_on_another_market_at_the_time_of_the_stop},
        {"Iso Paired Prime", enum_type::iso_paired_prime},
        {"Late And Is In Correct Sequence", enum_type::late_and_is_in_correct_sequence},
        {"Late And Is Out Of Sequence", enum_type::late_and_is_out_of_sequence},
        {"Late Report Of The Opening Trade And Is In Correct Sequence", enum_type::late_report_of_the_opening_trade_and_is_in_correct_sequence},
        {"Late Report Of The Opening Trade And Is Out Of Sequence", enum_type::late_report_of_the_opening_trade_and_is_out_of_sequence},
        {"Paired Prime", enum_type::paired_prime},
        {"Prime Customer To Customer Cross Or Prime Qcc", enum_type::prime_customer_to_customer_cross_or_prime_qcc},
        {"Regular", enum_type::regular},
        {"Reopening Of An Option", enum_type::reopening_of_an_option},
        {"Reserved", enum_type::reserved_K},
        {"Reserved", enum_type::reserved_N},
        {"Reserved", enum_type::reserved_O},
        {"Reserved", enum_type::reserved_T},
        {"Reserved", enum_type::reserved_d},
        {"Reserved", enum_type::reserved_e},
        {"Reserved", enum_type::reserved_i},
        {"Reserved", enum_type::reserved_m},
        {"Reserved", enum_type::reserved_p},
        {"Reserved", enum_type::reserved_q},
        {"Reserved", enum_type::reserved_r},
        {"Reserved", enum_type::reserved_s},
        {"Reserved", enum_type::reserved_t},
        {"Trade Through Exempt", enum_type::trade_through_exempt}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular: return "Regular";
            case enum_type::cancel_of_trade_previously_reported_other_than_as_the_last_or_opening: return "Cancel Of Trade Previously Reported Other Than As The Last Or Opening";
            case enum_type::late_and_is_out_of_sequence: return "Late And Is Out Of Sequence";
            case enum_type::cancel_of_the_last_reported_trade: return "Cancel Of The Last Reported Trade";
            case enum_type::late_and_is_in_correct_sequence: return "Late And Is In Correct Sequence";
            case enum_type::cancel_of_the_first_reported_trade: return "Cancel Of The First Reported Trade";
            case enum_type::late_report_of_the_opening_trade_and_is_out_of_sequence: return "Late Report Of The Opening Trade And Is Out Of Sequence";
            case enum_type::cancel_of_the_only_reported_trade: return "Cancel Of The Only Reported Trade";
            case enum_type::late_report_of_the_opening_trade_and_is_in_correct_sequence: return "Late Report Of The Opening Trade And Is In Correct Sequence";
            case enum_type::auto_value: return "Auto";
            case enum_type::reopening_of_an_option: return "Reopening Of An Option";
            case enum_type::reserved_K: return "Reserved";
            case enum_type::a_buy_and_a_sell_in_the_same_class: return "A Buy And A Sell In The Same Class";
            case enum_type::a_buy_and_a_sell_in_a_put_and_a_call: return "A Buy And A Sell In A Put And A Call";
            case enum_type::reserved_N: return "Reserved";
            case enum_type::reserved_O: return "Reserved";
            case enum_type::buy_or_sell_of_a_call_or_put: return "Buy Or Sell Of A Call Or Put";
            case enum_type::buy_of_a_call_and_a_sell_of_a_put_for_the_same_underlying_stock_or_index: return "Buy Of A Call And A Sell Of A Put For The Same Underlying Stock Or Index";
            case enum_type::execution_of_an_order_which_was_stopped_at_a_price_that_did_not_constitute_a_trade_through_on_another_market_at_the_time_of_the_stop: return "Execution Of An Order Which Was Stopped At A Price That Did Not Constitute A Trade Through On Another Market At The Time Of The Stop";
            case enum_type::execution_of_an_iso_order: return "Execution Of An Iso Order";
            case enum_type::reserved_T: return "Reserved";
            case enum_type::trade_through_exempt: return "Trade Through Exempt";
            case enum_type::paired_prime: return "Paired Prime";
            case enum_type::iso_paired_prime: return "Iso Paired Prime";
            case enum_type::prime_customer_to_customer_cross_or_prime_qcc: return "Prime Customer To Customer Cross Or Prime Qcc";
            case enum_type::reserved_d: return "Reserved";
            case enum_type::reserved_e: return "Reserved";
            case enum_type::complex_transaction_that_is_not_complex_stock_tied_and_does_not_involve_legging: return "Complex Transaction That Is Not Complex Stock Tied And Does Not Involve Legging";
            case enum_type::complex_prime_transaction_that_is_not_complex_stock_tied_and_does_not_involve_legging: return "Complex Prime Transaction That Is Not Complex Stock Tied And Does Not Involve Legging";
            case enum_type::complex_prime_customer_to_customer_cross_or_complex_prime_qcc_transaction_that_is_not_complex_stock_tied: return "Complex Prime Customer To Customer Cross Or Complex Prime Qcc Transaction That Is Not Complex Stock Tied";
            case enum_type::reserved_i: return "Reserved";
            case enum_type::complex_legging_transaction_that_is_not_complex_stock_tied: return "Complex Legging Transaction That Is Not Complex Stock Tied";
            case enum_type::complex_prime_stock_tied_transaction_that_does_not_involve_legging: return "Complex Prime Stock Tied Transaction That Does Not Involve Legging";
            case enum_type::complex_prime_legging_transaction_that_is_not_complex_stock_tied: return "Complex Prime Legging Transaction That Is Not Complex Stock Tied";
            case enum_type::reserved_m: return "Reserved";
            case enum_type::complex_stock_tied_transaction_that_does_not_involve_legging: return "Complex Stock Tied Transaction That Does Not Involve Legging";
            case enum_type::complex_customer_to_customer_cross_stock_tied_or_complex_qcc_stock_tied_transaction: return "Complex Customer To Customer Cross Stock Tied Or Complex Qcc Stock Tied Transaction";
            case enum_type::reserved_p: return "Reserved";
            case enum_type::reserved_q: return "Reserved";
            case enum_type::reserved_r: return "Reserved";
            case enum_type::reserved_s: return "Reserved";
            case enum_type::reserved_t: return "Reserved";
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
            set(enum_type::reserved_t);
    }

  protected:
    enum_type value;
};
}
