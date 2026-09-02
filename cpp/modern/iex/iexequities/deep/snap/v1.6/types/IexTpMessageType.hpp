#pragma once

#include <cstddef>

namespace iex::iexequities::deep::snap::v1_6 {


// Code identifying the wrapped Deep message type
struct IexTpMessageType {

    static constexpr auto name = "Iex Tp Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IexTpMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IexTpMessageType(const char &value)
     : value{ value } {}

    // get value of IexTpMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
