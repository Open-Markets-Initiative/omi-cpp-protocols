#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../enums/HaltReason.hpp"
#include "../enums/SecurityTradingEvent.hpp"
#include "../enums/WorkupTradingStatus.hpp"
#include "../messages/ServerTcpMessage.hpp"
#include "../structs/SecurityStatusWorkupGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class ServerTcpMessageVisitor;

// SecurityStatusWorkup
class ServerPayloadSecurityStatusWorkup : public ServerTcpMessage {
  public:
    // The code that selects this message
    static constexpr ServerTcpMessageCode message_type = TemplateId::SecurityStatusWorkup;

    ServerPayloadSecurityStatusWorkup() = default;
    ServerPayloadSecurityStatusWorkup(std::chrono::nanoseconds transact_time, std::optional<Decimal> md_entry_px_optional_ex, std::int32_t security_id, const MatchEventIndicator& match_event_indicator, std::optional<std::uint16_t> trade_date, std::uint32_t trade_link_id, WorkupTradingStatus workup_trading_status, HaltReason halt_reason, SecurityTradingEvent security_trading_event, const SecurityStatusWorkupGroups& security_status_workup_groups);

    // Transact Time: Start of event processing time in number of nanoseconds since Unix epoch
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Md Entry Px Optional Ex: Workup price
    std::optional<Decimal> md_entry_px_optional_ex() const;
    void set_md_entry_px_optional_ex(std::optional<Decimal> value);

    // Security Id: Security ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Trade Date: Trade Session Date
    std::optional<std::uint16_t> trade_date() const;
    void set_trade_date(std::optional<std::uint16_t> value);

    // Trade Link Id: Contains the workup ID; unique per instrument per day
    std::uint32_t trade_link_id() const;
    void set_trade_link_id(std::uint32_t value);

    // Workup Trading Status: Identifies the trading status applicable to the instrument
    WorkupTradingStatus workup_trading_status() const;
    void set_workup_trading_status(WorkupTradingStatus value);

    // Halt Reason: Identifies the reason for the status change
    HaltReason halt_reason() const;
    void set_halt_reason(HaltReason value);

    // Security Trading Event: Identifies an additional event or a rule related to the status
    SecurityTradingEvent security_trading_event() const;
    void set_security_trading_event(SecurityTradingEvent value);

    // Security Status Workup Groups: NoOrderIDEntries Block
    const SecurityStatusWorkupGroups& security_status_workup_groups() const;
    SecurityStatusWorkupGroups& security_status_workup_groups();
    void set_security_status_workup_groups(const SecurityStatusWorkupGroups& value);

    // ServerTcpMessage
    ServerTcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ServerTcpMessageVisitor& visitor) const override;
    std::unique_ptr<ServerTcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ServerTcpMessage& other) const override;

    bool operator==(const ServerPayloadSecurityStatusWorkup& other) const;
    bool operator!=(const ServerPayloadSecurityStatusWorkup& other) const;

  private:
    std::chrono::nanoseconds transact_time_{};
    std::optional<Decimal> md_entry_px_optional_ex_{};
    std::int32_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    std::optional<std::uint16_t> trade_date_{};
    std::uint32_t trade_link_id_{};
    WorkupTradingStatus workup_trading_status_{};
    HaltReason halt_reason_{};
    SecurityTradingEvent security_trading_event_{};
    SecurityStatusWorkupGroups security_status_workup_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
