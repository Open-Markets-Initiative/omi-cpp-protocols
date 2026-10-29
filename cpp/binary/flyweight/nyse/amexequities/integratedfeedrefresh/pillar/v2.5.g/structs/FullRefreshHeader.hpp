#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

// Sequence number fields that only the full Refresh Header carries.
class FullRefreshHeader {
  public:
    static constexpr const char* name = "FullRefreshHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FullRefreshHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FullRefreshHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint32_t last_seq_num() const { return wire::read_u32_le(at(0)); }

    std::uint32_t last_symbol_seq_num() const { return wire::read_u32_le(at(4)); }

    void print(std::ostream& out) const {
        out << "FullRefreshHeader{";
        out << "last_seq_num=";
        out << last_seq_num();
        out << ", last_symbol_seq_num=";
        out << last_symbol_seq_num();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FullRefreshHeader& value) {
    value.print(out);
    return out;
}

} // namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g
