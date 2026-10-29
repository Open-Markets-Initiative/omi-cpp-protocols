#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/PrintableFlag.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// An Order Execution message is sent when an order is partially or fully executed.
class OrderExecutionMessage {
  public:
    static constexpr const char* name = "OrderExecutionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 38;
    static constexpr std::size_t fixed_size = 38;
    std::size_t encoded_size() const { return 38; }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(0)); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(12)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(20)); }

    std::uint32_t price() const { return wire::read_u32_le(at(24)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(28)); }

    PrintableFlag printable_flag() const { return static_cast<PrintableFlag>(wire::read_u8(at(32))); }

    std::uint8_t num_parity_splits() const { return wire::read_u8(at(33)); }

    std::uint32_t db_exec_id() const { return wire::read_u32_le(at(34)); }

    void print(std::ostream& out) const {
        out << "OrderExecutionMessage{";
        out << "source_time_ns=";
        out << source_time_ns();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", order_id=";
        out << order_id();
        out << ", trade_id=";
        out << trade_id();
        out << ", price=";
        out << price();
        out << ", volume=";
        out << volume();
        out << ", printable_flag=";
        out << printable_flag();
        out << ", num_parity_splits=";
        out << static_cast<int>(num_parity_splits());
        out << ", db_exec_id=";
        out << db_exec_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderExecutionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
