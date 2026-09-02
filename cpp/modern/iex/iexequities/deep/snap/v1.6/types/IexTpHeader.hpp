#pragma once

#include <cstddef>

namespace iex::iexequities::deep::snap::v1_6 {


// IexTp header for the wrapped Deep feed message, see the Iex Transport specification
struct IexTpHeader {

    static constexpr auto name = "Iex Tp Header";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IexTpHeader()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IexTpHeader(const char &value)
     : value{ value } {}

    // get value of IexTpHeader field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
