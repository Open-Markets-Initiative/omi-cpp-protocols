// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: messages/details/PositionMaintenanceRequestMessageReader.hpp
#pragma once

#include "PositionMaintenanceRequestMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;


inline sbe_var_data<std::uint8_t> read_desk_id(const position_maintenance_request_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline sbe_var_data<std::uint8_t> read_memo(const std::byte* pos, const position_maintenance_request_message& msg) {
    return { pos, msg.tail_end() };
}

}
