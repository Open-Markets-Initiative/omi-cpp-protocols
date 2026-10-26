#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The time at which the Near Execution Price was determined
struct NearExecutionTime {

    static constexpr const char* name = "Near Execution Time";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr NearExecutionTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NearExecutionTime(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of NearExecutionTime field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
