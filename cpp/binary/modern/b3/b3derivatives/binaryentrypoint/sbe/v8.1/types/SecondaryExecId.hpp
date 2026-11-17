// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1: types/SecondaryExecId.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// secondaryExecID
struct SecondaryExecId {

    static constexpr const char* name = "Secondary Exec Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr SecondaryExecId()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit SecondaryExecId(const std::uint64_t value)
     : value{ value } {}

    // get value of SecondaryExecId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
