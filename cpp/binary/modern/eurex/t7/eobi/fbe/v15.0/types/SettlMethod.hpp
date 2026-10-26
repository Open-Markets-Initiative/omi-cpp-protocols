#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {


// 
struct SettlMethod {

    static constexpr auto name = "Settl Method";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 1;
static const type minimum_value = 0;

    // default constructor
    constexpr SettlMethod()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlMethod(const std::uint8_t &value)
     : value{ value } {}

    // get value of SettlMethod field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
