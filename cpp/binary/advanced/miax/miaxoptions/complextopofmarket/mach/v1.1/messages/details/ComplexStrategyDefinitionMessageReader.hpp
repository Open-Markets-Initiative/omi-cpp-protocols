// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/details/ComplexStrategyDefinitionMessageReader.hpp
#pragma once

#include "ComplexStrategyDefinitionMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;


inline external_count_iterator<complex_strategy_definition_message_leg_definition_entry> read_leg_definition(const complex_strategy_definition_message& msg) {
    return { msg.tail_begin(), msg.fields.number_of_legs.get().value(), msg.tail_end() };
}

}
