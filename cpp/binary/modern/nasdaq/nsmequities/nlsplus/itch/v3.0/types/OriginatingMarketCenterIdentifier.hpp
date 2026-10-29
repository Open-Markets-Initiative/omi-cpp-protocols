#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Denotes the Nasdaq market system that generated the trade report message
struct OriginatingMarketCenterIdentifier {

    static constexpr auto name = "Originating Market Center Identifier";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OriginatingMarketCenterIdentifier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginatingMarketCenterIdentifier(const char &value)
     : value{ value } {}

    // get value of OriginatingMarketCenterIdentifier field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
