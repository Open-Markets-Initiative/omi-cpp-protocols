#pragma once

#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v1_91 {


// Represents the actual number of Participants for which an issue will be reported.
struct NumberOfParticipants {

    static constexpr auto name = "Number Of Participants";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumberOfParticipants()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfParticipants(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumberOfParticipants field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
