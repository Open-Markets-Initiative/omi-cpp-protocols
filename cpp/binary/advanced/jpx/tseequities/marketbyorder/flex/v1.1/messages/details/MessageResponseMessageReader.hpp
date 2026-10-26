#pragma once

#include "MessageResponseMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;


inline sbe_var_data read_data(const message_response_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
