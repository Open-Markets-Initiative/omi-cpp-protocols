#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Aggregate size of Priority Customer contracts at the MIAX Best Price
struct MbboPriorityCustomerSizeShort {

    static constexpr const char* name = "MBBO Priority Customer Size Short";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MbboPriorityCustomerSizeShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MbboPriorityCustomerSizeShort(const std::uint16_t value)
     : value{ value } {}

    // get value of MbboPriorityCustomerSizeShort field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
