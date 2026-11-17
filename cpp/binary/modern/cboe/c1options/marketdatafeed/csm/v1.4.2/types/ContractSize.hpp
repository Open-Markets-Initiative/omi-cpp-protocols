// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/ContractSize.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The number of contracts per unit of size
struct ContractSize {

    static constexpr const char* name = "Contract Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ContractSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ContractSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ContractSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
