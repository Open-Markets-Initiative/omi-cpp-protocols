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
#include "../types/OpenInterestVolume.hpp"
#include "../types/OpenInterestMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

// Open Interest Message
struct open_interest_message {

    struct fields_type {
        obi_output::message_indicator message_indicator;
        obi_output::transaction_id transaction_id;
        obi_output::participant_reference_number participant_reference_number;
        obi_output::security_symbol security_symbol;
        obi_output::reserved_1 reserved_1;
        obi_output::expiration_block expiration_block;
        obi_output::strike_price_denominator_code strike_price_denominator_code;
        obi_output::strike_price strike_price;
        obi_output::open_interest_volume open_interest_volume;
    };

    obi_output::message_header header = {{}, message_category::enum_type::open_interest};
    obi_output::open_interest_message_type open_interest_message_type = obi_output::open_interest_message_type::enum_type::open_interest;

    fields_type fields;

    // parse method
    static open_interest_message* parse(std::byte* buffer) {
        return reinterpret_cast<open_interest_message*>(buffer);
    }

    // parse method const
    static const open_interest_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const open_interest_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(open_interest_message::fields_type, message_indicator) == 0, "unexpected offset of open_interest_message::fields_type::message_indicator");
static_assert(offsetof(open_interest_message::fields_type, transaction_id) == 1, "unexpected offset of open_interest_message::fields_type::transaction_id");
static_assert(offsetof(open_interest_message::fields_type, participant_reference_number) == 5, "unexpected offset of open_interest_message::fields_type::participant_reference_number");
static_assert(offsetof(open_interest_message::fields_type, security_symbol) == 9, "unexpected offset of open_interest_message::fields_type::security_symbol");
static_assert(offsetof(open_interest_message::fields_type, reserved_1) == 14, "unexpected offset of open_interest_message::fields_type::reserved_1");
static_assert(offsetof(open_interest_message::fields_type, expiration_block) == 15, "unexpected offset of open_interest_message::fields_type::expiration_block");
static_assert(offsetof(open_interest_message::fields_type, strike_price_denominator_code) == 18, "unexpected offset of open_interest_message::fields_type::strike_price_denominator_code");
static_assert(offsetof(open_interest_message::fields_type, strike_price) == 19, "unexpected offset of open_interest_message::fields_type::strike_price");
static_assert(offsetof(open_interest_message::fields_type, open_interest_volume) == 23, "unexpected offset of open_interest_message::fields_type::open_interest_volume");
static_assert(sizeof(open_interest_message::fields_type) == 27, "unexpected sizeof open_interest_message::fields_type");
static_assert(sizeof(open_interest_message) == sizeof(obi_output::message_header) + sizeof(obi_output::open_interest_message_type) + 27, "unexpected sizeof open_interest_message");

#pragma pack(pop)
}
