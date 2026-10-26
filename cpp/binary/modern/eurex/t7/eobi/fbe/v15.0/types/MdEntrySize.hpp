#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {

// 
struct MdEntrySize {

    static constexpr const char* name = "Md Entry Size";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;
static const type no_value = 0x8000000000000000;
static const type maximum_value = 922337203685477.5807;
static const type minimum_value = -922337203685477.5807;

    // default constructor
    constexpr MdEntrySize()
     : value{ 0 } {}

    // constructor for MdEntrySize field
    constexpr explicit MdEntrySize(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MdEntrySize field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MdEntrySize field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
