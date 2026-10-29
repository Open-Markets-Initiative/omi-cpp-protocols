#pragma once

#include <cstddef>

namespace cme::mdp3::v5 {


// Last Security update action on Incremental feed, 'D' or 'M' is used when a mid-week deletion or modification (i.e. extension) occurs
struct SecurityUpdateAction {

    static constexpr auto name = "Security Update Action";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecurityUpdateAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityUpdateAction(const char &value)
     : value{ value } {}

    // get value of SecurityUpdateAction field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
