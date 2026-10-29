#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Aggregate size at MIAX Best Price at the time stated in Timestamp and side specified in Message Type
struct CompactSize {

    static constexpr const char* name = "Compact Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr CompactSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CompactSize(const std::uint16_t value)
     : value{ value } {}

    // get value of CompactSize field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
