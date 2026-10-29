#pragma once

#include "ComplexStrategyDirectoryMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

namespace itch_ordercombofeed = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;


inline external_count_iterator<complex_strategy_directory_message_leg_information_entry> read_leg_information(const complex_strategy_directory_message& msg) {
    return { msg.tail_begin(), msg.fields.number_of_legs.get().value(), msg.tail_end() };
}

}
