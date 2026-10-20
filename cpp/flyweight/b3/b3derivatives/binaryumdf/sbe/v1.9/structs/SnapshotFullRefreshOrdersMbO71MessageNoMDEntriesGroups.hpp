#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSizeEncoding.hpp"
#include "../groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// noMDEntries Block
class SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups {
  public:
    static constexpr const char* name = "SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    std::size_t encoded_size() const { return snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_end(); }

    GroupSizeEncoding group_size_encoding() const { return GroupSizeEncoding{ bytes_.subspan(0) }; }

    view::entries<SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup> snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group() const { return view::entries<SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup>{ bytes_.subspan(3), static_cast<std::size_t>(group_size_encoding().num_in_group()), static_cast<std::size_t>(group_size_encoding().block_length()) }; }

    void print(std::ostream& out) const {
        out << "SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups{";
        out << "group_size_encoding=";
        group_size_encoding().print(out);
        out << ", snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group=";
        print::sequence(out, snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_end() const { return 3 + snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
