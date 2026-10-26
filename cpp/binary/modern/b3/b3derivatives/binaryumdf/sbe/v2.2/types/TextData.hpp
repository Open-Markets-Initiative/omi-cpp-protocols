#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {


// Bytes of the string, encoded in UTF-8.
struct TextData {

    static constexpr auto name = "Text Data";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TextData()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TextData(const char &value)
     : value{ value } {}

    // get value of TextData field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
