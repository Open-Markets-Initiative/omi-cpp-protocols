#pragma once

#include <cstddef>

namespace lseg::millennium::level2::mitch::v11_9 {


// This field will contain a space if the instrument is active.
struct SymbolStatus {

    static constexpr auto name = "Symbol Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SymbolStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolStatus(const char &value)
     : value{ value } {}

    // get value of SymbolStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
