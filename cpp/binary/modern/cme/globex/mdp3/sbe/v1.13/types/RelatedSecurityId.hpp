#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Related Security ID
struct RelatedSecurityId {

    static constexpr const char* name = "Related Security Id";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr RelatedSecurityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RelatedSecurityId(const std::int32_t value)
     : value{ value } {}

    // get value of RelatedSecurityId field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
