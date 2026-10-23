#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Chunk sequence
struct CurrentChunk {

    static constexpr const char* name = "Current Chunk";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CurrentChunk()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CurrentChunk(const std::uint32_t value)
     : value{ value } {}

    // get value of CurrentChunk field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
