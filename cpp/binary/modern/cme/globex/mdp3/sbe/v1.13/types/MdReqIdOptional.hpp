#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Unique identifier for Market Data Request
struct MdReqIdOptional {

    static constexpr const char* name = "Md Req Id Optional";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 4294967295;

    // default constructor
    constexpr MdReqIdOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdReqIdOptional(const std::uint32_t value)
     : value{ value } {}

    // get value of MdReqIdOptional field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
