#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Reason the trading session changed.
struct SessionChangeReason {

    static constexpr auto name = "Session Change Reason";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SessionChangeReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SessionChangeReason(const std::uint8_t &value)
     : value{ value } {}

    // get value of SessionChangeReason field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
