#pragma once

#include <cstddef>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {


// Unique code for feed
struct FeedIdentifier {

    static constexpr auto name = "Feed Identifier";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr FeedIdentifier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FeedIdentifier(const char &value)
     : value{ value } {}

    // get value of FeedIdentifier field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
