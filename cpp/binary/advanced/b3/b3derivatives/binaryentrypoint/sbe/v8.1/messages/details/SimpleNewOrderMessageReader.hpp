// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1: messages/details/SimpleNewOrderMessageReader.hpp
#pragma once

#include "SimpleNewOrderMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;


inline sbe_var_data<std::uint8_t> read_memo(const simple_new_order_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
