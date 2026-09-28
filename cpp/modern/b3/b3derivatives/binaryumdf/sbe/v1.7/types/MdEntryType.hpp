#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {


// mDEntryType
struct MdEntryType {

    static constexpr auto name = "Md Entry Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MdEntryType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntryType(const char &value)
     : value{ value } {}

    // get value of MdEntryType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
