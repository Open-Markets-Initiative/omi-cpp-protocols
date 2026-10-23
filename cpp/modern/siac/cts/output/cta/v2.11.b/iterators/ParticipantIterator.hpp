#pragma once

#include "../definitions.hpp"

namespace siac::cts::output::cta::v2_11_b {
// ParticipantIterator
struct ParticipantIterator {

    const std::byte* current = nullptr;

    const FractionalApproximateAdjustedVolumeMarketCenterMessage* fractional_approximate_adjusted_volume_market_center_message = nullptr;

    std::uint8_t number_of_participants = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        fractional_approximate_adjusted_volume_market_center_message = FractionalApproximateAdjustedVolumeMarketCenterMessage::parse(current);
        current += sizeof(FractionalApproximateAdjustedVolumeMarketCenterMessage);

        number_of_participants = fractional_approximate_adjusted_volume_market_center_message->number_of_participants.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= number_of_participants) {
            return false;
        }

        entry = current;
        entry_index++;

        return true;
    }

    // advance past processed entry
    void advance(std::size_t bytes) {
        current += bytes;
    }

    // reset iterator
    void reset() {
        current = nullptr;

        fractional_approximate_adjusted_volume_market_center_message = nullptr;

        number_of_participants = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
