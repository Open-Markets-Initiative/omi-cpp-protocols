#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Identifies the participant that entered the Best Bid.
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
