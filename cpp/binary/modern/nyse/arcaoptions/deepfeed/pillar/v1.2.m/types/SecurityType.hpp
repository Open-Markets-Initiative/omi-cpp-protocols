#pragma once

#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Type of Security used by Pillar markets.
struct SecurityType {

    static constexpr auto name = "Security Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecurityType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityType(const char &value)
     : value{ value } {}

    // get value of SecurityType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
