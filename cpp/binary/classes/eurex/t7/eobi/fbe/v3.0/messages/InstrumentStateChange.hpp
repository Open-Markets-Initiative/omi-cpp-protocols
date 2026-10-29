#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../enums/FastMarketIndicator.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

class Visitor;

// Instrument State Change
class InstrumentStateChange : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::InstrumentStateChange;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    InstrumentStateChange() = default;
    InstrumentStateChange(std::optional<std::int64_t> security_id, std::optional<SecurityStatus> security_status, std::optional<SecurityTradingStatus> security_trading_status, std::optional<FastMarketIndicator> fast_market_indicator, const std::array<std::byte, 5>& pad5, std::optional<std::chrono::nanoseconds> transact_time);

    // Security Id:
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Security Status:
    std::optional<SecurityStatus> security_status() const;
    void set_security_status(std::optional<SecurityStatus> value);

    // Security Trading Status:
    std::optional<SecurityTradingStatus> security_trading_status() const;
    void set_security_trading_status(std::optional<SecurityTradingStatus> value);

    // Fast Market Indicator:
    std::optional<FastMarketIndicator> fast_market_indicator() const;
    void set_fast_market_indicator(std::optional<FastMarketIndicator> value);

    // Pad5:
    const std::array<std::byte, 5>& pad5() const;
    std::array<std::byte, 5>& pad5();
    void set_pad5(const std::array<std::byte, 5>& value);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

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

    bool operator==(const InstrumentStateChange& other) const;
    bool operator!=(const InstrumentStateChange& other) const;

  private:
    std::optional<std::int64_t> security_id_{};
    std::optional<SecurityStatus> security_status_{};
    std::optional<SecurityTradingStatus> security_trading_status_{};
    std::optional<FastMarketIndicator> fast_market_indicator_{};
    std::array<std::byte, 5> pad5_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
};

} // namespace eurex::t7::eobi::fbe::v3_0
