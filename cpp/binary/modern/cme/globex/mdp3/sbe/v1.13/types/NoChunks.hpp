#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Total number of packets that constitutes a single instrument order book
struct NoChunks {

    static constexpr const char* name = "No Chunks";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NoChunks()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NoChunks(const std::uint32_t value)
     : value{ value } {}

    // get value of NoChunks field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
