#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {


// Bytes of the string, encoded in UTF-8.
struct UrlLinkData {

    static constexpr auto name = "Url Link Data";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr UrlLinkData()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UrlLinkData(const char &value)
     : value{ value } {}

    // get value of UrlLinkData field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
