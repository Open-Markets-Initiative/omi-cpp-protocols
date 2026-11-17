// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: messages/details/EstablishMessageReader.hpp
#pragma once

#include "EstablishMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;


inline sbe_var_data<std::uint8_t> read_credentials(const establish_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
