#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Order priority for execution on the order book
struct MdOrderPriorityOptional {

    static constexpr const char* name = "Md Order Priority Optional";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr MdOrderPriorityOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdOrderPriorityOptional(const std::uint64_t value)
     : value{ value } {}

    // get value of MdOrderPriorityOptional field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
