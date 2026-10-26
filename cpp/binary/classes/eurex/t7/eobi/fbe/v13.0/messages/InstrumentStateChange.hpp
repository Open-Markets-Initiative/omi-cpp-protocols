#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/FastMarketIndicator.hpp"
#include "../enums/MarketCondition.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/SecurityTradingEvent.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../enums/SoldOutIndicator.hpp"
#include "../enums/TesSecurityStatus.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class Visitor;

// Instrument State Change
class InstrumentStateChange : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::InstrumentStateChange;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 48;

    InstrumentStateChange() = default;
    InstrumentStateChange(std::optional<std::int64_t> security_id, std::optional<SecurityStatus> security_status, std::optional<SecurityTradingStatus> security_trading_status, std::optional<MarketCondition> market_condition, std::optional<FastMarketIndicator> fast_market_indicator, std::optional<SecurityTradingEvent> security_trading_event, std::optional<SoldOutIndicator> sold_out_indicator, const std::array<std::byte, 2>& pad2, std::optional<Decimal> high_px, std::optional<Decimal> low_px, std::optional<std::chrono::nanoseconds> transact_time, std::optional<TesSecurityStatus> tes_security_status, const std::array<std::byte, 7>& pad7);

    // Security Id:
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Security Status:
    std::optional<SecurityStatus> security_status() const;
    void set_security_status(std::optional<SecurityStatus> value);

    // Security Trading Status:
    std::optional<SecurityTradingStatus> security_trading_status() const;
    void set_security_trading_status(std::optional<SecurityTradingStatus> value);

    // Market Condition:
    std::optional<MarketCondition> market_condition() const;
    void set_market_condition(std::optional<MarketCondition> value);

    // Fast Market Indicator:
    std::optional<FastMarketIndicator> fast_market_indicator() const;
    void set_fast_market_indicator(std::optional<FastMarketIndicator> value);

    // Security Trading Event:
    std::optional<SecurityTradingEvent> security_trading_event() const;
    void set_security_trading_event(std::optional<SecurityTradingEvent> value);

    // Sold Out Indicator:
    std::optional<SoldOutIndicator> sold_out_indicator() const;
    void set_sold_out_indicator(std::optional<SoldOutIndicator> value);

    // Pad2:
    const std::array<std::byte, 2>& pad2() const;
    std::array<std::byte, 2>& pad2();
    void set_pad2(const std::array<std::byte, 2>& value);

    // High Px:
    std::optional<Decimal> high_px() const;
    void set_high_px(std::optional<Decimal> value);

    // Low Px:
    std::optional<Decimal> low_px() const;
    void set_low_px(std::optional<Decimal> value);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

    // Tes Security Status:
    std::optional<TesSecurityStatus> tes_security_status() const;
    void set_tes_security_status(std::optional<TesSecurityStatus> value);

    // Pad7:
    const std::array<std::byte, 7>& pad7() const;
    std::array<std::byte, 7>& pad7();
    void set_pad7(const std::array<std::byte, 7>& value);

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
    std::optional<MarketCondition> market_condition_{};
    std::optional<FastMarketIndicator> fast_market_indicator_{};
    std::optional<SecurityTradingEvent> security_trading_event_{};
    std::optional<SoldOutIndicator> sold_out_indicator_{};
    std::array<std::byte, 2> pad2_{};
    std::optional<Decimal> high_px_{};
    std::optional<Decimal> low_px_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
    std::optional<TesSecurityStatus> tes_security_status_{};
    std::array<std::byte, 7> pad7_{};
};

} // namespace eurex::t7::eobi::fbe::v13_0
