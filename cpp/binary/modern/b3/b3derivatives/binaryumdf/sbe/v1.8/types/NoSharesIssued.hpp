#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// noSharesIssued
struct NoSharesIssued {

    static constexpr const char* name = "No Shares Issued";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr NoSharesIssued()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NoSharesIssued(const std::uint64_t value)
     : value{ value } {}

    // get value of NoSharesIssued field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
