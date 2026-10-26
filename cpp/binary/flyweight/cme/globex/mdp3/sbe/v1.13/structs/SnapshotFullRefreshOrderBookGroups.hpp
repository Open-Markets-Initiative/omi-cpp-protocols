#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSize.hpp"
#include "../groups/SnapshotFullRefreshOrderBookGroup.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoMDEntries Block
class SnapshotFullRefreshOrderBookGroups {
  public:
    static constexpr const char* name = "SnapshotFullRefreshOrderBookGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotFullRefreshOrderBookGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotFullRefreshOrderBookGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    std::size_t encoded_size() const { return snapshot_full_refresh_order_book_group_end(); }

    GroupSize group_size() const { return GroupSize{ bytes_.subspan(0) }; }

    view::entries<SnapshotFullRefreshOrderBookGroup> snapshot_full_refresh_order_book_group() const { return view::entries<SnapshotFullRefreshOrderBookGroup>{ bytes_.subspan(3), wire::count(group_size().num_in_group()), wire::count(group_size().block_length()) }; }

    void print(std::ostream& out) const {
        out << "SnapshotFullRefreshOrderBookGroups{";
        out << "group_size=";
        group_size().print(out);
        out << ", snapshot_full_refresh_order_book_group=";
        print::sequence(out, snapshot_full_refresh_order_book_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t snapshot_full_refresh_order_book_group_end() const { return 3 + snapshot_full_refresh_order_book_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrderBookGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
