#pragma once

#include "ComplexInstrumentDefinitionExpandedMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;


inline external_count_iterator<complex_instrument_definition_expanded_message_complex_instrument_leg_entry> read_complex_instrument_leg(const complex_instrument_definition_expanded_message& msg) {
    return { msg.tail_begin(), msg.fields.leg_count.get().value(), msg.tail_end() };
}

}
