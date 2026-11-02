#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {

// Order priority for execution on the order book
struct MdOrderPriority {

    static constexpr const char* name = "Md Order Priority";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor: the null the model states, where it states one
    constexpr MdOrderPriority()
     : value{ no_value } {}

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
