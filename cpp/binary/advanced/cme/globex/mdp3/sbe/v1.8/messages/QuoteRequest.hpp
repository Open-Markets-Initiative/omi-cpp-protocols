#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/TransactTime.hpp"
#include "../types/QuoteReqId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/Padding3.hpp"
#include "../types/Symbol.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderQty.hpp"
#include "../types/QuoteType.hpp"
#include "../types/Side.hpp"
#include "../types/Padding2.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

#pragma pack(push, 1)
struct quote_request_related_sym_groups_entry {
    sbe_mdp3::symbol symbol;
    sbe_mdp3::security_id security_id;
    sbe_mdp3::order_qty order_qty;
    sbe_mdp3::quote_type quote_type;
    sbe_mdp3::side side;
    sbe_mdp3::padding_2 padding_2;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Quote Request
struct quote_request {

    struct fields_type {
        sbe_mdp3::transact_time transact_time;
        sbe_mdp3::quote_req_id quote_req_id;
        sbe_mdp3::match_event_indicator match_event_indicator;
        sbe_mdp3::padding_3 padding_3;
    };

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header) + sizeof(fields_type)), {}};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<quote_request_related_sym_groups_entry, group_size> related_sym_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static quote_request* parse(std::byte* buffer) {
        return reinterpret_cast<quote_request*>(buffer);
    }

    // parse method const
    static const quote_request* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_request*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_request::fields_type, transact_time) == 0, "unexpected offset of quote_request::fields_type::transact_time");
static_assert(offsetof(quote_request::fields_type, quote_req_id) == 8, "unexpected offset of quote_request::fields_type::quote_req_id");
static_assert(offsetof(quote_request::fields_type, match_event_indicator) == 31, "unexpected offset of quote_request::fields_type::match_event_indicator");
static_assert(offsetof(quote_request::fields_type, padding_3) == 32, "unexpected offset of quote_request::fields_type::padding_3");
static_assert(sizeof(quote_request::fields_type) == 35, "unexpected sizeof quote_request::fields_type");

#pragma pack(pop)
}

#include "details/QuoteRequestWriter.hpp"
#include "details/QuoteRequestReader.hpp"
