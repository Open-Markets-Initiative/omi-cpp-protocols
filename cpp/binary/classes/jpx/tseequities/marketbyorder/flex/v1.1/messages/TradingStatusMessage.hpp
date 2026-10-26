#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/MarketStatus.hpp"
#include "../enums/PricingMethod.hpp"
#include "../enums/ShortSellingStatus.hpp"
#include "../enums/StatusFlag.hpp"
#include "../messages/Message.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class Visitor;

// Provides information about the status of trading on a per-issue basis. Delivered when there
// is a change in the tag.
class TradingStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradingStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    TradingStatusMessage() = default;
    TradingStatusMessage(std::chrono::microseconds time_microseconds, MarketStatus market_status, const std::string& status_flag, ShortSellingStatus short_selling_status, PricingMethod pricing_method, Decimal book_center_price);

    // Time Microseconds: Time to the nearest microsecond
    std::chrono::microseconds time_microseconds() const;
    void set_time_microseconds(std::chrono::microseconds value);

    // Market Status: Indicates market status
    MarketStatus market_status() const;
    void set_market_status(MarketStatus value);

    // Status Flag: Indicates trading status
    const std::string& status_flag() const;
    std::string& status_flag();
    void set_status_flag(const std::string& value);

    // Short Selling Status: Indicates application of the Short Selling Regulation
    ShortSellingStatus short_selling_status() const;
    void set_short_selling_status(ShortSellingStatus value);

    // Pricing Method: Indicates method of pricing or status of quote display after the tag is
    // delivered
    PricingMethod pricing_method() const;
    void set_pricing_method(PricingMethod value);

    // Book Center Price: Set to the book center price while the Itayose method is in place or
    // while a quote is displayed
    Decimal book_center_price() const;
    void set_book_center_price(Decimal value);

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

    bool operator==(const TradingStatusMessage& other) const;
    bool operator!=(const TradingStatusMessage& other) const;

  private:
    std::chrono::microseconds time_microseconds_{};
    MarketStatus market_status_{};
    std::string status_flag_{};
    ShortSellingStatus short_selling_status_{};
    PricingMethod pricing_method_{};
    Decimal book_center_price_{ 0, -4 };
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
