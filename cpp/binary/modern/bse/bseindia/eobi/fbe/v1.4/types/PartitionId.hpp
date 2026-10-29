#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Grouping of Bse products
struct PartitionId {

    static constexpr auto name = "Partition Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PartitionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PartitionId(const std::uint8_t &value)
     : value{ value } {}

    // get value of PartitionId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
