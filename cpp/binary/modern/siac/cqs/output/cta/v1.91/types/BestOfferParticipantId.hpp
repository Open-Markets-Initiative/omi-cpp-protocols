#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Identifies the Participant that submitted the Best Bid on a consolidated basis.
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
