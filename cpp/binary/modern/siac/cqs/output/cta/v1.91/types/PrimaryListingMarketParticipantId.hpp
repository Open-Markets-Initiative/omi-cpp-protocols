#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Identifies the Primary Listing Market for a security
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
