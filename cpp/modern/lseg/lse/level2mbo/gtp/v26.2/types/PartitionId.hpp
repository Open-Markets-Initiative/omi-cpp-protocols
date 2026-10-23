#pragma once

#include <cstddef>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Trading System's partition in which the instrument is traded.
struct PartitionId {

    static constexpr auto name = "Partition Id";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PartitionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PartitionId(const char &value)
     : value{ value } {}

    // get value of PartitionId field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
