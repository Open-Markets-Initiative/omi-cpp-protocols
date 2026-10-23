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
#include "../types/PremiumPriceDenominatorCode.hpp"
#include "../types/PremiumPrice.hpp"
#include "../types/TradeIdentifier.hpp"
#include "../types/Reserved4.hpp"
#include "../types/EquityAndIndexLastSaleMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

// Equity And Index Last Sale Message
struct equity_and_index_last_sale_message {

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
        obi_output::premium_price_denominator_code premium_price_denominator_code;
        obi_output::premium_price premium_price;
        obi_output::trade_identifier trade_identifier;
        obi_output::reserved_4 reserved_4;
    };

    obi_output::message_header header = {{}, message_category::enum_type::equity_and_index_last_sale};
    obi_output::equity_and_index_last_sale_message_type equity_and_index_last_sale_message_type = obi_output::equity_and_index_last_sale_message_type::enum_type::canc;

    fields_type fields;

    // parse method
    static equity_and_index_last_sale_message* parse(std::byte* buffer) {
        return reinterpret_cast<equity_and_index_last_sale_message*>(buffer);
    }

    // parse method const
    static const equity_and_index_last_sale_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const equity_and_index_last_sale_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, message_indicator) == 0, "unexpected offset of equity_and_index_last_sale_message::fields_type::message_indicator");
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, transaction_id) == 1, "unexpected offset of equity_and_index_last_sale_message::fields_type::transaction_id");
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, participant_reference_number) == 5, "unexpected offset of equity_and_index_last_sale_message::fields_type::participant_reference_number");
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, security_symbol) == 9, "unexpected offset of equity_and_index_last_sale_message::fields_type::security_symbol");
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, reserved_1) == 14, "unexpected offset of equity_and_index_last_sale_message::fields_type::reserved_1");
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, expiration_block) == 15, "unexpected offset of equity_and_index_last_sale_message::fields_type::expiration_block");
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, strike_price_denominator_code) == 18, "unexpected offset of equity_and_index_last_sale_message::fields_type::strike_price_denominator_code");
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, strike_price) == 19, "unexpected offset of equity_and_index_last_sale_message::fields_type::strike_price");
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, volume) == 23, "unexpected offset of equity_and_index_last_sale_message::fields_type::volume");
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, premium_price_denominator_code) == 27, "unexpected offset of equity_and_index_last_sale_message::fields_type::premium_price_denominator_code");
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, premium_price) == 28, "unexpected offset of equity_and_index_last_sale_message::fields_type::premium_price");
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, trade_identifier) == 32, "unexpected offset of equity_and_index_last_sale_message::fields_type::trade_identifier");
static_assert(offsetof(equity_and_index_last_sale_message::fields_type, reserved_4) == 36, "unexpected offset of equity_and_index_last_sale_message::fields_type::reserved_4");
static_assert(sizeof(equity_and_index_last_sale_message::fields_type) == 40, "unexpected sizeof equity_and_index_last_sale_message::fields_type");
static_assert(sizeof(equity_and_index_last_sale_message) == sizeof(obi_output::message_header) + sizeof(obi_output::equity_and_index_last_sale_message_type) + 40, "unexpected sizeof equity_and_index_last_sale_message");

#pragma pack(pop)
}
