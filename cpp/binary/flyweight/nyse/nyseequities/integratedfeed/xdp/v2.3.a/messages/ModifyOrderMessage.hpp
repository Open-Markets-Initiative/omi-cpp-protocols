#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/PositionChange.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// A Modify Order message is sent when the price or volume of an order is changed due to an
// event other than a cancel-replace, or full or partial execution. The content of the price
// and volume fields represent the new values after modification.
class ModifyOrderMessage {
  public:
    static constexpr const char* name = "ModifyOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ModifyOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ModifyOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 31;
    static constexpr std::size_t fixed_size = 31;
    std::size_t encoded_size() const { return 31; }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(0)); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(12)); }

    std::uint32_t price() const { return wire::read_u32_le(at(20)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(24)); }

    PositionChange position_change() const { return static_cast<PositionChange>(wire::read_u8(at(28))); }

    std::uint8_t prev_price_parity_splits() const { return wire::read_u8(at(29)); }

    std::uint8_t new_price_parity_splits() const { return wire::read_u8(at(30)); }

    void print(std::ostream& out) const {
        out << "ModifyOrderMessage{";
        out << "source_time_ns=";
        out << source_time_ns();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", order_id=";
        out << order_id();
        out << ", price=";
        out << price();
        out << ", volume=";
        out << volume();
        out << ", position_change=";
        out << position_change();
        out << ", prev_price_parity_splits=";
        out << static_cast<int>(prev_price_parity_splits());
        out << ", new_price_parity_splits=";
        out << static_cast<int>(new_price_parity_splits());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ModifyOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
