#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


// Identifies the Participant that submitted the Best Offer on a consolidated basis
struct BestOfferParticipantId {

    static constexpr auto name = "Best Offer Participant Id";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr BestOfferParticipantId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BestOfferParticipantId(const char &value)
     : value{ value } {}

    // get value of BestOfferParticipantId field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
