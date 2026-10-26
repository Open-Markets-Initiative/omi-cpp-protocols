#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../messages/MktdataPayload.hpp"
#include "../structs/IncrementalRefreshTradeGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

class MktdataPayloadVisitor;

// MDIncrementalRefreshTrade
class MdIncrementalRefreshTrade : public MktdataPayload {
  public:
    // The code that selects this message
    static constexpr MktdataPayloadCode message_type = TemplateId::MdIncrementalRefreshTrade;

    MdIncrementalRefreshTrade() = default;
    MdIncrementalRefreshTrade(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 2>& padding_2, const IncrementalRefreshTradeGroups& incremental_refresh_trade_groups);

    // Transact Time: Start of event processing time in number of nanoseconds since Unix epoch
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& padding_2() const;
    std::array<std::byte, 2>& padding_2();
    void set_padding_2(const std::array<std::byte, 2>& value);

    // Incremental Refresh Trade Groups: NoMDEntries Block
    const IncrementalRefreshTradeGroups& incremental_refresh_trade_groups() const;
    IncrementalRefreshTradeGroups& incremental_refresh_trade_groups();
    void set_incremental_refresh_trade_groups(const IncrementalRefreshTradeGroups& value);

    // MktdataPayload
    MktdataPayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(MktdataPayloadVisitor& visitor) const override;
    std::unique_ptr<MktdataPayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const MktdataPayload& other) const override;

    bool operator==(const MdIncrementalRefreshTrade& other) const;
    bool operator!=(const MdIncrementalRefreshTrade& other) const;

  private:
    std::chrono::nanoseconds transact_time_{};
    MatchEventIndicator match_event_indicator_{};
    std::array<std::byte, 2> padding_2_{};
    IncrementalRefreshTradeGroups incremental_refresh_trade_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_8
