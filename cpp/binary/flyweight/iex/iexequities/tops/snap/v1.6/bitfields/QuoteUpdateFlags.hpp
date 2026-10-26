#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

// Quote Update Flags
class QuoteUpdateFlags {
  public:
    static constexpr const char* name = "QuoteUpdateFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteUpdateFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool market_session() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool symbol_availability() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
        out << "QuoteUpdateFlags{";
        out << "market_session=";
        out << (market_session() ? "true" : "false");
        out << ", symbol_availability=";
        out << (symbol_availability() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteUpdateFlags& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::tops::snap::v1_6
