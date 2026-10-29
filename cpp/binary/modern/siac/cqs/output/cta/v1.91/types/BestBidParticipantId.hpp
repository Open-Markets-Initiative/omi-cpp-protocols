#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Identifies the Participant that submitted the Best Bid on a consolidated basis.
struct BestBidParticipantId {

    static constexpr auto name = "Best Bid Participant Id";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr BestBidParticipantId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BestBidParticipantId(const char &value)
     : value{ value } {}

    // get value of BestBidParticipantId field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
