#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// 
struct ChangeReason {

    static constexpr auto name = "Change Reason";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ChangeReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ChangeReason(const char &value)
     : value{ value } {}

    // get value of ChangeReason field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
