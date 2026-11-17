// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/TradingSessionUpdate.hpp
#pragma once

#include <cstddef>
#include "../structs/EsesmPacketHeader.hpp"
#include "../types/MatchingEngineId.hpp"
#include "../types/TradingSessionId.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// Trading Session Update
struct trading_session_update {

    struct fields_type {
        mach_depthofmarket::matching_engine_id matching_engine_id;
        mach_depthofmarket::trading_session_id trading_session_id;
    };

    mach_depthofmarket::esesm_packet_header header = {std::uint16_t(sizeof(mach_depthofmarket::esesm_packet_header) + sizeof(fields_type) - 2), esesm_packet_type::enum_type::trading_session_update};

    fields_type fields;

    // parse method
    static trading_session_update* parse(std::byte* buffer) {
        return reinterpret_cast<trading_session_update*>(buffer);
    }

    // parse method const
    static const trading_session_update* parse(const std::byte* buffer) {
        return reinterpret_cast<const trading_session_update*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trading_session_update::fields_type, matching_engine_id) == 0, "unexpected offset of trading_session_update::fields_type::matching_engine_id");
static_assert(offsetof(trading_session_update::fields_type, trading_session_id) == 1, "unexpected offset of trading_session_update::fields_type::trading_session_id");
static_assert(sizeof(trading_session_update::fields_type) == 2, "unexpected sizeof trading_session_update::fields_type");
static_assert(sizeof(trading_session_update) == sizeof(mach_depthofmarket::esesm_packet_header) + 2, "unexpected sizeof trading_session_update");

#pragma pack(pop)
}
