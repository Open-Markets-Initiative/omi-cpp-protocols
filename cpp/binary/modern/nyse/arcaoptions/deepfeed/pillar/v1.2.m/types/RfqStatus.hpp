#pragma once

#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Status field for CUBE/COA
struct RfqStatus {

    static constexpr auto name = "Rfq Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RfqStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RfqStatus(const char &value)
     : value{ value } {}

    // get value of RfqStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
