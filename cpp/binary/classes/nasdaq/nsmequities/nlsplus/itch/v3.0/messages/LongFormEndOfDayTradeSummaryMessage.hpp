#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/MarketCategory.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class Visitor;

// End of Day Trade Summary carrying eight byte prices.
class LongFormEndOfDayTradeSummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::LongFormEndOfDayTradeSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 49;

    LongFormEndOfDayTradeSummaryMessage() = default;
    LongFormEndOfDayTradeSummaryMessage(const std::string& issue_symbol, MarketCategory market_category, Decimal consolidated_high_price_long, Decimal consolidated_low_price_long, Decimal consolidated_closing_price_long, std::uint64_t consolidated_volume, Decimal consolidated_open_price_long);

    // Issue Symbol: Denotes the Nasdaq-assigned issue symbol of the security for which the
    // trade report is being generated
    const std::string& issue_symbol() const;
    std::string& issue_symbol();
    void set_issue_symbol(const std::string& value);

    // Market Category: Indicates the listing market or listing market tier for the issue
    MarketCategory market_category() const;
    void set_market_category(MarketCategory value);

    // Consolidated High Price Long: The consolidated high price for the issue for the trading
    // day
    Decimal consolidated_high_price_long() const;
    void set_consolidated_high_price_long(Decimal value);

    // Consolidated Low Price Long: The consolidated low price for the issue for the trading
    // day
    Decimal consolidated_low_price_long() const;
    void set_consolidated_low_price_long(Decimal value);

    // Consolidated Closing Price Long: The consolidated closing price for the issue for the
    // trading day
    Decimal consolidated_closing_price_long() const;
    void set_consolidated_closing_price_long(Decimal value);

    // Consolidated Volume: Reflects the volume for the Issue Symbol as reported on the
    // consolidated market data feed at the time the trade message was generated
    std::uint64_t consolidated_volume() const;
    void set_consolidated_volume(std::uint64_t value);

    // Consolidated Open Price Long: The consolidated opening price for the issue for the
    // trading day
    Decimal consolidated_open_price_long() const;
    void set_consolidated_open_price_long(Decimal value);

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

    bool operator==(const LongFormEndOfDayTradeSummaryMessage& other) const;
    bool operator!=(const LongFormEndOfDayTradeSummaryMessage& other) const;

  private:
    std::string issue_symbol_{};
    MarketCategory market_category_{};
    Decimal consolidated_high_price_long_{ 0, -4 };
    Decimal consolidated_low_price_long_{ 0, -4 };
    Decimal consolidated_closing_price_long_{ 0, -4 };
    std::uint64_t consolidated_volume_{};
    Decimal consolidated_open_price_long_{ 0, -4 };
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
