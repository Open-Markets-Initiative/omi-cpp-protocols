#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Consolidated trade quantity, notional
struct MdEntrySize {

    static constexpr const char* name = "Md Entry Size";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MdEntrySize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntrySize(const std::uint64_t value)
     : value{ value } {}

    // get value of MdEntrySize field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
