#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v1_91 {


// Participant or Processor that generated the message
struct ParticipantId {

    static constexpr auto name = "Participant Id";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ParticipantId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ParticipantId(const char &value)
     : value{ value } {}

    // get value of ParticipantId field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
