#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// totNoRelatedSym
struct TotNoRelatedSym {

    static constexpr auto name = "Tot No Related Sym";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0;

    // default constructor
    constexpr TotNoRelatedSym()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotNoRelatedSym(const std::uint8_t &value)
     : value{ value } {}

    // get value of TotNoRelatedSym field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
