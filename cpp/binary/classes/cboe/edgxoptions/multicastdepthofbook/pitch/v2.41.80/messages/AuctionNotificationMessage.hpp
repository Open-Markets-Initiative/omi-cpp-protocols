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
#include "../enums/CustomerIndicator.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

class Visitor;

// C1 and EDGX Options Only. Auction Notification messages are used to disseminate order
// details of an auction. Auctions will be available for a defined period of time known as the
// exposure period.
class AuctionNotificationMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionNotificationMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 45;

    AuctionNotificationMessage() = default;
    AuctionNotificationMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, std::uint64_t auction_id, AuctionType auction_type, Side side, Decimal price_long, std::uint32_t contracts, CustomerIndicator customer_indicator, const std::string& participant_id, std::uint32_t auction_end_offset, const std::string& client_id);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Symbol: Symbol right padded with spaces.
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Auction Id: Day specific identifier assigned to this auction.
    std::uint64_t auction_id() const;
    void set_auction_id(std::uint64_t value);

    // Auction Type: G = GTH Opening (C1 Only), O = RTH Opening (C1 Only), H = Halt Re-Opening,
    // V = Volatility Opening.
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Side: B or S.
    Side side() const;
    void set_side(Side value);

    // Price Long: The limit order price.
    Decimal price_long() const;
    void set_price_long(Decimal value);

    // Contracts: Number of contracts available in the auction.
    std::uint32_t contracts() const;
    void set_contracts(std::uint32_t value);

    // Customer Indicator: BZX/C1/EDGX Options Only (space filled on C2 Options and all
    // equities markets). N = Non-Customer, C = Customer, R = Retail Priority order (EDGX
    // Equities only).
    CustomerIndicator customer_indicator() const;
    void set_customer_indicator(CustomerIndicator value);

    // Participant Id: Optionally specified. If specified, MPID (equities) or Executing Firm ID
    // (options) of firm attributed to this quote. Alternatively "RTAL" for retail specified
    // orders (equities). Space filled otherwise.
    const std::string& participant_id() const;
    std::string& participant_id();
    void set_participant_id(const std::string& value);

    // Auction End Offset: Nanosecond offset from last timestamp.
    std::uint32_t auction_end_offset() const;
    void set_auction_end_offset(std::uint32_t value);

    // Client Id: Options Only. Optional user specified value attributed to this quote. Space
    // filled otherwise.
    const std::string& client_id() const;
    std::string& client_id();
    void set_client_id(const std::string& value);

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

    bool operator==(const AuctionNotificationMessage& other) const;
    bool operator!=(const AuctionNotificationMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string symbol_{};
    std::uint64_t auction_id_{};
    AuctionType auction_type_{};
    Side side_{};
    Decimal price_long_{ 0, -4 };
    std::uint32_t contracts_{};
    CustomerIndicator customer_indicator_{};
    std::string participant_id_{};
    std::uint32_t auction_end_offset_{};
    std::string client_id_{};
};

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
