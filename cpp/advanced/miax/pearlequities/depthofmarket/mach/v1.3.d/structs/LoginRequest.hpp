#pragma once

#include <cstddef>
#include "../types/EsesmVersion.hpp"
#include "../types/Username.hpp"
#include "../types/ComputerId.hpp"
#include "../types/ApplicationProtocol.hpp"
#include "../types/RequestedTradingSessionId.hpp"
#include "../types/RequestedSequenceNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

struct login_request {

    mach_depthofmarket::esesm_version esesm_version;
    mach_depthofmarket::username username;
    mach_depthofmarket::computer_id computer_id;
    mach_depthofmarket::application_protocol application_protocol;
    mach_depthofmarket::requested_trading_session_id requested_trading_session_id;
    mach_depthofmarket::requested_sequence_number requested_sequence_number;

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
static_assert(offsetof(login_request, esesm_version) == 0, "unexpected offset of login_request::esesm_version");
static_assert(offsetof(login_request, username) == 5, "unexpected offset of login_request::username");
static_assert(offsetof(login_request, computer_id) == 10, "unexpected offset of login_request::computer_id");
static_assert(offsetof(login_request, application_protocol) == 18, "unexpected offset of login_request::application_protocol");
static_assert(offsetof(login_request, requested_trading_session_id) == 26, "unexpected offset of login_request::requested_trading_session_id");
static_assert(offsetof(login_request, requested_sequence_number) == 27, "unexpected offset of login_request::requested_sequence_number");
static_assert(sizeof(login_request) == 35, "unexpected sizeof login_request");

#pragma pack(pop)
}
