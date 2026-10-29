#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../messages/MktdataPayload.hpp"
#include "../structs/ChannelResetGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

class MktdataPayloadVisitor;

// ChannelReset
class ChannelReset : public MktdataPayload {
  public:
    // The code that selects this message
    static constexpr MktdataPayloadCode message_type = TemplateId::ChannelReset;

    ChannelReset() = default;
    ChannelReset(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, const ChannelResetGroups& channel_reset_groups);

    // Transact Time: Start of event processing time in number of nanoseconds since Unix epoch
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Channel Reset Groups: NoMDEntries Block
    const ChannelResetGroups& channel_reset_groups() const;
    ChannelResetGroups& channel_reset_groups();
    void set_channel_reset_groups(const ChannelResetGroups& value);

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

    bool operator==(const ChannelReset& other) const;
    bool operator!=(const ChannelReset& other) const;

  private:
    std::chrono::nanoseconds transact_time_{};
    MatchEventIndicator match_event_indicator_{};
    ChannelResetGroups channel_reset_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_5
