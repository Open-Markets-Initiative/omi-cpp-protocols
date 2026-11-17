// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1: messages/details/QuoteCancelMessageReader.hpp
#pragma once

#include "QuoteCancelMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;


inline sbe_var_data<std::uint8_t> read_desk_id(const quote_cancel_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline sbe_var_data<std::uint8_t> read_memo(const std::byte* pos, const quote_cancel_message& msg) {
    return { pos, msg.tail_end() };
}

}
