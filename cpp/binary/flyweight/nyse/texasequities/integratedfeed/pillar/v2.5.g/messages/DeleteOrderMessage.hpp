#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

// A Delete Order message is published when an order is taken off of the book.
class DeleteOrderMessage {
  public:
    static constexpr const char* name = "DeleteOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit DeleteOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every DeleteOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 21;
    static constexpr std::size_t fixed_size = 21;
    std::size_t encoded_size() const { return 21; }

    std::chrono::nanoseconds source_time_ns() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(12)); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(20).template first<1>(); }

    void print(std::ostream& out) const {
        out << "DeleteOrderMessage{";
        out << "source_time_ns=";
        out << source_time_ns().count();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", order_id=";
        out << order_id();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const DeleteOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
