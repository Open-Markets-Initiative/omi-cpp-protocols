#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// Free ASCII format text field defined by client.
struct MemoData {

    static constexpr auto name = "Memo Data";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MemoData()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MemoData(const char &value)
     : value{ value } {}

    // get value of MemoData field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
