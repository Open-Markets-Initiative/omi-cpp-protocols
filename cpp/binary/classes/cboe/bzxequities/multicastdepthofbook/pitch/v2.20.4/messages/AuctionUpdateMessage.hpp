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

// Auction Update message
class AuctionUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 45;

    AuctionUpdateMessage() = default;
    AuctionUpdateMessage(std::chrono::nanoseconds time_offset, const std::string& stock_symbol, AuctionType auction_type, std::uint64_t reference_price, std::uint32_t buy_shares, std::uint32_t sell_shares, std::uint64_t indicative_price, std::uint64_t auction_only_price);

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

    // Reference Price: BBO Collared auction price (see Auction Process Spec)
    std::uint64_t reference_price() const;
    void set_reference_price(std::uint64_t value);

    // Buy Shares: Number of shares on buy side at the Reference Price
    std::uint32_t buy_shares() const;
    void set_buy_shares(std::uint32_t value);

    // Sell Shares: Number of shares on sell side at the Reference Price
    std::uint32_t sell_shares() const;
    void set_sell_shares(std::uint32_t value);

    // Indicative Price: Price at which the auction book and the continuous book would match
    std::uint64_t indicative_price() const;
    void set_indicative_price(std::uint64_t value);

    // Auction Only Price: Price at which the auction book would match using only Eligible
    // Auction
    std::uint64_t auction_only_price() const;
    void set_auction_only_price(std::uint64_t value);

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

    bool operator==(const AuctionUpdateMessage& other) const;
    bool operator!=(const AuctionUpdateMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string stock_symbol_{};
    AuctionType auction_type_{};
    std::uint64_t reference_price_{};
    std::uint32_t buy_shares_{};
    std::uint32_t sell_shares_{};
    std::uint64_t indicative_price_{};
    std::uint64_t auction_only_price_{};
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
