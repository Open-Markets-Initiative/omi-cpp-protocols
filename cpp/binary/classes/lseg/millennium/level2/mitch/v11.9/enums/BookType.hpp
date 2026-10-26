#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::millennium::level2::mitch::v11_9 {

// Book Type
enum class BookType : std::uint8_t {
    OnBook = 1,     // On Book
    OffBook = 2,    // Off Book
    PrivateRfq = 3, // Private Rfq
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(BookType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, BookType value);

} // namespace lseg::millennium::level2::mitch::v11_9
