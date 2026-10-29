#pragma once

#include "ComplexSymbolDefinitionMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

namespace xdp_complexfeed = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;


inline external_count_iterator<complex_symbol_definition_message_leg_definition_entry> read_leg_definition(const complex_symbol_definition_message& msg) {
    return { msg.tail_begin(), msg.fields.no_of_legs.get().value(), msg.tail_end() };
}

}
