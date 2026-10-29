#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Identifies the security sub type for the issue as assigned by Nasdaq
struct IssueSubType {

    static constexpr auto name = "Issue Sub Type";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr IssueSubType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IssueSubType(const type &value)
     : value{ value } {}

    // get value of IssueSubType field
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
