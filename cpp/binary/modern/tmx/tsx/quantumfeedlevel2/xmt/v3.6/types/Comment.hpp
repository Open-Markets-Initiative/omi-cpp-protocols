// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/Comment.hpp
#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// A Text Field Corresponding To A Reason Code Entered When A Stock Is Halted Or The Initiator Of A Delayed Opening On A Stock Or When There Is A Change To The Rt Oddlot Trader On A Stock As Well This Is A System Produced Text Field To Describe The Disabling Of The Moc Session By Tsx Trading Services
struct Comment {

    static constexpr auto name = "Comment";
    static constexpr std::size_t size = 40;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Comment()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Comment(const type &value)
     : value{ value } {}

    // get value of Comment field
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
