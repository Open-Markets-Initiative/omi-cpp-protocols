// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/LoginRequest.hpp
#pragma once

#include <cstddef>
#include "../structs/EsesmPacketHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/EsesmVersion.hpp"
#include "../types/Username.hpp"
#include "../types/ComputerId.hpp"
#include "../types/ApplicationProtocol.hpp"
#include "../types/NumberOfMatchingEngines.hpp"
#include "../types/RequestedTradingSessionId.hpp"
#include "../types/RequestedSequenceNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)
struct login_request_requested_matching_engine_entry {
    mach_depthofmarket::requested_trading_session_id requested_trading_session_id;
    mach_depthofmarket::requested_sequence_number requested_sequence_number;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Login Request
struct login_request {

    struct fields_type {
        mach_depthofmarket::esesm_version esesm_version;
        mach_depthofmarket::username username;
        mach_depthofmarket::computer_id computer_id;
        mach_depthofmarket::application_protocol application_protocol;
        mach_depthofmarket::number_of_matching_engines number_of_matching_engines;
    };

    mach_depthofmarket::esesm_packet_header header = {std::uint16_t(sizeof(mach_depthofmarket::esesm_packet_header) + sizeof(fields_type) - 2), esesm_packet_type::enum_type::login_request};

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
    external_count_iterator<login_request_requested_matching_engine_entry> requested_matching_engine() const {
        return { tail_begin(), fields.number_of_matching_engines.get().value(), tail_end() };
    }


    // parse method
    static login_request* parse(std::byte* buffer) {
        return reinterpret_cast<login_request*>(buffer);
    }

    // parse method const
    static const login_request* parse(const std::byte* buffer) {
        return reinterpret_cast<const login_request*>(buffer);
    }

};

// layout verification
static_assert(offsetof(login_request::fields_type, esesm_version) == 0, "unexpected offset of login_request::fields_type::esesm_version");
static_assert(offsetof(login_request::fields_type, username) == 5, "unexpected offset of login_request::fields_type::username");
static_assert(offsetof(login_request::fields_type, computer_id) == 10, "unexpected offset of login_request::fields_type::computer_id");
static_assert(offsetof(login_request::fields_type, application_protocol) == 18, "unexpected offset of login_request::fields_type::application_protocol");
static_assert(offsetof(login_request::fields_type, number_of_matching_engines) == 26, "unexpected offset of login_request::fields_type::number_of_matching_engines");
static_assert(sizeof(login_request::fields_type) == 27, "unexpected sizeof login_request::fields_type");

#pragma pack(pop)
}

#include "details/LoginRequestWriter.hpp"
#include "details/LoginRequestReader.hpp"
