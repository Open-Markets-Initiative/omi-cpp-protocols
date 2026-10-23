#pragma once

#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Only populated when securityStatus = A and this security is listed on this exchange. Otherwise defaulted to space (0x20).
struct SsrTriggeringExchangeId {

    static constexpr auto name = "Ssr Triggering Exchange Id";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SsrTriggeringExchangeId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SsrTriggeringExchangeId(const char &value)
     : value{ value } {}

    // get value of SsrTriggeringExchangeId field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
