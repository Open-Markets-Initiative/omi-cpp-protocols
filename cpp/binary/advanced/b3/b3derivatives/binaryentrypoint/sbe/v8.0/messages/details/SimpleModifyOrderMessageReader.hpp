#pragma once

#include "SimpleModifyOrderMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;


inline sbe_var_data read_memo(const simple_modify_order_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
