#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_9 {


// Identifies the Participant whose summary information is provided
struct SummaryParticipantId {

    static constexpr auto name = "Summary Participant Id";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SummaryParticipantId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SummaryParticipantId(const char &value)
     : value{ value } {}

    // get value of SummaryParticipantId field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
