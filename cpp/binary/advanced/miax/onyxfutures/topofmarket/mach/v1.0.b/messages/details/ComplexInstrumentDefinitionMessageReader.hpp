// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/details/ComplexInstrumentDefinitionMessageReader.hpp
#pragma once

#include "ComplexInstrumentDefinitionMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

namespace mach_topofmarket = ::miax::onyxfutures::topofmarket::mach::v1_0_b;


inline external_count_iterator<complex_instrument_definition_message_instrument_leg_entry> read_instrument_leg(const complex_instrument_definition_message& msg) {
    return { msg.tail_begin(), msg.fields.number_of_legs.get().value(), msg.tail_end() };
}

}
