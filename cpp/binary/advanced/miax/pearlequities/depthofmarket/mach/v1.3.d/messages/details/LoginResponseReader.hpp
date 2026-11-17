// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/details/LoginResponseReader.hpp
#pragma once

#include "LoginResponseWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;


inline external_count_iterator<login_response_login_matching_engine_entry> read_login_matching_engine(const login_response& msg) {
    return { msg.tail_begin(), msg.fields.number_of_matching_engines.get().value(), msg.tail_end() };
}

}
