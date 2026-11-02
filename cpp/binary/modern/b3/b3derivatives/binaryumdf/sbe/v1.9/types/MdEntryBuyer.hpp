#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// mDEntryBuyer
struct MdEntryBuyer {

    static constexpr const char* name = "Md Entry Buyer";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr MdEntryBuyer()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit MdEntryBuyer(const std::uint32_t value)
     : value{ value } {}

    // get value of MdEntryBuyer field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
