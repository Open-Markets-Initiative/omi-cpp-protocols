#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/MessageIndicator.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/ExpirationBlock.hpp"
#include "../types/StrikePriceDenominatorCode.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/Volume.hpp"
#include "../types/OpenInterestVolume.hpp"
#include "../types/PremiumPriceDenominatorCode.hpp"
#include "../types/OpenPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/LastPrice.hpp"
#include "../types/NetChange.hpp"
#include "../types/UnderlyingPriceDenominatorCode.hpp"
#include "../types/UnderlyingPrice.hpp"
#include "../types/BidPrice.hpp"
#include "../types/OfferPrice.hpp"
#include "../types/EquityAndIndexEndOfDaySummaryMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

// Equity And Index End Of Day Summary Message
struct equity_and_index_end_of_day_summary_message {

    struct fields_type {
        obi_output::message_indicator message_indicator;
        obi_output::transaction_id transaction_id;
        obi_output::participant_reference_number participant_reference_number;
        obi_output::security_symbol security_symbol;
        obi_output::reserved_1 reserved_1;
        obi_output::expiration_block expiration_block;
        obi_output::strike_price_denominator_code strike_price_denominator_code;
        obi_output::strike_price strike_price;
        obi_output::volume volume;
        obi_output::open_interest_volume open_interest_volume;
        obi_output::premium_price_denominator_code premium_price_denominator_code;
        obi_output::open_price open_price;
        obi_output::high_price high_price;
        obi_output::low_price low_price;
        obi_output::last_price last_price;
        obi_output::net_change net_change;
        obi_output::underlying_price_denominator_code underlying_price_denominator_code;
        obi_output::underlying_price underlying_price;
        obi_output::bid_price bid_price;
        obi_output::offer_price offer_price;
    };

    obi_output::message_header header = {{}, message_category::enum_type::equity_and_index_end_of_day_summary};
    obi_output::equity_and_index_end_of_day_summary_message_type equity_and_index_end_of_day_summary_message_type = obi_output::equity_and_index_end_of_day_summary_message_type::enum_type::equity_and_index_end_of_day_summary;

    fields_type fields;

    // parse method
    static equity_and_index_end_of_day_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<equity_and_index_end_of_day_summary_message*>(buffer);
    }

    // parse method const
    static const equity_and_index_end_of_day_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const equity_and_index_end_of_day_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, message_indicator) == 0, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::message_indicator");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, transaction_id) == 1, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::transaction_id");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, participant_reference_number) == 5, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::participant_reference_number");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, security_symbol) == 9, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::security_symbol");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, reserved_1) == 14, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::reserved_1");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, expiration_block) == 15, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::expiration_block");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, strike_price_denominator_code) == 18, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::strike_price_denominator_code");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, strike_price) == 19, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::strike_price");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, volume) == 23, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::volume");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, open_interest_volume) == 27, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::open_interest_volume");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, premium_price_denominator_code) == 31, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::premium_price_denominator_code");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, open_price) == 32, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::open_price");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, high_price) == 36, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::high_price");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, low_price) == 40, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::low_price");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, last_price) == 44, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::last_price");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, net_change) == 48, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::net_change");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, underlying_price_denominator_code) == 52, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::underlying_price_denominator_code");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, underlying_price) == 53, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::underlying_price");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, bid_price) == 61, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::bid_price");
static_assert(offsetof(equity_and_index_end_of_day_summary_message::fields_type, offer_price) == 65, "unexpected offset of equity_and_index_end_of_day_summary_message::fields_type::offer_price");
static_assert(sizeof(equity_and_index_end_of_day_summary_message::fields_type) == 69, "unexpected sizeof equity_and_index_end_of_day_summary_message::fields_type");
static_assert(sizeof(equity_and_index_end_of_day_summary_message) == sizeof(obi_output::message_header) + sizeof(obi_output::equity_and_index_end_of_day_summary_message_type) + 69, "unexpected sizeof equity_and_index_end_of_day_summary_message");

#pragma pack(pop)
}
