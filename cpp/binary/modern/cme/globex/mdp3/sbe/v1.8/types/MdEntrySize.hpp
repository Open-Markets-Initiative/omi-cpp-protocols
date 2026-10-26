#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {

// Trade quantity
struct MdEntrySize {

    static constexpr const char* name = "Md Entry Size";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MdEntrySize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntrySize(const std::int32_t value)
     : value{ value } {}

    // get value of MdEntrySize field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
