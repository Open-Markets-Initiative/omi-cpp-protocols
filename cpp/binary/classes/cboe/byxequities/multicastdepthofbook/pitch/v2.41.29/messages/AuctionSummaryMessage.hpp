#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

class Visitor;

// Auction Summary messages are used to disseminate the results of an auction of a complex
// instrument. An Opening or Re-Opening Auction Summary message for each complex instrument is
// sent at the conclusion of its Opening or Re-Opening auction and represents Cboe opening
// price.
class AuctionSummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    AuctionSummaryMessage() = default;
    AuctionSummaryMessage(std::chrono::nanoseconds time_offset, const std::string& symbol_long, char auction_opening_type, Decimal price, std::uint32_t shares_contracts);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Symbol Long: Symbol
    const std::string& symbol_long() const;
    std::string& symbol_long();
    void set_symbol_long(const std::string& value);

    // Auction Opening Type: Auction Opening Type
    char auction_opening_type() const;
    void set_auction_opening_type(char value);

    // Price: The limit order price
    Decimal price() const;
    void set_price(Decimal value);

    // Shares Contracts: Cumulative number of shares/contracts executed during the auction or
    // CMC match
    std::uint32_t shares_contracts() const;
    void set_shares_contracts(std::uint32_t value);

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
    std::string symbol_long_{};
    char auction_opening_type_{};
    Decimal price_{ 0, -4 };
    std::uint32_t shares_contracts_{};
};

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
