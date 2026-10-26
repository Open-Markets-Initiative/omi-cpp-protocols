#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Heartbeat interval (seconds)
struct HeartBtInt {

    static constexpr auto name = "Heart Bt Int";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr HeartBtInt()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HeartBtInt(const std::int8_t &value)
     : value{ value } {}

    // get value of HeartBtInt field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
