#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Lower Limit Execution Price
struct LowerExecLimit {

    static constexpr const char* name = "Lower Exec Limit";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr LowerExecLimit()
     : value{ 0 } {}

    // constructor for LowerExecLimit field
    constexpr explicit LowerExecLimit(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of LowerExecLimit field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of LowerExecLimit field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
