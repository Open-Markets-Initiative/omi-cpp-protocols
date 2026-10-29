#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nationalequities::trades::pillar::v2_6 {


// The delivery method for the requested symbol index mapping information. Valid values: 0 - deliver via UDP.
struct RetransmitMethod {

    static constexpr auto name = "Retransmit Method";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr RetransmitMethod()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RetransmitMethod(const std::uint8_t &value)
     : value{ value } {}

    // get value of RetransmitMethod field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
