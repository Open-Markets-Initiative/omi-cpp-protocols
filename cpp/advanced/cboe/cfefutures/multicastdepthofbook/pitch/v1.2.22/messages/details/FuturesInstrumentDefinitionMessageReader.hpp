#pragma once

#include "FuturesInstrumentDefinitionMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;


inline external_count_iterator<futures_instrument_definition_message_future_leg_entry> read_future_leg(const futures_instrument_definition_message& msg) {
    return { msg.tail_begin(), msg.fields.leg_count.get().value(), msg.tail_end() };
}

}
