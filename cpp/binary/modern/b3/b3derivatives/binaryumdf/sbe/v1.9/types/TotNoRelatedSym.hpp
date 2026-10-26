#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// totNoRelatedSym
struct TotNoRelatedSym {

    static constexpr const char* name = "Tot No Related Sym";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotNoRelatedSym()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotNoRelatedSym(const std::uint32_t value)
     : value{ value } {}

    // get value of TotNoRelatedSym field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
