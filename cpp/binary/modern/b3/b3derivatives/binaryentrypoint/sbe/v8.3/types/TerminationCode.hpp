#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// terminationCode
struct TerminationCode {

    static constexpr auto name = "Termination Code";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TerminationCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TerminationCode(const std::uint8_t &value)
     : value{ value } {}

    // get value of TerminationCode field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
