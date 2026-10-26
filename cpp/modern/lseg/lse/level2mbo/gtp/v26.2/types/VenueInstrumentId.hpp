#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Instrument identifier used by the source venue.
struct VenueInstrumentId {

    static constexpr auto name = "Venue Instrument Id";
    static constexpr std::size_t size = 11;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr VenueInstrumentId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit VenueInstrumentId(const type &value)
     : value{ value } {}

    // get value of VenueInstrumentId field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
