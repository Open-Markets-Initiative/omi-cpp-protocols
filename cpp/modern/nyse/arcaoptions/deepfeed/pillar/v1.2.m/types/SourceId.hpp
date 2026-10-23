#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// The ID of the client requesting this retransmission. All trailing characters should be NULL.
struct SourceId {

    static constexpr auto name = "Source Id";
    static constexpr std::size_t size = 10;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SourceId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SourceId(const type &value)
     : value{ value } {}

    // get value of SourceId field
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
