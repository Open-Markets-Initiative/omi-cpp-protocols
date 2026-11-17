// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/details/ExtendedSecurityMessageReader.hpp
#pragma once

#include "ExtendedSecurityMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;


inline sbe_var_data<std::uint8_t> read_security_detail(const extended_security_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline sbe_var_data<std::uint8_t> read_issuer(const std::byte* pos, const extended_security_message& msg) {
    return { pos, msg.tail_end() };
}

}
