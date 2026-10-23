#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {


// Market Data Request Reject reason code
struct MdReqRejReason {

    static constexpr auto name = "Md Req Rej Reason";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MdReqRejReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdReqRejReason(const std::uint8_t &value)
     : value{ value } {}

    // get value of MdReqRejReason field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
