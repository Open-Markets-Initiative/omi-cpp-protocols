#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/AuctionType.hpp"
#include "../messages/Message.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

class Visitor;

// Auction Summary message
class AuctionSummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    AuctionSummaryMessage() = default;
    AuctionSummaryMessage(std::chrono::nanoseconds time_offset, const std::string& stock_symbol, AuctionType auction_type, std::uint64_t price_binary_8, std::uint32_t shares);

    // Time Offset: Nanosecond offset from last
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Stock Symbol: Stock Symbol right padded with spaces
    const std::string& stock_symbol() const;
    std::string& stock_symbol();
    void set_stock_symbol(const std::string& value);

    // Auction Type: "O" = Opening Auction "C" = Closing Auction "H" = Halt Auction "I" = IPO
    // Auction
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Price Binary 8: Auction price
    std::uint64_t price_binary_8() const;
    void set_price_binary_8(std::uint64_t value);

    // Shares: Cumulative number of shares executed
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
    std::uint64_t price_binary_8_{};
    std::uint32_t shares_{};
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
