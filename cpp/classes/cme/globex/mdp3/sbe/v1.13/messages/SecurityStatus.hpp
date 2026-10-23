#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/HaltReason.hpp"
#include "../enums/SecurityTradingEvent.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../messages/MktdataPayload.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class MktdataPayloadVisitor;

// SecurityStatus
class SecurityStatus : public MktdataPayload {
  public:
    // The code that selects this message
    static constexpr MktdataPayloadCode message_type = TemplateId::SecurityStatus;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 30;

    SecurityStatus() = default;
    SecurityStatus(std::chrono::nanoseconds transact_time, const std::string& security_group, const std::string& asset, std::optional<std::int32_t> security_id_optional, std::optional<std::uint16_t> trade_date, const MatchEventIndicator& match_event_indicator, std::optional<SecurityTradingStatus> security_trading_status, HaltReason halt_reason, SecurityTradingEvent security_trading_event);

    // Transact Time: Start of event processing time in number of nanoseconds since Unix epoch
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Security Group: Security Group
    const std::string& security_group() const;
    std::string& security_group();
    void set_security_group(const std::string& value);

    // Asset: Product Code within Security Group specified
    const std::string& asset() const;
    std::string& asset();
    void set_asset(const std::string& value);

    // Security Id Optional: If this tag is present, 35=f message is sent for the instrument
    std::optional<std::int32_t> security_id_optional() const;
    void set_security_id_optional(std::optional<std::int32_t> value);

    // Trade Date: Trade Session Date
    std::optional<std::uint16_t> trade_date() const;
    void set_trade_date(std::optional<std::uint16_t> value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Security Trading Status: Identifies the trading status applicable to the instrument or
    // Security Group
    std::optional<SecurityTradingStatus> security_trading_status() const;
    void set_security_trading_status(std::optional<SecurityTradingStatus> value);

    // Halt Reason: Identifies the reason for the status change
    HaltReason halt_reason() const;
    void set_halt_reason(HaltReason value);

    // Security Trading Event: Identifies an additional event or a rule related to the status
    SecurityTradingEvent security_trading_event() const;
    void set_security_trading_event(SecurityTradingEvent value);

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

    bool operator==(const SecurityStatus& other) const;
    bool operator!=(const SecurityStatus& other) const;

  private:
    std::chrono::nanoseconds transact_time_{};
    std::string security_group_{};
    std::string asset_{};
    std::optional<std::int32_t> security_id_optional_{};
    std::optional<std::uint16_t> trade_date_{};
    MatchEventIndicator match_event_indicator_{};
    std::optional<SecurityTradingStatus> security_trading_status_{};
    HaltReason halt_reason_{};
    SecurityTradingEvent security_trading_event_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
