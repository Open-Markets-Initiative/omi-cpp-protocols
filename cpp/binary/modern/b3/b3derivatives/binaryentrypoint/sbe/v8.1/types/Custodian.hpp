// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1: types/Custodian.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// custodian
struct Custodian {

    static constexpr const char* name = "Custodian";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr Custodian()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit Custodian(const std::uint32_t value)
     : value{ value } {}

    // get value of Custodian field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
