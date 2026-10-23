#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v13_0 {


// 
struct CrossRequestType {

    static constexpr auto name = "Cross Request Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 2;
static const type minimum_value = 1;

    // default constructor
    constexpr CrossRequestType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossRequestType(const std::uint8_t &value)
     : value{ value } {}

    // get value of CrossRequestType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
