#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::snap::v1_05 {

// Length of the IexTp message block, see the Iex Transport specification
struct IexTpMessageBlockLength {

    static constexpr const char* name = "Iex Tp Message Block Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr IexTpMessageBlockLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IexTpMessageBlockLength(const std::uint16_t value)
     : value{ value } {}

    // get value of IexTpMessageBlockLength field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
