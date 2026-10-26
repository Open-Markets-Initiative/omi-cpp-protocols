#pragma once

#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
struct NoteCodesBitField6 {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Note Codes Bit Field 6";
    static constexpr std::size_t size = 1;

    struct mask {
    };

    // default constructor
    constexpr NoteCodesBitField6()
     : value{ 0 } {}

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
