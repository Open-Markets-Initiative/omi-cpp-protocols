#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// The Transaction ID will be populated by CQS and is Reserved for Internal Use only
struct TransactionId {

    static constexpr const char* name = "Transaction Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TransactionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TransactionId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TransactionId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
