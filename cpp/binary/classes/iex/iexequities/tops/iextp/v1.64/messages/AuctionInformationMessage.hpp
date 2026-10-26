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
#include "../enums/ImbalanceSide.hpp"
#include "../messages/Message.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

class Visitor;

// Broadcasts an Auction Information Message every one second between the Lock-in Time and the
// auction match for Opening and Closing Auctions, and during the Display Only Period for IPO,
// Halt, and Volatility Auctions.
class AuctionInformationMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionInformationMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 79;

    AuctionInformationMessage() = default;
    AuctionInformationMessage(AuctionType auction_type, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint32_t paired_shares, Decimal reference_price, Decimal indicative_clearing_price, std::uint32_t imbalance_shares, ImbalanceSide imbalance_side, char extension_number, std::chrono::seconds scheduled_auction_time, Decimal auction_book_clearing_price, Decimal collar_reference_price, Decimal lower_auction_collar, Decimal upper_auction_collar);

    // Auction Type: Auction type identifier
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Paired Shares: Number of shares paired at the Reference Price using orders on the
    // Auction Book
    std::uint32_t paired_shares() const;
    void set_paired_shares(std::uint32_t value);

    // Reference Price: Clearing price at or within the Reference Price Range using orders on
    // the Auction Book
    Decimal reference_price() const;
    void set_reference_price(Decimal value);

    // Indicative Clearing Price: Clearing price using Eligible Auction Orders
    Decimal indicative_clearing_price() const;
    void set_indicative_clearing_price(Decimal value);

    // Imbalance Shares: Number of unpaired shares at the Reference Price using orders on the
    // Auction Book
    std::uint32_t imbalance_shares() const;
    void set_imbalance_shares(std::uint32_t value);

    // Imbalance Side: Side of the unpaired shares at the Reference Price using orders on the
    // Auction Book
    ImbalanceSide imbalance_side() const;
    void set_imbalance_side(ImbalanceSide value);

    // Extension Number: Number of extensions an auction received
    char extension_number() const;
    void set_extension_number(char value);

    // Scheduled Auction Time: Projected time of the auction match
    std::chrono::seconds scheduled_auction_time() const;
    void set_scheduled_auction_time(std::chrono::seconds value);

    // Auction Book Clearing Price: Clearing price using orders on the Auction Book
    Decimal auction_book_clearing_price() const;
    void set_auction_book_clearing_price(Decimal value);

    // Collar Reference Price: Reference priced used for the auction collar, if any
    Decimal collar_reference_price() const;
    void set_collar_reference_price(Decimal value);

    // Lower Auction Collar: Lower threshold price of the auction collar, if any
    Decimal lower_auction_collar() const;
    void set_lower_auction_collar(Decimal value);

    // Upper Auction Collar: Upper threshold price of the auction collar, if any
    Decimal upper_auction_collar() const;
    void set_upper_auction_collar(Decimal value);

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

    bool operator==(const AuctionInformationMessage& other) const;
    bool operator!=(const AuctionInformationMessage& other) const;

  private:
    AuctionType auction_type_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
    std::uint32_t paired_shares_{};
    Decimal reference_price_{ 0, -4 };
    Decimal indicative_clearing_price_{ 0, -4 };
    std::uint32_t imbalance_shares_{};
    ImbalanceSide imbalance_side_{};
    char extension_number_{};
    std::chrono::seconds scheduled_auction_time_{};
    Decimal auction_book_clearing_price_{ 0, -4 };
    Decimal collar_reference_price_{ 0, -4 };
    Decimal lower_auction_collar_{ 0, -4 };
    Decimal upper_auction_collar_{ 0, -4 };
};

} // namespace iex::iexequities::tops::iextp::v1_64
