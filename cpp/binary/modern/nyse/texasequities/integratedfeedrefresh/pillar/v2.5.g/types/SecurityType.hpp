#pragma once

#include <cstddef>

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {


// Type of Security used by Pillar-powered markets.
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
