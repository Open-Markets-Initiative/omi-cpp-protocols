#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/FastMarketIndicator.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Provides state information for a single instrument.
class InstrumentStateChangeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::InstrumentStateChangeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    InstrumentStateChangeMessage() = default;
    InstrumentStateChangeMessage(std::int64_t security_id, SecurityStatus security_status, SecurityTradingStatus security_trading_status, FastMarketIndicator fast_market_indicator, const std::array<std::byte, 5>& pad_5, std::chrono::nanoseconds transact_time);

    // Security Id: Unique instrument identifier.
    std::int64_t security_id() const;
    void set_security_id(std::int64_t value);

    // Security Status: Instrument status.
    SecurityStatus security_status() const;
    void set_security_status(SecurityStatus value);

    // Security Trading Status: Instrument state status.
    SecurityTradingStatus security_trading_status() const;
    void set_security_trading_status(SecurityTradingStatus value);

    // Fast Market Indicator: Indicates if product is in the state Fast Market.
    FastMarketIndicator fast_market_indicator() const;
    void set_fast_market_indicator(FastMarketIndicator value);

    // Pad 5: not used
    const std::array<std::byte, 5>& pad_5() const;
    std::array<std::byte, 5>& pad_5();
    void set_pad_5(const std::array<std::byte, 5>& value);

    // Transact Time: Transaction timestamp.
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

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

    bool operator==(const InstrumentStateChangeMessage& other) const;
    bool operator!=(const InstrumentStateChangeMessage& other) const;

  private:
    std::int64_t security_id_{};
    SecurityStatus security_status_{};
    SecurityTradingStatus security_trading_status_{};
    FastMarketIndicator fast_market_indicator_{};
    std::array<std::byte, 5> pad_5_{};
    std::chrono::nanoseconds transact_time_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
