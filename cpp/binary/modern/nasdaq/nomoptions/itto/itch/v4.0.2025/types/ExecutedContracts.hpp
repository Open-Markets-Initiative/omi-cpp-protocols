#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The number of contracts executed.
struct ExecutedContracts {

    static constexpr const char* name = "Executed Contracts";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ExecutedContracts()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecutedContracts(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ExecutedContracts field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
