// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/LoginResponse.hpp
#pragma once

#include <cstddef>
#include "../structs/EsesmPacketHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/NumberOfMatchingEngines.hpp"
#include "../types/LoginStatus.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/HighestSequenceNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)
struct login_response_login_matching_engine_entry {
    mach_depthofmarket::login_status login_status;
    mach_depthofmarket::trading_session_id trading_session_id;
    mach_depthofmarket::highest_sequence_number highest_sequence_number;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Login Response
struct login_response {

    struct fields_type {
        mach_depthofmarket::number_of_matching_engines number_of_matching_engines;
    };

    mach_depthofmarket::esesm_packet_header header = {std::uint16_t(sizeof(mach_depthofmarket::esesm_packet_header) + sizeof(fields_type) - 2), esesm_packet_type::enum_type::login_response};

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
    external_count_iterator<login_response_login_matching_engine_entry> login_matching_engine() const {
        return { tail_begin(), fields.number_of_matching_engines.get().value(), tail_end() };
    }


    // parse method
    static login_response* parse(std::byte* buffer) {
        return reinterpret_cast<login_response*>(buffer);
    }

    // parse method const
    static const login_response* parse(const std::byte* buffer) {
        return reinterpret_cast<const login_response*>(buffer);
    }

};

// layout verification
static_assert(offsetof(login_response::fields_type, number_of_matching_engines) == 0, "unexpected offset of login_response::fields_type::number_of_matching_engines");
static_assert(sizeof(login_response::fields_type) == 1, "unexpected sizeof login_response::fields_type");

#pragma pack(pop)
}

#include "details/LoginResponseWriter.hpp"
#include "details/LoginResponseReader.hpp"
