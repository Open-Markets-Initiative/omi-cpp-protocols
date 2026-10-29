#pragma once

#include <cstddef>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// Underlying Asset Type of this instrument
struct UnderlyingAssetType {

    static constexpr auto name = "Underlying Asset Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr UnderlyingAssetType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingAssetType(const char &value)
     : value{ value } {}

    // get value of UnderlyingAssetType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
