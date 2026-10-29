#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Ack Required Poss Dup
struct AckRequiredPossDup {

    static constexpr auto name = "Ack Required Poss Dup";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AckRequiredPossDup()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AckRequiredPossDup(const char &value)
     : value{ value } {}

    // get value of AckRequiredPossDup field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
