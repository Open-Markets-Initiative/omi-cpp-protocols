#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// SnapshotFullRefresh_Header_30Message
class SnapshotFullRefreshHeader30Message {
  public:
    static constexpr const char* name = "SnapshotFullRefreshHeader30Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotFullRefreshHeader30Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotFullRefreshHeader30Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    std::uint32_t last_msg_seq_num_processed() const { return wire::read_u32_le(at(8)); }

    std::uint32_t tot_num_reports() const { return wire::read_u32_le(at(12)); }

    std::uint32_t tot_num_bids() const { return wire::read_u32_le(at(16)); }

    std::uint32_t tot_num_offers() const { return wire::read_u32_le(at(20)); }

    std::uint16_t tot_num_stats() const { return wire::read_u16_le(at(24)); }

    std::span<const std::byte, 2> offset_26_padding_2() const { return bytes_.subspan(26).template first<2>(); }

    std::optional<std::uint32_t> last_rpt_seq() const { return wire::nullable(wire::read_u32_le(at(28)), static_cast<std::uint32_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "SnapshotFullRefreshHeader30Message{";
        out << "security_id=";
        out << security_id();
        out << ", last_msg_seq_num_processed=";
        out << last_msg_seq_num_processed();
        out << ", tot_num_reports=";
        out << tot_num_reports();
        out << ", tot_num_bids=";
        out << tot_num_bids();
        out << ", tot_num_offers=";
        out << tot_num_offers();
        out << ", tot_num_stats=";
        out << tot_num_stats();
        out << ", offset_26_padding_2=";
        print::hex(out, offset_26_padding_2().data(), offset_26_padding_2().size());
        out << ", last_rpt_seq=";
        print::optional(out, last_rpt_seq());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshHeader30Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
