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
#include "../enums/OpeningCondition.hpp"
#include "../messages/Message.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

class Visitor;

// Options Only. Options Auction Update messages are used to disseminate price and size
// information and Composite Market bid and offer prices during Opening and Re-Opening (halt)
// auctions on the Cboe Options Exchange. Options Auction Update messages are sent every five
// seconds during an opening period provided that one of the field values has changed. When no
// values have changed, a message is sent once every 60 seconds. Refer to the Cboe Options
// Opening Process specification for more information.
class OptionsAuctionUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsAuctionUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 62;

    OptionsAuctionUpdateMessage() = default;
    OptionsAuctionUpdateMessage(std::chrono::nanoseconds time_offset, const std::string& expanded_symbol, AuctionType auction_type, Decimal reference_price, std::uint32_t buy_contracts, std::uint32_t sell_contracts, Decimal indicative_price, Decimal auction_only_price, OpeningCondition opening_condition, Decimal composite_market_bid_price, Decimal composite_market_offer_price);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Expanded Symbol: Symbol right padded with spaces.
    const std::string& expanded_symbol() const;
    std::string& expanded_symbol();
    void set_expanded_symbol(const std::string& value);

    // Auction Type: G = GTH Opening (C1 Only), O = RTH Opening (C1 Only), H = Halt Re-Opening,
    // V = Volatility Opening.
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Reference Price: Collared VMIM price computed on the queuing book only.
    Decimal reference_price() const;
    void set_reference_price(Decimal value);

    // Buy Contracts: Cumulative Buy contracts at the Reference Price and above.
    std::uint32_t buy_contracts() const;
    void set_buy_contracts(std::uint32_t value);

    // Sell Contracts: Cumulative Sell contracts at the Reference Price and below.
    std::uint32_t sell_contracts() const;
    void set_sell_contracts(std::uint32_t value);

    // Indicative Price: Collared VMIM price computed on the combined queueing book and the
    // continuous book. Equal to Reference Price for options that do not have a GTH trading
    // session.
    Decimal indicative_price() const;
    void set_indicative_price(Decimal value);

    // Auction Only Price: Uncollared VMIM price computed on the queuing book only.
    Decimal auction_only_price() const;
    void set_auction_only_price(Decimal value);

    // Opening Condition: O = Would open, Q = Need quote to open, B = Need more buyers (C1
    // Only), S = Need more sellers (C1 Only), C = Crossed Composite Market.
    OpeningCondition opening_condition() const;
    void set_opening_condition(OpeningCondition value);

    // Composite Market Bid Price: Bid Price of the prevailing Composite Market.
    Decimal composite_market_bid_price() const;
    void set_composite_market_bid_price(Decimal value);

    // Composite Market Offer Price: Offer Price of the prevailing Composite Market.
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

    bool operator==(const OptionsAuctionUpdateMessage& other) const;
    bool operator!=(const OptionsAuctionUpdateMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string expanded_symbol_{};
    AuctionType auction_type_{};
    Decimal reference_price_{ 0, -4 };
    std::uint32_t buy_contracts_{};
    std::uint32_t sell_contracts_{};
    Decimal indicative_price_{ 0, -4 };
    Decimal auction_only_price_{ 0, -4 };
    OpeningCondition opening_condition_{};
    Decimal composite_market_bid_price_{ 0, -4 };
    Decimal composite_market_offer_price_{ 0, -4 };
};

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
