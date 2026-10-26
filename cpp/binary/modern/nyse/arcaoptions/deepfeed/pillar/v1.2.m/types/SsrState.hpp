#pragma once

#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// The current SSR state.
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
