#pragma once

#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {


// The Message ID identifies the individual message within the block beginning with number one
struct MessageId {

    static constexpr auto name = "Message Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MessageId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageId(const std::uint8_t &value)
     : value{ value } {}

    // get value of MessageId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
