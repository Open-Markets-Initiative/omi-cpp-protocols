// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/AckRequiredPossDup.hpp
#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


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
