#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {


// 
struct NoMdEntries {

    static constexpr auto name = "No Md Entries";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 11;
static const type minimum_value = 0;

    // default constructor
    constexpr NoMdEntries()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NoMdEntries(const std::uint8_t &value)
     : value{ value } {}

    // get value of NoMdEntries field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
