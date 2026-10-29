#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// allocRejCode
struct AllocRejCode {

    static constexpr const char* name = "Alloc Rej Code";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr AllocRejCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AllocRejCode(const std::uint32_t value)
     : value{ value } {}

    // get value of AllocRejCode field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
