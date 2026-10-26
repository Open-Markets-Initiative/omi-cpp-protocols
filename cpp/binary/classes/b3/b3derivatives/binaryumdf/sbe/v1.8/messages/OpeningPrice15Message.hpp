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
#include "../common/Decimal.hpp"
#include "../enums/MdUpdateAction.hpp"
#include "../enums/OpenCloseSettlFlag.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

class Visitor;

// OpeningPrice_15Message
class OpeningPrice15Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::OpeningPrice15Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 44;

    OpeningPrice15Message() = default;
    OpeningPrice15Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, MdUpdateAction md_update_action, OpenCloseSettlFlag open_close_settl_flag, const std::array<std::byte, 1>& offset_11_padding_1, Decimal md_future_price, std::optional<Decimal> net_chg_prev_day, std::uint16_t trade_date, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq, const std::array<std::byte, 2>& padding_2);

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

    // Open Close Settl Flag: openCloseSettlFlag
    OpenCloseSettlFlag open_close_settl_flag() const;
    void set_open_close_settl_flag(OpenCloseSettlFlag value);

    // Offset 11 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_11_padding_1() const;
    std::array<std::byte, 1>& offset_11_padding_1();
    void set_offset_11_padding_1(const std::array<std::byte, 1>& value);

    // Md Future Price: mDEntryPx
    Decimal md_future_price() const;
    void set_md_future_price(Decimal value);

    // Net Chg Prev Day: netChgPrevDay
    std::optional<Decimal> net_chg_prev_day() const;
    void set_net_chg_prev_day(std::optional<Decimal> value);

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Md Entry Timestamp: mDEntryTimestamp
    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const;
    void set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value);

    // Rpt Seq: rptSeq
    std::optional<std::uint32_t> rpt_seq() const;
    void set_rpt_seq(std::optional<std::uint32_t> value);

    // Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& padding_2() const;
    std::array<std::byte, 2>& padding_2();
    void set_padding_2(const std::array<std::byte, 2>& value);

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

    bool operator==(const OpeningPrice15Message& other) const;
    bool operator!=(const OpeningPrice15Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    MdUpdateAction md_update_action_{};
    OpenCloseSettlFlag open_close_settl_flag_{};
    std::array<std::byte, 1> offset_11_padding_1_{};
    Decimal md_future_price_{ 0, -4 };
    std::optional<Decimal> net_chg_prev_day_{};
    std::uint16_t trade_date_{};
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
    std::optional<std::uint32_t> rpt_seq_{};
    std::array<std::byte, 2> padding_2_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
