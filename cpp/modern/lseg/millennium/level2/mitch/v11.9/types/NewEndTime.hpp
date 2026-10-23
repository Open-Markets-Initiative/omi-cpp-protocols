#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace lseg::millennium::level2::mitch::v11_9 {


// New time the session will end. Will only be stamped if the session change was not in the original schedule e.g. AESP auction call or unscheduled session.
struct NewEndTime {

    static constexpr auto name = "New End Time";
    static constexpr std::size_t size = 8;

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

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
