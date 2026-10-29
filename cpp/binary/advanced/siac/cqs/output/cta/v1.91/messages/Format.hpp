#pragma once

#include <ostream>
#include <string_view>

#include "AdministrativeUnformattedMessage.hpp"
#include "StartOfDayMessage.hpp"
#include "FinraCloseMessage.hpp"
#include "ResetBlockSequenceNumberMessage.hpp"
#include "StartOfTestCycleMessage.hpp"
#include "EndOfTestCycleMessage.hpp"
#include "FinraOpenMessage.hpp"
#include "DisasterRecoveryDataCenterActivationMessage.hpp"
#include "LineIntegrityMessage.hpp"
#include "EndOfDayMessage.hpp"
#include "MarketWideCircuitBreakerDeclineLevelStatusMessage.hpp"
#include "MarketWideCircuitBreakerStatusMessage.hpp"
#include "AuctionStatusMessage.hpp"
#include "LongQuoteMessage.hpp"
#include "ShortQuoteMessage.hpp"
#include "SpecialLongQuoteMessage.hpp"

namespace siac::cqs::output::cta::v1_91 {

namespace cta_output = ::siac::cqs::output::cta::v1_91;

inline std::ostream& operator<<(std::ostream& os, const block_header& value) {
    os << "version=" << static_cast<unsigned>(value.version.get().value())
       << ",block_size=" << value.block_size.get().value()
       << ",data_feed_indicator=\"" << value.data_feed_indicator.get().value() << '"'
       << ",retransmission_indicator=\"" << cta_output::retransmission_indicator::to_string(value.retransmission_indicator.get().value()) << '"'
       << ",block_sequence_number=" << value.block_sequence_number.get().value()
       << ",messages_in_block=" << static_cast<unsigned>(value.messages_in_block.get().value())
       << ",sip_block_timestamp.seconds=" << value.sip_block_timestamp.seconds.get().value()
       << ",sip_block_timestamp.nanoseconds=" << value.sip_block_timestamp.nanoseconds.get().value()
       << ",block_checksum=" << value.block_checksum.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_category=\"" << cta_output::message_category::to_string(value.message_category.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const administrative_message& value) {
    os << "administrative_message_type=\"" << cta_output::administrative_message_type::to_string(value.administrative_message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sip_block_timestamp& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const participant_timestamp& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const adf_timestamp& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const national_best_bid_long_appendage& value) {
    os << "best_bid_participant_id=\"" << cta_output::best_bid_participant_id::to_string(value.best_bid_participant_id.get().value()) << '"'
       << ",best_bid_quote_condition=\"" << value.best_bid_quote_condition.get().value() << '"'
       << ",best_bid_price_long=" << value.best_bid_price_long.get().value()
       << ",best_bid_size_long=" << value.best_bid_size_long.get().value()
       << ",finra_best_bid_market_maker_id=\"" << value.finra_best_bid_market_maker_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const national_best_offer_long_appendage& value) {
    os << "best_offer_participant_id=\"" << cta_output::best_offer_participant_id::to_string(value.best_offer_participant_id.get().value()) << '"'
       << ",best_offer_quote_condition=\"" << value.best_offer_quote_condition.get().value() << '"'
       << ",best_offer_price_long=" << value.best_offer_price_long.get().value()
       << ",best_offer_size_long=" << value.best_offer_size_long.get().value()
       << ",finra_best_offer_market_maker_id=\"" << value.finra_best_offer_market_maker_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const national_best_bid_short_appendage& value) {
    os << "best_bid_participant_id=\"" << cta_output::best_bid_participant_id::to_string(value.best_bid_participant_id.get().value()) << '"'
       << ",best_bid_price_short=" << value.best_bid_price_short.get().value()
       << ",best_bid_size_short=" << value.best_bid_size_short.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const national_best_offer_short_appendage& value) {
    os << "best_offer_participant_id=\"" << cta_output::best_offer_participant_id::to_string(value.best_offer_participant_id.get().value()) << '"'
       << ",best_offer_price_short=" << value.best_offer_price_short.get().value()
       << ",best_offer_size_short=" << value.best_offer_size_short.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const administrative_unformatted_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",text=\"" << msg.fields.text.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const start_of_day_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const finra_close_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reset_block_sequence_number_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const start_of_test_cycle_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_test_cycle_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const finra_open_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const disaster_recovery_data_center_activation_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const line_integrity_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_day_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_wide_circuit_breaker_decline_level_status_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",mwcb_level_1=" << msg.fields.mwcb_level_1.get().value()
       << ",mwcb_level_2=" << msg.fields.mwcb_level_2.get().value()
       << ",mwcb_level_3=" << msg.fields.mwcb_level_3.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_wide_circuit_breaker_status_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",market_wide_circuit_breaker_level_indicator=\"" << cta_output::market_wide_circuit_breaker_level_indicator::to_string(msg.fields.market_wide_circuit_breaker_level_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_status_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol_long=\"" << msg.fields.security_symbol_long.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",auction_collar_reference_price=" << (msg.fields.auction_collar_reference_price.get().has_value() ? std::to_string(msg.fields.auction_collar_reference_price.get().value()) : std::string_view("null"))
       << ",auction_collar_upper_threshold_price=" << (msg.fields.auction_collar_upper_threshold_price.get().has_value() ? std::to_string(msg.fields.auction_collar_upper_threshold_price.get().value()) : std::string_view("null"))
       << ",auction_collar_lower_threshold_price=" << (msg.fields.auction_collar_lower_threshold_price.get().has_value() ? std::to_string(msg.fields.auction_collar_lower_threshold_price.get().value()) : std::string_view("null"))
       << ",number_of_extensions=" << static_cast<unsigned>(msg.fields.number_of_extensions.get().value())
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",future=\"" << msg.fields.future.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const long_quote_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol_long=\"" << msg.fields.security_symbol_long.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",quote_condition=\"" << cta_output::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",security_status_indicator=\"" << cta_output::security_status_indicator::to_string(msg.fields.security_status_indicator.get().value()) << '"'
       << ",bid_price_lower_limit_price_band=" << msg.fields.bid_price_lower_limit_price_band.get().value()
       << ",bid_size_long=" << msg.fields.bid_size_long.get().value()
       << ",offer_price_upper_limit_price_band=" << msg.fields.offer_price_upper_limit_price_band.get().value()
       << ",offer_size_long=" << msg.fields.offer_size_long.get().value()
       << ",retail_interest_indicator=\"" << cta_output::retail_interest_indicator::to_string(msg.fields.retail_interest_indicator.get().value()) << '"'
       << ",settlement_condition=\"" << cta_output::settlement_condition::to_string(msg.fields.settlement_condition.get().value()) << '"'
       << ",market_condition=\"" << cta_output::market_condition::to_string(msg.fields.market_condition.get().value()) << '"'
       << ",finra_market_maker_id=\"" << msg.fields.finra_market_maker_id.get_trimmed().value() << '"'
       << ",finra_bbo_indicator=\"" << cta_output::finra_bbo_indicator::to_string(msg.fields.finra_bbo_indicator.get().value()) << '"'
       << ",adf_timestamp.seconds=" << msg.fields.adf_timestamp.seconds.get().value()
       << ",adf_timestamp.nanoseconds=" << msg.fields.adf_timestamp.nanoseconds.get().value()
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",sip_generated_message_identifier=\"" << cta_output::sip_generated_message_identifier::to_string(msg.fields.sip_generated_message_identifier.get().value()) << '"'
       << ",luld_indicator=\"" << msg.fields.luld_indicator.get().value() << '"'
       << ",national_bbo_luld_indicator=\"" << cta_output::national_bbo_luld_indicator::to_string(msg.fields.national_bbo_luld_indicator.get().value()) << '"'
       << ",national_bbo_indicator=\"" << cta_output::national_bbo_indicator::to_string(msg.fields.national_bbo_indicator.get().value()) << '"'
       ;
    {
        auto desc = msg.describe_appendages();
        if (desc.has_bid || desc.has_offer) {
            if (desc.has_bid == true && desc.has_offer == false && desc.bid_is_long == true && desc.offer_is_long == false) {
                if (auto* a = msg.national_best_bid_long_appendage()) os << ",national_best_bid_long_appendage={" << *a << "}";
            }
            if (desc.has_bid == false && desc.has_offer == true && desc.bid_is_long == false && desc.offer_is_long == true) {
                if (auto* a = msg.national_best_offer_long_appendage()) os << ",national_best_offer_long_appendage={" << *a << "}";
            }
            if (desc.has_bid == true && desc.has_offer == false && desc.bid_is_long == false && desc.offer_is_long == false) {
                if (auto* a = msg.national_best_bid_short_appendage()) os << ",national_best_bid_short_appendage={" << *a << "}";
            }
            if (desc.has_bid == false && desc.has_offer == true && desc.bid_is_long == false && desc.offer_is_long == false) {
                if (auto* a = msg.national_best_offer_short_appendage()) os << ",national_best_offer_short_appendage={" << *a << "}";
            }
        }
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const short_quote_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol_short=\"" << msg.fields.security_symbol_short.get_trimmed().value() << '"'
       << ",bid_price_short=" << msg.fields.bid_price_short.get().value()
       << ",bid_size_short=" << msg.fields.bid_size_short.get().value()
       << ",offer_price_short=" << msg.fields.offer_price_short.get().value()
       << ",offer_size_short=" << msg.fields.offer_size_short.get().value()
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",national_bbo_indicator=\"" << cta_output::national_bbo_indicator::to_string(msg.fields.national_bbo_indicator.get().value()) << '"'
       ;
    {
        auto desc = msg.describe_appendages();
        if (desc.has_bid || desc.has_offer) {
            if (desc.has_bid == true && desc.has_offer == false && desc.bid_is_long == true && desc.offer_is_long == false) {
                if (auto* a = msg.national_best_bid_long_appendage()) os << ",national_best_bid_long_appendage={" << *a << "}";
            }
            if (desc.has_bid == false && desc.has_offer == true && desc.bid_is_long == false && desc.offer_is_long == true) {
                if (auto* a = msg.national_best_offer_long_appendage()) os << ",national_best_offer_long_appendage={" << *a << "}";
            }
            if (desc.has_bid == true && desc.has_offer == false && desc.bid_is_long == false && desc.offer_is_long == false) {
                if (auto* a = msg.national_best_bid_short_appendage()) os << ",national_best_bid_short_appendage={" << *a << "}";
            }
            if (desc.has_bid == false && desc.has_offer == true && desc.bid_is_long == false && desc.offer_is_long == false) {
                if (auto* a = msg.national_best_offer_short_appendage()) os << ",national_best_offer_short_appendage={" << *a << "}";
            }
        }
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const special_long_quote_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",participant_timestamp.seconds=" << msg.fields.participant_timestamp.seconds.get().value()
       << ",participant_timestamp.nanoseconds=" << msg.fields.participant_timestamp.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol_long=\"" << msg.fields.security_symbol_long.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",quote_condition=\"" << cta_output::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",security_status_indicator=\"" << cta_output::security_status_indicator::to_string(msg.fields.security_status_indicator.get().value()) << '"'
       << ",bid_price_long=" << msg.fields.bid_price_long.get().value()
       << ",bid_size_long=" << msg.fields.bid_size_long.get().value()
       << ",offer_price_long=" << msg.fields.offer_price_long.get().value()
       << ",offer_size_long=" << msg.fields.offer_size_long.get().value()
       << ",retail_interest_indicator=\"" << cta_output::retail_interest_indicator::to_string(msg.fields.retail_interest_indicator.get().value()) << '"'
       << ",settlement_condition=\"" << cta_output::settlement_condition::to_string(msg.fields.settlement_condition.get().value()) << '"'
       << ",market_condition=\"" << cta_output::market_condition::to_string(msg.fields.market_condition.get().value()) << '"'
       << ",finra_market_maker_id=\"" << msg.fields.finra_market_maker_id.get_trimmed().value() << '"'
       << ",finra_best_bid_quote_condition=\"" << msg.fields.finra_best_bid_quote_condition.get().value() << '"'
       << ",finra_best_bid_price=" << msg.fields.finra_best_bid_price.get().value()
       << ",finra_best_bid_size=" << msg.fields.finra_best_bid_size.get().value()
       << ",finra_best_bid_market_maker_id=\"" << msg.fields.finra_best_bid_market_maker_id.get_trimmed().value() << '"'
       << ",finra_best_offer_quote_condition=\"" << msg.fields.finra_best_offer_quote_condition.get().value() << '"'
       << ",finra_best_offer_price=" << msg.fields.finra_best_offer_price.get().value()
       << ",finra_best_offer_size=" << msg.fields.finra_best_offer_size.get().value()
       << ",finra_best_offer_market_maker_id=\"" << msg.fields.finra_best_offer_market_maker_id.get_trimmed().value() << '"'
       << ",adf_timestamp.seconds=" << msg.fields.adf_timestamp.seconds.get().value()
       << ",adf_timestamp.nanoseconds=" << msg.fields.adf_timestamp.nanoseconds.get().value()
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",sip_generated_message_identifier=\"" << cta_output::sip_generated_message_identifier::to_string(msg.fields.sip_generated_message_identifier.get().value()) << '"'
       << ",finra_bbo_luld_indicator=\"" << cta_output::finra_bbo_luld_indicator::to_string(msg.fields.finra_bbo_luld_indicator.get().value()) << '"'
       << ",national_bbo_luld_indicator=\"" << cta_output::national_bbo_luld_indicator::to_string(msg.fields.national_bbo_luld_indicator.get().value()) << '"'
       << ",national_bbo_indicator=\"" << cta_output::national_bbo_indicator::to_string(msg.fields.national_bbo_indicator.get().value()) << '"'
       ;
    {
        auto desc = msg.describe_appendages();
        if (desc.has_bid || desc.has_offer) {
            if (desc.has_bid == true && desc.has_offer == false && desc.bid_is_long == true && desc.offer_is_long == false) {
                if (auto* a = msg.national_best_bid_long_appendage()) os << ",national_best_bid_long_appendage={" << *a << "}";
            }
            if (desc.has_bid == false && desc.has_offer == true && desc.bid_is_long == false && desc.offer_is_long == true) {
                if (auto* a = msg.national_best_offer_long_appendage()) os << ",national_best_offer_long_appendage={" << *a << "}";
            }
            if (desc.has_bid == true && desc.has_offer == false && desc.bid_is_long == false && desc.offer_is_long == false) {
                if (auto* a = msg.national_best_bid_short_appendage()) os << ",national_best_bid_short_appendage={" << *a << "}";
            }
            if (desc.has_bid == false && desc.has_offer == true && desc.bid_is_long == false && desc.offer_is_long == false) {
                if (auto* a = msg.national_best_offer_short_appendage()) os << ",national_best_offer_short_appendage={" << *a << "}";
            }
        }
    }
    return os;
}

}
