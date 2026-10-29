#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/Eop.hpp"
#include "../types/Eos.hpp"
#include "../types/EopType.hpp"
#include "../types/LegalMarket.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

// Expected Opening Price And Size Message
struct expected_opening_price_and_size_message {

    struct fields_type {
        csm_marketdatafeed::class_key class_key;
        csm_marketdatafeed::security_id security_id;
        csm_marketdatafeed::eop eop;
        csm_marketdatafeed::eos eos;
        csm_marketdatafeed::eop_type eop_type;
        csm_marketdatafeed::legal_market legal_market;
    };

    csm_marketdatafeed::message_header header = {{}, template_id::enum_type::expected_opening_price_and_size_message, {}, {}};

    fields_type fields;

    // parse method
    static expected_opening_price_and_size_message* parse(std::byte* buffer) {
        return reinterpret_cast<expected_opening_price_and_size_message*>(buffer);
    }

    // parse method const
    static const expected_opening_price_and_size_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const expected_opening_price_and_size_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(expected_opening_price_and_size_message::fields_type, class_key) == 0, "unexpected offset of expected_opening_price_and_size_message::fields_type::class_key");
static_assert(offsetof(expected_opening_price_and_size_message::fields_type, security_id) == 4, "unexpected offset of expected_opening_price_and_size_message::fields_type::security_id");
static_assert(offsetof(expected_opening_price_and_size_message::fields_type, eop) == 8, "unexpected offset of expected_opening_price_and_size_message::fields_type::eop");
static_assert(offsetof(expected_opening_price_and_size_message::fields_type, eos) == 13, "unexpected offset of expected_opening_price_and_size_message::fields_type::eos");
static_assert(offsetof(expected_opening_price_and_size_message::fields_type, eop_type) == 17, "unexpected offset of expected_opening_price_and_size_message::fields_type::eop_type");
static_assert(offsetof(expected_opening_price_and_size_message::fields_type, legal_market) == 18, "unexpected offset of expected_opening_price_and_size_message::fields_type::legal_market");
static_assert(sizeof(expected_opening_price_and_size_message::fields_type) == 19, "unexpected sizeof expected_opening_price_and_size_message::fields_type");
static_assert(sizeof(expected_opening_price_and_size_message) == sizeof(csm_marketdatafeed::message_header) + 19, "unexpected sizeof expected_opening_price_and_size_message");

#pragma pack(pop)
}
