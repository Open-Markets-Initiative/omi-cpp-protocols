#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// External unique broken date Instrument ID
struct BrokenDateGuid {

    static constexpr const char* name = "Broken Date Guid";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr BrokenDateGuid()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BrokenDateGuid(const std::uint64_t value)
     : value{ value } {}

    // get value of BrokenDateGuid field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
