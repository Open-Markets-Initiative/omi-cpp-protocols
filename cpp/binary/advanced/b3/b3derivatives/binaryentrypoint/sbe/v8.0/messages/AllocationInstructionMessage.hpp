#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../types/AllocId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/AllocTransType.hpp"
#include "../types/AllocType.hpp"
#include "../types/AllocNoOrdersType.hpp"
#include "../types/Quantity.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/TradeId.hpp"
#include "../types/TradeDateOptional.hpp"
#include "../types/IndividualAllocId.hpp"
#include "../types/AllocAccount.hpp"
#include "../types/AllocQty.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;


#pragma pack(push, 1)

// Allocation Instruction Message
struct allocation_instruction_message {

    struct fields_type {
        sbe_binaryentrypoint::inbound_business_header inbound_business_header;
        sbe_binaryentrypoint::alloc_id alloc_id;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::alloc_trans_type alloc_trans_type;
        sbe_binaryentrypoint::alloc_type alloc_type;
        sbe_binaryentrypoint::alloc_no_orders_type alloc_no_orders_type;
        sbe_binaryentrypoint::quantity quantity;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::entering_trader entering_trader;
        sbe_binaryentrypoint::trade_id trade_id;
        sbe_binaryentrypoint::trade_date_optional trade_date_optional;
        sbe_binaryentrypoint::individual_alloc_id individual_alloc_id;
        sbe_binaryentrypoint::alloc_account alloc_account;
        sbe_binaryentrypoint::alloc_qty alloc_qty;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_binaryentrypoint::simple_open_framing_header) - sizeof(fields_type) - sizeof(sbe_binaryentrypoint::message_header);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_length.get().value();
        return sz == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_binaryentrypoint::simple_open_framing_header) - sizeof(fields_type) - sizeof(sbe_binaryentrypoint::message_header));
    }

    // sequential access to variable-length regions
    sbe_var_data desk_id() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data memo(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static allocation_instruction_message* parse(std::byte* buffer) {
        return reinterpret_cast<allocation_instruction_message*>(buffer);
    }

    // parse method const
    static const allocation_instruction_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const allocation_instruction_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(allocation_instruction_message::fields_type, inbound_business_header) == 0, "unexpected offset of allocation_instruction_message::fields_type::inbound_business_header");
static_assert(offsetof(allocation_instruction_message::fields_type, alloc_id) == 18, "unexpected offset of allocation_instruction_message::fields_type::alloc_id");
static_assert(offsetof(allocation_instruction_message::fields_type, security_id) == 26, "unexpected offset of allocation_instruction_message::fields_type::security_id");
static_assert(offsetof(allocation_instruction_message::fields_type, alloc_trans_type) == 34, "unexpected offset of allocation_instruction_message::fields_type::alloc_trans_type");
static_assert(offsetof(allocation_instruction_message::fields_type, alloc_type) == 35, "unexpected offset of allocation_instruction_message::fields_type::alloc_type");
static_assert(offsetof(allocation_instruction_message::fields_type, alloc_no_orders_type) == 36, "unexpected offset of allocation_instruction_message::fields_type::alloc_no_orders_type");
static_assert(offsetof(allocation_instruction_message::fields_type, quantity) == 37, "unexpected offset of allocation_instruction_message::fields_type::quantity");
static_assert(offsetof(allocation_instruction_message::fields_type, sender_location) == 45, "unexpected offset of allocation_instruction_message::fields_type::sender_location");
static_assert(offsetof(allocation_instruction_message::fields_type, entering_trader) == 55, "unexpected offset of allocation_instruction_message::fields_type::entering_trader");
static_assert(offsetof(allocation_instruction_message::fields_type, trade_id) == 60, "unexpected offset of allocation_instruction_message::fields_type::trade_id");
static_assert(offsetof(allocation_instruction_message::fields_type, trade_date_optional) == 64, "unexpected offset of allocation_instruction_message::fields_type::trade_date_optional");
static_assert(offsetof(allocation_instruction_message::fields_type, individual_alloc_id) == 66, "unexpected offset of allocation_instruction_message::fields_type::individual_alloc_id");
static_assert(offsetof(allocation_instruction_message::fields_type, alloc_account) == 74, "unexpected offset of allocation_instruction_message::fields_type::alloc_account");
static_assert(offsetof(allocation_instruction_message::fields_type, alloc_qty) == 78, "unexpected offset of allocation_instruction_message::fields_type::alloc_qty");
static_assert(sizeof(allocation_instruction_message::fields_type) == 86, "unexpected sizeof allocation_instruction_message::fields_type");

#pragma pack(pop)
}

#include "details/AllocationInstructionMessageWriter.hpp"
#include "details/AllocationInstructionMessageReader.hpp"
