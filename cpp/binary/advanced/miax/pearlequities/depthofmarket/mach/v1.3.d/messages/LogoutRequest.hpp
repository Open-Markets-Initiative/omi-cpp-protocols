// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/LogoutRequest.hpp
#pragma once

#include <cstddef>
#include "../structs/EsesmPacketHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/LogoutReason.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;


#pragma pack(push, 1)

// Logout Request
struct logout_request {

    struct fields_type {
        mach_depthofmarket::logout_reason logout_reason;
    };

    mach_depthofmarket::esesm_packet_header header = {std::uint16_t(sizeof(mach_depthofmarket::esesm_packet_header) + sizeof(fields_type) - 2), esesm_packet_type::enum_type::logout_request};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(mach_depthofmarket::esesm_packet_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.esesm_packet_length.get().value();
        return (sz + 2) == sizeof(mach_depthofmarket::esesm_packet_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + ((sz + 2) - sizeof(mach_depthofmarket::esesm_packet_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    external_var_data logout_text() const {
        return { tail_begin(), static_cast<std::size_t>(header.esesm_packet_length.get().value() - 2), tail_end() };
    }


    // parse method
    static logout_request* parse(std::byte* buffer) {
        return reinterpret_cast<logout_request*>(buffer);
    }

    // parse method const
    static const logout_request* parse(const std::byte* buffer) {
        return reinterpret_cast<const logout_request*>(buffer);
    }

};

// layout verification
static_assert(offsetof(logout_request::fields_type, logout_reason) == 0, "unexpected offset of logout_request::fields_type::logout_reason");
static_assert(sizeof(logout_request::fields_type) == 1, "unexpected sizeof logout_request::fields_type");

#pragma pack(pop)
}

#include "details/LogoutRequestWriter.hpp"
#include "details/LogoutRequestReader.hpp"
