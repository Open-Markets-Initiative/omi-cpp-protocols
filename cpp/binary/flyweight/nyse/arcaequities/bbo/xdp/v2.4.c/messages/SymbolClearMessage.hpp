#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

// In case of a failure and recovery of a Matching Engine or an XDP Publisher, the publisher
// may send a full state refresh for every symbol affected. This kind of unrequested refresh is
// preceded by a Symbol Clear message. The client should react to receipt of a Symbol Clear
// message by clearing all state information for the specified symbol in anticipation of
// receiving a full state refresh.
class SymbolClearMessage {
  public:
    static constexpr const char* name = "SymbolClearMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolClearMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolClearMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t next_source_seq_num() const { return wire::read_u32_le(at(12)); }

    void print(std::ostream& out) const {
        out << "SymbolClearMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", next_source_seq_num=";
        out << next_source_seq_num();
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

} // namespace nyse::arcaequities::bbo::xdp::v2_4_c
