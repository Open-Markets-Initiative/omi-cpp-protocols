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
#include "../enums/SecurityTradingEvent.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../enums/TradingSessionId.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

class Visitor;

// SecurityStatus_3Message
class SecurityStatus3Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::SecurityStatus3Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    SecurityStatus3Message() = default;
    SecurityStatus3Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, TradingSessionId trading_session_id, SecurityTradingStatus security_trading_status, std::optional<SecurityTradingEvent> security_trading_event, std::uint16_t trade_date, const std::array<std::byte, 2>& offset_14_padding_2, std::optional<std::chrono::nanoseconds> trad_ses_open_time, std::optional<std::uint64_t> transact_time, std::optional<std::uint32_t> rpt_seq);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Trading Session Id: tradingSessionID
    TradingSessionId trading_session_id() const;
    void set_trading_session_id(TradingSessionId value);

    // Security Trading Status: securityTradingStatus
    SecurityTradingStatus security_trading_status() const;
    void set_security_trading_status(SecurityTradingStatus value);

    // Security Trading Event: securityTradingEvent
    std::optional<SecurityTradingEvent> security_trading_event() const;
    void set_security_trading_event(std::optional<SecurityTradingEvent> value);

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Offset 14 Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& offset_14_padding_2() const;
    std::array<std::byte, 2>& offset_14_padding_2();
    void set_offset_14_padding_2(const std::array<std::byte, 2>& value);

    // Trad Ses Open Time: tradSesOpenTime
    std::optional<std::chrono::nanoseconds> trad_ses_open_time() const;
    void set_trad_ses_open_time(std::optional<std::chrono::nanoseconds> value);

    // Transact Time: transactTime
    std::optional<std::uint64_t> transact_time() const;
    void set_transact_time(std::optional<std::uint64_t> value);

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

    bool operator==(const SecurityStatus3Message& other) const;
    bool operator!=(const SecurityStatus3Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    TradingSessionId trading_session_id_{};
    SecurityTradingStatus security_trading_status_{};
    std::optional<SecurityTradingEvent> security_trading_event_{};
    std::uint16_t trade_date_{};
    std::array<std::byte, 2> offset_14_padding_2_{};
    std::optional<std::chrono::nanoseconds> trad_ses_open_time_{};
    std::optional<std::uint64_t> transact_time_{};
    std::optional<std::uint32_t> rpt_seq_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
