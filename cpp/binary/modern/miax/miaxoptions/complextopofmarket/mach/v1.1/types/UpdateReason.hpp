#pragma once

#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// “N” – New strategy created
struct UpdateReason {

    static constexpr auto name = "Update Reason";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr UpdateReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UpdateReason(const char &value)
     : value{ value } {}

    // get value of UpdateReason field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
