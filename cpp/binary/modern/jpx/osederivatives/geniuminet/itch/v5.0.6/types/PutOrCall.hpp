#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {


// 1=Call, 2=Put
struct PutOrCall {

    static constexpr auto name = "Put Or Call";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PutOrCall()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PutOrCall(const std::uint8_t &value)
     : value{ value } {}

    // get value of PutOrCall field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
