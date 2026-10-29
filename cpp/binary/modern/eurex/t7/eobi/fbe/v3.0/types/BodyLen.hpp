#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {

// Total packet body length in bytes (header + messages)
struct BodyLen {

    static constexpr const char* name = "Body Len";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0xFFFF;
static const type maximum_value = 65534;
static const type minimum_value = 0;

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
