#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {


// Status of the request acknowledgement
struct MdReqIdStatus {

    static constexpr auto name = "Md Req Id Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MdReqIdStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdReqIdStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of MdReqIdStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
