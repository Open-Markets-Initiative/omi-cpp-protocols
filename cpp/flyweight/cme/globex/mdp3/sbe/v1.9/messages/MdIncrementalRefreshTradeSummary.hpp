#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../structs/IncrementalRefreshTradeSummaryGroups.hpp"
#include "../structs/IncrementalRefreshTradeSummaryOrderIdGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// MDIncrementalRefreshTradeSummary
class MdIncrementalRefreshTradeSummary {
  public:
    static constexpr const char* name = "MdIncrementalRefreshTradeSummary";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MdIncrementalRefreshTradeSummary(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MdIncrementalRefreshTradeSummary has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 11;
    std::size_t encoded_size() const { return incremental_refresh_trade_summary_order_id_groups_end(); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    std::span<const std::byte, 2> padding_2() const { return bytes_.subspan(9).template first<2>(); }

    IncrementalRefreshTradeSummaryGroups incremental_refresh_trade_summary_groups() const { return IncrementalRefreshTradeSummaryGroups{ bytes_.subspan(11) }; }

    IncrementalRefreshTradeSummaryOrderIdGroups incremental_refresh_trade_summary_order_id_groups() const {
        wire::require("MdIncrementalRefreshTradeSummary", incremental_refresh_trade_summary_groups_end() + IncrementalRefreshTradeSummaryOrderIdGroups::minimum_size, bytes_.size());
        return IncrementalRefreshTradeSummaryOrderIdGroups{ bytes_.subspan(incremental_refresh_trade_summary_groups_end()) };
    }

    void print(std::ostream& out) const {
        out << "MdIncrementalRefreshTradeSummary{";
        out << "transact_time=";
        out << transact_time().count();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", padding_2=";
        print::hex(out, padding_2().data(), padding_2().size());
        out << ", incremental_refresh_trade_summary_groups=";
        incremental_refresh_trade_summary_groups().print(out);
        out << ", incremental_refresh_trade_summary_order_id_groups=";
        incremental_refresh_trade_summary_order_id_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t incremental_refresh_trade_summary_groups_end() const { return 11 + incremental_refresh_trade_summary_groups().encoded_size(); }
    std::size_t incremental_refresh_trade_summary_order_id_groups_end() const { return incremental_refresh_trade_summary_groups_end() + incremental_refresh_trade_summary_order_id_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MdIncrementalRefreshTradeSummary& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
