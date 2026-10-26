#pragma once

#include "FractionalApproximateAdjustedVolumeMarketCenterMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

namespace cta_output = ::siac::cts::output::cta::v2_11_b;


inline external_count_iterator<fractional_approximate_adjusted_volume_market_center_message_participant_entry> read_participant(const fractional_approximate_adjusted_volume_market_center_message& msg) {
    return { msg.tail_begin(), msg.fields.number_of_participants.get().value(), msg.tail_end() };
}

}
