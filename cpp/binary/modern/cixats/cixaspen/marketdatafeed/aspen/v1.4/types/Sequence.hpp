#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Sequence number for next message
struct Sequence {

    static constexpr const char* name = "Sequence";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr Sequence()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Sequence(const std::uint64_t value)
     : value{ value } {}

    // get value of Sequence field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
