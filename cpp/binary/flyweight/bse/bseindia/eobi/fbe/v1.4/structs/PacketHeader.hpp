#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/EobiHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Technical header delivered in every Udp datagram, identifying the product, the partition,
// and the send time
class PacketHeader {
  public:
    static constexpr const char* name = "PacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    EobiHeader eobi_header() const { return EobiHeader{ bytes_.subspan(0) }; }

    std::uint32_t appl_seq_num() const { return wire::read_u32_le(at(8)); }

    std::int32_t market_segment_id() const { return wire::read_i32_le(at(12)); }

    std::uint8_t partition_id() const { return wire::read_u8(at(16)); }

    std::uint8_t completion_indicator() const { return wire::read_u8(at(17)); }

    std::uint8_t appl_seq_reset_indicator() const { return wire::read_u8(at(18)); }

    std::span<const std::byte, 5> pad_5() const { return bytes_.subspan(19).template first<5>(); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(24)))); }

    void print(std::ostream& out) const {
        out << "PacketHeader{";
        out << "eobi_header=";
        eobi_header().print(out);
        out << ", appl_seq_num=";
        out << appl_seq_num();
        out << ", market_segment_id=";
        out << market_segment_id();
        out << ", partition_id=";
        out << static_cast<int>(partition_id());
        out << ", completion_indicator=";
        out << static_cast<int>(completion_indicator());
        out << ", appl_seq_reset_indicator=";
        out << static_cast<int>(appl_seq_reset_indicator());
        out << ", pad_5=";
        print::hex(out, pad_5().data(), pad_5().size());
        out << ", transact_time=";
        out << transact_time().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
