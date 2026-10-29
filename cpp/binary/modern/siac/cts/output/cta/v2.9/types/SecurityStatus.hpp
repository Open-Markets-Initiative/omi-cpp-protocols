#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_9 {


// Identifies the trading status applicable to the transaction
struct SecurityStatus {

    static constexpr auto name = "Security Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecurityStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityStatus(const char &value)
     : value{ value } {}

    // get value of SecurityStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
