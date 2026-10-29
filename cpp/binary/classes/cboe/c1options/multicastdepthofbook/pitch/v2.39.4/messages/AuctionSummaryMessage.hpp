#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/AuctionType.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

class Visitor;

// Auction Summary messages are used to disseminate the results of an auction of a Cboe listed
// security.
class AuctionSummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    AuctionSummaryMessage() = default;
    AuctionSummaryMessage(std::chrono::nanoseconds time_offset, const std::string& stock_symbol, AuctionType auction_type, Decimal long_price, std::uint32_t shares);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Stock Symbol: Stock Symbol right padded with spaces.
    const std::string& stock_symbol() const;
    std::string& stock_symbol();
    void set_stock_symbol(const std::string& value);

    // Auction Type: Auction type value
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Long Price: The limit order price
    Decimal long_price() const;
    void set_long_price(Decimal value);

    // Shares: Cumulative number of shares executed during the auction.
    std::uint32_t shares() const;
    void set_shares(std::uint32_t value);

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

    bool operator==(const AuctionSummaryMessage& other) const;
    bool operator!=(const AuctionSummaryMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string stock_symbol_{};
    AuctionType auction_type_{};
    Decimal long_price_{ 0, -4 };
    std::uint32_t shares_{};
};

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
