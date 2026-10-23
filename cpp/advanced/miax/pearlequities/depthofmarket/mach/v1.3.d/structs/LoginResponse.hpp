#pragma once

#include <cstddef>
#include "../types/NumberOfMatchingEngines.hpp"
#include "../types/LoginStatus.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/HighestSequenceNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

struct login_response {

    mach_depthofmarket::number_of_matching_engines number_of_matching_engines;
    mach_depthofmarket::login_status login_status;
    mach_depthofmarket::trading_session_id trading_session_id;
    mach_depthofmarket::highest_sequence_number highest_sequence_number;

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
static_assert(offsetof(login_response, number_of_matching_engines) == 0, "unexpected offset of login_response::number_of_matching_engines");
static_assert(offsetof(login_response, login_status) == 1, "unexpected offset of login_response::login_status");
static_assert(offsetof(login_response, trading_session_id) == 2, "unexpected offset of login_response::trading_session_id");
static_assert(offsetof(login_response, highest_sequence_number) == 3, "unexpected offset of login_response::highest_sequence_number");
static_assert(sizeof(login_response) == 11, "unexpected sizeof login_response");

#pragma pack(pop)
}
