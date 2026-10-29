#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_10 {


// Denotes whether the referenced transaction is to be cancelled or error
struct CancelErrorAction {

    static constexpr auto name = "Cancel Error Action";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CancelErrorAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CancelErrorAction(const char &value)
     : value{ value } {}

    // get value of CancelErrorAction field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
