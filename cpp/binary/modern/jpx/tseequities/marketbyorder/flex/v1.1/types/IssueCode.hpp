#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Securities Identification Code left aligned with trailing spaces
struct IssueCode {

    static constexpr auto name = "Issue Code";
    static constexpr std::size_t size = 12;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr IssueCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IssueCode(const type &value)
     : value{ value } {}

    // get value of IssueCode field
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
