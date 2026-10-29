#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Size of the auction response (zero if not shown).
struct ResponseSize {

    static constexpr const char* name = "Response Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ResponseSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ResponseSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ResponseSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
