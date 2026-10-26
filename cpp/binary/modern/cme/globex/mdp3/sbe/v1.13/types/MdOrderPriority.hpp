#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Order priority for execution on the order book
struct MdOrderPriority {

    static constexpr const char* name = "Md Order Priority";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MdOrderPriority()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdOrderPriority(const std::uint64_t value)
     : value{ value } {}

    // get value of MdOrderPriority field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
