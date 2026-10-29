#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {

// 
struct MdEntrySize {

    static constexpr const char* name = "Md Entry Size";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 0x80000000;
static const type maximum_value = 2147483647;
static const type minimum_value = -2147483647;

    // default constructor
    constexpr MdEntrySize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntrySize(const std::int32_t value)
     : value{ value } {}

    // get value of MdEntrySize field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
