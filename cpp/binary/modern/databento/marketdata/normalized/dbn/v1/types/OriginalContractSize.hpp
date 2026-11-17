// Databento.MarketData.Normalized.Dbn.v1: types/OriginalContractSize.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The original contract size
struct OriginalContractSize {

    static constexpr const char* name = "Original Contract Size";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr OriginalContractSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalContractSize(const std::int32_t value)
     : value{ value } {}

    // get value of OriginalContractSize field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
