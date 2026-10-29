#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Matching timestamp.
struct ExecId {

    static constexpr auto name = "Exec Id";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr ExecId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecId(const std::uint64_t &value)
     : value{ value } {}

    // get value of ExecId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
