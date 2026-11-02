#pragma once

// Shared null-terminated, runtime-bounded string parser.
// Each per-field type (Title, Reference, ...) is a fully self-contained struct
// that holds its own (data, start, length, status) and calls parse_null_terminated()
// in its constructor. No inheritance — types are not thin subclasses of anything.
//
// Caller threads a `size_t&` offset through each variable field of the enclosing
// message, so the offset is always anchored to the previous field's end. The parser
// scans up to `maximum + 1` bytes (or fewer if the buffer ends sooner) and either:
//   - finds the terminator → length is bytes-before-terminator, offset is past it (Ok)
//   - exhausts buffer       → length is what we read, offset clamps to `available`  (Truncated)
//   - no terminator in max  → length is `maximum`, offset is `start + maximum`      (MissingTerminator)
//
// Failure paths never claim a terminator we didn't see, and never advance offset
// past the buffer.

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string_view>

namespace omi {

enum class NullTerminatedStatus : std::uint8_t { Ok, Truncated, MissingTerminator };

struct NullTerminatedResult {
    std::size_t          length;
    NullTerminatedStatus status;
};

[[nodiscard]] inline NullTerminatedResult parse_null_terminated(
    const std::byte* data,
    std::size_t&     offset,
    std::size_t      available,
    std::size_t      maximum,
    char             terminator)
{
    const std::size_t start = offset;

    if (start >= available) {
        offset = available;
        return { 0, NullTerminatedStatus::Truncated };
    }

    const std::size_t scan  = std::min(maximum + 1, available - start);
    const auto*       begin = reinterpret_cast<const char*>(data + start);
    const auto*       term  = static_cast<const char*>(std::memchr(begin, terminator, scan));

    if (term) {
        const std::size_t length = static_cast<std::size_t>(term - begin);
        offset = start + length + 1;
        return { length, NullTerminatedStatus::Ok };
    }

    const std::size_t length = std::min(maximum, available - start);
    offset = start + length;
    return {
        length,
        (available - start < maximum + 1) ? NullTerminatedStatus::Truncated
                                          : NullTerminatedStatus::MissingTerminator
    };
}

[[nodiscard]] inline std::string_view view_of(const std::byte* data, std::size_t start, std::size_t length) {
    return std::string_view{ reinterpret_cast<const char*>(data + start), length };
}

}