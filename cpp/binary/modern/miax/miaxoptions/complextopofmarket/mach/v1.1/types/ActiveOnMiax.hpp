#pragma once

#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// Indicates if this symbol is tradable on MIAX in the current session: “A” = Active (tradable) on MIAX “I” = Inactive (not tradable) on MIAX
struct ActiveOnMiax {

    static constexpr auto name = "Active On Miax";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ActiveOnMiax()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ActiveOnMiax(const char &value)
     : value{ value } {}

    // get value of ActiveOnMiax field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
