#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Participant tick direction
struct ParticipantTick {

    static constexpr auto name = "Participant Tick";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ParticipantTick()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ParticipantTick(const char &value)
     : value{ value } {}

    // get value of ParticipantTick field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
