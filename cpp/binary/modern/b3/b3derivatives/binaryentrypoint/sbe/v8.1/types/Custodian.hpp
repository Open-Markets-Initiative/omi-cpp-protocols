#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// custodian
struct Custodian {

    static constexpr const char* name = "Custodian";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Custodian()
     : value{ 0 } {}

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
