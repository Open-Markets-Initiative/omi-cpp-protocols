#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Upper Limit Execution Price
struct UpperExecLimit {

    static constexpr const char* name = "Upper Exec Limit";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr UpperExecLimit()
     : value{ 0 } {}

    // constructor for UpperExecLimit field
    constexpr explicit UpperExecLimit(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of UpperExecLimit field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of UpperExecLimit field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
