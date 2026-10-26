#pragma once

#include <cstddef>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {


// Trading state of the order book
struct SymbolState {

    static constexpr auto name = "Symbol State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SymbolState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolState(const char &value)
     : value{ value } {}

    // get value of SymbolState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
