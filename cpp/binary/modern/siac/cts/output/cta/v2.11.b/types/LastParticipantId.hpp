#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Refer to Participant ID field description for Participant codes. Space-filled
struct LastParticipantId {

    static constexpr auto name = "Last Participant Id";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LastParticipantId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastParticipantId(const char &value)
     : value{ value } {}

    // get value of LastParticipantId field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
