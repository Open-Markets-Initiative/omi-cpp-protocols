#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Aggregate size at MIAX Best Price at the time stated in Timestamp and side specified in Message Type
struct MbboSizeShort {

    static constexpr const char* name = "MBBO Size Short";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MbboSizeShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MbboSizeShort(const std::uint16_t value)
     : value{ value } {}

    // get value of MbboSizeShort field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
