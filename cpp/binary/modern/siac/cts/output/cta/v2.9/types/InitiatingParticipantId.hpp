#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_9 {


// Participant or Processor that generated the message
struct InitiatingParticipantId {

    static constexpr auto name = "Initiating Participant Id";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr InitiatingParticipantId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InitiatingParticipantId(const char &value)
     : value{ value } {}

    // get value of InitiatingParticipantId field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
