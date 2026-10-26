#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/MessageIndicator.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/Reserved1.hpp"
#include "../types/IndexValueDenominatorCode.hpp"
#include "../types/IndexValue.hpp"
#include "../types/Reserved4.hpp"
#include "../types/UnderlyingValueMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

// Underlying Value Last Sale Message
struct underlying_value_last_sale_message {

    struct fields_type {
        obi_output::message_indicator message_indicator;
        obi_output::transaction_id transaction_id;
        obi_output::participant_reference_number participant_reference_number;
        obi_output::security_symbol security_symbol;
        obi_output::reserved_1 reserved_1;
        obi_output::index_value_denominator_code index_value_denominator_code;
        obi_output::index_value index_value;
        obi_output::reserved_4 reserved_4;
    };

    obi_output::message_header header = {{}, message_category::enum_type::underlying_value};
    obi_output::underlying_value_message_type underlying_value_message_type = obi_output::underlying_value_message_type::enum_type::index_based_on_last_sale;

    fields_type fields;

    // parse method
    static underlying_value_last_sale_message* parse(std::byte* buffer) {
        return reinterpret_cast<underlying_value_last_sale_message*>(buffer);
    }

    // parse method const
    static const underlying_value_last_sale_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const underlying_value_last_sale_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(underlying_value_last_sale_message::fields_type, message_indicator) == 0, "unexpected offset of underlying_value_last_sale_message::fields_type::message_indicator");
static_assert(offsetof(underlying_value_last_sale_message::fields_type, transaction_id) == 1, "unexpected offset of underlying_value_last_sale_message::fields_type::transaction_id");
static_assert(offsetof(underlying_value_last_sale_message::fields_type, participant_reference_number) == 5, "unexpected offset of underlying_value_last_sale_message::fields_type::participant_reference_number");
static_assert(offsetof(underlying_value_last_sale_message::fields_type, security_symbol) == 9, "unexpected offset of underlying_value_last_sale_message::fields_type::security_symbol");
static_assert(offsetof(underlying_value_last_sale_message::fields_type, reserved_1) == 14, "unexpected offset of underlying_value_last_sale_message::fields_type::reserved_1");
static_assert(offsetof(underlying_value_last_sale_message::fields_type, index_value_denominator_code) == 15, "unexpected offset of underlying_value_last_sale_message::fields_type::index_value_denominator_code");
static_assert(offsetof(underlying_value_last_sale_message::fields_type, index_value) == 16, "unexpected offset of underlying_value_last_sale_message::fields_type::index_value");
static_assert(offsetof(underlying_value_last_sale_message::fields_type, reserved_4) == 20, "unexpected offset of underlying_value_last_sale_message::fields_type::reserved_4");
static_assert(sizeof(underlying_value_last_sale_message::fields_type) == 24, "unexpected sizeof underlying_value_last_sale_message::fields_type");
static_assert(sizeof(underlying_value_last_sale_message) == sizeof(obi_output::message_header) + sizeof(obi_output::underlying_value_message_type) + 24, "unexpected sizeof underlying_value_last_sale_message");

#pragma pack(pop)
}
