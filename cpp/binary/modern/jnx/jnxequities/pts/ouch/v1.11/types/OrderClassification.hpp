#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::ouch::v1_11 {


// High-frequency trading order classification
struct OrderClassification {

    static constexpr auto name = "Order Classification";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OrderClassification()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderClassification(const char &value)
     : value{ value } {}

    // get value of OrderClassification field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
