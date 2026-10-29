#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/AuctionOpeningType.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

class Visitor;

// Options Auction Update messages are used to disseminate price and size information during
// the Opening and Re-Opening (halt) process for complex instruments.
class AuctionUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 62;

    AuctionUpdateMessage() = default;
    AuctionUpdateMessage(std::chrono::nanoseconds time_offset, const std::string& complex_instrument_id_8, AuctionOpeningType auction_opening_type, Decimal reference_price, std::uint32_t buy_contracts, std::uint32_t sell_contracts, Decimal indicative_price, Decimal auction_only_price, char opening_condition, Decimal composite_market_bid_price, Decimal composite_market_offer_price);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Complex Instrument Id 8: Complex Instrument Id right padded with spaces.
    const std::string& complex_instrument_id_8() const;
    std::string& complex_instrument_id_8();
    void set_complex_instrument_id_8(const std::string& value);

    // Auction Opening Type: Auction Opening Type
    AuctionOpeningType auction_opening_type() const;
    void set_auction_opening_type(AuctionOpeningType value);

    // Reference Price: Not used for complex series. Will contain zero value.
    Decimal reference_price() const;
    void set_reference_price(Decimal value);

    // Buy Contracts: Cumulative Buy interest at the Indicative Price.
    std::uint32_t buy_contracts() const;
    void set_buy_contracts(std::uint32_t value);

    // Sell Contracts: Cumulative Sell interest at the Indicative Price.
    std::uint32_t sell_contracts() const;
    void set_sell_contracts(std::uint32_t value);

    // Indicative Price: SNBBO Collared Volume Maximizing Imbalance Minimizing Price computed
    // on combined Auction-Only and Continuous Book (if any).
    Decimal indicative_price() const;
    void set_indicative_price(Decimal value);

    // Auction Only Price: Not used for complex series. Will contain zero value.
    Decimal auction_only_price() const;
    void set_auction_only_price(Decimal value);

    // Opening Condition: Not used for Complex series. Will contain zero value.
    char opening_condition() const;
    void set_opening_condition(char value);

    // Composite Market Bid Price: Not used for Complex series. Will contain zero value.
    Decimal composite_market_bid_price() const;
    void set_composite_market_bid_price(Decimal value);

    // Composite Market Offer Price: Not used for complex series. Will contain zero value.
    Decimal composite_market_offer_price() const;
    void set_composite_market_offer_price(Decimal value);

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
    std::string complex_instrument_id_8_{};
    AuctionOpeningType auction_opening_type_{};
    Decimal reference_price_{ 0, -4 };
    std::uint32_t buy_contracts_{};
    std::uint32_t sell_contracts_{};
    Decimal indicative_price_{ 0, -4 };
    Decimal auction_only_price_{ 0, -4 };
    char opening_condition_{};
    Decimal composite_market_bid_price_{ 0, -4 };
    Decimal composite_market_offer_price_{ 0, -4 };
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
