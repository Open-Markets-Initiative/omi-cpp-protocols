#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


// Bytes of the string, encoded in UTF-8.
struct HeadlineData {

    static constexpr auto name = "Headline Data";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr HeadlineData()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HeadlineData(const char &value)
     : value{ value } {}

    // get value of HeadlineData field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
