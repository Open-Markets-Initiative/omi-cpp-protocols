#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Consolidated last participant ID
struct ConsolidatedLastParticipantId {

    static constexpr auto name = "Consolidated Last Participant Id";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ConsolidatedLastParticipantId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ConsolidatedLastParticipantId(const char &value)
     : value{ value } {}

    // get value of ConsolidatedLastParticipantId field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
