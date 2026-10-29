#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/ClosePrice.hpp"
#include "../types/PrevClosePrice.hpp"
#include "../types/UpperCktLimit.hpp"
#include "../types/LowerCktLimit.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Instrument Info Message
struct instrument_info_message {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::close_price close_price;
        fbe_eobi::prev_close_price prev_close_price;
        fbe_eobi::upper_ckt_limit upper_ckt_limit;
        fbe_eobi::lower_ckt_limit lower_ckt_limit;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::instrument_info_message, {}};

    fields_type fields;

    // parse method
    static instrument_info_message* parse(std::byte* buffer) {
        return reinterpret_cast<instrument_info_message*>(buffer);
    }

    // parse method const
    static const instrument_info_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const instrument_info_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(instrument_info_message::fields_type, security_id) == 0, "unexpected offset of instrument_info_message::fields_type::security_id");
static_assert(offsetof(instrument_info_message::fields_type, close_price) == 8, "unexpected offset of instrument_info_message::fields_type::close_price");
static_assert(offsetof(instrument_info_message::fields_type, prev_close_price) == 16, "unexpected offset of instrument_info_message::fields_type::prev_close_price");
static_assert(offsetof(instrument_info_message::fields_type, upper_ckt_limit) == 24, "unexpected offset of instrument_info_message::fields_type::upper_ckt_limit");
static_assert(offsetof(instrument_info_message::fields_type, lower_ckt_limit) == 32, "unexpected offset of instrument_info_message::fields_type::lower_ckt_limit");
static_assert(sizeof(instrument_info_message::fields_type) == 40, "unexpected sizeof instrument_info_message::fields_type");
static_assert(sizeof(instrument_info_message) == sizeof(fbe_eobi::message_header) + 40, "unexpected sizeof instrument_info_message");

#pragma pack(pop)
}
