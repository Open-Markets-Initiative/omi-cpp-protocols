// B3.B3Derivatives.BinaryUmdf.Sbe.v2.2: messages/details/News5MessageReader.hpp
#pragma once

#include "News5MessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_2;


inline sbe_var_data<std::uint16_t> read_headline(const news_5_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline sbe_var_data<std::uint16_t> read_text(const std::byte* pos, const news_5_message& msg) {
    return { pos, msg.tail_end() };
}

inline sbe_var_data<std::uint16_t> read_url_link(const std::byte* pos, const news_5_message& msg) {
    return { pos, msg.tail_end() };
}

}
