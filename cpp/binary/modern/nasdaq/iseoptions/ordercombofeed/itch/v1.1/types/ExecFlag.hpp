#pragma once

#include <cstddef>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {


// ‘N’ = None ‘A’ = AON
struct ExecFlag {

    static constexpr auto name = "Exec Flag";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ExecFlag()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecFlag(const char &value)
     : value{ value } {}

    // get value of ExecFlag field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
