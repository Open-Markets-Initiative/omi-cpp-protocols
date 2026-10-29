#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Number of bytes for the message, including this field
struct BodyLen {

    static constexpr const char* name = "Body Len";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BodyLen()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BodyLen(const std::uint16_t value)
     : value{ value } {}

    // get value of BodyLen field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
