// B3.B3Derivatives.BinaryUmdf.Sbe.v2.1: types/NoSharesIssued.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// noSharesIssued
struct NoSharesIssued {

    static constexpr const char* name = "No Shares Issued";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr NoSharesIssued()
     : value{ no_value } {}

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
