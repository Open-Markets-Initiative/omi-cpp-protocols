// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/details/SecurityDefinitionMessageReader.hpp
#pragma once

#include "SecurityDefinitionMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;


inline sbe_var_data<std::uint8_t> read_security_type(const security_definition_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline sbe_var_data<std::uint8_t> read_symbol(const std::byte* pos, const security_definition_message& msg) {
    return { pos, msg.tail_end() };
}

inline sbe_var_data<std::uint8_t> read_target_location_id(const std::byte* pos, const security_definition_message& msg) {
    return { pos, msg.tail_end() };
}

inline sbe_var_data<std::uint8_t> read_currency_code(const std::byte* pos, const security_definition_message& msg) {
    return { pos, msg.tail_end() };
}

inline sbe_var_data<std::uint8_t> read_underlying_symbol(const std::byte* pos, const security_definition_message& msg) {
    return { pos, msg.tail_end() };
}

inline sbe_var_data<std::uint8_t> read_underlying_type(const std::byte* pos, const security_definition_message& msg) {
    return { pos, msg.tail_end() };
}

template<typename CountT>
inline external_count_iterator<security_definition_message_security_definition_leg_entry> read_security_definition_leg(const std::byte* pos, CountT count, const security_definition_message& msg) {
    return { pos, count, msg.tail_end() };
}

}
