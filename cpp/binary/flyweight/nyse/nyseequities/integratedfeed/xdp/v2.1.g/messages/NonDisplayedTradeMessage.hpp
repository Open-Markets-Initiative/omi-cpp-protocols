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

// An Non Displayed Trade message is sent as a result of a match between two non-displayed
// orders.
class NonDisplayedTradeMessage {
  public:
    static constexpr const char* name = "NonDisplayedTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NonDisplayedTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NonDisplayedTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 29;
    static constexpr std::size_t fixed_size = 29;
    std::size_t encoded_size() const { return 29; }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(0)); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(12)); }

    std::uint32_t price() const { return wire::read_u32_le(at(16)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(20)); }

    PrintableFlag printable_flag() const { return static_cast<PrintableFlag>(wire::read_u8(at(24))); }

    std::uint32_t db_exec_id() const { return wire::read_u32_le(at(25)); }

    void print(std::ostream& out) const {
        out << "NonDisplayedTradeMessage{";
        out << "source_time_ns=";
        out << source_time_ns();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", trade_id=";
        out << trade_id();
        out << ", price=";
        out << price();
        out << ", volume=";
        out << volume();
        out << ", printable_flag=";
        out << printable_flag();
        out << ", db_exec_id=";
        out << db_exec_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NonDisplayedTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
