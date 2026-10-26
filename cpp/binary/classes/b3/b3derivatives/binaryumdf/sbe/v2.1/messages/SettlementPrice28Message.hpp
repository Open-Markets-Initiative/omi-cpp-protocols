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
#include "../enums/PriceType.hpp"
#include "../enums/SettlPriceType.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

class Visitor;

// SettlementPrice_28Message
class SettlementPrice28Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::SettlementPrice28Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    SettlementPrice28Message() = default;
    SettlementPrice28Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 1>& offset_9_padding_1, std::uint16_t trade_date, Decimal md_future_price, std::optional<std::chrono::nanoseconds> md_entry_timestamp, OpenCloseSettlFlag open_close_settl_flag, PriceType price_type, SettlPriceType settl_price_type, std::optional<std::uint32_t> rpt_seq, const std::array<std::byte, 1>& padding_1);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Offset 9 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_9_padding_1() const;
    std::array<std::byte, 1>& offset_9_padding_1();
    void set_offset_9_padding_1(const std::array<std::byte, 1>& value);

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Md Future Price: mDEntryPx
    Decimal md_future_price() const;
    void set_md_future_price(Decimal value);

    // Md Entry Timestamp: mDEntryTimestamp
    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const;
    void set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value);

    // Open Close Settl Flag: openCloseSettlFlag
    OpenCloseSettlFlag open_close_settl_flag() const;
    void set_open_close_settl_flag(OpenCloseSettlFlag value);

    // Price Type: priceType
    PriceType price_type() const;
    void set_price_type(PriceType value);

    // Settl Price Type: settlPriceType
    SettlPriceType settl_price_type() const;
    void set_settl_price_type(SettlPriceType value);

    // Rpt Seq: rptSeq
    std::optional<std::uint32_t> rpt_seq() const;
    void set_rpt_seq(std::optional<std::uint32_t> value);

    // Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& padding_1() const;
    std::array<std::byte, 1>& padding_1();
    void set_padding_1(const std::array<std::byte, 1>& value);

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

    bool operator==(const SettlementPrice28Message& other) const;
    bool operator!=(const SettlementPrice28Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    std::array<std::byte, 1> offset_9_padding_1_{};
    std::uint16_t trade_date_{};
    Decimal md_future_price_{ 0, -4 };
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
    OpenCloseSettlFlag open_close_settl_flag_{};
    PriceType price_type_{};
    SettlPriceType settl_price_type_{};
    std::optional<std::uint32_t> rpt_seq_{};
    std::array<std::byte, 1> padding_1_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
