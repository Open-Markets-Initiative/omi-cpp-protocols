#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v5 {


// Identifies the reason for the status change
struct HaltReason {

    static constexpr auto name = "Halt Reason";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr HaltReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HaltReason(const std::uint8_t &value)
     : value{ value } {}

    // get value of HaltReason field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
