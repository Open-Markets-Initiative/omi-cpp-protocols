#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// An Add Order message is published when a new visible order has been received and added to
// the book. The Order ID is assigned by the matching engine and is good for today only. It is
// unique across all markets, except that for NYSE Tape A symbols, it is only unique per
// matching engine instance.
class AddOrderMessage {
  public:
    static constexpr const char* name = "AddOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 35;
    static constexpr std::size_t fixed_size = 35;
    std::size_t encoded_size() const { return 35; }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(0)); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(12)); }

    std::uint32_t price() const { return wire::read_u32_le(at(20)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(24)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(28))); }

    std::string_view firm_id() const { return view::text(at(29), 5, ' '); }

    std::uint8_t num_parity_splits() const { return wire::read_u8(at(34)); }

    void print(std::ostream& out) const {
        out << "AddOrderMessage{";
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
        out << ", side=";
        out << side();
        out << ", firm_id=";
        print::text(out, firm_id());
        out << ", num_parity_splits=";
        out << static_cast<int>(num_parity_splits());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
