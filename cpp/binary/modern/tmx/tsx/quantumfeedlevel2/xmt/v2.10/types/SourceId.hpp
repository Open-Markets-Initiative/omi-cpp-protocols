#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Source Id of the Business message
struct SourceId {

    static constexpr auto name = "Source Id";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SourceId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SourceId(const char &value)
     : value{ value } {}

    // get value of SourceId field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
