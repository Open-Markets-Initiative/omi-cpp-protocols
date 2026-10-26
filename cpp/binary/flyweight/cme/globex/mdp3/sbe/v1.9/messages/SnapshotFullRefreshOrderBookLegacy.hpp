#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/SnapshotFullRefreshOrderBookGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// SnapshotFullRefreshOrderBook
class SnapshotFullRefreshOrderBookLegacy {
  public:
    static constexpr const char* name = "SnapshotFullRefreshOrderBookLegacy";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotFullRefreshOrderBookLegacy(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotFullRefreshOrderBookLegacy has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    std::size_t encoded_size() const { return snapshot_full_refresh_order_book_groups_end(); }

    std::uint32_t last_msg_seq_num_processed() const { return wire::read_u32_le(at(0)); }

    std::uint32_t tot_num_reports() const { return wire::read_u32_le(at(4)); }

    std::int32_t security_id() const { return wire::read_i32_le(at(8)); }

    std::uint32_t no_chunks() const { return wire::read_u32_le(at(12)); }

    std::uint32_t current_chunk() const { return wire::read_u32_le(at(16)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(20)))); }

    SnapshotFullRefreshOrderBookGroups snapshot_full_refresh_order_book_groups() const { return SnapshotFullRefreshOrderBookGroups{ bytes_.subspan(28) }; }

    void print(std::ostream& out) const {
        out << "SnapshotFullRefreshOrderBookLegacy{";
        out << "last_msg_seq_num_processed=";
        out << last_msg_seq_num_processed();
        out << ", tot_num_reports=";
        out << tot_num_reports();
        out << ", security_id=";
        out << security_id();
        out << ", no_chunks=";
        out << no_chunks();
        out << ", current_chunk=";
        out << current_chunk();
        out << ", transact_time=";
        out << transact_time().count();
        out << ", snapshot_full_refresh_order_book_groups=";
        snapshot_full_refresh_order_book_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t snapshot_full_refresh_order_book_groups_end() const { return 28 + snapshot_full_refresh_order_book_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrderBookLegacy& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
