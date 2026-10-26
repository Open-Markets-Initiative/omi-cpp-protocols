#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Modify Order flags. Bit 0 indicates Order Position; bits 1-7 are undefined.
struct ModifyOrderFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Modify Order Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type OrderPosition = 0x01;
    };

    // default constructor
    constexpr ModifyOrderFlags()
     : value{ 0 } {}

    // 0 - Order kept its position in the book; 1 - Order lost its position in the book.
    [[nodiscard]] constexpr bool OrderPosition() const {
        return value & mask::OrderPosition;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
