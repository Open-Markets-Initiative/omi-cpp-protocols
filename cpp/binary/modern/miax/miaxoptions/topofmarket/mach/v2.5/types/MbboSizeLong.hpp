#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Aggregate size at MIAX Best Price at the time stated in Timestamp and side specified in Message Type
struct MbboSizeLong {

    static constexpr const char* name = "MBBO Size Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MbboSizeLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MbboSizeLong(const std::uint32_t value)
     : value{ value } {}

    // get value of MbboSizeLong field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
