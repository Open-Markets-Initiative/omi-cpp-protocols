#pragma once

#include "ComplexStrategyDirectoryMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

namespace itch_topcomboquotefeed = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;


inline external_count_iterator<complex_strategy_directory_message_leg_information_entry> read_leg_information(const complex_strategy_directory_message& msg) {
    return { msg.tail_begin(), msg.fields.number_of_legs.get().value(), msg.tail_end() };
}

}
