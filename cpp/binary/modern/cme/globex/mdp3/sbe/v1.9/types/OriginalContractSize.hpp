#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// Fixed contract value assigned to each product
struct OriginalContractSize {

    static constexpr const char* name = "Original Contract Size";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor: the null the model states, where it states one
    constexpr OriginalContractSize()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit OriginalContractSize(const std::int32_t value)
     : value{ value } {}

    // get value of OriginalContractSize field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
