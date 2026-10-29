#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Denotes the Nasdaq-assigned issue symbol of the security for which the trade report is being generated
struct IssueSymbol {

    static constexpr auto name = "Issue Symbol";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr IssueSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IssueSymbol(const type &value)
     : value{ value } {}

    // get value of IssueSymbol field
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
