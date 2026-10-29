#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// quote_reject_reason
struct quote_reject_reason {

    enum class enum_type : std::uint32_t {
        no_value = 0,
        technical_error_function_not_performed = 9999,
        exercise_price_not_allowed = 8006,
        no_positions_blocked = 8007,
        quantity_doesnt_match_with_the_original_request_quantity_on_original_request_quantity_on_original_request = 8008,
        exercise_must_be_on_maturity_date = 8011,
        function_not_available_this_time = 8014,
        blocking_quantity_more_than_999999999 = 8015,
        trade_does_not_belong_to_the_specified_firm_firm_id_xxx = 8020,
        blocking_qty_more_than_available_quantity = 8021,
        there_arent_positions_available_to_exercise = 8022,
        total_qty_must_be_the_sum_of_all_allocqty = 8023,
        trade_already_cancelled_or_does_not_exist_trade_id_xxx = 8024,
        available_quantity_to_block_is_zero = 8027,
        invalid_operation_for_contract_type = 8028,
        function_closed_or_suspended = 8036,
        exercise_price_outside_required_moneyness = 8039,
        invalid_exercise_request_id_to_cancel = 8040,
        invalid_blocking_id_to_unblock = 8059,
        invalid_quantity_to_unblock = 8062,
        on_behalf_operation_not_allowed_during_ccr_recovery = 8063,
        problem_parsing_incoming_message = 8065,
        exercise_quantity_should_be_greater_than_zero = 8066,
        contrary_exercise_already_registered_for_this_position = 8069,
        inthemoney_contract_allows_contrary_exercise_to_not_exercise_automatically_only = 8070,
        atoutthemoney_contract_allows_contrary_exercise_to_exercise_automatically_only = 8071,
        dma_is_not_allowed_to_request_contrary_exercise = 8072,
        contrary_exercises_can_only_be_requested_by_default_link_or_position_owner_with_direct_access_on_absence_of_default_link = 8073,
        contrary_exercise_invalid_operation = 8074,
        threshold_must_not_be_informed = 8075
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 30> from_string_map = {{
        {"At/Out-the-money contract allows Contrary Exercise to exercise automatically only", enum_type::atoutthemoney_contract_allows_contrary_exercise_to_exercise_automatically_only},
        {"Available quantity to block is zero", enum_type::available_quantity_to_block_is_zero},
        {"Blocking qty more than available quantity", enum_type::blocking_qty_more_than_available_quantity},
        {"Blocking quantity more than 999999999", enum_type::blocking_quantity_more_than_999999999},
        {"Contrary Exercise already registered for this position", enum_type::contrary_exercise_already_registered_for_this_position},
        {"Contrary Exercise invalid operation.", enum_type::contrary_exercise_invalid_operation},
        {"Contrary Exercises can only be requested by default link or position owner with direct access on absence of default link", enum_type::contrary_exercises_can_only_be_requested_by_default_link_or_position_owner_with_direct_access_on_absence_of_default_link},
        {"DMA is not allowed to request Contrary Exercise", enum_type::dma_is_not_allowed_to_request_contrary_exercise},
        {"Exercise must be on maturity date.", enum_type::exercise_must_be_on_maturity_date},
        {"Exercise price not allowed", enum_type::exercise_price_not_allowed},
        {"Exercise price outside required moneyness.", enum_type::exercise_price_outside_required_moneyness},
        {"Exercise quantity should be greater than zero", enum_type::exercise_quantity_should_be_greater_than_zero},
        {"Function closed or suspended.", enum_type::function_closed_or_suspended},
        {"Function not available this time", enum_type::function_not_available_this_time},
        {"In-the-money contract allows Contrary Exercise to not exercise automatically only", enum_type::inthemoney_contract_allows_contrary_exercise_to_not_exercise_automatically_only},
        {"Invalid blocking Id to unblock", enum_type::invalid_blocking_id_to_unblock},
        {"Invalid exercise request id to cancel", enum_type::invalid_exercise_request_id_to_cancel},
        {"Invalid Operation for contract type.", enum_type::invalid_operation_for_contract_type},
        {"Invalid quantity to unblock", enum_type::invalid_quantity_to_unblock},
        {"No positions blocked", enum_type::no_positions_blocked},
        {"No Value", enum_type::no_value},
        {"On Behalf Operation not allowed during CCR recovery", enum_type::on_behalf_operation_not_allowed_during_ccr_recovery},
        {"Problem parsing incoming message", enum_type::problem_parsing_incoming_message},
        {"Quantity doesn't match with the original request [Quantity on original request: <quantity on original request>]", enum_type::quantity_doesnt_match_with_the_original_request_quantity_on_original_request_quantity_on_original_request},
        {"Technical Error: Function not performed", enum_type::technical_error_function_not_performed},
        {"There aren't positions available to exercise", enum_type::there_arent_positions_available_to_exercise},
        {"Threshold must not be informed", enum_type::threshold_must_not_be_informed},
        {"Total qty must be the sum of all AllocQty", enum_type::total_qty_must_be_the_sum_of_all_allocqty},
        {"Trade already cancelled or does not exist ‘Trade Id: <XXX>’", enum_type::trade_already_cancelled_or_does_not_exist_trade_id_xxx},
        {"Trade does not belong to the specified firm ‘Firm Id: <XXX>’", enum_type::trade_does_not_belong_to_the_specified_firm_firm_id_xxx}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_value: return "No Value";
            case enum_type::technical_error_function_not_performed: return "Technical Error: Function not performed";
            case enum_type::exercise_price_not_allowed: return "Exercise price not allowed";
            case enum_type::no_positions_blocked: return "No positions blocked";
            case enum_type::quantity_doesnt_match_with_the_original_request_quantity_on_original_request_quantity_on_original_request: return "Quantity doesn't match with the original request [Quantity on original request: <quantity on original request>]";
            case enum_type::exercise_must_be_on_maturity_date: return "Exercise must be on maturity date.";
            case enum_type::function_not_available_this_time: return "Function not available this time";
            case enum_type::blocking_quantity_more_than_999999999: return "Blocking quantity more than 999999999";
            case enum_type::trade_does_not_belong_to_the_specified_firm_firm_id_xxx: return "Trade does not belong to the specified firm ‘Firm Id: <XXX>’";
            case enum_type::blocking_qty_more_than_available_quantity: return "Blocking qty more than available quantity";
            case enum_type::there_arent_positions_available_to_exercise: return "There aren't positions available to exercise";
            case enum_type::total_qty_must_be_the_sum_of_all_allocqty: return "Total qty must be the sum of all AllocQty";
            case enum_type::trade_already_cancelled_or_does_not_exist_trade_id_xxx: return "Trade already cancelled or does not exist ‘Trade Id: <XXX>’";
            case enum_type::available_quantity_to_block_is_zero: return "Available quantity to block is zero";
            case enum_type::invalid_operation_for_contract_type: return "Invalid Operation for contract type.";
            case enum_type::function_closed_or_suspended: return "Function closed or suspended.";
            case enum_type::exercise_price_outside_required_moneyness: return "Exercise price outside required moneyness.";
            case enum_type::invalid_exercise_request_id_to_cancel: return "Invalid exercise request id to cancel";
            case enum_type::invalid_blocking_id_to_unblock: return "Invalid blocking Id to unblock";
            case enum_type::invalid_quantity_to_unblock: return "Invalid quantity to unblock";
            case enum_type::on_behalf_operation_not_allowed_during_ccr_recovery: return "On Behalf Operation not allowed during CCR recovery";
            case enum_type::problem_parsing_incoming_message: return "Problem parsing incoming message";
            case enum_type::exercise_quantity_should_be_greater_than_zero: return "Exercise quantity should be greater than zero";
            case enum_type::contrary_exercise_already_registered_for_this_position: return "Contrary Exercise already registered for this position";
            case enum_type::inthemoney_contract_allows_contrary_exercise_to_not_exercise_automatically_only: return "In-the-money contract allows Contrary Exercise to not exercise automatically only";
            case enum_type::atoutthemoney_contract_allows_contrary_exercise_to_exercise_automatically_only: return "At/Out-the-money contract allows Contrary Exercise to exercise automatically only";
            case enum_type::dma_is_not_allowed_to_request_contrary_exercise: return "DMA is not allowed to request Contrary Exercise";
            case enum_type::contrary_exercises_can_only_be_requested_by_default_link_or_position_owner_with_direct_access_on_absence_of_default_link: return "Contrary Exercises can only be requested by default link or position owner with direct access on absence of default link";
            case enum_type::contrary_exercise_invalid_operation: return "Contrary Exercise invalid operation.";
            case enum_type::threshold_must_not_be_informed: return "Threshold must not be informed";
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

    static constexpr const char* name = "quote_reject_reason";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<quote_reject_reason::enum_type>;
    using storage_type = result_type;

    constexpr quote_reject_reason()
     : value{ enum_type{} } {}

    constexpr quote_reject_reason(enum_type v)
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
            set(static_cast<enum_type>(0));
    }

  protected:
    enum_type value;
};
}
