#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/RetailLiquidityIndicator.hpp"
#include "../messages/IexTpMessageData.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

class IexTpMessageDataVisitor;

// broadcasts a real-time Retail Liquidity Indicator Message each time there is an update to
// IEX's eligible retail liquidity interest during the trading day
class RetailLiquidityIndicatorMessage : public IexTpMessageData {
  public:
    // The code that selects this message
    static constexpr IexTpMessageDataCode message_type = IexTpMessageType::RetailLiquidityIndicatorMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    RetailLiquidityIndicatorMessage() = default;
    RetailLiquidityIndicatorMessage(RetailLiquidityIndicator retail_liquidity_indicator, std::chrono::nanoseconds timestamp, const std::string& symbol);

    // Retail Liquidity Indicator: Retail Liquidity Indicator identifier
    RetailLiquidityIndicator retail_liquidity_indicator() const;
    void set_retail_liquidity_indicator(RetailLiquidityIndicator value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // IexTpMessageData
    IexTpMessageDataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(IexTpMessageDataVisitor& visitor) const override;
    std::unique_ptr<IexTpMessageData> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const IexTpMessageData& other) const override;

    bool operator==(const RetailLiquidityIndicatorMessage& other) const;
    bool operator!=(const RetailLiquidityIndicatorMessage& other) const;

  private:
    RetailLiquidityIndicator retail_liquidity_indicator_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
};

} // namespace iex::iexequities::deepplus::snap::v1_05
