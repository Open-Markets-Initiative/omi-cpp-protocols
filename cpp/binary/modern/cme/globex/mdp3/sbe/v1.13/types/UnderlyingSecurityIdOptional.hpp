#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Underlying Security ID as qualified by tag 305-UnderlyingSecurityIDSource. Provided only if the underlying is a Globex listed instrument, this value will be the same as that contained in Security Definition Tag 48-SecurityID.
struct UnderlyingSecurityIdOptional {

    static constexpr const char* name = "Underlying Security Id Optional";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor
    constexpr UnderlyingSecurityIdOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingSecurityIdOptional(const std::int32_t value)
     : value{ value } {}

    // get value of UnderlyingSecurityIdOptional field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
