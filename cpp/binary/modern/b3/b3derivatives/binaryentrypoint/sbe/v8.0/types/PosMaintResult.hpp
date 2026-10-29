#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// posMaintResult
struct PosMaintResult {

    static constexpr const char* name = "Pos Maint Result";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr PosMaintResult()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PosMaintResult(const std::uint32_t value)
     : value{ value } {}

    // get value of PosMaintResult field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
