#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/SecurityTradingStatus.hpp"
#include "../enums/SecurityTradingStatusReason.hpp"
#include "../messages/Payload.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

class PayloadVisitor;

// SecurityTradingStatusMessage
class SecurityTradingStatusMessage : public Payload {
  public:
    // The code that selects this message
    static constexpr PayloadCode message_type = TemplateId::SecurityTradingStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 12;

    SecurityTradingStatusMessage() = default;
    SecurityTradingStatusMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, SecurityTradingStatus security_trading_status, SecurityTradingStatusReason security_trading_status_reason);

    // Timestamp: Timestamp
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Security Id: SecurityID
    std::uint16_t security_id() const;
    void set_security_id(std::uint16_t value);

    // Security Trading Status: SecurityTradingStatus
    SecurityTradingStatus security_trading_status() const;
    void set_security_trading_status(SecurityTradingStatus value);

    // Security Trading Status Reason: SecurityTradingStatusReason
    SecurityTradingStatusReason security_trading_status_reason() const;
    void set_security_trading_status_reason(SecurityTradingStatusReason value);

    // Payload
    PayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PayloadVisitor& visitor) const override;
    std::unique_ptr<Payload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Payload& other) const override;

    bool operator==(const SecurityTradingStatusMessage& other) const;
    bool operator!=(const SecurityTradingStatusMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t security_id_{};
    SecurityTradingStatus security_trading_status_{};
    SecurityTradingStatusReason security_trading_status_reason_{};
};

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
