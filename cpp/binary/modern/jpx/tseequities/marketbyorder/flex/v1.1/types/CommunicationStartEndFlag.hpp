#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Indicates the start or end of communication
struct CommunicationStartEndFlag {

    static constexpr auto name = "Communication Start End Flag";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr CommunicationStartEndFlag()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CommunicationStartEndFlag(const std::uint8_t &value)
     : value{ value } {}

    // get value of CommunicationStartEndFlag field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
