#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// OCC Number for the Clearing firm specified with the order. '0' - (0x00) indicates OCC Number was not specified. Only valid for BOLD (Type = B).
struct Participant {

    static constexpr const char* name = "Participant";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Participant()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Participant(const std::uint32_t value)
     : value{ value } {}

    // get value of Participant field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
