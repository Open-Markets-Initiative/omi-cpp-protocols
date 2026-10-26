#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// This message format is used to indicate that the MIAX Pearl Equities book for a symbol has
// been cleared of all orders.
class SymbolClearMessage {
  public:
    static constexpr const char* name = "SymbolClearMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolClearMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolClearMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t symbol_id() const { return wire::read_u32_le(at(4)); }

    void print(std::ostream& out) const {
        out << "SymbolClearMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", symbol_id=";
        out << symbol_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SymbolClearMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
