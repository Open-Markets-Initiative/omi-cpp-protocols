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
#include "../enums/OpenCloseSettlFlag.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

class Visitor;

// ClosingPrice_17Message
class ClosingPrice17Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ClosingPrice17Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    ClosingPrice17Message() = default;
    ClosingPrice17Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, OpenCloseSettlFlag open_close_settl_flag, const std::array<std::byte, 2>& offset_10_padding_2, Decimal md_corporate_price, std::optional<std::uint16_t> last_trade_date, std::uint16_t trade_date, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Open Close Settl Flag: openCloseSettlFlag
    OpenCloseSettlFlag open_close_settl_flag() const;
    void set_open_close_settl_flag(OpenCloseSettlFlag value);

    // Offset 10 Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& offset_10_padding_2() const;
    std::array<std::byte, 2>& offset_10_padding_2();
    void set_offset_10_padding_2(const std::array<std::byte, 2>& value);

    // Md Corporate Price: mDEntryPx
    Decimal md_corporate_price() const;
    void set_md_corporate_price(Decimal value);

    // Last Trade Date: lastTradeDate
    std::optional<std::uint16_t> last_trade_date() const;
    void set_last_trade_date(std::optional<std::uint16_t> value);

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

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

    bool operator==(const ClosingPrice17Message& other) const;
    bool operator!=(const ClosingPrice17Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    OpenCloseSettlFlag open_close_settl_flag_{};
    std::array<std::byte, 2> offset_10_padding_2_{};
    Decimal md_corporate_price_{ 0, -8 };
    std::optional<std::uint16_t> last_trade_date_{};
    std::uint16_t trade_date_{};
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
    std::optional<std::uint32_t> rpt_seq_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
