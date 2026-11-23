// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/MsgType.hpp
#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// Msg Type
struct MsgType {

    static constexpr auto name = "Msg Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MsgType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MsgType(const char &value)
     : value{ value } {}

    // get value of MsgType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
