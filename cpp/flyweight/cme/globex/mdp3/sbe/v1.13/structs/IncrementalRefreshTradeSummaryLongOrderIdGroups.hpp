#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSize8Byte.hpp"
#include "../groups/IncrementalRefreshTradeSummaryLongOrderIdGroup.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoOrderIDEntries Block
class IncrementalRefreshTradeSummaryLongOrderIdGroups {
  public:
    static constexpr const char* name = "IncrementalRefreshTradeSummaryLongOrderIdGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshTradeSummaryLongOrderIdGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshTradeSummaryLongOrderIdGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    std::size_t encoded_size() const { return incremental_refresh_trade_summary_long_order_id_group_end(); }

    GroupSize8Byte group_size_8_byte() const { return GroupSize8Byte{ bytes_.subspan(0) }; }

    view::entries<IncrementalRefreshTradeSummaryLongOrderIdGroup> incremental_refresh_trade_summary_long_order_id_group() const { return view::entries<IncrementalRefreshTradeSummaryLongOrderIdGroup>{ bytes_.subspan(8), wire::count(group_size_8_byte().num_in_group()), wire::count(group_size_8_byte().block_length()) }; }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshTradeSummaryLongOrderIdGroups{";
        out << "group_size_8_byte=";
        group_size_8_byte().print(out);
        out << ", incremental_refresh_trade_summary_long_order_id_group=";
        print::sequence(out, incremental_refresh_trade_summary_long_order_id_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t incremental_refresh_trade_summary_long_order_id_group_end() const { return 8 + incremental_refresh_trade_summary_long_order_id_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryLongOrderIdGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
