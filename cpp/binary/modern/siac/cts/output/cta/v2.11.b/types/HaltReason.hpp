#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Denotes the reason for the Trading Halt
struct HaltReason {

    static constexpr auto name = "Halt Reason";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr HaltReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HaltReason(const char &value)
     : value{ value } {}

    // get value of HaltReason field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
