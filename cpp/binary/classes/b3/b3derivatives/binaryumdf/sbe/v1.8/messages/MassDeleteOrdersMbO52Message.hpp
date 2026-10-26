#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/MdEntryType.hpp"
#include "../enums/MdUpdateAction.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

class Visitor;

// MassDeleteOrders_MBO_52Message
class MassDeleteOrdersMbO52Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::MassDeleteOrdersMbO52Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    MassDeleteOrdersMbO52Message() = default;
    MassDeleteOrdersMbO52Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, MdUpdateAction md_update_action, MdEntryType md_entry_type, const std::array<std::byte, 1>& offset_11_padding_1, std::uint32_t md_entry_position_no, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Md Update Action: mDUpdateAction
    MdUpdateAction md_update_action() const;
    void set_md_update_action(MdUpdateAction value);

    // Md Entry Type: mDEntryType
    MdEntryType md_entry_type() const;
    void set_md_entry_type(MdEntryType value);

    // Offset 11 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_11_padding_1() const;
    std::array<std::byte, 1>& offset_11_padding_1();
    void set_offset_11_padding_1(const std::array<std::byte, 1>& value);

    // Md Entry Position No: mDEntryPositionNo
    std::uint32_t md_entry_position_no() const;
    void set_md_entry_position_no(std::uint32_t value);

    // Md Entry Timestamp: mDEntryTimestamp
    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const;
    void set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value);

    // Rpt Seq: rptSeq
    std::optional<std::uint32_t> rpt_seq() const;
    void set_rpt_seq(std::optional<std::uint32_t> value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const MassDeleteOrdersMbO52Message& other) const;
    bool operator!=(const MassDeleteOrdersMbO52Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    MdUpdateAction md_update_action_{};
    MdEntryType md_entry_type_{};
    std::array<std::byte, 1> offset_11_padding_1_{};
    std::uint32_t md_entry_position_no_{};
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
    std::optional<std::uint32_t> rpt_seq_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
