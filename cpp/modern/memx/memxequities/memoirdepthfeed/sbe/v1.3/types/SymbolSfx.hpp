#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {


// SymbolSfx
struct SymbolSfx {

    static constexpr auto name = "Symbol Sfx";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SymbolSfx()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolSfx(const type &value)
     : value{ value } {}

    // get value of SymbolSfx field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
