// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/MocEligible.hpp
#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// Identifies Whether The Stock Is Eligible To Trade In The Market On Close Session Each Trading Day
struct MocEligible {

    static constexpr auto name = "Moc Eligible";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MocEligible()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MocEligible(const char &value)
     : value{ value } {}

    // get value of MocEligible field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
