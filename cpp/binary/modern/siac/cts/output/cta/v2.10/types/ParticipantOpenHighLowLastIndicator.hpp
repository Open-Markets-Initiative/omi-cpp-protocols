#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_10 {


// Identifies the Participant Open/High/Low/Last applicable to the transaction
struct ParticipantOpenHighLowLastIndicator {

    static constexpr auto name = "Participant Open High Low Last Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ParticipantOpenHighLowLastIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ParticipantOpenHighLowLastIndicator(const char &value)
     : value{ value } {}

    // get value of ParticipantOpenHighLowLastIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
