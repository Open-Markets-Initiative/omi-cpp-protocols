#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {


// Flag describing IOP and Open Price entries
struct OpenCloseSettlFlag {

    static constexpr auto name = "Open Close Settl Flag";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr OpenCloseSettlFlag()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenCloseSettlFlag(const std::uint8_t &value)
     : value{ value } {}

    // get value of OpenCloseSettlFlag field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
