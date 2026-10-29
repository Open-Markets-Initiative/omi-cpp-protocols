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

// Auction Update messages are used to disseminate Cboe price and size information during
// auctions for Cboe listed securities and for Cboe Market Close (CMC) crosses.
class AuctionUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 45;

    AuctionUpdateMessage() = default;
    AuctionUpdateMessage(std::chrono::nanoseconds time_offset, const std::string& stock_symbol, AuctionType auction_type, Decimal reference_price, std::uint32_t buy_shares, std::uint32_t sell_shares, Decimal indicative_price, Decimal auction_only_price);

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

    // Reference Price: BBO Collared auction price
    Decimal reference_price() const;
    void set_reference_price(Decimal value);

    // Buy Shares: Number of shares on buy side at the Reference Price.
    std::uint32_t buy_shares() const;
    void set_buy_shares(std::uint32_t value);

    // Sell Shares: Number of shares on sell side at the Reference Price.
    std::uint32_t sell_shares() const;
    void set_sell_shares(std::uint32_t value);

    // Indicative Price: Price at which the auction book and the continuous book would match.
    Decimal indicative_price() const;
    void set_indicative_price(Decimal value);

    // Auction Only Price: Price at which the auction book would match using only Eligible
    // Auction Orders
    Decimal auction_only_price() const;
    void set_auction_only_price(Decimal value);

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
    Decimal reference_price_{ 0, -4 };
    std::uint32_t buy_shares_{};
    std::uint32_t sell_shares_{};
    Decimal indicative_price_{ 0, -4 };
    Decimal auction_only_price_{ 0, -4 };
};

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
