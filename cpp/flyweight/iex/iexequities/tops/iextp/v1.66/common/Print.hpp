#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>
#include <type_traits>

// How every generated print() writes a value. Text is quoted, a character is
// quoted, bytes are hex, an absent optional is null, a sequence is bracketed.
namespace iex::iexequities::tops::iextp::v1_66::print {

template <typename T>
inline void value(std::ostream& out, const T& item) {
    if constexpr (std::is_same_v<T, std::uint8_t> || std::is_same_v<T, std::int8_t>) {
        out << static_cast<int>(item);
    } else {
        out << item;
    }
}

inline void text(std::ostream& out, std::string_view item) {
    out << '"' << item << '"';
}

inline void character(std::ostream& out, char item) {
    out << '\'' << item << '\'';
}

inline void hex(std::ostream& out, const std::byte* data, std::size_t size) {
    static constexpr char digits[] = "0123456789abcdef";
    for (std::size_t index = 0; index < size; ++index) {
        const auto byte = std::to_integer<unsigned>(data[index]);
        out << digits[byte >> 4] << digits[byte & 0x0F];
    }
}

template <typename T>
inline void optional(std::ostream& out, const std::optional<T>& item) {
    if (item) { value(out, *item); } else { out << "null"; }
}

template <typename D>
inline void optional_duration(std::ostream& out, const std::optional<D>& item) {
    if (item) { out << item->count(); } else { out << "null"; }
}

template <typename Sequence>
inline void sequence(std::ostream& out, const Sequence& items) {
    out << '[';
    bool first = true;
    for (const auto& item : items) {
        if (!first) { out << ", "; }
        first = false;
        value(out, item);
    }
    out << ']';
}

} // namespace iex::iexequities::tops::iextp::v1_66::print
