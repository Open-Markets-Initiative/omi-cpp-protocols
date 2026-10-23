#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Execution timestamp as reported by the supported market. If a trade is cancelled or amended, this field will contain the transaction time of the original trade.
struct TransactionTime {

    static constexpr auto name = "Transaction Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr TransactionTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TransactionTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of TransactionTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
