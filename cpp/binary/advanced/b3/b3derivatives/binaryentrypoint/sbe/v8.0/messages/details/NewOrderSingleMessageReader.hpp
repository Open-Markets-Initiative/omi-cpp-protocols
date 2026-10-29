#pragma once

#include "NewOrderSingleMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;


inline sbe_var_data read_desk_id(const new_order_single_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline sbe_var_data read_memo(const std::byte* pos, const new_order_single_message& msg) {
    return { pos, msg.tail_end() };
}

}
