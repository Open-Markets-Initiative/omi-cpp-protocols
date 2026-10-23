#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Message Size
struct TcpMessageSize {

    static constexpr const char* name = "Tcp Message Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr TcpMessageSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TcpMessageSize(const std::uint16_t value)
     : value{ value } {}

    // get value of TcpMessageSize field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
