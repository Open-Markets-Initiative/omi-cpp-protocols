#pragma once

#include "News5MessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_9;


inline sbe_var_data read_headline(const news_5_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline sbe_var_data read_text(const std::byte* pos, const news_5_message& msg) {
    return { pos, msg.tail_end() };
}

inline sbe_var_data read_url_link(const std::byte* pos, const news_5_message& msg) {
    return { pos, msg.tail_end() };
}

}
