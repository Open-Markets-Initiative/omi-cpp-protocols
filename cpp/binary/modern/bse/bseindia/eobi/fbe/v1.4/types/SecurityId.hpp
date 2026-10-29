#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Unique instrument identifier.
struct SecurityId {

    static constexpr const char* name = "Security Id";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr SecurityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityId(const std::int64_t value)
     : value{ value } {}

    // get value of SecurityId field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
