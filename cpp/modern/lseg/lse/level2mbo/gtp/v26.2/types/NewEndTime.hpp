#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// New time the session will end. The field will contain only spaces if Session Change Reason is '0' or the Session Change Reason is not present. New End Time will be in terms of the local time on the server (i.e., not UTC).
struct NewEndTime {

    static constexpr auto name = "New End Time";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr NewEndTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NewEndTime(const type &value)
     : value{ value } {}

    // get value of NewEndTime field
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
