#pragma once

#include <cstddef>

namespace nyse::nyseequities::bbo::pillar::v2_5_b {


// The current SSR state, which this msg updates if the Security Status field contains an SSR Code. Valid
struct SsrState {

    static constexpr auto name = "Ssr State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SsrState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SsrState(const char &value)
     : value{ value } {}

    // get value of SsrState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
