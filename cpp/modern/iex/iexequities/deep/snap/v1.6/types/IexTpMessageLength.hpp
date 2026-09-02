#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::snap::v1_6 {

// Length of the wrapped Deep message in bytes not including this field
struct IexTpMessageLength {

    static constexpr const char* name = "Iex Tp Message Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr IexTpMessageLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IexTpMessageLength(const std::uint16_t value)
     : value{ value } {}

    // get value of IexTpMessageLength field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
