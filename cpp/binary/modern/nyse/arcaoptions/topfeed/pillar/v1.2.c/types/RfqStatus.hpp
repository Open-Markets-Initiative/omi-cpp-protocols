#pragma once

#include <cstddef>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {


// This status field is used for CUBE/COA (Type = C).
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
