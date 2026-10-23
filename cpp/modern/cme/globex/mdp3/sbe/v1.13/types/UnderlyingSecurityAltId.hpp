#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Underlying Alternate Security identifier value as qualified by Tag 305-UnderlyingSecuityAltIDSource (e.g. CUSIP, ISIN, etc). For Repo special will contain underlying CUSIP or ISIN. For GC Repo may contain a synthetic CUSIP or ISIN representing a basket
struct UnderlyingSecurityAltId {

    static constexpr auto name = "Underlying Security Alt Id";
    static constexpr std::size_t size = 12;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr UnderlyingSecurityAltId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingSecurityAltId(const type &value)
     : value{ value } {}

    // get value of UnderlyingSecurityAltId field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
