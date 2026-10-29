#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// ord_rej_reason
struct ord_rej_reason {

    enum class enum_type : std::uint32_t {
        unable_to_send_fix_from_volatilityupdate_message = 908,
        orders_may_not_be_entered_while_the_market_is_closedpaused = 1003,
        fix_field_missing_or_incorrect = 1007,
        required_field_missing = 1010,
        fix_field_incorrect_001011 = 1011,
        price_must_be_greater_than_zero = 1012,
        invalid_order_qualifier = 1013,
        user_not_authorized_to_trade = 1014,
        required_field_missing_stop_orders_cannot_be_iocfak = 1016,
        required_field_missing_display_quantity_orders_cannot_be_iocfok = 1017,
        required_field_missing_stop_orders_cannot_be_iocfok = 1018,
        market_price_orders_not_supported_by_opposite_limit = 2013,
        order_gtd_expire_date_is_before_the_current_or_next_if_not_currently_in_a_session_trading_session_end_date = 2019,
        cannot_modify_order_because_order_does_not_exist = 2045,
        disclosed_quantity_cannot_be_greater_than_total_or_remaining_quantity = 2046,
        order_contract_is_unknown_002047 = 2047,
        the_order_was_submitted_with_a_different_sendercompid_than_the_requesting_cancel = 2048,
        the_order_was_submitted_with_a_different_clorderid_than_the_correlationclorderid_of_the_requesting_cancel = 2049,
        the_order_was_submitted_with_a_different_clorderid_than_the_originalclorderid_of_the_requesting_cancel = 2050,
        the_order_was_submitted_with_a_different_side_than_the_requesting_cancel = 2051,
        the_order_was_submitted_with_a_different_group_tag_55_than_the_requesting_cancel = 2052,
        the_order_was_submitted_with_a_different_security_type_than_the_requesting_cancel = 2053,
        the_order_was_submitted_with_a_different_account_than_the_requesting_cancel = 2054,
        the_order_was_submitted_with_a_different_quantity_than_the_requesting_cancel = 2055,
        the_order_was_submitted_with_a_different_traderid_than_the_requesting_cancel = 2056,
        attempt_to_cancel_an_order_with_a_different_firmid_than_the_original_order = 2057,
        attempt_to_cancel_an_order_with_a_different_senderlocationid_than_the_original_order = 2058,
        stop_price_maximini_must_be_smaller_than_or_equal_to_trigger_price = 2059,
        sell_order_stop_price_must_be_below_last_trade_price = 2060,
        buy_order_stop_price_must_be_above_last_trade_price = 2061,
        the_modify_was_submitted_on_a_different_product_than_the_original_order = 2100,
        attempt_to_modify_an_order_with_a_different_inflightfill_mitigation_status_than_first_modification = 2101,
        attempt_to_modify_an_order_with_a_different_sendercompid_than_the_original_order = 2102,
        attempt_to_modify_an_order_with_a_different_traderid_than_the_original_order = 2103,
        attempt_to_modify_an_order_with_a_different_accountid_than_the_original_order = 2104,
        attempt_to_modify_an_order_with_a_different_firmid_than_the_original_order = 2105,
        attempt_to_modify_an_order_with_a_different_senderlocationid_than_the_original_order = 2106,
        disclosed_quantity_is_not_allowed = 2107,
        account_or_give_up_firm_required_for_dma_customers = 2108,
        disclosed_qty_cannot_be_less_than_disclosed_qty_min = 2109,
        acct_type38_not_valid_for_tag_581_for_dma_customers = 2110,
        give_up_not_valid_for_fx_spot_contract = 2111,
        visibility_permission_not_granted_for_executing_traderentering_trader = 2112,
        executing_trader_doesnt_have_access_to_product_group = 2113,
        attempt_to_modify_market_order_to_some_other_type = 2114,
        order_quantity_is_outside_of_the_allowable_range = 2115,
        account_is_mandatory_for_fx_spot = 2116,
        order_on_behalf_by_dma_customer_is_not_allowed = 2117,
        attempt_to_modify_an_order_with_a_different_accounttype_than_the_original_order = 2118,
        account_or_give_up_firm_required_for_equities = 2123,
        order_type_not_permitted_while_the_market_is_in_pre_open = 2130,
        order_price_is_outside_limits = 2137,
        qty_is_not_multiple_of_round_lot = 2138,
        qty_is_greater_or_equal_than_maximum_trade_volume = 2139,
        order_price_is_outside_bands = 2179,
        order_price_is_outside_auction_bands = 2180,
        trade_outside_of_short_term_volatility_bands = 2181,
        all_legs_must_have_same_lot_types = 2182,
        all_legs_must_have_same_tick_increment = 2183,
        all_legs_must_have_same_step_of_quotation = 2184,
        trade_price_is_outside_of_static_limits = 2185,
        cod_not_supported_for_gtc_gtd_orders = 2186,
        order_not_bookable_at_this_time = 2187,
        minimum_quantity_was_not_filled = 2188,
        order_attributes_not_allowed_to_trip_an_auction = 2189,
        order_type_not_permitted_for_group = 2311,
        instrument_has_an_request_for_cross_in_progress = 2500,
        order_quantity_too_low = 2501,
        crosstype_ineligible_for_instrument = 2502,
        rfq_for_cross_is_not_allowed_since_contract_is_not_rfq_for_cross_eligible = 2503,
        dma_crossorder_not_allowed = 2504,
        cross_order_rejected_due_to_auction_trigger_validation = 2505,
        trade_on_behalf_rejected = 2506,
        market_maker_protection_in_effect_for_user_xxxxxxxx_and_group_xxxxxx = 2600,
        rfq_rejected_instrumentexchange_not_tradable = 3000,
        rfq_rejected_instrumentexchange_not_known = 3001,
        error_creating_contract = 3002,
        business_reject_other = 3010,
        business_reject_unknown_id = 3011,
        business_reject_unknown_security = 3012,
        business_reject_unsupported_message_type = 3013,
        business_reject_application_not_available = 3014,
        business_reject_required_field_missing = 3015,
        contract_claims_to_be_a_spread_but_is_missing_one_or_more_legs = 3016,
        fix_field_length_exceeds_max_length = 3017,
        special_auction_permissions_order_entry_not_allowed = 3020,
        engine_did_not_respond_to_fas_request = 4000,
        termo_message_rejected_unknown_instrument = 6001,
        termo_message_rejected_exchange_security_closed = 6002,
        termo_rejected_instrumentexchange_not_tradable = 6003,
        termo_message_rejected_limits_exceeded = 6004,
        termo_message_rejected_too_late_to_enter = 6005,
        termo_message_rejected_unknown_termo_quote = 6006,
        termo_message_rejected_duplicate_termo_quote = 6007,
        termo_message_rejected_invalid_bidask_spread = 6008,
        termo_message_rejected_invalid_price = 6009,
        termo_message_rejected_not_authorized_to_termo_quote_this_instrument = 6010,
        termo_message_rejected_pass = 6011,
        fix_field_incorrect_006012 = 6012,
        not_a_valid_termo_instrument = 6013,
        values_dont_match_with_the_original_request = 6014,
        current_termo_request_status_does_not_allow_rejection = 6015,
        current_termo_request_status_does_not_allow_acceptance = 6016,
        wrong_type_of_order_book_for_termo = 6017,
        wrong_type_of_request_for_termo = 6018,
        days_to_settlement_must_be_between_16_and_999 = 6019,
        days_to_settlement_must_be_between_16_and_90 = 6020,
        instrument_not_allowed_to_this_market_006021 = 6021,
        instrument_not_allowed_to_this_market_006022 = 6022,
        termo_price_should_be_greater_than_zero = 6023,
        termo_messages_should_not_be_entered_when_market_is_paused = 6024,
        termo_messages_should_not_be_entered_when_market_is_pre_open_006025 = 6025,
        termo_messages_should_not_be_entered_when_market_is_pcp = 6026,
        termo_messages_should_not_be_entered_when_market_is_no_cancel = 6027,
        termo_messages_should_not_be_entered_when_market_is_reserved = 6028,
        termo_messages_should_not_be_entered_when_market_is_forbidden = 6029,
        termo_messages_should_not_be_entered_when_market_is_pre_close = 6030,
        termo_messages_should_not_be_entered_when_market_is_pre_open_006031 = 6031,
        not_a_valid_termo_underlying_instrument = 6032,
        received_a_null_adminoperation = 6033,
        first_trade_of_day_for_underlying_termo_instrument = 6034,
        termo_messages_should_not_be_entered_when_market_is_in_final_closing_call = 6035,
        invalid_cash_trade_in_tvr_006036 = 6036,
        only_buy_entry_request_for_tvr_is_accepted = 6037,
        there_is_no_bid_and_ask_for_underlying_contract = 6038,
        invalid_price_006039 = 6039,
        invalid_cash_trade_in_tvr_006040 = 6040,
        invalid_cash_trade_in_tvr_006041 = 6041,
        invalid_cash_trade_in_tvr_006042 = 6042,
        invalid_cash_trade_in_tvr_006043 = 6043,
        invalid_cash_trade_in_tvr_006044 = 6044,
        order_rejected = 7000,
        fok_order_unmatchable_in_market = 7001,
        orders_may_not_be_entered_while_the_market_is_closed = 7002,
        order_contract_is_unknown_007005 = 7005,
        no_partial_match_found_for_this_fak_order = 7006,
        maximum_quantity_depth_for_any_one_price_group_max_may_not_exceed_integermax_value = 7008,
        contract_for_this_order_contract_is_past_expiration_date_and_may_no_longer_be_traded = 7009,
        invalid_spread_price = 7010,
        maximum_number_of_working_orders_for_this_contract_has_been_exceeded = 7011,
        order_would_overwrite_existing_order_on_book = 7012,
        order_group_does_not_match_group_of_contract = 7013,
        order_security_type_does_not_match_security_type_of_contract = 7014,
        order_modify_has_different_side_than_existing_order = 7015,
        contract_is_not_eligible_for_electronic_matching = 7017,
        order_contract_is_not_gtc_or_gtd_eligible = 7018,
        no_trading_calendar_found_on_or_after_order_gtd_expire_date = 7020,
        tag_expiredate_432_beyond_instrument_expiration = 7021,
        tag_expiredate_432_beyond_uds_combo_earliest_leg_expiration = 7022,
        order_cannot_be_modified_or_cancelled_while_the_market_is_in_no_cancel = 7024,
        order_type_not_permitted_while_the_market_is_reserved = 7027,
        order_session_date_is_in_the_past = 7028,
        orders_may_not_be_entered_while_the_market_is_forbidden = 7029,
        quote_rejected_exchange_security_is_forbidden_007030 = 7030,
        orders_may_not_be_entered_while_the_market_is_preclosed = 7031,
        quote_rejected_exchange_security_is_preclosed = 7032,
        orders_may_not_be_entered_while_the_market_is_open = 7033,
        quote_rejected_exchange_security_is_forbidden_007034 = 7034,
        rfq_rejected_instrument_exchange_is_open = 7035,
        time_in_force_59_not_valid_for_order_type_40 = 7036,
        good_for_auction_order_not_allowed = 7037,
        on_close_order_not_allowed = 7038,
        duplicate_client_order_id_for_this_sessioncontract = 7039,
        good_for_auction_order_cancel_not_allowed = 7040,
        on_close_order_cancel_not_allowed = 7041,
        good_for_auction_order_modify_not_allowed = 7042,
        on_close_order_modify_not_allowed = 7043,
        modify_of_order_participating_in_top_not_allowed = 7044,
        cancel_of_order_participating_in_top_not_allowed = 7045,
        order_type_duration_combination_invalid_for_auction = 7046,
        order_type_duration_combination_invalid = 7047,
        quantity_attribute_not_allowed_on_order_during_auction = 7048,
        order_entry_was_unsuccessful_error_message_is_not_possible_to_send_orders_with_validity_type_market_on_auction_with_minimum_quantity = 7049,
        max_floor_111_not_valid_for_time_in_force_59 = 7050,
        spread_orders_may_not_be_entered_while_the_underlying_leg_market_is_in_non_trading_state = 7055,
        orders_may_not_be_entered_while_the_market_is_in_final_closing_call = 7056,
        quote_rejected_unknown_instrument = 7101,
        quote_rejected_exchange_security_closed = 7102,
        quote_rejected_quote_exceeds_limit = 7103,
        quote_rejected_too_late_to_enter = 7104,
        quote_rejected_unknown_quote = 7105,
        quote_rejected_duplicate_quote_in_same_message = 7106,
        quote_rejected_invalid_bidask_spread = 7107,
        quote_rejected_invalid_price = 7108,
        quote_rejected_not_authorized_to_quote_this_instrument = 7109,
        quote_rejected_resting_cancelled_too_many_rejects = 7110,
        quote_rejected_duplicate_quote_different_id = 7111,
        quote_rejected_resting_cancelled_quote_exceeds_limit = 7112,
        quote_rejected_resting_cancelled_duplicate_quote = 7113,
        quote_rejected_resting_cancelled_invalid_bidask_spread = 7114,
        quote_rejected_resting_cancelled_invalid_price = 7115,
        quote_rejected_resting_cancelled_not_authorized_to_quote_this_instrument = 7116,
        quote_rejected_unspecified_reason = 7117,
        quote_rejected_exchange_security_is_in_pre_open = 7118,
        quote_rejected_exchange_security_is_in_no_cancel = 7119,
        quote_rejected_exchange_security_is_reserved = 7120,
        contract_not_eligible_for_negotiated_quote = 7121,
        rlp_order_rejected_participant_not_authorized = 7122,
        attempt_to_modify_the_order_type_fromto_rlp = 7123,
        invalid_field_for_order_with_order_type_tag_40_equals_w_rlp = 7124,
        rlp_order_rejected_only_one_order_is_allowed_by_firm_and_side = 7125,
        invalid_field_for_order_with_routing_instruction_tag_35487_equals_1_retail_liquidity_taker = 7126,
        invalid_field_for_order_with_order_type_tag_40_equals_p_pegged = 7127,
        qty_is_not_multiple_of_minimum_execution_quantity_for_pegged_order = 7128,
        account_is_mandatory_for_pegged_order = 7129,
        pegged_order_can_not_be_sent_in_non_regular_session = 7130,
        attempt_to_modify_the_order_type_fromto_pegged = 7131,
        order_rejected_pegged_orders_are_not_allowed_for_this_contract = 7132,
        order_rejected_routing_instruction_tag_35487_equals_broker_only_3_not_allowed_for_this_group = 7133,
        order_rejected_only_pegged_order_with_routing_instruction_tag_35487_equals_broker_only_3_is_allowed_for_this_group = 7134,
        cross_order_suspended_for_the_participant_or_session = 7135,
        order_quantity_is_outside_of_the_allowable_range_order_quantity_orderqty_contract_minimum_quantity_for_cross_mincrossqty = 7136,
        bbt_messages_should_not_be_entered_when_market_is_paused = 7137,
        bbt_messages_should_not_be_entered_when_market_is_pre_open = 7138,
        bbt_messages_should_not_be_entered_when_market_is_pcp = 7139,
        bbt_messages_should_not_be_entered_when_market_is_no_cancel = 7140,
        bbt_messages_should_not_be_entered_when_market_is_reserved = 7141,
        bbt_messages_should_not_be_entered_when_market_is_forbidden = 7142,
        bbt_messages_should_not_be_entered_when_market_is_pre_close = 7143,
        invalid_field_for_bbt_order = 7144,
        for_cancel_on_behalf_must_be_informed_only_the_actiontargetsessionid_or_the_actiontargetgroupid = 7145,
        actiontargetgroupid_invalid_it_doesnt_exist_or_it_is_disabled = 7146,
        fix_session_is_blocked_due_to_mass_cancel = 7147,
        actiontargetgroupid_must_be_informed = 7148,
        fix_session_doesnt_belong_to_the_actiontargetgroupid = 7149,
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
        system_initialization = 30002,
        line_busy = 30003,
        message_or_atributes_are_invalid = 30004,
        internal_error = 30005,
        timeout_waiting_risk_evaluation = 30006,
        timeout_waiting_risk_evaluation_low_priority = 30007,
        broker_negotiation_blocked_030011 = 30011,
        broker_not_available_030012 = 30012,
        brokers_capture_account_not_found_030013 = 30013,
        brokers_segment_negotiation_blocked_030014 = 30014,
        broker_segment_not_available_030015 = 30015,
        brokers_segment_protected_mode_under_activation_030016 = 30016,
        broker_pn_negotiation_blocked = 30017,
        broker_pn_not_available = 30018,
        broker_pn_protected_mode_under_activation = 30019,
        account_negotiation_blocked_030021 = 30021,
        account_not_available_030022 = 30022,
        accounts_protected_mode_under_activation_030023 = 30023,
        account_mandatory_on_dma_orders_030024 = 30024,
        transient_account_is_hierarchically_blocked_on_protected_mode_030025 = 30025,
        crossorders_or_crossforward_not_allowed_while_account_in_protected_mode_030026 = 30026,
        transient_account_not_allowed_in_extended_hours_030027 = 30027,
        document_negotiation_blocked_030031 = 30031,
        document_not_available_030032 = 30032,
        documents_protected_mode_under_activation_030033 = 30033,
        executor_document_cannot_use_default_broker_profile_030034 = 30034,
        document_in_blocked_profile_030035 = 30035,
        crossorders_or_crossforward_not_allowed_while_document_in_protected_mode_030036 = 30036,
        entering_trader_negotiation_blocked_030041 = 30041,
        entering_trader_not_available_030042 = 30042,
        entering_trader_blocked_by_sfd_overflow_030043 = 30043,
        non_dma_orders_must_provide_account_while_in_brokers_protected_mode_030044 = 30044,
        entering_trader_not_authorized_to_trade_accountless_orders_030045 = 30045,
        entering_trader_cannot_trade_on_behalf_of_other_firms_account_030046 = 30046,
        symbol_not_available_030050 = 30050,
        symbol_internal_data_corrupted_030051 = 30051,
        fix_message_type_does_not_support_operations_on_such_symbol_030052 = 30052,
        symbols_underlying_not_found_for_risk_aggregation_030053 = 30053,
        symbols_risk_unit_matrix_not_available_030054 = 30054,
        symbols_reference_price_missing_market_orders_not_allowed_030055 = 30055,
        symbols_calculated_price_invalid_032056 = 32056,
        spreads_leg_not_available_030060 = 30060,
        spreads_leg_internal_data_corrupted_030061 = 30061,
        unexpected_internal_error_during_risk_evaluation_030070 = 30070,
        sfd_broker_pn_pn_document_aggregation_day_trade_cash_balance_stop_loss_not_configured = 30113,
        sdp_broker_pn_pn_document_aggregation_order_exceeded_cash_settlement_exposure = 30114,
        rmkt_broker_pn_pn_document_aggregation_order_quantity_exceeded_risk_increase = 30115,
        sdp_broker_pn_pn_trader_aggregation_order_exceeded_cash_settlement_exposure = 30116,
        spvd_broker_pn_pn_document_aggregation_order_exceeded_potential_short_uncovered_balance = 30117,
        spvd_broker_pn_pn_trader_aggregation_order_exceeded_potential_short_uncovered_balance = 30118,
        rmse_broker_pn_pn_document_aggregation_order_exceeded_risk_increase_at_extended_session = 30119,
        rmse_broker_order_exceeded_risk_increase_at_extended_session = 30166,
        mkta_account_buy_not_allowed_for_symbols_market_030201 = 30201,
        mkta_account_sell_not_allowed_for_symbols_market_030202 = 30202,
        tmoc_account_maximum_order_size_exceeded_for_single_order = 30204,
        tmov_account_maximum_order_size_exceeded_for_single_order = 30205,
        spci_account_order_quantity_exceeded_short_position_per_instrument = 30206,
        spvi_account_order_quantity_exceeded_long_position_per_instrument = 30207,
        sdp_account_order_exceeded_cash_settlement_exposure = 30208,
        rmkt_account_order_quantity_exceeded_risk_increase = 30210,
        irmkt_account_order_quantity_exceeded_risk_increase_reducing_mode = 30211,
        spi_account_order_quantity_exceeded_long_and_short_position_reducing_mode = 30212,
        std_account_termo_not_allowed_protected_mode_enabled_030213 = 30213,
        spvd_account_order_exceeded_potential_short_uncovered_balance_030215 = 30215,
        mkta_document_buysell_symbols_market_not_configured_030300 = 30300,
        mkta_document_buy_not_allowed_for_symbols_market_030301 = 30301,
        mkta_document_sell_not_allowed_for_symbols_market_030302 = 30302,
        tmox_document_max = 30303,
        tmoc_document_max_bid_quantity_exceeded_for_single_order = 30304,
        tmov_document_max_offer_quantity_exceeded_for_single_order = 30305,
        spci_document_order_quantity_exceeded_max_bid_potential_balance = 30306,
        spvi_document_order_quantity_exceeded_max_offer_potential_balance = 30307,
        sdp_document_order_exceeded_max_financial_potential_balance_due = 30308,
        std_document_order_quantity_exceeded_max_operations_forward_balance = 30309,
        rmkt = 30310,
        irmkt_document_order_quantity_exceeded_max_incremental_market_risk = 30311,
        spi_document_order_quantity_exceeded_previous_potencial_balance = 30312,
        std_document_termo_not_allowed = 30313,
        sfd_document_day_trade_cash_balance_stop_loss_not_configured_030314 = 30314,
        spvd_document_order_exceeded_potential_short_uncovered_balance_030315 = 30315,
        rmse_document_order_exceeded_risk_increase_at_extended_session_030316 = 30316,
        rmse_document_order_exceeded_risk_increase_of_broker_at_extended_session_030317 = 30317,
        mkta_entering_trader_buysell_symbols_market_not_configured_030400 = 30400,
        mkta_entering_trader_buy_not_allowed_for_symbols_market_030401 = 30401,
        mkta_entering = 30402,
        tmox_entering_trader_max_bidoffer_quantity_not_configured = 30403,
        tmoc_entering_trader_max_bid_quantity_exceeded_for_single_order = 30404,
        tmov_entering_trader_max_offer_quantity_exceeded_for_si = 30405,
        spci_entering_trader_order_quantity_exceeded_max_bid_potential_balance = 30406,
        spvi_entering_trader_order_quantity_exceeded_max_offer_potential_balance = 30407,
        sdp_entering_trader_order_exceeded_max_financial_potential = 30408,
        spvd_trader_order_exceeded_potential_short_uncovered_balance = 30415,
        oms_unexpected_internal_error_030500 = 30500,
        oms_invalid_session_or_symbol_030501 = 30501,
        oms_clordid_cannot_be_empty_030502 = 30502,
        oms_clordid_is_duplicated_030503 = 30503,
        oms_clordid_not_found_030504 = 30504,
        oms_origclordid_cannot_be_empty_030505 = 30505,
        oms_crossid_cannot_be_empty_030506 = 30506,
        oms_clordid_is_duplicated_within_cross_order_030507 = 30507,
        oms_cross_order_modification_is_not_allowed_030508 = 30508,
        oms_orderid_not_found_030509 = 30509,
        oms_orderid_cannot_be_empty_030510 = 30510,
        oms_quotereqid_cannot_be_empty_030511 = 30511,
        oms_quotereqid_is_duplicated_030512 = 30512,
        oms_quotereqid_not_found_030513 = 30513,
        oms_quoteid_cannot_be_empty_030514 = 30514,
        oms_in = 30521,
        oms = 30522,
        oms_entering_firm_modification_is_not_allowed_030523 = 30523,
        oms_account_modification_on_dma_order_is_not_allowed_030524 = 30524,
        oms_account_information_missing_on_non = 30525,
        oms_entering_trader = 30526,
        oms_received_execution_report_rejection_for_an_active_order_030527 = 30527,
        broker_negotiation_blocked_031011 = 31011,
        broker_not_available_031012 = 31012,
        brokers_capture_account_not_found_031013 = 31013,
        brokers_segment_negotiation_blocked_031014 = 31014,
        broker_segment_not_available_031015 = 31015,
        brokers_segment_protected_mode_under_activation_031016 = 31016,
        account_negotiation_blocked_031021 = 31021,
        account_not_available_031022 = 31022,
        accounts_protected_mode_under_activation_031023 = 31023,
        account_mandatory_on_dma_orders_031024 = 31024,
        transient_account_is_hierarchically_blocked_on_protected_mode_031025 = 31025,
        crossorders_or_crossforward_not_allowed_while_account_in_protected_mode_031026 = 31026,
        transient_account_not_allowed_in_extended_hours_031027 = 31027,
        document_negotiation_blocked_031031 = 31031,
        document_not_available_031032 = 31032,
        documents_protected_mode_under_activation_031033 = 31033,
        executor_document_cannot_use_default_broker_profile_031034 = 31034,
        document_in_blocked_profile_031035 = 31035,
        crossorders_or_crossforward_not_allowed_while_document_in_protected_mode_031036 = 31036,
        entering_trader_negotiation_blocked_031041 = 31041,
        entering_trader_not_available_031042 = 31042,
        entering_trader_blocked_by_sfd_overflow_031043 = 31043,
        non_dma_orders_must_provide_account_while_in_brokers_protected_mode_031044 = 31044,
        entering_trader_not_authorized_to_trade_accountless_orders_031045 = 31045,
        entering_trader_cannot_trade_on_behalf_of_other_firms_account_031046 = 31046,
        symbol_not_available_031050 = 31050,
        symbol_internal_data_corrupted_031051 = 31051,
        fix_message_type_does_not_support_operations_on_such_symbol_031052 = 31052,
        symbols_underlying_not_found_for_risk_aggregation_031053 = 31053,
        symbols_risk_unit_matrix_not_available_031054 = 31054,
        symbols_reference_price_missing_market_orders_not_allowed_031055 = 31055,
        symbols_calculated_price_invalid_031056 = 31056,
        spreads_leg_not_available_031060 = 31060,
        spreads_leg_internal_data_corrupted_031061 = 31061,
        unexpected_internal_error_during_risk_evaluation_031070 = 31070,
        mkta_account_buy_not_allowed_for_symbols_market_031201 = 31201,
        mkta_account_sell_not_allowed_for_symbols_market_031202 = 31202,
        tmoc_account_max_bid_quantity_exceeded_for_single_order = 31204,
        tmov_account_max_offer_quantity_exceeded_for_single_order = 31205,
        spci_account_order_quantity_exceeded_max_bid_potential_balance = 31206,
        spvi_account_order_quantity_exceeded_max_offer_potential_balance = 31207,
        sdp_account_order_exceeded_max_financial_potential_balance_due = 31208,
        rmkt_account_order_quantity_exceeded_max_market_risk = 31210,
        irmkt_account_order_quantity_exceeded_max_incremental_market_risk = 31211,
        spi_account_order_quantity_exceeded_previous_potencial_balance = 31212,
        std_account_termo_not_allowed_protected_mode_enabled_031213 = 31213,
        spvd_account_order_exceeded_potential_short_uncovered_balance_031215 = 31215,
        mkta_document_buysell_symbols_market_not_configured_031300 = 31300,
        mkta_document_buy_not_allowed_for_symbols_market_031301 = 31301,
        mkta_document_sell_not_allowed_for_symbols_market_031302 = 31302,
        tmox_document_maximum_order_size_not_configured = 31303,
        tmoc_document_maximum_order_size_exceeded_for_single_order = 31304,
        tmov_document_maximum_order_size_exceeded_for_single_order = 31305,
        spci_document_order_quantity_exceeded_short_position_per_instrument = 31306,
        spvi_document_order_quantity_exceeded_long_position_per_instrument = 31307,
        sdp_document_order_exceeded_cash_settlement_exposure = 31308,
        std_document_order_quantity_exceeded_forward_contracts_exposure = 31309,
        rmkt_document_order_quantity_exceeded_risk_increase = 31310,
        irmkt_document_order_quantity_exceeded_risk_increase_reducing_mode = 31311,
        spi_document_order_quantity_exceeded_long_and_short_position_reducing_mode = 31312,
        std_document_termo_not_allowed_protected_mode_enabled = 31313,
        sfd_document_day_trade_cash_balance_stop_loss_not_configured_031314 = 31314,
        spvd_document_order_exceeded_potential_short_uncovered_balance_031315 = 31315,
        rmse_document_order_exceeded_risk_increase_at_extended_session_031316 = 31316,
        rmse_document_order_exceeded_risk_increase_of_broker_at_extended_session_031317 = 31317,
        mkta_entering_trader_buysell_symbols_market_not_configured_031400 = 31400,
        mkta_entering_trader_buy_not_allowed_for_symbols_market_031401 = 31401,
        mkta_entering_trader_sell_not_allowed_for_symbols_market = 31402,
        tmox_entering_trader_maximum_order_size_not_configured = 31403,
        tmoc_entering_trader_maximum_order_size_exceeded_for_single_order = 31404,
        tmov_entering_trader_maximum_order_size_exceeded_for_single_order = 31405,
        spci_entering_trader_order_quantity_exceeded_short_position_per_instrument = 31406,
        spvi_entering_trader_order_quantity_exceeded_long_position_per_instrument = 31407,
        sdp_entering_trader_order_exceeded_cash_settlement_exposure = 31408,
        oms_unexpected_internal_error_031500 = 31500,
        oms_invalid_session_or_symbol_031501 = 31501,
        oms_clordid_cannot_be_empty_031502 = 31502,
        oms_clordid_is_duplicated_031503 = 31503,
        oms_clordid_not_found_031504 = 31504,
        oms_origclordid_cannot_be_empty_031505 = 31505,
        oms_crossid_cannot_be_empty_031506 = 31506,
        oms_clordid_is_duplicated_within_cross_order_031507 = 31507,
        oms_cross_order_modification_is_not_allowed_031508 = 31508,
        oms_orderid_not_found_031509 = 31509,
        oms_orderid_cannot_be_empty_031510 = 31510,
        oms_quotereqid_cannot_be_empty_031511 = 31511,
        oms_quotereqid_is_duplicated_031512 = 31512,
        oms_quotereqid_not_found_031513 = 31513,
        oms_quoteid_cannot_be_empty_031514 = 31514,
        oms_inflight_modification_is_not_allowed = 31521,
        oms_side_modification_is_not_allowed = 31522,
        oms_entering_firm_modification_is_not_allowed_031523 = 31523,
        oms_account_modification_on_dma_order_is_not_allowed_031524 = 31524,
        oms_account_information_missing_on_nondma_order = 31525,
        oms_entering_trader_modification_on_nondma_order_is_not_allowed = 31526,
        oms_received_execution_report_rejection_for_an_active_order_031527 = 31527,
        field_missing_or_incorrect_032000 = 32000,
        line_not_available_or_busy = 32001,
        line_internal_error = 32002,
        line_recovering_or_starting_up = 32003,
        internal_gateway_error_message_forwarding_failure = 32004,
        invalid_quantity = 32005,
        duplicate_order = 32006,
        missing_account_field = 32007,
        unknown_account = 32008,
        unknown_firmid_for_routing = 32009,
        duplicate_firmid = 32010,
        duplicate_sender_location = 32011,
        duplicate_entering_trader = 32012,
        firm_or_trader_is_missing_in_nondma_order = 32013,
        firm_or_account_is_missing_in_dma_order = 32014,
        same_participants_on_both_sides_or_invalid_sides = 32015,
        buy_side_and_sell_side_having_different_firmids = 32016,
        buy_side_and_sell_side_trading_different_assets = 32017,
        invalid_price_032018 = 32018,
        line_overloaded = 32019,
        line_administratively_blocked = 32020,
        invalid_price_032021 = 32021,
        system_overloaded = 32022,
        system_error_032023 = 32023,
        throttle_limit_reached = 33000,
        invalid_security_id = 33001,
        unknown_market_segment_id = 33002,
        field_missing_or_incorrect_033003 = 33003,
        system_error_033050 = 33050
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 486> from_string_map = {{
        {"[IRMKT] Account: Order quantity exceeded Max Incremental Market Risk", enum_type::irmkt_account_order_quantity_exceeded_max_incremental_market_risk},
        {"[IRMKT] Account: Order quantity exceeded risk increase - reducing mode", enum_type::irmkt_account_order_quantity_exceeded_risk_increase_reducing_mode},
        {"[IRMKT] Document: Order quantity exceeded Max Incremental Market Risk", enum_type::irmkt_document_order_quantity_exceeded_max_incremental_market_risk},
        {"[IRMKT] Document: Order quantity exceeded risk increase - reducing mode", enum_type::irmkt_document_order_quantity_exceeded_risk_increase_reducing_mode},
        {"[MKTA] Account: Buy not allowed for symbol's market", enum_type::mkta_account_buy_not_allowed_for_symbols_market_030201},
        {"[MKTA] Account: Buy not allowed for symbol's market", enum_type::mkta_account_buy_not_allowed_for_symbols_market_031201},
        {"[MKTA] Account: Sell not allowed for symbol's market", enum_type::mkta_account_sell_not_allowed_for_symbols_market_030202},
        {"[MKTA] Account: Sell not allowed for symbol's market", enum_type::mkta_account_sell_not_allowed_for_symbols_market_031202},
        {"[MKTA] Document: Buy not allowed for symbol's market", enum_type::mkta_document_buy_not_allowed_for_symbols_market_030301},
        {"[MKTA] Document: Buy not allowed for symbol's market", enum_type::mkta_document_buy_not_allowed_for_symbols_market_031301},
        {"[MKTA] Document: Buy/Sell symbol's market not configured", enum_type::mkta_document_buysell_symbols_market_not_configured_030300},
        {"[MKTA] Document: Buy/Sell symbol's market not configured", enum_type::mkta_document_buysell_symbols_market_not_configured_031300},
        {"[MKTA] Document: Sell not allowed for symbol's market", enum_type::mkta_document_sell_not_allowed_for_symbols_market_030302},
        {"[MKTA] Document: Sell not allowed for symbol's market", enum_type::mkta_document_sell_not_allowed_for_symbols_market_031302},
        {"[MKTA] Entering", enum_type::mkta_entering},
        {"[MKTA] Entering trader: Buy not allowed for symbol's market", enum_type::mkta_entering_trader_buy_not_allowed_for_symbols_market_030401},
        {"[MKTA] Entering trader: Buy not allowed for symbol's market", enum_type::mkta_entering_trader_buy_not_allowed_for_symbols_market_031401},
        {"[MKTA] Entering trader: Buy/Sell symbol's market not configured", enum_type::mkta_entering_trader_buysell_symbols_market_not_configured_030400},
        {"[MKTA] Entering trader: Buy/Sell symbol's market not configured", enum_type::mkta_entering_trader_buysell_symbols_market_not_configured_031400},
        {"[MKTA] Entering trader: Sell not allowed for symbol's market", enum_type::mkta_entering_trader_sell_not_allowed_for_symbols_market},
        {"[OMS]", enum_type::oms},
        {"[OMS] Account information missing on non", enum_type::oms_account_information_missing_on_non},
        {"[OMS] Account information missing on non-DMA order", enum_type::oms_account_information_missing_on_nondma_order},
        {"[OMS] Account modification on DMA order is not allowed", enum_type::oms_account_modification_on_dma_order_is_not_allowed_030524},
        {"[OMS] Account modification on DMA order is not allowed", enum_type::oms_account_modification_on_dma_order_is_not_allowed_031524},
        {"[OMS] ClOrdID cannot be empty", enum_type::oms_clordid_cannot_be_empty_030502},
        {"[OMS] ClOrdID cannot be empty", enum_type::oms_clordid_cannot_be_empty_031502},
        {"[OMS] ClOrdID is duplicated", enum_type::oms_clordid_is_duplicated_030503},
        {"[OMS] ClOrdID is duplicated", enum_type::oms_clordid_is_duplicated_031503},
        {"[OMS] ClOrdID is duplicated within Cross Order", enum_type::oms_clordid_is_duplicated_within_cross_order_030507},
        {"[OMS] ClOrdID is duplicated within Cross Order", enum_type::oms_clordid_is_duplicated_within_cross_order_031507},
        {"[OMS] ClOrdID not found", enum_type::oms_clordid_not_found_030504},
        {"[OMS] ClOrdID not found", enum_type::oms_clordid_not_found_031504},
        {"[OMS] Cross Order modification is not allowed", enum_type::oms_cross_order_modification_is_not_allowed_030508},
        {"[OMS] Cross Order modification is not allowed", enum_type::oms_cross_order_modification_is_not_allowed_031508},
        {"[OMS] CrossID cannot be empty", enum_type::oms_crossid_cannot_be_empty_030506},
        {"[OMS] CrossID cannot be empty", enum_type::oms_crossid_cannot_be_empty_031506},
        {"[OMS] Entering firm modification is not allowed", enum_type::oms_entering_firm_modification_is_not_allowed_030523},
        {"[OMS] Entering firm modification is not allowed", enum_type::oms_entering_firm_modification_is_not_allowed_031523},
        {"[OMS] Entering trader", enum_type::oms_entering_trader},
        {"[OMS] Entering trader modification on non-DMA order is not allowed", enum_type::oms_entering_trader_modification_on_nondma_order_is_not_allowed},
        {"[OMS] In", enum_type::oms_in},
        {"[OMS] In-Flight modification is not allowed", enum_type::oms_inflight_modification_is_not_allowed},
        {"[OMS] Invalid session or symbol", enum_type::oms_invalid_session_or_symbol_030501},
        {"[OMS] Invalid session or symbol", enum_type::oms_invalid_session_or_symbol_031501},
        {"[OMS] OrderID cannot be empty", enum_type::oms_orderid_cannot_be_empty_030510},
        {"[OMS] OrderID cannot be empty", enum_type::oms_orderid_cannot_be_empty_031510},
        {"[OMS] OrderID not found", enum_type::oms_orderid_not_found_030509},
        {"[OMS] OrderID not found", enum_type::oms_orderid_not_found_031509},
        {"[OMS] OrigClOrdID cannot be empty", enum_type::oms_origclordid_cannot_be_empty_030505},
        {"[OMS] OrigClOrdID cannot be empty", enum_type::oms_origclordid_cannot_be_empty_031505},
        {"[OMS] QuoteID cannot be empty", enum_type::oms_quoteid_cannot_be_empty_030514},
        {"[OMS] QuoteID cannot be empty", enum_type::oms_quoteid_cannot_be_empty_031514},
        {"[OMS] QuoteReqID cannot be empty", enum_type::oms_quotereqid_cannot_be_empty_030511},
        {"[OMS] QuoteReqID cannot be empty", enum_type::oms_quotereqid_cannot_be_empty_031511},
        {"[OMS] QuoteReqID is duplicated", enum_type::oms_quotereqid_is_duplicated_030512},
        {"[OMS] QuoteReqID is duplicated", enum_type::oms_quotereqid_is_duplicated_031512},
        {"[OMS] QuoteReqID not found", enum_type::oms_quotereqid_not_found_030513},
        {"[OMS] QuoteReqID not found", enum_type::oms_quotereqid_not_found_031513},
        {"[OMS] Received Execution Report Rejection for an active order", enum_type::oms_received_execution_report_rejection_for_an_active_order_030527},
        {"[OMS] Received Execution Report Rejection for an active order", enum_type::oms_received_execution_report_rejection_for_an_active_order_031527},
        {"[OMS] Side modification is not allowed", enum_type::oms_side_modification_is_not_allowed},
        {"[OMS] Unexpected internal error", enum_type::oms_unexpected_internal_error_030500},
        {"[OMS] Unexpected internal error", enum_type::oms_unexpected_internal_error_031500},
        {"[RMKT]", enum_type::rmkt},
        {"[RMKT] Account: Order quantity exceeded Max Market Risk", enum_type::rmkt_account_order_quantity_exceeded_max_market_risk},
        {"[RMKT] Account: Order quantity exceeded risk increase", enum_type::rmkt_account_order_quantity_exceeded_risk_increase},
        {"[RMKT] Broker PN <pn> document aggregation: Order quantity exceeded risk increase", enum_type::rmkt_broker_pn_pn_document_aggregation_order_quantity_exceeded_risk_increase},
        {"[RMKT] Document: Order quantity exceeded risk increase", enum_type::rmkt_document_order_quantity_exceeded_risk_increase},
        {"[RMSE] Broker PN <pn> document aggregation: Order exceeded risk increase at extended session", enum_type::rmse_broker_pn_pn_document_aggregation_order_exceeded_risk_increase_at_extended_session},
        {"[RMSE] Broker: Order exceeded risk increase at extended session", enum_type::rmse_broker_order_exceeded_risk_increase_at_extended_session},
        {"[RMSE] Document: Order exceeded risk increase at extended session", enum_type::rmse_document_order_exceeded_risk_increase_at_extended_session_030316},
        {"[RMSE] Document: Order exceeded risk increase at extended session", enum_type::rmse_document_order_exceeded_risk_increase_at_extended_session_031316},
        {"[RMSE] Document: Order exceeded risk increase of broker at extended session", enum_type::rmse_document_order_exceeded_risk_increase_of_broker_at_extended_session_030317},
        {"[RMSE] Document: Order exceeded risk increase of broker at extended session", enum_type::rmse_document_order_exceeded_risk_increase_of_broker_at_extended_session_031317},
        {"[SDP] Account: Order exceeded cash settlement exposure", enum_type::sdp_account_order_exceeded_cash_settlement_exposure},
        {"[SDP] Account: Order exceeded Max Financial Potential Balance Due", enum_type::sdp_account_order_exceeded_max_financial_potential_balance_due},
        {"[SDP] Broker PN <pn> document aggregation: Order exceeded cash settlement exposure", enum_type::sdp_broker_pn_pn_document_aggregation_order_exceeded_cash_settlement_exposure},
        {"[SDP] Broker PN <pn> trader aggregation: Order exceeded cash settlement exposure", enum_type::sdp_broker_pn_pn_trader_aggregation_order_exceeded_cash_settlement_exposure},
        {"[SDP] Document: Order exceeded cash settlement exposure", enum_type::sdp_document_order_exceeded_cash_settlement_exposure},
        {"[SDP] Document: Order exceeded Max Financial Potential Balance Due", enum_type::sdp_document_order_exceeded_max_financial_potential_balance_due},
        {"[SDP] Entering trader: Order exceeded cash settlement exposure", enum_type::sdp_entering_trader_order_exceeded_cash_settlement_exposure},
        {"[SDP] Entering trader: Order exceeded Max Financial Potential", enum_type::sdp_entering_trader_order_exceeded_max_financial_potential},
        {"[SFD] Broker PN <pn> document aggregation: Day trade cash balance (stop loss) not configured", enum_type::sfd_broker_pn_pn_document_aggregation_day_trade_cash_balance_stop_loss_not_configured},
        {"[SFD] Document: Day trade cash balance (stop loss) not configured", enum_type::sfd_document_day_trade_cash_balance_stop_loss_not_configured_030314},
        {"[SFD] Document: Day trade cash balance (stop loss) not configured", enum_type::sfd_document_day_trade_cash_balance_stop_loss_not_configured_031314},
        {"[SPCI] Account: Order quantity exceeded Max Bid Potential Balance", enum_type::spci_account_order_quantity_exceeded_max_bid_potential_balance},
        {"[SPCI] Account: Order quantity exceeded short position per instrument", enum_type::spci_account_order_quantity_exceeded_short_position_per_instrument},
        {"[SPCI] Document: Order quantity exceeded Max Bid Potential Balance", enum_type::spci_document_order_quantity_exceeded_max_bid_potential_balance},
        {"[SPCI] Document: Order quantity exceeded short position per instrument", enum_type::spci_document_order_quantity_exceeded_short_position_per_instrument},
        {"[SPCI] Entering trader: Order quantity exceeded Max Bid Potential Balance", enum_type::spci_entering_trader_order_quantity_exceeded_max_bid_potential_balance},
        {"[SPCI] Entering trader: Order quantity exceeded short position per instrument", enum_type::spci_entering_trader_order_quantity_exceeded_short_position_per_instrument},
        {"[SPI] Account: Order quantity exceeded long and short position - reducing mode", enum_type::spi_account_order_quantity_exceeded_long_and_short_position_reducing_mode},
        {"[SPI] Account: Order quantity exceeded Previous Potencial Balance", enum_type::spi_account_order_quantity_exceeded_previous_potencial_balance},
        {"[SPI] Document: Order quantity exceeded long and short position - reducing mode", enum_type::spi_document_order_quantity_exceeded_long_and_short_position_reducing_mode},
        {"[SPI] Document: Order quantity exceeded Previous Potencial Balance", enum_type::spi_document_order_quantity_exceeded_previous_potencial_balance},
        {"[SPVD] Account: Order exceeded potential short uncovered balance.", enum_type::spvd_account_order_exceeded_potential_short_uncovered_balance_030215},
        {"[SPVD] Account: Order exceeded potential short uncovered balance.", enum_type::spvd_account_order_exceeded_potential_short_uncovered_balance_031215},
        {"[SPVD] Broker PN <pn> document aggregation: Order exceeded potential short uncovered balance.", enum_type::spvd_broker_pn_pn_document_aggregation_order_exceeded_potential_short_uncovered_balance},
        {"[SPVD] Broker PN <pn> trader aggregation: Order exceeded potential short uncovered balance.", enum_type::spvd_broker_pn_pn_trader_aggregation_order_exceeded_potential_short_uncovered_balance},
        {"[SPVD] Document: Order exceeded potential short uncovered balance", enum_type::spvd_document_order_exceeded_potential_short_uncovered_balance_030315},
        {"[SPVD] Document: Order exceeded potential short uncovered balance.", enum_type::spvd_document_order_exceeded_potential_short_uncovered_balance_031315},
        {"[SPVD] Trader: Order exceeded potential short uncovered balance.", enum_type::spvd_trader_order_exceeded_potential_short_uncovered_balance},
        {"[SPVI] Account: Order quantity exceeded long position per instrument", enum_type::spvi_account_order_quantity_exceeded_long_position_per_instrument},
        {"[SPVI] Account: Order quantity exceeded Max Offer Potential Balance", enum_type::spvi_account_order_quantity_exceeded_max_offer_potential_balance},
        {"[SPVI] Document: Order quantity exceeded long position per instrument", enum_type::spvi_document_order_quantity_exceeded_long_position_per_instrument},
        {"[SPVI] Document: Order quantity exceeded Max Offer Potential Balance", enum_type::spvi_document_order_quantity_exceeded_max_offer_potential_balance},
        {"[SPVI] Entering trader: Order quantity exceeded long position per instrument", enum_type::spvi_entering_trader_order_quantity_exceeded_long_position_per_instrument},
        {"[SPVI] Entering trader: Order quantity exceeded Max Offer Potential Balance", enum_type::spvi_entering_trader_order_quantity_exceeded_max_offer_potential_balance},
        {"[STD] Account: Termo not allowed, protected mode enabled", enum_type::std_account_termo_not_allowed_protected_mode_enabled_030213},
        {"[STD] Account: Termo not allowed, protected mode enabled", enum_type::std_account_termo_not_allowed_protected_mode_enabled_031213},
        {"[STD] Document: Order quantity exceeded forward contracts exposure", enum_type::std_document_order_quantity_exceeded_forward_contracts_exposure},
        {"[STD] Document: Order quantity exceeded Max Operations Forward Balance", enum_type::std_document_order_quantity_exceeded_max_operations_forward_balance},
        {"[STD] Document: Termo not allowed,", enum_type::std_document_termo_not_allowed},
        {"[STD] Document: Termo not allowed, protected mode enabled", enum_type::std_document_termo_not_allowed_protected_mode_enabled},
        {"[TMOC] Account: Max Bid quantity exceeded for single order", enum_type::tmoc_account_max_bid_quantity_exceeded_for_single_order},
        {"[TMOC] Account: Maximum order size exceeded for single order", enum_type::tmoc_account_maximum_order_size_exceeded_for_single_order},
        {"[TMOC] Document: Max Bid quantity exceeded for single order", enum_type::tmoc_document_max_bid_quantity_exceeded_for_single_order},
        {"[TMOC] Document: Maximum order size exceeded for single order", enum_type::tmoc_document_maximum_order_size_exceeded_for_single_order},
        {"[TMOC] Entering trader: Max Bid quantity exceeded for single order", enum_type::tmoc_entering_trader_max_bid_quantity_exceeded_for_single_order},
        {"[TMOC] Entering trader: Maximum order size exceeded for single order", enum_type::tmoc_entering_trader_maximum_order_size_exceeded_for_single_order},
        {"[TMOV] Account: Max Offer quantity exceeded for single order", enum_type::tmov_account_max_offer_quantity_exceeded_for_single_order},
        {"[TMOV] Account: Maximum order size exceeded for single order", enum_type::tmov_account_maximum_order_size_exceeded_for_single_order},
        {"[TMOV] Document: Max Offer quantity exceeded for single order", enum_type::tmov_document_max_offer_quantity_exceeded_for_single_order},
        {"[TMOV] Document: Maximum order size exceeded for single order", enum_type::tmov_document_maximum_order_size_exceeded_for_single_order},
        {"[TMOV] Entering trader: Max Offer quantity exceeded for si", enum_type::tmov_entering_trader_max_offer_quantity_exceeded_for_si},
        {"[TMOV] Entering trader: Maximum order size exceeded for single order", enum_type::tmov_entering_trader_maximum_order_size_exceeded_for_single_order},
        {"[TMOX] Document: Max", enum_type::tmox_document_max},
        {"[TMOX] Document: Maximum order size not configured", enum_type::tmox_document_maximum_order_size_not_configured},
        {"[TMOX] Entering trader: Max Bid/Offer quantity not configured", enum_type::tmox_entering_trader_max_bidoffer_quantity_not_configured},
        {"[TMOX] Entering trader: Maximum order size not configured", enum_type::tmox_entering_trader_maximum_order_size_not_configured},
        {"Account is mandatory for FX SPOT", enum_type::account_is_mandatory_for_fx_spot},
        {"Account is mandatory for Pegged Order", enum_type::account_is_mandatory_for_pegged_order},
        {"Account mandatory on DMA orders", enum_type::account_mandatory_on_dma_orders_030024},
        {"Account mandatory on DMA orders", enum_type::account_mandatory_on_dma_orders_031024},
        {"Account negotiation blocked", enum_type::account_negotiation_blocked_030021},
        {"Account negotiation blocked", enum_type::account_negotiation_blocked_031021},
        {"Account not available", enum_type::account_not_available_030022},
        {"Account not available", enum_type::account_not_available_031022},
        {"Account or Give Up firm required for DMA customers", enum_type::account_or_give_up_firm_required_for_dma_customers},
        {"Account or Give Up firm required for equities", enum_type::account_or_give_up_firm_required_for_equities},
        {"Account's protected mode under activation", enum_type::accounts_protected_mode_under_activation_030023},
        {"Account's protected mode under activation", enum_type::accounts_protected_mode_under_activation_031023},
        {"Acct Type(38) not valid for Tag 581 for DMA customers", enum_type::acct_type38_not_valid_for_tag_581_for_dma_customers},
        {"ActionTargetGroupID  invalid . It doesn't exist or it is disabled", enum_type::actiontargetgroupid_invalid_it_doesnt_exist_or_it_is_disabled},
        {"ActionTargetGroupID must be informed", enum_type::actiontargetgroupid_must_be_informed},
        {"All Legs must have same Lot Types", enum_type::all_legs_must_have_same_lot_types},
        {"All Legs must have same Step of Quotation", enum_type::all_legs_must_have_same_step_of_quotation},
        {"All Legs must have same Tick Increment", enum_type::all_legs_must_have_same_tick_increment},
        {"Attempt to cancel an order with a different FirmID than the original order", enum_type::attempt_to_cancel_an_order_with_a_different_firmid_than_the_original_order},
        {"Attempt to cancel an order with a different SenderLocationID than the original order", enum_type::attempt_to_cancel_an_order_with_a_different_senderlocationid_than_the_original_order},
        {"Attempt to modify an order with a different AccountID than the original order", enum_type::attempt_to_modify_an_order_with_a_different_accountid_than_the_original_order},
        {"Attempt to modify an order with a different AccountType than the original order", enum_type::attempt_to_modify_an_order_with_a_different_accounttype_than_the_original_order},
        {"Attempt to modify an order with a different FirmID than the original order", enum_type::attempt_to_modify_an_order_with_a_different_firmid_than_the_original_order},
        {"Attempt to modify an order with a different in-flight-fill mitigation status than first modification", enum_type::attempt_to_modify_an_order_with_a_different_inflightfill_mitigation_status_than_first_modification},
        {"Attempt to modify an order with a different SenderCompID than the original order", enum_type::attempt_to_modify_an_order_with_a_different_sendercompid_than_the_original_order},
        {"Attempt to modify an order with a different SenderLocationID than the original order", enum_type::attempt_to_modify_an_order_with_a_different_senderlocationid_than_the_original_order},
        {"Attempt to modify an order with a different TraderID than the original order", enum_type::attempt_to_modify_an_order_with_a_different_traderid_than_the_original_order},
        {"Attempt to modify market order to some other type", enum_type::attempt_to_modify_market_order_to_some_other_type},
        {"Attempt to modify the order type from/to Pegged", enum_type::attempt_to_modify_the_order_type_fromto_pegged},
        {"Attempt to modify the order type from/to RLP", enum_type::attempt_to_modify_the_order_type_fromto_rlp},
        {"Available quantity to block is zero", enum_type::available_quantity_to_block_is_zero},
        {"BBT messages should not be entered when market is forbidden", enum_type::bbt_messages_should_not_be_entered_when_market_is_forbidden},
        {"BBT messages should not be entered when market is no cancel", enum_type::bbt_messages_should_not_be_entered_when_market_is_no_cancel},
        {"BBT messages should not be entered when market is paused", enum_type::bbt_messages_should_not_be_entered_when_market_is_paused},
        {"BBT messages should not be entered when market is PCP", enum_type::bbt_messages_should_not_be_entered_when_market_is_pcp},
        {"BBT messages should not be entered when market is pre close", enum_type::bbt_messages_should_not_be_entered_when_market_is_pre_close},
        {"BBT messages should not be entered when market is pre open", enum_type::bbt_messages_should_not_be_entered_when_market_is_pre_open},
        {"BBT messages should not be entered when market is reserved", enum_type::bbt_messages_should_not_be_entered_when_market_is_reserved},
        {"Blocking qty more than available quantity", enum_type::blocking_qty_more_than_available_quantity},
        {"Blocking quantity more than 999999999", enum_type::blocking_quantity_more_than_999999999},
        {"Broker negotiation blocked", enum_type::broker_negotiation_blocked_030011},
        {"Broker negotiation blocked", enum_type::broker_negotiation_blocked_031011},
        {"Broker not available", enum_type::broker_not_available_030012},
        {"Broker not available", enum_type::broker_not_available_031012},
        {"Broker PN negotiation blocked", enum_type::broker_pn_negotiation_blocked},
        {"Broker PN not available", enum_type::broker_pn_not_available},
        {"Broker PN protected mode under activation", enum_type::broker_pn_protected_mode_under_activation},
        {"Broker segment not available", enum_type::broker_segment_not_available_030015},
        {"Broker segment not available", enum_type::broker_segment_not_available_031015},
        {"Broker's capture account not found", enum_type::brokers_capture_account_not_found_030013},
        {"Broker's capture account not found", enum_type::brokers_capture_account_not_found_031013},
        {"Broker's segment negotiation blocked", enum_type::brokers_segment_negotiation_blocked_030014},
        {"Broker's segment negotiation blocked", enum_type::brokers_segment_negotiation_blocked_031014},
        {"Broker's segment protected mode under activation", enum_type::brokers_segment_protected_mode_under_activation_030016},
        {"Broker's segment protected mode under activation", enum_type::brokers_segment_protected_mode_under_activation_031016},
        {"Business reject: Application Not Available", enum_type::business_reject_application_not_available},
        {"Business reject: Other", enum_type::business_reject_other},
        {"Business reject: Required field missing", enum_type::business_reject_required_field_missing},
        {"Business reject: Unknown ID", enum_type::business_reject_unknown_id},
        {"Business reject: Unknown security", enum_type::business_reject_unknown_security},
        {"Business reject: Unsupported message type", enum_type::business_reject_unsupported_message_type},
        {"Buy order stop price must be above last trade price", enum_type::buy_order_stop_price_must_be_above_last_trade_price},
        {"BUY side and SELL side having different FirmIDs", enum_type::buy_side_and_sell_side_having_different_firmids},
        {"BUY side and SELL side trading different assets", enum_type::buy_side_and_sell_side_trading_different_assets},
        {"Cancel of Order Participating in TOP not allowed.", enum_type::cancel_of_order_participating_in_top_not_allowed},
        {"Cannot modify order because order does not exist", enum_type::cannot_modify_order_because_order_does_not_exist},
        {"COD Not Supported for GTC/ GTD Orders", enum_type::cod_not_supported_for_gtc_gtd_orders},
        {"Contract claims to be a spread but is missing one or more legs", enum_type::contract_claims_to_be_a_spread_but_is_missing_one_or_more_legs},
        {"Contract for this order contract is past expiration date and may no longer be traded", enum_type::contract_for_this_order_contract_is_past_expiration_date_and_may_no_longer_be_traded},
        {"Contract is not eligible for electronic matching", enum_type::contract_is_not_eligible_for_electronic_matching},
        {"Contract not eligible for negotiated quote", enum_type::contract_not_eligible_for_negotiated_quote},
        {"Cross Order Rejected due to Auction Trigger Validation", enum_type::cross_order_rejected_due_to_auction_trigger_validation},
        {"Cross order suspended for the participant or session", enum_type::cross_order_suspended_for_the_participant_or_session},
        {"Cross-orders or cross-forward not allowed while account in protected mode", enum_type::crossorders_or_crossforward_not_allowed_while_account_in_protected_mode_030026},
        {"Cross-orders or cross-forward not allowed while account in protected mode", enum_type::crossorders_or_crossforward_not_allowed_while_account_in_protected_mode_031026},
        {"Cross-orders or cross-forward not allowed while document in protected mode", enum_type::crossorders_or_crossforward_not_allowed_while_document_in_protected_mode_030036},
        {"Cross-orders or cross-forward not allowed while document in protected mode", enum_type::crossorders_or_crossforward_not_allowed_while_document_in_protected_mode_031036},
        {"CrossType ineligible for instrument", enum_type::crosstype_ineligible_for_instrument},
        {"Current termo request status does not allow acceptance", enum_type::current_termo_request_status_does_not_allow_acceptance},
        {"Current termo request status does not allow rejection", enum_type::current_termo_request_status_does_not_allow_rejection},
        {"Days to Settlement must be between 16 and 90", enum_type::days_to_settlement_must_be_between_16_and_90},
        {"Days to Settlement must be between 16 and 999.", enum_type::days_to_settlement_must_be_between_16_and_999},
        {"Disclosed Qty cannot be less than Disclosed Qty Min", enum_type::disclosed_qty_cannot_be_less_than_disclosed_qty_min},
        {"Disclosed Quantity cannot be greater than total or remaining quantity", enum_type::disclosed_quantity_cannot_be_greater_than_total_or_remaining_quantity},
        {"Disclosed Quantity is not allowed", enum_type::disclosed_quantity_is_not_allowed},
        {"DMA CrossOrder Not allowed", enum_type::dma_crossorder_not_allowed},
        {"Document in blocked profile", enum_type::document_in_blocked_profile_030035},
        {"Document in blocked profile", enum_type::document_in_blocked_profile_031035},
        {"Document negotiation blocked", enum_type::document_negotiation_blocked_030031},
        {"Document negotiation blocked", enum_type::document_negotiation_blocked_031031},
        {"Document not available", enum_type::document_not_available_030032},
        {"Document not available", enum_type::document_not_available_031032},
        {"Document's protected mode under activation", enum_type::documents_protected_mode_under_activation_030033},
        {"Document's protected mode under activation", enum_type::documents_protected_mode_under_activation_031033},
        {"Duplicate Client Order Id for this Session/Contract.", enum_type::duplicate_client_order_id_for_this_sessioncontract},
        {"Duplicate Entering Trader", enum_type::duplicate_entering_trader},
        {"Duplicate FirmID", enum_type::duplicate_firmid},
        {"Duplicate Order", enum_type::duplicate_order},
        {"Duplicate Sender Location", enum_type::duplicate_sender_location},
        {"Engine did not respond to FAS request", enum_type::engine_did_not_respond_to_fas_request},
        {"Entering Trader blocked by SFD overflow", enum_type::entering_trader_blocked_by_sfd_overflow_030043},
        {"Entering Trader blocked by SFD overflow", enum_type::entering_trader_blocked_by_sfd_overflow_031043},
        {"Entering Trader cannot trade on behalf of other firm's account", enum_type::entering_trader_cannot_trade_on_behalf_of_other_firms_account_030046},
        {"Entering Trader cannot trade on behalf of other firm's account", enum_type::entering_trader_cannot_trade_on_behalf_of_other_firms_account_031046},
        {"Entering Trader negotiation blocked", enum_type::entering_trader_negotiation_blocked_030041},
        {"Entering Trader negotiation blocked", enum_type::entering_trader_negotiation_blocked_031041},
        {"Entering Trader not authorized to trade accountless orders", enum_type::entering_trader_not_authorized_to_trade_accountless_orders_030045},
        {"Entering Trader not authorized to trade accountless orders", enum_type::entering_trader_not_authorized_to_trade_accountless_orders_031045},
        {"Entering Trader not available", enum_type::entering_trader_not_available_030042},
        {"Entering Trader not available", enum_type::entering_trader_not_available_031042},
        {"Error creating contract", enum_type::error_creating_contract},
        {"Executing Trader doesn't have access to Product Group", enum_type::executing_trader_doesnt_have_access_to_product_group},
        {"Executor document cannot use default broker profile", enum_type::executor_document_cannot_use_default_broker_profile_030034},
        {"Executor document cannot use default broker profile", enum_type::executor_document_cannot_use_default_broker_profile_031034},
        {"Exercise must be on maturity date.", enum_type::exercise_must_be_on_maturity_date},
        {"Exercise price not allowed", enum_type::exercise_price_not_allowed},
        {"Exercise price outside required moneyness.", enum_type::exercise_price_outside_required_moneyness},
        {"Exercise quantity should be greater than zero", enum_type::exercise_quantity_should_be_greater_than_zero},
        {"Field missing or incorrect", enum_type::field_missing_or_incorrect_032000},
        {"Field missing or incorrect", enum_type::field_missing_or_incorrect_033003},
        {"Firm or Account is missing in DMA order", enum_type::firm_or_account_is_missing_in_dma_order},
        {"Firm or Trader is missing in non-DMA order", enum_type::firm_or_trader_is_missing_in_nondma_order},
        {"First trade of day for underlying termo instrument", enum_type::first_trade_of_day_for_underlying_termo_instrument},
        {"Fix field incorrect", enum_type::fix_field_incorrect_006012},
        {"FIX field incorrect", enum_type::fix_field_incorrect_001011},
        {"Fix Field Length Exceeds Max Length", enum_type::fix_field_length_exceeds_max_length},
        {"FIX field missing or incorrect", enum_type::fix_field_missing_or_incorrect},
        {"FIX Message Type does not support operations on such symbol", enum_type::fix_message_type_does_not_support_operations_on_such_symbol_030052},
        {"FIX Message Type does not support operations on such symbol", enum_type::fix_message_type_does_not_support_operations_on_such_symbol_031052},
        {"Fix Session doesn't belong to the ActionTargetGroupID", enum_type::fix_session_doesnt_belong_to_the_actiontargetgroupid},
        {"Fix Session is blocked due to Mass Cancel", enum_type::fix_session_is_blocked_due_to_mass_cancel},
        {"FOK order unmatchable in market", enum_type::fok_order_unmatchable_in_market},
        {"For Cancel On Behalf  must be informed only the ActionTargetSessionID  OR the ActionTargetGroupID", enum_type::for_cancel_on_behalf_must_be_informed_only_the_actiontargetsessionid_or_the_actiontargetgroupid},
        {"Function closed or suspended.", enum_type::function_closed_or_suspended},
        {"Function not available this time", enum_type::function_not_available_this_time},
        {"Give Up not valid for FX Spot contract", enum_type::give_up_not_valid_for_fx_spot_contract},
        {"Good for auction order cancel not allowed.", enum_type::good_for_auction_order_cancel_not_allowed},
        {"Good for auction order modify not allowed.", enum_type::good_for_auction_order_modify_not_allowed},
        {"Good for auction order not allowed.", enum_type::good_for_auction_order_not_allowed},
        {"Instrument has an request for cross in progress", enum_type::instrument_has_an_request_for_cross_in_progress},
        {"Instrument not allowed to this market.", enum_type::instrument_not_allowed_to_this_market_006021},
        {"Instrument not allowed to this market.", enum_type::instrument_not_allowed_to_this_market_006022},
        {"Internal error", enum_type::internal_error},
        {"Internal gateway error (message forwarding failure)", enum_type::internal_gateway_error_message_forwarding_failure},
        {"Invalid blocking Id to unblock", enum_type::invalid_blocking_id_to_unblock},
        {"Invalid Cash Trade in TVR", enum_type::invalid_cash_trade_in_tvr_006036},
        {"Invalid Cash Trade in TVR", enum_type::invalid_cash_trade_in_tvr_006040},
        {"Invalid Cash Trade in TVR", enum_type::invalid_cash_trade_in_tvr_006041},
        {"Invalid Cash Trade in TVR", enum_type::invalid_cash_trade_in_tvr_006042},
        {"Invalid Cash Trade in TVR", enum_type::invalid_cash_trade_in_tvr_006043},
        {"Invalid Cash Trade in TVR", enum_type::invalid_cash_trade_in_tvr_006044},
        {"Invalid exercise request id to cancel", enum_type::invalid_exercise_request_id_to_cancel},
        {"Invalid field for BBT Order", enum_type::invalid_field_for_bbt_order},
        {"Invalid field for Order with Order Type (tag 40) equals P (PEGGED)", enum_type::invalid_field_for_order_with_order_type_tag_40_equals_p_pegged},
        {"Invalid field for Order with Order Type (tag 40) equals W (RLP)", enum_type::invalid_field_for_order_with_order_type_tag_40_equals_w_rlp},
        {"Invalid field for Order with Routing Instruction (tag 35487) equals 1 (RETAIL_LIQUIDITY_TAKER)", enum_type::invalid_field_for_order_with_routing_instruction_tag_35487_equals_1_retail_liquidity_taker},
        {"Invalid Operation for contract type.", enum_type::invalid_operation_for_contract_type},
        {"Invalid order qualifier", enum_type::invalid_order_qualifier},
        {"Invalid price", enum_type::invalid_price_006039},
        {"Invalid Price", enum_type::invalid_price_032018},
        {"Invalid Price", enum_type::invalid_price_032021},
        {"Invalid Quantity", enum_type::invalid_quantity},
        {"Invalid quantity to unblock", enum_type::invalid_quantity_to_unblock},
        {"Invalid Security ID", enum_type::invalid_security_id},
        {"Invalid spread price", enum_type::invalid_spread_price},
        {"LiNe administratively blocked", enum_type::line_administratively_blocked},
        {"Line busy", enum_type::line_busy},
        {"LiNe internal error", enum_type::line_internal_error},
        {"LiNe not available or busy", enum_type::line_not_available_or_busy},
        {"LiNe overloaded", enum_type::line_overloaded},
        {"LiNe recovering or starting up", enum_type::line_recovering_or_starting_up},
        {"Market Maker Protection in effect for user <XXXXXXXX> and group <XXXXXX>", enum_type::market_maker_protection_in_effect_for_user_xxxxxxxx_and_group_xxxxxx},
        {"Market price orders not supported by opposite limit", enum_type::market_price_orders_not_supported_by_opposite_limit},
        {"Max Floor (111) not valid for Time in Force (59).", enum_type::max_floor_111_not_valid_for_time_in_force_59},
        {"Maximum number of working orders for this contract has been exceeded", enum_type::maximum_number_of_working_orders_for_this_contract_has_been_exceeded},
        {"Maximum quantity depth for any one price group max may not exceed + Integer.MAX_VALUE", enum_type::maximum_quantity_depth_for_any_one_price_group_max_may_not_exceed_integermax_value},
        {"Message or atributes are invalid", enum_type::message_or_atributes_are_invalid},
        {"Minimum Quantity was not Filled", enum_type::minimum_quantity_was_not_filled},
        {"Missing Account Field", enum_type::missing_account_field},
        {"Modify of Order Participating in TOP not allowed.", enum_type::modify_of_order_participating_in_top_not_allowed},
        {"No partial match found for this FAK order", enum_type::no_partial_match_found_for_this_fak_order},
        {"No positions blocked", enum_type::no_positions_blocked},
        {"No Trading Calendar found on or after order GTD Expire Date", enum_type::no_trading_calendar_found_on_or_after_order_gtd_expire_date},
        {"Non DMA orders must provide account while in broker's protected mode", enum_type::non_dma_orders_must_provide_account_while_in_brokers_protected_mode_030044},
        {"Non DMA orders must provide account while in broker's protected mode", enum_type::non_dma_orders_must_provide_account_while_in_brokers_protected_mode_031044},
        {"Not a valid termo instrument", enum_type::not_a_valid_termo_instrument},
        {"Not a valid Termo Underlying Instrument.", enum_type::not_a_valid_termo_underlying_instrument},
        {"On Behalf Operation not allowed during CCR recovery", enum_type::on_behalf_operation_not_allowed_during_ccr_recovery},
        {"On close order cancel not allowed.", enum_type::on_close_order_cancel_not_allowed},
        {"On close order modify not allowed.", enum_type::on_close_order_modify_not_allowed},
        {"On close order not allowed.", enum_type::on_close_order_not_allowed},
        {"Only Buy Entry Request for TVR is accepted", enum_type::only_buy_entry_request_for_tvr_is_accepted},
        {"Order Attributes Not Allowed to Trip an Auction", enum_type::order_attributes_not_allowed_to_trip_an_auction},
        {"Order cannot be modified or cancelled while the market is in no cancel", enum_type::order_cannot_be_modified_or_cancelled_while_the_market_is_in_no_cancel},
        {"Order contract is not GTC or GTD eligible", enum_type::order_contract_is_not_gtc_or_gtd_eligible},
        {"Order contract is unknown", enum_type::order_contract_is_unknown_002047},
        {"Order contract is unknown", enum_type::order_contract_is_unknown_007005},
        {"Order Entry was unsuccessful. Error Message: Is not possible to send orders with Validity Type 'Market on Auction' with Minimum quantity.", enum_type::order_entry_was_unsuccessful_error_message_is_not_possible_to_send_orders_with_validity_type_market_on_auction_with_minimum_quantity},
        {"Order group does not match group of contract", enum_type::order_group_does_not_match_group_of_contract},
        {"Order GTD Expire Date is before the current (or next, if not currently in a session) trading session end date", enum_type::order_gtd_expire_date_is_before_the_current_or_next_if_not_currently_in_a_session_trading_session_end_date},
        {"Order modify has different side than existing order", enum_type::order_modify_has_different_side_than_existing_order},
        {"Order not bookable at this time", enum_type::order_not_bookable_at_this_time},
        {"Order On Behalf by DMA customer is not allowed", enum_type::order_on_behalf_by_dma_customer_is_not_allowed},
        {"Order price is outside auction bands", enum_type::order_price_is_outside_auction_bands},
        {"Order price is outside bands", enum_type::order_price_is_outside_bands},
        {"Order price is outside limits", enum_type::order_price_is_outside_limits},
        {"Order quantity is outside of the allowable range", enum_type::order_quantity_is_outside_of_the_allowable_range},
        {"Order quantity is outside of the allowable range “Order Quantity: [OrderQty] / Contract Minimum Quantity for Cross : [MinCrossQty]", enum_type::order_quantity_is_outside_of_the_allowable_range_order_quantity_orderqty_contract_minimum_quantity_for_cross_mincrossqty},
        {"Order Quantity too low", enum_type::order_quantity_too_low},
        {"Order rejected", enum_type::order_rejected},
        {"Order rejected: Only Pegged Order with ROUTING_INSTRUCTION (tag 35487) equals BROKER_ONLY (3) is allowed for this group.", enum_type::order_rejected_only_pegged_order_with_routing_instruction_tag_35487_equals_broker_only_3_is_allowed_for_this_group},
        {"Order rejected: pegged orders are not allowed for this contract", enum_type::order_rejected_pegged_orders_are_not_allowed_for_this_contract},
        {"Order rejected: ROUTING_INSTRUCTION (tag 35487) equals BROKER_ONLY (3) not allowed for this group.", enum_type::order_rejected_routing_instruction_tag_35487_equals_broker_only_3_not_allowed_for_this_group},
        {"Order security type does not match security type of contract", enum_type::order_security_type_does_not_match_security_type_of_contract},
        {"Order session date is in the past", enum_type::order_session_date_is_in_the_past},
        {"Order Type / Duration combination invalid", enum_type::order_type_duration_combination_invalid},
        {"Order type not permitted for group", enum_type::order_type_not_permitted_for_group},
        {"Order type not permitted while the market is in pre open", enum_type::order_type_not_permitted_while_the_market_is_in_pre_open},
        {"Order type not permitted while the market is reserved", enum_type::order_type_not_permitted_while_the_market_is_reserved},
        {"Order Type/ Duration combination invalid for auction", enum_type::order_type_duration_combination_invalid_for_auction},
        {"Order would overwrite existing order on book", enum_type::order_would_overwrite_existing_order_on_book},
        {"Orders may not be entered while the market is closed", enum_type::orders_may_not_be_entered_while_the_market_is_closed},
        {"Orders may not be entered while the market is closed/paused", enum_type::orders_may_not_be_entered_while_the_market_is_closedpaused},
        {"Orders may not be entered while the market is forbidden", enum_type::orders_may_not_be_entered_while_the_market_is_forbidden},
        {"Orders may not be entered while the market is in final closing call", enum_type::orders_may_not_be_entered_while_the_market_is_in_final_closing_call},
        {"Orders may not be entered while the market is open", enum_type::orders_may_not_be_entered_while_the_market_is_open},
        {"Orders may not be entered while the market is preclosed", enum_type::orders_may_not_be_entered_while_the_market_is_preclosed},
        {"Pegged order can not be sent in Non Regular Session", enum_type::pegged_order_can_not_be_sent_in_non_regular_session},
        {"Price must be greater than zero", enum_type::price_must_be_greater_than_zero},
        {"Problem parsing incoming message", enum_type::problem_parsing_incoming_message},
        {"Qty is greater or equal than Maximum Trade Volume", enum_type::qty_is_greater_or_equal_than_maximum_trade_volume},
        {"Qty is not multiple of minimum execution quantity for Pegged order", enum_type::qty_is_not_multiple_of_minimum_execution_quantity_for_pegged_order},
        {"Qty is not multiple of Round Lot", enum_type::qty_is_not_multiple_of_round_lot},
        {"Quantity Attribute Not Allowed On Order During Auction.", enum_type::quantity_attribute_not_allowed_on_order_during_auction},
        {"Quantity doesn't match with the original request [Quantity on original request: <quantity on original request>]", enum_type::quantity_doesnt_match_with_the_original_request_quantity_on_original_request_quantity_on_original_request},
        {"Quote rejected, resting cancelled: Duplicate Quote", enum_type::quote_rejected_resting_cancelled_duplicate_quote},
        {"Quote rejected, resting cancelled: Invalid bid/ask spread", enum_type::quote_rejected_resting_cancelled_invalid_bidask_spread},
        {"Quote rejected, resting cancelled: Invalid price", enum_type::quote_rejected_resting_cancelled_invalid_price},
        {"Quote rejected, resting cancelled: Not authorized to quote this instrument", enum_type::quote_rejected_resting_cancelled_not_authorized_to_quote_this_instrument},
        {"Quote rejected, resting cancelled: Quote exceeds limit", enum_type::quote_rejected_resting_cancelled_quote_exceeds_limit},
        {"Quote rejected, resting cancelled: Too many rejects", enum_type::quote_rejected_resting_cancelled_too_many_rejects},
        {"Quote rejected: Duplicate Quote in same message", enum_type::quote_rejected_duplicate_quote_in_same_message},
        {"Quote rejected: Duplicate Quote, different ID;", enum_type::quote_rejected_duplicate_quote_different_id},
        {"Quote rejected: Exchange (security) closed", enum_type::quote_rejected_exchange_security_closed},
        {"Quote rejected: Exchange (security) is forbidden", enum_type::quote_rejected_exchange_security_is_forbidden_007030},
        {"Quote rejected: Exchange (security) is forbidden", enum_type::quote_rejected_exchange_security_is_forbidden_007034},
        {"Quote rejected: Exchange (security) is in no cancel", enum_type::quote_rejected_exchange_security_is_in_no_cancel},
        {"Quote rejected: Exchange (security) is in pre open", enum_type::quote_rejected_exchange_security_is_in_pre_open},
        {"Quote rejected: Exchange (security) is preclosed", enum_type::quote_rejected_exchange_security_is_preclosed},
        {"Quote rejected: Exchange (security) is reserved", enum_type::quote_rejected_exchange_security_is_reserved},
        {"Quote rejected: Invalid bid/ask spread", enum_type::quote_rejected_invalid_bidask_spread},
        {"Quote rejected: Invalid price", enum_type::quote_rejected_invalid_price},
        {"Quote rejected: Not authorized to quote this instrument", enum_type::quote_rejected_not_authorized_to_quote_this_instrument},
        {"Quote rejected: Quote exceeds limit", enum_type::quote_rejected_quote_exceeds_limit},
        {"Quote rejected: Too late to enter", enum_type::quote_rejected_too_late_to_enter},
        {"Quote rejected: Unknown instrument", enum_type::quote_rejected_unknown_instrument},
        {"Quote rejected: Unknown Quote", enum_type::quote_rejected_unknown_quote},
        {"Quote rejected: Unspecified reason", enum_type::quote_rejected_unspecified_reason},
        {"Received a null AdminOperation", enum_type::received_a_null_adminoperation},
        {"Required field missing", enum_type::required_field_missing},
        {"Required field missing 'Display Quantity orders cannot be IOC/FOK'", enum_type::required_field_missing_display_quantity_orders_cannot_be_iocfok},
        {"Required field missing 'Stop orders cannot be IOC/FAK'", enum_type::required_field_missing_stop_orders_cannot_be_iocfak},
        {"Required field missing 'Stop orders cannot be IOC/FOK'", enum_type::required_field_missing_stop_orders_cannot_be_iocfok},
        {"RFQ for Cross is not allowed since contract is not RFQ for Cross eligible", enum_type::rfq_for_cross_is_not_allowed_since_contract_is_not_rfq_for_cross_eligible},
        {"RFQ rejected, instrument/exchange not known", enum_type::rfq_rejected_instrumentexchange_not_known},
        {"RFQ rejected, instrument/exchange not tradable", enum_type::rfq_rejected_instrumentexchange_not_tradable},
        {"RFQ rejected: Instrument / exchange is open", enum_type::rfq_rejected_instrument_exchange_is_open},
        {"RLP Order rejected - Only one order is allowed by firm and side", enum_type::rlp_order_rejected_only_one_order_is_allowed_by_firm_and_side},
        {"RLP Order rejected – Participant not authorized", enum_type::rlp_order_rejected_participant_not_authorized},
        {"Same Participants on both sides or invalid sides", enum_type::same_participants_on_both_sides_or_invalid_sides},
        {"Sell order stop price must be below last trade price", enum_type::sell_order_stop_price_must_be_below_last_trade_price},
        {"Special Auction Permissions: 'Order entry not allowed.'", enum_type::special_auction_permissions_order_entry_not_allowed},
        {"Spread orders may not be entered while the underlying leg market is in non trading state", enum_type::spread_orders_may_not_be_entered_while_the_underlying_leg_market_is_in_non_trading_state},
        {"Spread's leg internal data corrupted", enum_type::spreads_leg_internal_data_corrupted_030061},
        {"Spread's leg internal data corrupted", enum_type::spreads_leg_internal_data_corrupted_031061},
        {"Spread's leg not available", enum_type::spreads_leg_not_available_030060},
        {"Spread's leg not available", enum_type::spreads_leg_not_available_031060},
        {"Stop price maxi-mini must be smaller than or equal to trigger price", enum_type::stop_price_maximini_must_be_smaller_than_or_equal_to_trigger_price},
        {"Symbol internal data corrupted", enum_type::symbol_internal_data_corrupted_030051},
        {"Symbol internal data corrupted", enum_type::symbol_internal_data_corrupted_031051},
        {"Symbol not available", enum_type::symbol_not_available_030050},
        {"Symbol not available", enum_type::symbol_not_available_031050},
        {"Symbol's calculated price invalid", enum_type::symbols_calculated_price_invalid_032056},
        {"Symbol's calculated price invalid", enum_type::symbols_calculated_price_invalid_031056},
        {"Symbol's reference price missing, market orders not allowed", enum_type::symbols_reference_price_missing_market_orders_not_allowed_030055},
        {"Symbol's reference price missing, market orders not allowed", enum_type::symbols_reference_price_missing_market_orders_not_allowed_031055},
        {"Symbol's risk unit matrix not available", enum_type::symbols_risk_unit_matrix_not_available_030054},
        {"Symbol's risk unit matrix not available", enum_type::symbols_risk_unit_matrix_not_available_031054},
        {"Symbol's underlying not found for risk aggregation", enum_type::symbols_underlying_not_found_for_risk_aggregation_030053},
        {"Symbol's underlying not found for risk aggregation", enum_type::symbols_underlying_not_found_for_risk_aggregation_031053},
        {"System Error", enum_type::system_error_032023},
        {"System Error", enum_type::system_error_033050},
        {"System initialization", enum_type::system_initialization},
        {"System Overloaded", enum_type::system_overloaded},
        {"Tag ExpireDate (432) beyond instrument expiration.", enum_type::tag_expiredate_432_beyond_instrument_expiration},
        {"Tag ExpireDate (432) beyond UDS COMBO earliest leg expiration.", enum_type::tag_expiredate_432_beyond_uds_combo_earliest_leg_expiration},
        {"Technical Error: Function not performed", enum_type::technical_error_function_not_performed},
        {"Termo message rejected : Exchange (security) closed", enum_type::termo_message_rejected_exchange_security_closed},
        {"Termo message rejected : Unknown instrument", enum_type::termo_message_rejected_unknown_instrument},
        {"Termo message rejected: Duplicate Termo Quote", enum_type::termo_message_rejected_duplicate_termo_quote},
        {"Termo message rejected: Invalid bid/ask spread", enum_type::termo_message_rejected_invalid_bidask_spread},
        {"Termo message rejected: Invalid price", enum_type::termo_message_rejected_invalid_price},
        {"Termo message rejected: Limits exceeded", enum_type::termo_message_rejected_limits_exceeded},
        {"Termo message rejected: Not authorized to termo quote this instrument", enum_type::termo_message_rejected_not_authorized_to_termo_quote_this_instrument},
        {"Termo message rejected: Pass", enum_type::termo_message_rejected_pass},
        {"Termo message rejected: Too late to enter", enum_type::termo_message_rejected_too_late_to_enter},
        {"Termo message rejected: Unknown Termo Quote", enum_type::termo_message_rejected_unknown_termo_quote},
        {"Termo messages should not be entered when market is forbidden", enum_type::termo_messages_should_not_be_entered_when_market_is_forbidden},
        {"Termo messages should not be entered when market is in final closing call", enum_type::termo_messages_should_not_be_entered_when_market_is_in_final_closing_call},
        {"Termo messages should not be entered when market is no cancel", enum_type::termo_messages_should_not_be_entered_when_market_is_no_cancel},
        {"Termo messages should not be entered when market is paused", enum_type::termo_messages_should_not_be_entered_when_market_is_paused},
        {"Termo messages should not be entered when market is PCP", enum_type::termo_messages_should_not_be_entered_when_market_is_pcp},
        {"Termo messages should not be entered when market is pre close", enum_type::termo_messages_should_not_be_entered_when_market_is_pre_close},
        {"Termo messages should not be entered when market is pre open", enum_type::termo_messages_should_not_be_entered_when_market_is_pre_open_006025},
        {"Termo messages should not be entered when market is pre open", enum_type::termo_messages_should_not_be_entered_when_market_is_pre_open_006031},
        {"Termo messages should not be entered when market is reserved", enum_type::termo_messages_should_not_be_entered_when_market_is_reserved},
        {"Termo Price should be greater than zero.", enum_type::termo_price_should_be_greater_than_zero},
        {"Termo rejected, instrument/exchange not tradable", enum_type::termo_rejected_instrumentexchange_not_tradable},
        {"The modify was submitted on a different product than the original order", enum_type::the_modify_was_submitted_on_a_different_product_than_the_original_order},
        {"The Order was submitted with a different account than the requesting Cancel", enum_type::the_order_was_submitted_with_a_different_account_than_the_requesting_cancel},
        {"The Order was submitted with a different CLOrderID than the CorrelationClOrderID of the requesting Cancel", enum_type::the_order_was_submitted_with_a_different_clorderid_than_the_correlationclorderid_of_the_requesting_cancel},
        {"The Order was submitted with a different CLOrderID than the OriginalClOrderID of the requesting Cancel", enum_type::the_order_was_submitted_with_a_different_clorderid_than_the_originalclorderid_of_the_requesting_cancel},
        {"The Order was submitted with a different group (tag 55) than the requesting Cancel", enum_type::the_order_was_submitted_with_a_different_group_tag_55_than_the_requesting_cancel},
        {"The Order was submitted with a different quantity than the requesting Cancel", enum_type::the_order_was_submitted_with_a_different_quantity_than_the_requesting_cancel},
        {"The Order was submitted with a different security type than the requesting Cancel", enum_type::the_order_was_submitted_with_a_different_security_type_than_the_requesting_cancel},
        {"The Order was submitted with a different SenderCompID than the requesting Cancel", enum_type::the_order_was_submitted_with_a_different_sendercompid_than_the_requesting_cancel},
        {"The Order was submitted with a different side than the requesting Cancel", enum_type::the_order_was_submitted_with_a_different_side_than_the_requesting_cancel},
        {"The Order was submitted with a different TraderID than the requesting Cancel", enum_type::the_order_was_submitted_with_a_different_traderid_than_the_requesting_cancel},
        {"There aren't positions available to exercise", enum_type::there_arent_positions_available_to_exercise},
        {"There is no bid and ask for underlying contract", enum_type::there_is_no_bid_and_ask_for_underlying_contract},
        {"Throttle limit reached", enum_type::throttle_limit_reached},
        {"Time in Force (59) not valid for Order Type (40).", enum_type::time_in_force_59_not_valid_for_order_type_40},
        {"Timeout waiting risk evaluation", enum_type::timeout_waiting_risk_evaluation},
        {"Timeout waiting risk evaluation (low priority)", enum_type::timeout_waiting_risk_evaluation_low_priority},
        {"Total qty must be the sum of all AllocQty", enum_type::total_qty_must_be_the_sum_of_all_allocqty},
        {"Trade already cancelled or does not exist ‘Trade Id: <XXX>’", enum_type::trade_already_cancelled_or_does_not_exist_trade_id_xxx},
        {"Trade does not belong to the specified firm ‘Firm Id: <XXX>’", enum_type::trade_does_not_belong_to_the_specified_firm_firm_id_xxx},
        {"Trade on Behalf Rejected.", enum_type::trade_on_behalf_rejected},
        {"Trade outside of short term volatility bands", enum_type::trade_outside_of_short_term_volatility_bands},
        {"Trade price is outside of static limits", enum_type::trade_price_is_outside_of_static_limits},
        {"Transient Account is hierarchically blocked on protected mode", enum_type::transient_account_is_hierarchically_blocked_on_protected_mode_030025},
        {"Transient Account is hierarchically blocked on protected mode", enum_type::transient_account_is_hierarchically_blocked_on_protected_mode_031025},
        {"Transient Account not allowed in Extended Hours", enum_type::transient_account_not_allowed_in_extended_hours_030027},
        {"Transient Account not allowed in Extended Hours", enum_type::transient_account_not_allowed_in_extended_hours_031027},
        {"Unable to send FIX from VolatilityUpdate message", enum_type::unable_to_send_fix_from_volatilityupdate_message},
        {"Unexpected internal error during risk evaluation", enum_type::unexpected_internal_error_during_risk_evaluation_030070},
        {"Unexpected internal error during risk evaluation", enum_type::unexpected_internal_error_during_risk_evaluation_031070},
        {"Unknown Account", enum_type::unknown_account},
        {"Unknown FirmID (for routing)", enum_type::unknown_firmid_for_routing},
        {"Unknown Market Segment ID", enum_type::unknown_market_segment_id},
        {"User not authorized to trade", enum_type::user_not_authorized_to_trade},
        {"Values don`t match with the original request", enum_type::values_dont_match_with_the_original_request},
        {"Visibility Permission Not granted for Executing Trader/Entering Trader", enum_type::visibility_permission_not_granted_for_executing_traderentering_trader},
        {"Wrong type of order book for Termo.", enum_type::wrong_type_of_order_book_for_termo},
        {"Wrong type of request for Termo.", enum_type::wrong_type_of_request_for_termo}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::unable_to_send_fix_from_volatilityupdate_message: return "Unable to send FIX from VolatilityUpdate message";
            case enum_type::orders_may_not_be_entered_while_the_market_is_closedpaused: return "Orders may not be entered while the market is closed/paused";
            case enum_type::fix_field_missing_or_incorrect: return "FIX field missing or incorrect";
            case enum_type::required_field_missing: return "Required field missing";
            case enum_type::fix_field_incorrect_001011: return "FIX field incorrect";
            case enum_type::price_must_be_greater_than_zero: return "Price must be greater than zero";
            case enum_type::invalid_order_qualifier: return "Invalid order qualifier";
            case enum_type::user_not_authorized_to_trade: return "User not authorized to trade";
            case enum_type::required_field_missing_stop_orders_cannot_be_iocfak: return "Required field missing 'Stop orders cannot be IOC/FAK'";
            case enum_type::required_field_missing_display_quantity_orders_cannot_be_iocfok: return "Required field missing 'Display Quantity orders cannot be IOC/FOK'";
            case enum_type::required_field_missing_stop_orders_cannot_be_iocfok: return "Required field missing 'Stop orders cannot be IOC/FOK'";
            case enum_type::market_price_orders_not_supported_by_opposite_limit: return "Market price orders not supported by opposite limit";
            case enum_type::order_gtd_expire_date_is_before_the_current_or_next_if_not_currently_in_a_session_trading_session_end_date: return "Order GTD Expire Date is before the current (or next, if not currently in a session) trading session end date";
            case enum_type::cannot_modify_order_because_order_does_not_exist: return "Cannot modify order because order does not exist";
            case enum_type::disclosed_quantity_cannot_be_greater_than_total_or_remaining_quantity: return "Disclosed Quantity cannot be greater than total or remaining quantity";
            case enum_type::order_contract_is_unknown_002047: return "Order contract is unknown";
            case enum_type::the_order_was_submitted_with_a_different_sendercompid_than_the_requesting_cancel: return "The Order was submitted with a different SenderCompID than the requesting Cancel";
            case enum_type::the_order_was_submitted_with_a_different_clorderid_than_the_correlationclorderid_of_the_requesting_cancel: return "The Order was submitted with a different CLOrderID than the CorrelationClOrderID of the requesting Cancel";
            case enum_type::the_order_was_submitted_with_a_different_clorderid_than_the_originalclorderid_of_the_requesting_cancel: return "The Order was submitted with a different CLOrderID than the OriginalClOrderID of the requesting Cancel";
            case enum_type::the_order_was_submitted_with_a_different_side_than_the_requesting_cancel: return "The Order was submitted with a different side than the requesting Cancel";
            case enum_type::the_order_was_submitted_with_a_different_group_tag_55_than_the_requesting_cancel: return "The Order was submitted with a different group (tag 55) than the requesting Cancel";
            case enum_type::the_order_was_submitted_with_a_different_security_type_than_the_requesting_cancel: return "The Order was submitted with a different security type than the requesting Cancel";
            case enum_type::the_order_was_submitted_with_a_different_account_than_the_requesting_cancel: return "The Order was submitted with a different account than the requesting Cancel";
            case enum_type::the_order_was_submitted_with_a_different_quantity_than_the_requesting_cancel: return "The Order was submitted with a different quantity than the requesting Cancel";
            case enum_type::the_order_was_submitted_with_a_different_traderid_than_the_requesting_cancel: return "The Order was submitted with a different TraderID than the requesting Cancel";
            case enum_type::attempt_to_cancel_an_order_with_a_different_firmid_than_the_original_order: return "Attempt to cancel an order with a different FirmID than the original order";
            case enum_type::attempt_to_cancel_an_order_with_a_different_senderlocationid_than_the_original_order: return "Attempt to cancel an order with a different SenderLocationID than the original order";
            case enum_type::stop_price_maximini_must_be_smaller_than_or_equal_to_trigger_price: return "Stop price maxi-mini must be smaller than or equal to trigger price";
            case enum_type::sell_order_stop_price_must_be_below_last_trade_price: return "Sell order stop price must be below last trade price";
            case enum_type::buy_order_stop_price_must_be_above_last_trade_price: return "Buy order stop price must be above last trade price";
            case enum_type::the_modify_was_submitted_on_a_different_product_than_the_original_order: return "The modify was submitted on a different product than the original order";
            case enum_type::attempt_to_modify_an_order_with_a_different_inflightfill_mitigation_status_than_first_modification: return "Attempt to modify an order with a different in-flight-fill mitigation status than first modification";
            case enum_type::attempt_to_modify_an_order_with_a_different_sendercompid_than_the_original_order: return "Attempt to modify an order with a different SenderCompID than the original order";
            case enum_type::attempt_to_modify_an_order_with_a_different_traderid_than_the_original_order: return "Attempt to modify an order with a different TraderID than the original order";
            case enum_type::attempt_to_modify_an_order_with_a_different_accountid_than_the_original_order: return "Attempt to modify an order with a different AccountID than the original order";
            case enum_type::attempt_to_modify_an_order_with_a_different_firmid_than_the_original_order: return "Attempt to modify an order with a different FirmID than the original order";
            case enum_type::attempt_to_modify_an_order_with_a_different_senderlocationid_than_the_original_order: return "Attempt to modify an order with a different SenderLocationID than the original order";
            case enum_type::disclosed_quantity_is_not_allowed: return "Disclosed Quantity is not allowed";
            case enum_type::account_or_give_up_firm_required_for_dma_customers: return "Account or Give Up firm required for DMA customers";
            case enum_type::disclosed_qty_cannot_be_less_than_disclosed_qty_min: return "Disclosed Qty cannot be less than Disclosed Qty Min";
            case enum_type::acct_type38_not_valid_for_tag_581_for_dma_customers: return "Acct Type(38) not valid for Tag 581 for DMA customers";
            case enum_type::give_up_not_valid_for_fx_spot_contract: return "Give Up not valid for FX Spot contract";
            case enum_type::visibility_permission_not_granted_for_executing_traderentering_trader: return "Visibility Permission Not granted for Executing Trader/Entering Trader";
            case enum_type::executing_trader_doesnt_have_access_to_product_group: return "Executing Trader doesn't have access to Product Group";
            case enum_type::attempt_to_modify_market_order_to_some_other_type: return "Attempt to modify market order to some other type";
            case enum_type::order_quantity_is_outside_of_the_allowable_range: return "Order quantity is outside of the allowable range";
            case enum_type::account_is_mandatory_for_fx_spot: return "Account is mandatory for FX SPOT";
            case enum_type::order_on_behalf_by_dma_customer_is_not_allowed: return "Order On Behalf by DMA customer is not allowed";
            case enum_type::attempt_to_modify_an_order_with_a_different_accounttype_than_the_original_order: return "Attempt to modify an order with a different AccountType than the original order";
            case enum_type::account_or_give_up_firm_required_for_equities: return "Account or Give Up firm required for equities";
            case enum_type::order_type_not_permitted_while_the_market_is_in_pre_open: return "Order type not permitted while the market is in pre open";
            case enum_type::order_price_is_outside_limits: return "Order price is outside limits";
            case enum_type::qty_is_not_multiple_of_round_lot: return "Qty is not multiple of Round Lot";
            case enum_type::qty_is_greater_or_equal_than_maximum_trade_volume: return "Qty is greater or equal than Maximum Trade Volume";
            case enum_type::order_price_is_outside_bands: return "Order price is outside bands";
            case enum_type::order_price_is_outside_auction_bands: return "Order price is outside auction bands";
            case enum_type::trade_outside_of_short_term_volatility_bands: return "Trade outside of short term volatility bands";
            case enum_type::all_legs_must_have_same_lot_types: return "All Legs must have same Lot Types";
            case enum_type::all_legs_must_have_same_tick_increment: return "All Legs must have same Tick Increment";
            case enum_type::all_legs_must_have_same_step_of_quotation: return "All Legs must have same Step of Quotation";
            case enum_type::trade_price_is_outside_of_static_limits: return "Trade price is outside of static limits";
            case enum_type::cod_not_supported_for_gtc_gtd_orders: return "COD Not Supported for GTC/ GTD Orders";
            case enum_type::order_not_bookable_at_this_time: return "Order not bookable at this time";
            case enum_type::minimum_quantity_was_not_filled: return "Minimum Quantity was not Filled";
            case enum_type::order_attributes_not_allowed_to_trip_an_auction: return "Order Attributes Not Allowed to Trip an Auction";
            case enum_type::order_type_not_permitted_for_group: return "Order type not permitted for group";
            case enum_type::instrument_has_an_request_for_cross_in_progress: return "Instrument has an request for cross in progress";
            case enum_type::order_quantity_too_low: return "Order Quantity too low";
            case enum_type::crosstype_ineligible_for_instrument: return "CrossType ineligible for instrument";
            case enum_type::rfq_for_cross_is_not_allowed_since_contract_is_not_rfq_for_cross_eligible: return "RFQ for Cross is not allowed since contract is not RFQ for Cross eligible";
            case enum_type::dma_crossorder_not_allowed: return "DMA CrossOrder Not allowed";
            case enum_type::cross_order_rejected_due_to_auction_trigger_validation: return "Cross Order Rejected due to Auction Trigger Validation";
            case enum_type::trade_on_behalf_rejected: return "Trade on Behalf Rejected.";
            case enum_type::market_maker_protection_in_effect_for_user_xxxxxxxx_and_group_xxxxxx: return "Market Maker Protection in effect for user <XXXXXXXX> and group <XXXXXX>";
            case enum_type::rfq_rejected_instrumentexchange_not_tradable: return "RFQ rejected, instrument/exchange not tradable";
            case enum_type::rfq_rejected_instrumentexchange_not_known: return "RFQ rejected, instrument/exchange not known";
            case enum_type::error_creating_contract: return "Error creating contract";
            case enum_type::business_reject_other: return "Business reject: Other";
            case enum_type::business_reject_unknown_id: return "Business reject: Unknown ID";
            case enum_type::business_reject_unknown_security: return "Business reject: Unknown security";
            case enum_type::business_reject_unsupported_message_type: return "Business reject: Unsupported message type";
            case enum_type::business_reject_application_not_available: return "Business reject: Application Not Available";
            case enum_type::business_reject_required_field_missing: return "Business reject: Required field missing";
            case enum_type::contract_claims_to_be_a_spread_but_is_missing_one_or_more_legs: return "Contract claims to be a spread but is missing one or more legs";
            case enum_type::fix_field_length_exceeds_max_length: return "Fix Field Length Exceeds Max Length";
            case enum_type::special_auction_permissions_order_entry_not_allowed: return "Special Auction Permissions: 'Order entry not allowed.'";
            case enum_type::engine_did_not_respond_to_fas_request: return "Engine did not respond to FAS request";
            case enum_type::termo_message_rejected_unknown_instrument: return "Termo message rejected : Unknown instrument";
            case enum_type::termo_message_rejected_exchange_security_closed: return "Termo message rejected : Exchange (security) closed";
            case enum_type::termo_rejected_instrumentexchange_not_tradable: return "Termo rejected, instrument/exchange not tradable";
            case enum_type::termo_message_rejected_limits_exceeded: return "Termo message rejected: Limits exceeded";
            case enum_type::termo_message_rejected_too_late_to_enter: return "Termo message rejected: Too late to enter";
            case enum_type::termo_message_rejected_unknown_termo_quote: return "Termo message rejected: Unknown Termo Quote";
            case enum_type::termo_message_rejected_duplicate_termo_quote: return "Termo message rejected: Duplicate Termo Quote";
            case enum_type::termo_message_rejected_invalid_bidask_spread: return "Termo message rejected: Invalid bid/ask spread";
            case enum_type::termo_message_rejected_invalid_price: return "Termo message rejected: Invalid price";
            case enum_type::termo_message_rejected_not_authorized_to_termo_quote_this_instrument: return "Termo message rejected: Not authorized to termo quote this instrument";
            case enum_type::termo_message_rejected_pass: return "Termo message rejected: Pass";
            case enum_type::fix_field_incorrect_006012: return "Fix field incorrect";
            case enum_type::not_a_valid_termo_instrument: return "Not a valid termo instrument";
            case enum_type::values_dont_match_with_the_original_request: return "Values don`t match with the original request";
            case enum_type::current_termo_request_status_does_not_allow_rejection: return "Current termo request status does not allow rejection";
            case enum_type::current_termo_request_status_does_not_allow_acceptance: return "Current termo request status does not allow acceptance";
            case enum_type::wrong_type_of_order_book_for_termo: return "Wrong type of order book for Termo.";
            case enum_type::wrong_type_of_request_for_termo: return "Wrong type of request for Termo.";
            case enum_type::days_to_settlement_must_be_between_16_and_999: return "Days to Settlement must be between 16 and 999.";
            case enum_type::days_to_settlement_must_be_between_16_and_90: return "Days to Settlement must be between 16 and 90";
            case enum_type::instrument_not_allowed_to_this_market_006021: return "Instrument not allowed to this market.";
            case enum_type::instrument_not_allowed_to_this_market_006022: return "Instrument not allowed to this market.";
            case enum_type::termo_price_should_be_greater_than_zero: return "Termo Price should be greater than zero.";
            case enum_type::termo_messages_should_not_be_entered_when_market_is_paused: return "Termo messages should not be entered when market is paused";
            case enum_type::termo_messages_should_not_be_entered_when_market_is_pre_open_006025: return "Termo messages should not be entered when market is pre open";
            case enum_type::termo_messages_should_not_be_entered_when_market_is_pcp: return "Termo messages should not be entered when market is PCP";
            case enum_type::termo_messages_should_not_be_entered_when_market_is_no_cancel: return "Termo messages should not be entered when market is no cancel";
            case enum_type::termo_messages_should_not_be_entered_when_market_is_reserved: return "Termo messages should not be entered when market is reserved";
            case enum_type::termo_messages_should_not_be_entered_when_market_is_forbidden: return "Termo messages should not be entered when market is forbidden";
            case enum_type::termo_messages_should_not_be_entered_when_market_is_pre_close: return "Termo messages should not be entered when market is pre close";
            case enum_type::termo_messages_should_not_be_entered_when_market_is_pre_open_006031: return "Termo messages should not be entered when market is pre open";
            case enum_type::not_a_valid_termo_underlying_instrument: return "Not a valid Termo Underlying Instrument.";
            case enum_type::received_a_null_adminoperation: return "Received a null AdminOperation";
            case enum_type::first_trade_of_day_for_underlying_termo_instrument: return "First trade of day for underlying termo instrument";
            case enum_type::termo_messages_should_not_be_entered_when_market_is_in_final_closing_call: return "Termo messages should not be entered when market is in final closing call";
            case enum_type::invalid_cash_trade_in_tvr_006036: return "Invalid Cash Trade in TVR";
            case enum_type::only_buy_entry_request_for_tvr_is_accepted: return "Only Buy Entry Request for TVR is accepted";
            case enum_type::there_is_no_bid_and_ask_for_underlying_contract: return "There is no bid and ask for underlying contract";
            case enum_type::invalid_price_006039: return "Invalid price";
            case enum_type::invalid_cash_trade_in_tvr_006040: return "Invalid Cash Trade in TVR";
            case enum_type::invalid_cash_trade_in_tvr_006041: return "Invalid Cash Trade in TVR";
            case enum_type::invalid_cash_trade_in_tvr_006042: return "Invalid Cash Trade in TVR";
            case enum_type::invalid_cash_trade_in_tvr_006043: return "Invalid Cash Trade in TVR";
            case enum_type::invalid_cash_trade_in_tvr_006044: return "Invalid Cash Trade in TVR";
            case enum_type::order_rejected: return "Order rejected";
            case enum_type::fok_order_unmatchable_in_market: return "FOK order unmatchable in market";
            case enum_type::orders_may_not_be_entered_while_the_market_is_closed: return "Orders may not be entered while the market is closed";
            case enum_type::order_contract_is_unknown_007005: return "Order contract is unknown";
            case enum_type::no_partial_match_found_for_this_fak_order: return "No partial match found for this FAK order";
            case enum_type::maximum_quantity_depth_for_any_one_price_group_max_may_not_exceed_integermax_value: return "Maximum quantity depth for any one price group max may not exceed + Integer.MAX_VALUE";
            case enum_type::contract_for_this_order_contract_is_past_expiration_date_and_may_no_longer_be_traded: return "Contract for this order contract is past expiration date and may no longer be traded";
            case enum_type::invalid_spread_price: return "Invalid spread price";
            case enum_type::maximum_number_of_working_orders_for_this_contract_has_been_exceeded: return "Maximum number of working orders for this contract has been exceeded";
            case enum_type::order_would_overwrite_existing_order_on_book: return "Order would overwrite existing order on book";
            case enum_type::order_group_does_not_match_group_of_contract: return "Order group does not match group of contract";
            case enum_type::order_security_type_does_not_match_security_type_of_contract: return "Order security type does not match security type of contract";
            case enum_type::order_modify_has_different_side_than_existing_order: return "Order modify has different side than existing order";
            case enum_type::contract_is_not_eligible_for_electronic_matching: return "Contract is not eligible for electronic matching";
            case enum_type::order_contract_is_not_gtc_or_gtd_eligible: return "Order contract is not GTC or GTD eligible";
            case enum_type::no_trading_calendar_found_on_or_after_order_gtd_expire_date: return "No Trading Calendar found on or after order GTD Expire Date";
            case enum_type::tag_expiredate_432_beyond_instrument_expiration: return "Tag ExpireDate (432) beyond instrument expiration.";
            case enum_type::tag_expiredate_432_beyond_uds_combo_earliest_leg_expiration: return "Tag ExpireDate (432) beyond UDS COMBO earliest leg expiration.";
            case enum_type::order_cannot_be_modified_or_cancelled_while_the_market_is_in_no_cancel: return "Order cannot be modified or cancelled while the market is in no cancel";
            case enum_type::order_type_not_permitted_while_the_market_is_reserved: return "Order type not permitted while the market is reserved";
            case enum_type::order_session_date_is_in_the_past: return "Order session date is in the past";
            case enum_type::orders_may_not_be_entered_while_the_market_is_forbidden: return "Orders may not be entered while the market is forbidden";
            case enum_type::quote_rejected_exchange_security_is_forbidden_007030: return "Quote rejected: Exchange (security) is forbidden";
            case enum_type::orders_may_not_be_entered_while_the_market_is_preclosed: return "Orders may not be entered while the market is preclosed";
            case enum_type::quote_rejected_exchange_security_is_preclosed: return "Quote rejected: Exchange (security) is preclosed";
            case enum_type::orders_may_not_be_entered_while_the_market_is_open: return "Orders may not be entered while the market is open";
            case enum_type::quote_rejected_exchange_security_is_forbidden_007034: return "Quote rejected: Exchange (security) is forbidden";
            case enum_type::rfq_rejected_instrument_exchange_is_open: return "RFQ rejected: Instrument / exchange is open";
            case enum_type::time_in_force_59_not_valid_for_order_type_40: return "Time in Force (59) not valid for Order Type (40).";
            case enum_type::good_for_auction_order_not_allowed: return "Good for auction order not allowed.";
            case enum_type::on_close_order_not_allowed: return "On close order not allowed.";
            case enum_type::duplicate_client_order_id_for_this_sessioncontract: return "Duplicate Client Order Id for this Session/Contract.";
            case enum_type::good_for_auction_order_cancel_not_allowed: return "Good for auction order cancel not allowed.";
            case enum_type::on_close_order_cancel_not_allowed: return "On close order cancel not allowed.";
            case enum_type::good_for_auction_order_modify_not_allowed: return "Good for auction order modify not allowed.";
            case enum_type::on_close_order_modify_not_allowed: return "On close order modify not allowed.";
            case enum_type::modify_of_order_participating_in_top_not_allowed: return "Modify of Order Participating in TOP not allowed.";
            case enum_type::cancel_of_order_participating_in_top_not_allowed: return "Cancel of Order Participating in TOP not allowed.";
            case enum_type::order_type_duration_combination_invalid_for_auction: return "Order Type/ Duration combination invalid for auction";
            case enum_type::order_type_duration_combination_invalid: return "Order Type / Duration combination invalid";
            case enum_type::quantity_attribute_not_allowed_on_order_during_auction: return "Quantity Attribute Not Allowed On Order During Auction.";
            case enum_type::order_entry_was_unsuccessful_error_message_is_not_possible_to_send_orders_with_validity_type_market_on_auction_with_minimum_quantity: return "Order Entry was unsuccessful. Error Message: Is not possible to send orders with Validity Type 'Market on Auction' with Minimum quantity.";
            case enum_type::max_floor_111_not_valid_for_time_in_force_59: return "Max Floor (111) not valid for Time in Force (59).";
            case enum_type::spread_orders_may_not_be_entered_while_the_underlying_leg_market_is_in_non_trading_state: return "Spread orders may not be entered while the underlying leg market is in non trading state";
            case enum_type::orders_may_not_be_entered_while_the_market_is_in_final_closing_call: return "Orders may not be entered while the market is in final closing call";
            case enum_type::quote_rejected_unknown_instrument: return "Quote rejected: Unknown instrument";
            case enum_type::quote_rejected_exchange_security_closed: return "Quote rejected: Exchange (security) closed";
            case enum_type::quote_rejected_quote_exceeds_limit: return "Quote rejected: Quote exceeds limit";
            case enum_type::quote_rejected_too_late_to_enter: return "Quote rejected: Too late to enter";
            case enum_type::quote_rejected_unknown_quote: return "Quote rejected: Unknown Quote";
            case enum_type::quote_rejected_duplicate_quote_in_same_message: return "Quote rejected: Duplicate Quote in same message";
            case enum_type::quote_rejected_invalid_bidask_spread: return "Quote rejected: Invalid bid/ask spread";
            case enum_type::quote_rejected_invalid_price: return "Quote rejected: Invalid price";
            case enum_type::quote_rejected_not_authorized_to_quote_this_instrument: return "Quote rejected: Not authorized to quote this instrument";
            case enum_type::quote_rejected_resting_cancelled_too_many_rejects: return "Quote rejected, resting cancelled: Too many rejects";
            case enum_type::quote_rejected_duplicate_quote_different_id: return "Quote rejected: Duplicate Quote, different ID;";
            case enum_type::quote_rejected_resting_cancelled_quote_exceeds_limit: return "Quote rejected, resting cancelled: Quote exceeds limit";
            case enum_type::quote_rejected_resting_cancelled_duplicate_quote: return "Quote rejected, resting cancelled: Duplicate Quote";
            case enum_type::quote_rejected_resting_cancelled_invalid_bidask_spread: return "Quote rejected, resting cancelled: Invalid bid/ask spread";
            case enum_type::quote_rejected_resting_cancelled_invalid_price: return "Quote rejected, resting cancelled: Invalid price";
            case enum_type::quote_rejected_resting_cancelled_not_authorized_to_quote_this_instrument: return "Quote rejected, resting cancelled: Not authorized to quote this instrument";
            case enum_type::quote_rejected_unspecified_reason: return "Quote rejected: Unspecified reason";
            case enum_type::quote_rejected_exchange_security_is_in_pre_open: return "Quote rejected: Exchange (security) is in pre open";
            case enum_type::quote_rejected_exchange_security_is_in_no_cancel: return "Quote rejected: Exchange (security) is in no cancel";
            case enum_type::quote_rejected_exchange_security_is_reserved: return "Quote rejected: Exchange (security) is reserved";
            case enum_type::contract_not_eligible_for_negotiated_quote: return "Contract not eligible for negotiated quote";
            case enum_type::rlp_order_rejected_participant_not_authorized: return "RLP Order rejected – Participant not authorized";
            case enum_type::attempt_to_modify_the_order_type_fromto_rlp: return "Attempt to modify the order type from/to RLP";
            case enum_type::invalid_field_for_order_with_order_type_tag_40_equals_w_rlp: return "Invalid field for Order with Order Type (tag 40) equals W (RLP)";
            case enum_type::rlp_order_rejected_only_one_order_is_allowed_by_firm_and_side: return "RLP Order rejected - Only one order is allowed by firm and side";
            case enum_type::invalid_field_for_order_with_routing_instruction_tag_35487_equals_1_retail_liquidity_taker: return "Invalid field for Order with Routing Instruction (tag 35487) equals 1 (RETAIL_LIQUIDITY_TAKER)";
            case enum_type::invalid_field_for_order_with_order_type_tag_40_equals_p_pegged: return "Invalid field for Order with Order Type (tag 40) equals P (PEGGED)";
            case enum_type::qty_is_not_multiple_of_minimum_execution_quantity_for_pegged_order: return "Qty is not multiple of minimum execution quantity for Pegged order";
            case enum_type::account_is_mandatory_for_pegged_order: return "Account is mandatory for Pegged Order";
            case enum_type::pegged_order_can_not_be_sent_in_non_regular_session: return "Pegged order can not be sent in Non Regular Session";
            case enum_type::attempt_to_modify_the_order_type_fromto_pegged: return "Attempt to modify the order type from/to Pegged";
            case enum_type::order_rejected_pegged_orders_are_not_allowed_for_this_contract: return "Order rejected: pegged orders are not allowed for this contract";
            case enum_type::order_rejected_routing_instruction_tag_35487_equals_broker_only_3_not_allowed_for_this_group: return "Order rejected: ROUTING_INSTRUCTION (tag 35487) equals BROKER_ONLY (3) not allowed for this group.";
            case enum_type::order_rejected_only_pegged_order_with_routing_instruction_tag_35487_equals_broker_only_3_is_allowed_for_this_group: return "Order rejected: Only Pegged Order with ROUTING_INSTRUCTION (tag 35487) equals BROKER_ONLY (3) is allowed for this group.";
            case enum_type::cross_order_suspended_for_the_participant_or_session: return "Cross order suspended for the participant or session";
            case enum_type::order_quantity_is_outside_of_the_allowable_range_order_quantity_orderqty_contract_minimum_quantity_for_cross_mincrossqty: return "Order quantity is outside of the allowable range “Order Quantity: [OrderQty] / Contract Minimum Quantity for Cross : [MinCrossQty]";
            case enum_type::bbt_messages_should_not_be_entered_when_market_is_paused: return "BBT messages should not be entered when market is paused";
            case enum_type::bbt_messages_should_not_be_entered_when_market_is_pre_open: return "BBT messages should not be entered when market is pre open";
            case enum_type::bbt_messages_should_not_be_entered_when_market_is_pcp: return "BBT messages should not be entered when market is PCP";
            case enum_type::bbt_messages_should_not_be_entered_when_market_is_no_cancel: return "BBT messages should not be entered when market is no cancel";
            case enum_type::bbt_messages_should_not_be_entered_when_market_is_reserved: return "BBT messages should not be entered when market is reserved";
            case enum_type::bbt_messages_should_not_be_entered_when_market_is_forbidden: return "BBT messages should not be entered when market is forbidden";
            case enum_type::bbt_messages_should_not_be_entered_when_market_is_pre_close: return "BBT messages should not be entered when market is pre close";
            case enum_type::invalid_field_for_bbt_order: return "Invalid field for BBT Order";
            case enum_type::for_cancel_on_behalf_must_be_informed_only_the_actiontargetsessionid_or_the_actiontargetgroupid: return "For Cancel On Behalf  must be informed only the ActionTargetSessionID  OR the ActionTargetGroupID";
            case enum_type::actiontargetgroupid_invalid_it_doesnt_exist_or_it_is_disabled: return "ActionTargetGroupID  invalid . It doesn't exist or it is disabled";
            case enum_type::fix_session_is_blocked_due_to_mass_cancel: return "Fix Session is blocked due to Mass Cancel";
            case enum_type::actiontargetgroupid_must_be_informed: return "ActionTargetGroupID must be informed";
            case enum_type::fix_session_doesnt_belong_to_the_actiontargetgroupid: return "Fix Session doesn't belong to the ActionTargetGroupID";
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
            case enum_type::system_initialization: return "System initialization";
            case enum_type::line_busy: return "Line busy";
            case enum_type::message_or_atributes_are_invalid: return "Message or atributes are invalid";
            case enum_type::internal_error: return "Internal error";
            case enum_type::timeout_waiting_risk_evaluation: return "Timeout waiting risk evaluation";
            case enum_type::timeout_waiting_risk_evaluation_low_priority: return "Timeout waiting risk evaluation (low priority)";
            case enum_type::broker_negotiation_blocked_030011: return "Broker negotiation blocked";
            case enum_type::broker_not_available_030012: return "Broker not available";
            case enum_type::brokers_capture_account_not_found_030013: return "Broker's capture account not found";
            case enum_type::brokers_segment_negotiation_blocked_030014: return "Broker's segment negotiation blocked";
            case enum_type::broker_segment_not_available_030015: return "Broker segment not available";
            case enum_type::brokers_segment_protected_mode_under_activation_030016: return "Broker's segment protected mode under activation";
            case enum_type::broker_pn_negotiation_blocked: return "Broker PN negotiation blocked";
            case enum_type::broker_pn_not_available: return "Broker PN not available";
            case enum_type::broker_pn_protected_mode_under_activation: return "Broker PN protected mode under activation";
            case enum_type::account_negotiation_blocked_030021: return "Account negotiation blocked";
            case enum_type::account_not_available_030022: return "Account not available";
            case enum_type::accounts_protected_mode_under_activation_030023: return "Account's protected mode under activation";
            case enum_type::account_mandatory_on_dma_orders_030024: return "Account mandatory on DMA orders";
            case enum_type::transient_account_is_hierarchically_blocked_on_protected_mode_030025: return "Transient Account is hierarchically blocked on protected mode";
            case enum_type::crossorders_or_crossforward_not_allowed_while_account_in_protected_mode_030026: return "Cross-orders or cross-forward not allowed while account in protected mode";
            case enum_type::transient_account_not_allowed_in_extended_hours_030027: return "Transient Account not allowed in Extended Hours";
            case enum_type::document_negotiation_blocked_030031: return "Document negotiation blocked";
            case enum_type::document_not_available_030032: return "Document not available";
            case enum_type::documents_protected_mode_under_activation_030033: return "Document's protected mode under activation";
            case enum_type::executor_document_cannot_use_default_broker_profile_030034: return "Executor document cannot use default broker profile";
            case enum_type::document_in_blocked_profile_030035: return "Document in blocked profile";
            case enum_type::crossorders_or_crossforward_not_allowed_while_document_in_protected_mode_030036: return "Cross-orders or cross-forward not allowed while document in protected mode";
            case enum_type::entering_trader_negotiation_blocked_030041: return "Entering Trader negotiation blocked";
            case enum_type::entering_trader_not_available_030042: return "Entering Trader not available";
            case enum_type::entering_trader_blocked_by_sfd_overflow_030043: return "Entering Trader blocked by SFD overflow";
            case enum_type::non_dma_orders_must_provide_account_while_in_brokers_protected_mode_030044: return "Non DMA orders must provide account while in broker's protected mode";
            case enum_type::entering_trader_not_authorized_to_trade_accountless_orders_030045: return "Entering Trader not authorized to trade accountless orders";
            case enum_type::entering_trader_cannot_trade_on_behalf_of_other_firms_account_030046: return "Entering Trader cannot trade on behalf of other firm's account";
            case enum_type::symbol_not_available_030050: return "Symbol not available";
            case enum_type::symbol_internal_data_corrupted_030051: return "Symbol internal data corrupted";
            case enum_type::fix_message_type_does_not_support_operations_on_such_symbol_030052: return "FIX Message Type does not support operations on such symbol";
            case enum_type::symbols_underlying_not_found_for_risk_aggregation_030053: return "Symbol's underlying not found for risk aggregation";
            case enum_type::symbols_risk_unit_matrix_not_available_030054: return "Symbol's risk unit matrix not available";
            case enum_type::symbols_reference_price_missing_market_orders_not_allowed_030055: return "Symbol's reference price missing, market orders not allowed";
            case enum_type::symbols_calculated_price_invalid_032056: return "Symbol's calculated price invalid";
            case enum_type::spreads_leg_not_available_030060: return "Spread's leg not available";
            case enum_type::spreads_leg_internal_data_corrupted_030061: return "Spread's leg internal data corrupted";
            case enum_type::unexpected_internal_error_during_risk_evaluation_030070: return "Unexpected internal error during risk evaluation";
            case enum_type::sfd_broker_pn_pn_document_aggregation_day_trade_cash_balance_stop_loss_not_configured: return "[SFD] Broker PN <pn> document aggregation: Day trade cash balance (stop loss) not configured";
            case enum_type::sdp_broker_pn_pn_document_aggregation_order_exceeded_cash_settlement_exposure: return "[SDP] Broker PN <pn> document aggregation: Order exceeded cash settlement exposure";
            case enum_type::rmkt_broker_pn_pn_document_aggregation_order_quantity_exceeded_risk_increase: return "[RMKT] Broker PN <pn> document aggregation: Order quantity exceeded risk increase";
            case enum_type::sdp_broker_pn_pn_trader_aggregation_order_exceeded_cash_settlement_exposure: return "[SDP] Broker PN <pn> trader aggregation: Order exceeded cash settlement exposure";
            case enum_type::spvd_broker_pn_pn_document_aggregation_order_exceeded_potential_short_uncovered_balance: return "[SPVD] Broker PN <pn> document aggregation: Order exceeded potential short uncovered balance.";
            case enum_type::spvd_broker_pn_pn_trader_aggregation_order_exceeded_potential_short_uncovered_balance: return "[SPVD] Broker PN <pn> trader aggregation: Order exceeded potential short uncovered balance.";
            case enum_type::rmse_broker_pn_pn_document_aggregation_order_exceeded_risk_increase_at_extended_session: return "[RMSE] Broker PN <pn> document aggregation: Order exceeded risk increase at extended session";
            case enum_type::rmse_broker_order_exceeded_risk_increase_at_extended_session: return "[RMSE] Broker: Order exceeded risk increase at extended session";
            case enum_type::mkta_account_buy_not_allowed_for_symbols_market_030201: return "[MKTA] Account: Buy not allowed for symbol's market";
            case enum_type::mkta_account_sell_not_allowed_for_symbols_market_030202: return "[MKTA] Account: Sell not allowed for symbol's market";
            case enum_type::tmoc_account_maximum_order_size_exceeded_for_single_order: return "[TMOC] Account: Maximum order size exceeded for single order";
            case enum_type::tmov_account_maximum_order_size_exceeded_for_single_order: return "[TMOV] Account: Maximum order size exceeded for single order";
            case enum_type::spci_account_order_quantity_exceeded_short_position_per_instrument: return "[SPCI] Account: Order quantity exceeded short position per instrument";
            case enum_type::spvi_account_order_quantity_exceeded_long_position_per_instrument: return "[SPVI] Account: Order quantity exceeded long position per instrument";
            case enum_type::sdp_account_order_exceeded_cash_settlement_exposure: return "[SDP] Account: Order exceeded cash settlement exposure";
            case enum_type::rmkt_account_order_quantity_exceeded_risk_increase: return "[RMKT] Account: Order quantity exceeded risk increase";
            case enum_type::irmkt_account_order_quantity_exceeded_risk_increase_reducing_mode: return "[IRMKT] Account: Order quantity exceeded risk increase - reducing mode";
            case enum_type::spi_account_order_quantity_exceeded_long_and_short_position_reducing_mode: return "[SPI] Account: Order quantity exceeded long and short position - reducing mode";
            case enum_type::std_account_termo_not_allowed_protected_mode_enabled_030213: return "[STD] Account: Termo not allowed, protected mode enabled";
            case enum_type::spvd_account_order_exceeded_potential_short_uncovered_balance_030215: return "[SPVD] Account: Order exceeded potential short uncovered balance.";
            case enum_type::mkta_document_buysell_symbols_market_not_configured_030300: return "[MKTA] Document: Buy/Sell symbol's market not configured";
            case enum_type::mkta_document_buy_not_allowed_for_symbols_market_030301: return "[MKTA] Document: Buy not allowed for symbol's market";
            case enum_type::mkta_document_sell_not_allowed_for_symbols_market_030302: return "[MKTA] Document: Sell not allowed for symbol's market";
            case enum_type::tmox_document_max: return "[TMOX] Document: Max";
            case enum_type::tmoc_document_max_bid_quantity_exceeded_for_single_order: return "[TMOC] Document: Max Bid quantity exceeded for single order";
            case enum_type::tmov_document_max_offer_quantity_exceeded_for_single_order: return "[TMOV] Document: Max Offer quantity exceeded for single order";
            case enum_type::spci_document_order_quantity_exceeded_max_bid_potential_balance: return "[SPCI] Document: Order quantity exceeded Max Bid Potential Balance";
            case enum_type::spvi_document_order_quantity_exceeded_max_offer_potential_balance: return "[SPVI] Document: Order quantity exceeded Max Offer Potential Balance";
            case enum_type::sdp_document_order_exceeded_max_financial_potential_balance_due: return "[SDP] Document: Order exceeded Max Financial Potential Balance Due";
            case enum_type::std_document_order_quantity_exceeded_max_operations_forward_balance: return "[STD] Document: Order quantity exceeded Max Operations Forward Balance";
            case enum_type::rmkt: return "[RMKT]";
            case enum_type::irmkt_document_order_quantity_exceeded_max_incremental_market_risk: return "[IRMKT] Document: Order quantity exceeded Max Incremental Market Risk";
            case enum_type::spi_document_order_quantity_exceeded_previous_potencial_balance: return "[SPI] Document: Order quantity exceeded Previous Potencial Balance";
            case enum_type::std_document_termo_not_allowed: return "[STD] Document: Termo not allowed,";
            case enum_type::sfd_document_day_trade_cash_balance_stop_loss_not_configured_030314: return "[SFD] Document: Day trade cash balance (stop loss) not configured";
            case enum_type::spvd_document_order_exceeded_potential_short_uncovered_balance_030315: return "[SPVD] Document: Order exceeded potential short uncovered balance";
            case enum_type::rmse_document_order_exceeded_risk_increase_at_extended_session_030316: return "[RMSE] Document: Order exceeded risk increase at extended session";
            case enum_type::rmse_document_order_exceeded_risk_increase_of_broker_at_extended_session_030317: return "[RMSE] Document: Order exceeded risk increase of broker at extended session";
            case enum_type::mkta_entering_trader_buysell_symbols_market_not_configured_030400: return "[MKTA] Entering trader: Buy/Sell symbol's market not configured";
            case enum_type::mkta_entering_trader_buy_not_allowed_for_symbols_market_030401: return "[MKTA] Entering trader: Buy not allowed for symbol's market";
            case enum_type::mkta_entering: return "[MKTA] Entering";
            case enum_type::tmox_entering_trader_max_bidoffer_quantity_not_configured: return "[TMOX] Entering trader: Max Bid/Offer quantity not configured";
            case enum_type::tmoc_entering_trader_max_bid_quantity_exceeded_for_single_order: return "[TMOC] Entering trader: Max Bid quantity exceeded for single order";
            case enum_type::tmov_entering_trader_max_offer_quantity_exceeded_for_si: return "[TMOV] Entering trader: Max Offer quantity exceeded for si";
            case enum_type::spci_entering_trader_order_quantity_exceeded_max_bid_potential_balance: return "[SPCI] Entering trader: Order quantity exceeded Max Bid Potential Balance";
            case enum_type::spvi_entering_trader_order_quantity_exceeded_max_offer_potential_balance: return "[SPVI] Entering trader: Order quantity exceeded Max Offer Potential Balance";
            case enum_type::sdp_entering_trader_order_exceeded_max_financial_potential: return "[SDP] Entering trader: Order exceeded Max Financial Potential";
            case enum_type::spvd_trader_order_exceeded_potential_short_uncovered_balance: return "[SPVD] Trader: Order exceeded potential short uncovered balance.";
            case enum_type::oms_unexpected_internal_error_030500: return "[OMS] Unexpected internal error";
            case enum_type::oms_invalid_session_or_symbol_030501: return "[OMS] Invalid session or symbol";
            case enum_type::oms_clordid_cannot_be_empty_030502: return "[OMS] ClOrdID cannot be empty";
            case enum_type::oms_clordid_is_duplicated_030503: return "[OMS] ClOrdID is duplicated";
            case enum_type::oms_clordid_not_found_030504: return "[OMS] ClOrdID not found";
            case enum_type::oms_origclordid_cannot_be_empty_030505: return "[OMS] OrigClOrdID cannot be empty";
            case enum_type::oms_crossid_cannot_be_empty_030506: return "[OMS] CrossID cannot be empty";
            case enum_type::oms_clordid_is_duplicated_within_cross_order_030507: return "[OMS] ClOrdID is duplicated within Cross Order";
            case enum_type::oms_cross_order_modification_is_not_allowed_030508: return "[OMS] Cross Order modification is not allowed";
            case enum_type::oms_orderid_not_found_030509: return "[OMS] OrderID not found";
            case enum_type::oms_orderid_cannot_be_empty_030510: return "[OMS] OrderID cannot be empty";
            case enum_type::oms_quotereqid_cannot_be_empty_030511: return "[OMS] QuoteReqID cannot be empty";
            case enum_type::oms_quotereqid_is_duplicated_030512: return "[OMS] QuoteReqID is duplicated";
            case enum_type::oms_quotereqid_not_found_030513: return "[OMS] QuoteReqID not found";
            case enum_type::oms_quoteid_cannot_be_empty_030514: return "[OMS] QuoteID cannot be empty";
            case enum_type::oms_in: return "[OMS] In";
            case enum_type::oms: return "[OMS]";
            case enum_type::oms_entering_firm_modification_is_not_allowed_030523: return "[OMS] Entering firm modification is not allowed";
            case enum_type::oms_account_modification_on_dma_order_is_not_allowed_030524: return "[OMS] Account modification on DMA order is not allowed";
            case enum_type::oms_account_information_missing_on_non: return "[OMS] Account information missing on non";
            case enum_type::oms_entering_trader: return "[OMS] Entering trader";
            case enum_type::oms_received_execution_report_rejection_for_an_active_order_030527: return "[OMS] Received Execution Report Rejection for an active order";
            case enum_type::broker_negotiation_blocked_031011: return "Broker negotiation blocked";
            case enum_type::broker_not_available_031012: return "Broker not available";
            case enum_type::brokers_capture_account_not_found_031013: return "Broker's capture account not found";
            case enum_type::brokers_segment_negotiation_blocked_031014: return "Broker's segment negotiation blocked";
            case enum_type::broker_segment_not_available_031015: return "Broker segment not available";
            case enum_type::brokers_segment_protected_mode_under_activation_031016: return "Broker's segment protected mode under activation";
            case enum_type::account_negotiation_blocked_031021: return "Account negotiation blocked";
            case enum_type::account_not_available_031022: return "Account not available";
            case enum_type::accounts_protected_mode_under_activation_031023: return "Account's protected mode under activation";
            case enum_type::account_mandatory_on_dma_orders_031024: return "Account mandatory on DMA orders";
            case enum_type::transient_account_is_hierarchically_blocked_on_protected_mode_031025: return "Transient Account is hierarchically blocked on protected mode";
            case enum_type::crossorders_or_crossforward_not_allowed_while_account_in_protected_mode_031026: return "Cross-orders or cross-forward not allowed while account in protected mode";
            case enum_type::transient_account_not_allowed_in_extended_hours_031027: return "Transient Account not allowed in Extended Hours";
            case enum_type::document_negotiation_blocked_031031: return "Document negotiation blocked";
            case enum_type::document_not_available_031032: return "Document not available";
            case enum_type::documents_protected_mode_under_activation_031033: return "Document's protected mode under activation";
            case enum_type::executor_document_cannot_use_default_broker_profile_031034: return "Executor document cannot use default broker profile";
            case enum_type::document_in_blocked_profile_031035: return "Document in blocked profile";
            case enum_type::crossorders_or_crossforward_not_allowed_while_document_in_protected_mode_031036: return "Cross-orders or cross-forward not allowed while document in protected mode";
            case enum_type::entering_trader_negotiation_blocked_031041: return "Entering Trader negotiation blocked";
            case enum_type::entering_trader_not_available_031042: return "Entering Trader not available";
            case enum_type::entering_trader_blocked_by_sfd_overflow_031043: return "Entering Trader blocked by SFD overflow";
            case enum_type::non_dma_orders_must_provide_account_while_in_brokers_protected_mode_031044: return "Non DMA orders must provide account while in broker's protected mode";
            case enum_type::entering_trader_not_authorized_to_trade_accountless_orders_031045: return "Entering Trader not authorized to trade accountless orders";
            case enum_type::entering_trader_cannot_trade_on_behalf_of_other_firms_account_031046: return "Entering Trader cannot trade on behalf of other firm's account";
            case enum_type::symbol_not_available_031050: return "Symbol not available";
            case enum_type::symbol_internal_data_corrupted_031051: return "Symbol internal data corrupted";
            case enum_type::fix_message_type_does_not_support_operations_on_such_symbol_031052: return "FIX Message Type does not support operations on such symbol";
            case enum_type::symbols_underlying_not_found_for_risk_aggregation_031053: return "Symbol's underlying not found for risk aggregation";
            case enum_type::symbols_risk_unit_matrix_not_available_031054: return "Symbol's risk unit matrix not available";
            case enum_type::symbols_reference_price_missing_market_orders_not_allowed_031055: return "Symbol's reference price missing, market orders not allowed";
            case enum_type::symbols_calculated_price_invalid_031056: return "Symbol's calculated price invalid";
            case enum_type::spreads_leg_not_available_031060: return "Spread's leg not available";
            case enum_type::spreads_leg_internal_data_corrupted_031061: return "Spread's leg internal data corrupted";
            case enum_type::unexpected_internal_error_during_risk_evaluation_031070: return "Unexpected internal error during risk evaluation";
            case enum_type::mkta_account_buy_not_allowed_for_symbols_market_031201: return "[MKTA] Account: Buy not allowed for symbol's market";
            case enum_type::mkta_account_sell_not_allowed_for_symbols_market_031202: return "[MKTA] Account: Sell not allowed for symbol's market";
            case enum_type::tmoc_account_max_bid_quantity_exceeded_for_single_order: return "[TMOC] Account: Max Bid quantity exceeded for single order";
            case enum_type::tmov_account_max_offer_quantity_exceeded_for_single_order: return "[TMOV] Account: Max Offer quantity exceeded for single order";
            case enum_type::spci_account_order_quantity_exceeded_max_bid_potential_balance: return "[SPCI] Account: Order quantity exceeded Max Bid Potential Balance";
            case enum_type::spvi_account_order_quantity_exceeded_max_offer_potential_balance: return "[SPVI] Account: Order quantity exceeded Max Offer Potential Balance";
            case enum_type::sdp_account_order_exceeded_max_financial_potential_balance_due: return "[SDP] Account: Order exceeded Max Financial Potential Balance Due";
            case enum_type::rmkt_account_order_quantity_exceeded_max_market_risk: return "[RMKT] Account: Order quantity exceeded Max Market Risk";
            case enum_type::irmkt_account_order_quantity_exceeded_max_incremental_market_risk: return "[IRMKT] Account: Order quantity exceeded Max Incremental Market Risk";
            case enum_type::spi_account_order_quantity_exceeded_previous_potencial_balance: return "[SPI] Account: Order quantity exceeded Previous Potencial Balance";
            case enum_type::std_account_termo_not_allowed_protected_mode_enabled_031213: return "[STD] Account: Termo not allowed, protected mode enabled";
            case enum_type::spvd_account_order_exceeded_potential_short_uncovered_balance_031215: return "[SPVD] Account: Order exceeded potential short uncovered balance.";
            case enum_type::mkta_document_buysell_symbols_market_not_configured_031300: return "[MKTA] Document: Buy/Sell symbol's market not configured";
            case enum_type::mkta_document_buy_not_allowed_for_symbols_market_031301: return "[MKTA] Document: Buy not allowed for symbol's market";
            case enum_type::mkta_document_sell_not_allowed_for_symbols_market_031302: return "[MKTA] Document: Sell not allowed for symbol's market";
            case enum_type::tmox_document_maximum_order_size_not_configured: return "[TMOX] Document: Maximum order size not configured";
            case enum_type::tmoc_document_maximum_order_size_exceeded_for_single_order: return "[TMOC] Document: Maximum order size exceeded for single order";
            case enum_type::tmov_document_maximum_order_size_exceeded_for_single_order: return "[TMOV] Document: Maximum order size exceeded for single order";
            case enum_type::spci_document_order_quantity_exceeded_short_position_per_instrument: return "[SPCI] Document: Order quantity exceeded short position per instrument";
            case enum_type::spvi_document_order_quantity_exceeded_long_position_per_instrument: return "[SPVI] Document: Order quantity exceeded long position per instrument";
            case enum_type::sdp_document_order_exceeded_cash_settlement_exposure: return "[SDP] Document: Order exceeded cash settlement exposure";
            case enum_type::std_document_order_quantity_exceeded_forward_contracts_exposure: return "[STD] Document: Order quantity exceeded forward contracts exposure";
            case enum_type::rmkt_document_order_quantity_exceeded_risk_increase: return "[RMKT] Document: Order quantity exceeded risk increase";
            case enum_type::irmkt_document_order_quantity_exceeded_risk_increase_reducing_mode: return "[IRMKT] Document: Order quantity exceeded risk increase - reducing mode";
            case enum_type::spi_document_order_quantity_exceeded_long_and_short_position_reducing_mode: return "[SPI] Document: Order quantity exceeded long and short position - reducing mode";
            case enum_type::std_document_termo_not_allowed_protected_mode_enabled: return "[STD] Document: Termo not allowed, protected mode enabled";
            case enum_type::sfd_document_day_trade_cash_balance_stop_loss_not_configured_031314: return "[SFD] Document: Day trade cash balance (stop loss) not configured";
            case enum_type::spvd_document_order_exceeded_potential_short_uncovered_balance_031315: return "[SPVD] Document: Order exceeded potential short uncovered balance.";
            case enum_type::rmse_document_order_exceeded_risk_increase_at_extended_session_031316: return "[RMSE] Document: Order exceeded risk increase at extended session";
            case enum_type::rmse_document_order_exceeded_risk_increase_of_broker_at_extended_session_031317: return "[RMSE] Document: Order exceeded risk increase of broker at extended session";
            case enum_type::mkta_entering_trader_buysell_symbols_market_not_configured_031400: return "[MKTA] Entering trader: Buy/Sell symbol's market not configured";
            case enum_type::mkta_entering_trader_buy_not_allowed_for_symbols_market_031401: return "[MKTA] Entering trader: Buy not allowed for symbol's market";
            case enum_type::mkta_entering_trader_sell_not_allowed_for_symbols_market: return "[MKTA] Entering trader: Sell not allowed for symbol's market";
            case enum_type::tmox_entering_trader_maximum_order_size_not_configured: return "[TMOX] Entering trader: Maximum order size not configured";
            case enum_type::tmoc_entering_trader_maximum_order_size_exceeded_for_single_order: return "[TMOC] Entering trader: Maximum order size exceeded for single order";
            case enum_type::tmov_entering_trader_maximum_order_size_exceeded_for_single_order: return "[TMOV] Entering trader: Maximum order size exceeded for single order";
            case enum_type::spci_entering_trader_order_quantity_exceeded_short_position_per_instrument: return "[SPCI] Entering trader: Order quantity exceeded short position per instrument";
            case enum_type::spvi_entering_trader_order_quantity_exceeded_long_position_per_instrument: return "[SPVI] Entering trader: Order quantity exceeded long position per instrument";
            case enum_type::sdp_entering_trader_order_exceeded_cash_settlement_exposure: return "[SDP] Entering trader: Order exceeded cash settlement exposure";
            case enum_type::oms_unexpected_internal_error_031500: return "[OMS] Unexpected internal error";
            case enum_type::oms_invalid_session_or_symbol_031501: return "[OMS] Invalid session or symbol";
            case enum_type::oms_clordid_cannot_be_empty_031502: return "[OMS] ClOrdID cannot be empty";
            case enum_type::oms_clordid_is_duplicated_031503: return "[OMS] ClOrdID is duplicated";
            case enum_type::oms_clordid_not_found_031504: return "[OMS] ClOrdID not found";
            case enum_type::oms_origclordid_cannot_be_empty_031505: return "[OMS] OrigClOrdID cannot be empty";
            case enum_type::oms_crossid_cannot_be_empty_031506: return "[OMS] CrossID cannot be empty";
            case enum_type::oms_clordid_is_duplicated_within_cross_order_031507: return "[OMS] ClOrdID is duplicated within Cross Order";
            case enum_type::oms_cross_order_modification_is_not_allowed_031508: return "[OMS] Cross Order modification is not allowed";
            case enum_type::oms_orderid_not_found_031509: return "[OMS] OrderID not found";
            case enum_type::oms_orderid_cannot_be_empty_031510: return "[OMS] OrderID cannot be empty";
            case enum_type::oms_quotereqid_cannot_be_empty_031511: return "[OMS] QuoteReqID cannot be empty";
            case enum_type::oms_quotereqid_is_duplicated_031512: return "[OMS] QuoteReqID is duplicated";
            case enum_type::oms_quotereqid_not_found_031513: return "[OMS] QuoteReqID not found";
            case enum_type::oms_quoteid_cannot_be_empty_031514: return "[OMS] QuoteID cannot be empty";
            case enum_type::oms_inflight_modification_is_not_allowed: return "[OMS] In-Flight modification is not allowed";
            case enum_type::oms_side_modification_is_not_allowed: return "[OMS] Side modification is not allowed";
            case enum_type::oms_entering_firm_modification_is_not_allowed_031523: return "[OMS] Entering firm modification is not allowed";
            case enum_type::oms_account_modification_on_dma_order_is_not_allowed_031524: return "[OMS] Account modification on DMA order is not allowed";
            case enum_type::oms_account_information_missing_on_nondma_order: return "[OMS] Account information missing on non-DMA order";
            case enum_type::oms_entering_trader_modification_on_nondma_order_is_not_allowed: return "[OMS] Entering trader modification on non-DMA order is not allowed";
            case enum_type::oms_received_execution_report_rejection_for_an_active_order_031527: return "[OMS] Received Execution Report Rejection for an active order";
            case enum_type::field_missing_or_incorrect_032000: return "Field missing or incorrect";
            case enum_type::line_not_available_or_busy: return "LiNe not available or busy";
            case enum_type::line_internal_error: return "LiNe internal error";
            case enum_type::line_recovering_or_starting_up: return "LiNe recovering or starting up";
            case enum_type::internal_gateway_error_message_forwarding_failure: return "Internal gateway error (message forwarding failure)";
            case enum_type::invalid_quantity: return "Invalid Quantity";
            case enum_type::duplicate_order: return "Duplicate Order";
            case enum_type::missing_account_field: return "Missing Account Field";
            case enum_type::unknown_account: return "Unknown Account";
            case enum_type::unknown_firmid_for_routing: return "Unknown FirmID (for routing)";
            case enum_type::duplicate_firmid: return "Duplicate FirmID";
            case enum_type::duplicate_sender_location: return "Duplicate Sender Location";
            case enum_type::duplicate_entering_trader: return "Duplicate Entering Trader";
            case enum_type::firm_or_trader_is_missing_in_nondma_order: return "Firm or Trader is missing in non-DMA order";
            case enum_type::firm_or_account_is_missing_in_dma_order: return "Firm or Account is missing in DMA order";
            case enum_type::same_participants_on_both_sides_or_invalid_sides: return "Same Participants on both sides or invalid sides";
            case enum_type::buy_side_and_sell_side_having_different_firmids: return "BUY side and SELL side having different FirmIDs";
            case enum_type::buy_side_and_sell_side_trading_different_assets: return "BUY side and SELL side trading different assets";
            case enum_type::invalid_price_032018: return "Invalid Price";
            case enum_type::line_overloaded: return "LiNe overloaded";
            case enum_type::line_administratively_blocked: return "LiNe administratively blocked";
            case enum_type::invalid_price_032021: return "Invalid Price";
            case enum_type::system_overloaded: return "System Overloaded";
            case enum_type::system_error_032023: return "System Error";
            case enum_type::throttle_limit_reached: return "Throttle limit reached";
            case enum_type::invalid_security_id: return "Invalid Security ID";
            case enum_type::unknown_market_segment_id: return "Unknown Market Segment ID";
            case enum_type::field_missing_or_incorrect_033003: return "Field missing or incorrect";
            case enum_type::system_error_033050: return "System Error";
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

    static constexpr const char* name = "ord_rej_reason";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<ord_rej_reason::enum_type>;
    using storage_type = result_type;

    constexpr ord_rej_reason()
     : value{ enum_type{} } {}

    constexpr ord_rej_reason(enum_type v)
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
            set(enum_type::system_error_033050);
    }

  protected:
    enum_type value;
};
}
