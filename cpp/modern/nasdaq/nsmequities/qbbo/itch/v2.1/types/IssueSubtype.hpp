#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {


// Identifies the security sub-type for the issue as assigned by Nasdaq. See Appendix for allowable values.
struct IssueSubtype {

    static constexpr auto name = "Issue Subtype";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr IssueSubtype()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IssueSubtype(const type &value)
     : value{ value } {}

    // get value of IssueSubtype field
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
