#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies the Primary Listing Market of the security symbol
struct PrimaryListingMarketParticipantId {

    static constexpr auto name = "Primary Listing Market Participant Id";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PrimaryListingMarketParticipantId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PrimaryListingMarketParticipantId(const char &value)
     : value{ value } {}

    // get value of PrimaryListingMarketParticipantId field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
