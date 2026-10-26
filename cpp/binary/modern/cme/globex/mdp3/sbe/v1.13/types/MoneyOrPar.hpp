#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Money or Par indicates if the GC is filled by par amount or by money amount
struct MoneyOrPar {

    static constexpr auto name = "Money Or Par";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr MoneyOrPar()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MoneyOrPar(const std::uint8_t &value)
     : value{ value } {}

    // get value of MoneyOrPar field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
