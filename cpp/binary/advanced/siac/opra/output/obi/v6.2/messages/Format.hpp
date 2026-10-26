#pragma once

#include <ostream>
#include <string_view>

#include "AdministrativeMessage.hpp"
#include "ControlMessage.hpp"
#include "EquityAndIndexLastSaleMessage.hpp"
#include "OpenInterestMessage.hpp"
#include "EquityAndIndexEndOfDaySummaryMessage.hpp"
#include "LongEquityAndIndexQuoteMessage.hpp"
#include "ShortEquityAndIndexQuoteMessage.hpp"
#include "UnderlyingValueLastSaleMessage.hpp"
#include "UnderlyingValueBidAndOfferMessage.hpp"
#include "../json/messages/administrative_message_json.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

inline std::ostream& operator<<(std::ostream& os, const block_header& value) {
    os << "version=" << static_cast<unsigned>(value.version.get().value())
       << ",block_size=" << value.block_size.get().value()
       << ",data_feed_indicator=\"" << obi_output::data_feed_indicator::to_string(value.data_feed_indicator.get().value()) << '"'
       << ",retransmission_indicator=\"" << obi_output::retransmission_indicator::to_string(value.retransmission_indicator.get().value()) << '"'
       << ",session_indicator=\"" << obi_output::session_indicator::to_string(value.session_indicator.get().value()) << '"'
       << ",block_sequence_number=" << value.block_sequence_number.get().value()
       << ",messages_in_block=" << static_cast<unsigned>(value.messages_in_block.get().value())
       << ",block_timestamp.seconds=" << value.block_timestamp.seconds.get().value()
       << ",block_timestamp.nanoseconds=" << value.block_timestamp.nanoseconds.get().value()
       << ",block_checksum=" << value.block_checksum.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "participant_id=\"" << obi_output::participant_id::to_string(value.participant_id.get().value()) << '"'
       << ",message_category=\"" << obi_output::message_category::to_string(value.message_category.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const administrative_category& value) {
    os << "administrative_message_type=\"" << obi_output::administrative_message_type::to_string(value.administrative_message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const block_timestamp& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const best_bid_appendage& value) {
    os << "best_bid_participant_id=\"" << obi_output::best_bid_participant_id::to_string(value.best_bid_participant_id.get().value()) << '"'
       << ",best_bid_denominator_code=\"" << obi_output::best_bid_denominator_code::to_string(value.best_bid_denominator_code.get().value()) << '"'
       << ",best_bid_price=" << value.best_bid_price.get().value()
       << ",best_bid_size=" << value.best_bid_size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const best_offer_appendage& value) {
    os << "best_offer_participant_id=\"" << obi_output::best_offer_participant_id::to_string(value.best_offer_participant_id.get().value()) << '"'
       << ",best_offer_denominator_code=\"" << obi_output::best_offer_denominator_code::to_string(value.best_offer_denominator_code.get().value()) << '"'
       << ",best_offer_price=" << value.best_offer_price.get().value()
       << ",best_offer_size=" << value.best_offer_size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const best_bid_and_offer_appendage& value) {
    os << "best_bid_participant_id=\"" << obi_output::best_bid_participant_id::to_string(value.best_bid_participant_id.get().value()) << '"'
       << ",best_bid_denominator_code=\"" << obi_output::best_bid_denominator_code::to_string(value.best_bid_denominator_code.get().value()) << '"'
       << ",best_bid_price=" << value.best_bid_price.get().value()
       << ",best_bid_size=" << value.best_bid_size.get().value()
       << ",best_offer_participant_id=\"" << obi_output::best_offer_participant_id::to_string(value.best_offer_participant_id.get().value()) << '"'
       << ",best_offer_denominator_code=\"" << obi_output::best_offer_denominator_code::to_string(value.best_offer_denominator_code.get().value()) << '"'
       << ",best_offer_price=" << value.best_offer_price.get().value()
       << ",best_offer_size=" << value.best_offer_size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const administrative_message& msg) {
    os << "message_indicator=\"" << msg.fields.message_indicator.get().value() << '"'
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",message_data_length=" << msg.fields.message_data_length.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const control_message& msg) {
    os << "message_indicator=\"" << msg.fields.message_indicator.get().value() << '"'
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const equity_and_index_last_sale_message& msg) {
    os << "message_indicator=\"" << msg.fields.message_indicator.get().value() << '"'
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",expiration_block.expiration_month=\"" << obi_output::expiration_month::to_string(msg.fields.expiration_block.expiration_month.get().value()) << '"'
       << ",expiration_block.expiration_day=" << static_cast<unsigned>(msg.fields.expiration_block.expiration_day.get().value())
       << ",expiration_block.expiration_year=" << static_cast<unsigned>(msg.fields.expiration_block.expiration_year.get().value())
       << ",strike_price_denominator_code=\"" << obi_output::strike_price_denominator_code::to_string(msg.fields.strike_price_denominator_code.get().value()) << '"'
       << ",strike_price=" << msg.fields.strike_price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",premium_price_denominator_code=\"" << obi_output::premium_price_denominator_code::to_string(msg.fields.premium_price_denominator_code.get().value()) << '"'
       << ",premium_price=" << msg.fields.premium_price.get().value()
       << ",trade_identifier=" << msg.fields.trade_identifier.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const open_interest_message& msg) {
    os << "message_indicator=\"" << msg.fields.message_indicator.get().value() << '"'
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",expiration_block.expiration_month=\"" << obi_output::expiration_month::to_string(msg.fields.expiration_block.expiration_month.get().value()) << '"'
       << ",expiration_block.expiration_day=" << static_cast<unsigned>(msg.fields.expiration_block.expiration_day.get().value())
       << ",expiration_block.expiration_year=" << static_cast<unsigned>(msg.fields.expiration_block.expiration_year.get().value())
       << ",strike_price_denominator_code=\"" << obi_output::strike_price_denominator_code::to_string(msg.fields.strike_price_denominator_code.get().value()) << '"'
       << ",strike_price=" << msg.fields.strike_price.get().value()
       << ",open_interest_volume=" << msg.fields.open_interest_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const equity_and_index_end_of_day_summary_message& msg) {
    os << "message_indicator=\"" << msg.fields.message_indicator.get().value() << '"'
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",expiration_block.expiration_month=\"" << obi_output::expiration_month::to_string(msg.fields.expiration_block.expiration_month.get().value()) << '"'
       << ",expiration_block.expiration_day=" << static_cast<unsigned>(msg.fields.expiration_block.expiration_day.get().value())
       << ",expiration_block.expiration_year=" << static_cast<unsigned>(msg.fields.expiration_block.expiration_year.get().value())
       << ",strike_price_denominator_code=\"" << obi_output::strike_price_denominator_code::to_string(msg.fields.strike_price_denominator_code.get().value()) << '"'
       << ",strike_price=" << msg.fields.strike_price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",open_interest_volume=" << msg.fields.open_interest_volume.get().value()
       << ",premium_price_denominator_code=\"" << obi_output::premium_price_denominator_code::to_string(msg.fields.premium_price_denominator_code.get().value()) << '"'
       << ",open_price=" << msg.fields.open_price.get().value()
       << ",high_price=" << msg.fields.high_price.get().value()
       << ",low_price=" << msg.fields.low_price.get().value()
       << ",last_price=" << msg.fields.last_price.get().value()
       << ",net_change=" << msg.fields.net_change.get().value()
       << ",underlying_price_denominator_code=\"" << obi_output::underlying_price_denominator_code::to_string(msg.fields.underlying_price_denominator_code.get().value()) << '"'
       << ",underlying_price=" << msg.fields.underlying_price.get().value()
       << ",bid_price=" << msg.fields.bid_price.get().value()
       << ",offer_price=" << msg.fields.offer_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const long_equity_and_index_quote_message& msg) {
    os << "bbo_indicator=\"" << obi_output::bbo_indicator::to_string(msg.fields.bbo_indicator.get().value()) << '"'
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",expiration_block.expiration_month=\"" << obi_output::expiration_month::to_string(msg.fields.expiration_block.expiration_month.get().value()) << '"'
       << ",expiration_block.expiration_day=" << static_cast<unsigned>(msg.fields.expiration_block.expiration_day.get().value())
       << ",expiration_block.expiration_year=" << static_cast<unsigned>(msg.fields.expiration_block.expiration_year.get().value())
       << ",strike_price_denominator_code=\"" << obi_output::strike_price_denominator_code::to_string(msg.fields.strike_price_denominator_code.get().value()) << '"'
       << ",strike_price=" << msg.fields.strike_price.get().value()
       << ",premium_price_denominator_code=\"" << obi_output::premium_price_denominator_code::to_string(msg.fields.premium_price_denominator_code.get().value()) << '"'
       << ",bid_price=" << msg.fields.bid_price.get().value()
       << ",bid_size=" << msg.fields.bid_size.get().value()
       << ",offer_price=" << msg.fields.offer_price.get().value()
       << ",offer_size=" << msg.fields.offer_size.get().value()
       ;
    {
        auto desc = msg.describe_appendages();
        if (desc.has_bid || desc.has_offer) {
            if (desc.has_bid == true && desc.has_offer == false) {
                if (auto* a = msg.best_bid_appendage()) os << ",best_bid_appendage={" << *a << "}";
            }
            if (desc.has_bid == false && desc.has_offer == true) {
                if (auto* a = msg.best_offer_appendage()) os << ",best_offer_appendage={" << *a << "}";
            }
            if (desc.has_bid == true && desc.has_offer == true) {
                if (auto* a = msg.best_bid_and_offer_appendage()) os << ",best_bid_and_offer_appendage={" << *a << "}";
            }
        }
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const short_equity_and_index_quote_message& msg) {
    os << "bbo_indicator=\"" << obi_output::bbo_indicator::to_string(msg.fields.bbo_indicator.get().value()) << '"'
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol_short=\"" << msg.fields.security_symbol_short.get_trimmed().value() << '"'
       << ",expiration_block.expiration_month=\"" << obi_output::expiration_month::to_string(msg.fields.expiration_block.expiration_month.get().value()) << '"'
       << ",expiration_block.expiration_day=" << static_cast<unsigned>(msg.fields.expiration_block.expiration_day.get().value())
       << ",expiration_block.expiration_year=" << static_cast<unsigned>(msg.fields.expiration_block.expiration_year.get().value())
       << ",strike_price_short=" << msg.fields.strike_price_short.get().value()
       << ",bid_price_short=" << msg.fields.bid_price_short.get().value()
       << ",bid_size_short=" << msg.fields.bid_size_short.get().value()
       << ",offer_price_short=" << msg.fields.offer_price_short.get().value()
       << ",offer_size_short=" << msg.fields.offer_size_short.get().value()
       ;
    {
        auto desc = msg.describe_appendages();
        if (desc.has_bid || desc.has_offer) {
            if (desc.has_bid == true && desc.has_offer == false) {
                if (auto* a = msg.best_bid_appendage()) os << ",best_bid_appendage={" << *a << "}";
            }
            if (desc.has_bid == false && desc.has_offer == true) {
                if (auto* a = msg.best_offer_appendage()) os << ",best_offer_appendage={" << *a << "}";
            }
            if (desc.has_bid == true && desc.has_offer == true) {
                if (auto* a = msg.best_bid_and_offer_appendage()) os << ",best_bid_and_offer_appendage={" << *a << "}";
            }
        }
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const underlying_value_last_sale_message& msg) {
    os << "message_indicator=\"" << msg.fields.message_indicator.get().value() << '"'
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",index_value_denominator_code=\"" << obi_output::index_value_denominator_code::to_string(msg.fields.index_value_denominator_code.get().value()) << '"'
       << ",index_value=" << msg.fields.index_value.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const underlying_value_bid_and_offer_message& msg) {
    os << "message_indicator=\"" << msg.fields.message_indicator.get().value() << '"'
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",index_value_denominator_code=\"" << obi_output::index_value_denominator_code::to_string(msg.fields.index_value_denominator_code.get().value()) << '"'
       << ",bid_index_value=" << msg.fields.bid_index_value.get().value()
       << ",offer_index_value=" << msg.fields.offer_index_value.get().value()
       ;
    return os;
}

}
