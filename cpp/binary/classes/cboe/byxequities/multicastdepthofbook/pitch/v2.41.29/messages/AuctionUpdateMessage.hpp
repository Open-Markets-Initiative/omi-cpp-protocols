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

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

class Visitor;

// On the BYX Exchange, Auction Update messages will be sent out at a randomized time between
// the start of an auction period and the end of the auction period minus 1 millisecond to
// inform participants that a Periodic Auction is taking place
class AuctionUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 45;

    AuctionUpdateMessage() = default;
    AuctionUpdateMessage(std::chrono::nanoseconds time_offset, const std::string& symbol_long, AuctionType auction_type, std::uint64_t reference_price, std::uint32_t buy_shares, std::uint32_t sell_shares, std::uint64_t indicative_price, std::uint64_t auction_only_price);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Symbol Long: Symbol
    const std::string& symbol_long() const;
    std::string& symbol_long();
    void set_symbol_long(const std::string& value);

    // Auction Type: Auction Type
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Reference Price: Collared price at which the periodic auction would trade
    std::uint64_t reference_price() const;
    void set_reference_price(std::uint64_t value);

    // Buy Shares: Paired size of eligible periodic auction orders at the Reference Price
    std::uint32_t buy_shares() const;
    void set_buy_shares(std::uint32_t value);

    // Sell Shares: Paired size of eligible periodic auction orders at the Reference Price.
    std::uint32_t sell_shares() const;
    void set_sell_shares(std::uint32_t value);

    // Indicative Price: N/A. Populated with zero
    std::uint64_t indicative_price() const;
    void set_indicative_price(std::uint64_t value);

    // Auction Only Price: N/A. Populated with zero
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
    std::string symbol_long_{};
    AuctionType auction_type_{};
    std::uint64_t reference_price_{};
    std::uint32_t buy_shares_{};
    std::uint32_t sell_shares_{};
    std::uint64_t indicative_price_{};
    std::uint64_t auction_only_price_{};
};

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
