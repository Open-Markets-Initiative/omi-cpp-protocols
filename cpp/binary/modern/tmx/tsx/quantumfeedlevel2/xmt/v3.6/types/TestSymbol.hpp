// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/TestSymbol.hpp
#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// Indicates The Symbol Is A Test Symbol
struct TestSymbol {

    static constexpr auto name = "Test Symbol";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TestSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TestSymbol(const char &value)
     : value{ value } {}

    // get value of TestSymbol field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
