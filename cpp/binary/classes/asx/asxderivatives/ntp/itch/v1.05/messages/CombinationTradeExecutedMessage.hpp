#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/BuyerSide.hpp"
#include "../enums/SellerSide.hpp"
#include "../enums/TradeType.hpp"
#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// The Combination Trade Executed Message is designed to provide details for executions where
// one or both orders are resting from a different order book id from the order book id of the
// trade
class CombinationTradeExecutedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::CombinationTradeExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 79;

    CombinationTradeExecutedMessage() = default;
    CombinationTradeExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, TradeType trade_type, std::uint64_t trade_id, std::uint32_t executed_quantity, Decimal trade_price, std::uint32_t buyer_tradeable_instrument_id, BuyerSide buyer_side, std::uint64_t buyer_order_id, std::uint64_t buyer_combination_trade_id, const std::string& buyer_participant_id, std::uint32_t seller_tradeable_instrument_id, SellerSide seller_side, std::uint64_t seller_order_id, std::uint64_t seller_combination_trade_id, const std::string& seller_participant_id);

    // Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Trade Date: Trade Date. Represented as number of days since 1 January 1970.
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Tradeable Instrument Id: Identifier of the Order Book.
    std::uint32_t tradeable_instrument_id() const;
    void set_tradeable_instrument_id(std::uint32_t value);

    // Trade Type: Nature of the match
    TradeType trade_type() const;
    void set_trade_type(TradeType value);

    // Trade Id: Public trade id of the trade.
    std::uint64_t trade_id() const;
    void set_trade_id(std::uint64_t value);

    // Executed Quantity: Volume traded.
    std::uint32_t executed_quantity() const;
    void set_executed_quantity(std::uint32_t value);

    // Trade Price: Price of trade (may be negative for combination trades).
    Decimal trade_price() const;
    void set_trade_price(Decimal value);

    // Buyer Tradeable Instrument Id: Identifier of the Buyers Order Book.
    std::uint32_t buyer_tradeable_instrument_id() const;
    void set_buyer_tradeable_instrument_id(std::uint32_t value);

    // Buyer Side: Type of order
    BuyerSide buyer_side() const;
    void set_buyer_side(BuyerSide value);

    // Buyer Order Id: Reference number of the Buyer’s order – 0 if order is aggressive.
    std::uint64_t buyer_order_id() const;
    void set_buyer_order_id(std::uint64_t value);

    // Buyer Combination Trade Id: A non-zero value indicates that this trade is part of an
    // execution cycle for a combination trade from the E or P message.
    std::uint64_t buyer_combination_trade_id() const;
    void set_buyer_combination_trade_id(std::uint64_t value);

    // Buyer Participant Id: Buying participant identifier of the owner of the aggressive
    // order.
    const std::string& buyer_participant_id() const;
    std::string& buyer_participant_id();
    void set_buyer_participant_id(const std::string& value);

    // Seller Tradeable Instrument Id: Identifier of the Seller’s Order Book.
    std::uint32_t seller_tradeable_instrument_id() const;
    void set_seller_tradeable_instrument_id(std::uint32_t value);

    // Seller Side: Type of order
    SellerSide seller_side() const;
    void set_seller_side(SellerSide value);

    // Seller Order Id: Reference number of the Seller’s order – 0 if order is aggressive.
    std::uint64_t seller_order_id() const;
    void set_seller_order_id(std::uint64_t value);

    // Seller Combination Trade Id: A non-zero value indicates that this trade is part of an
    // execution cycle for a combination trade from the E or P message.
    std::uint64_t seller_combination_trade_id() const;
    void set_seller_combination_trade_id(std::uint64_t value);

    // Seller Participant Id: Selling participant identifier of the owner of the aggressive
    // order.
    const std::string& seller_participant_id() const;
    std::string& seller_participant_id();
    void set_seller_participant_id(const std::string& value);

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

    bool operator==(const CombinationTradeExecutedMessage& other) const;
    bool operator!=(const CombinationTradeExecutedMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::uint32_t tradeable_instrument_id_{};
    TradeType trade_type_{};
    std::uint64_t trade_id_{};
    std::uint32_t executed_quantity_{};
    Decimal trade_price_{ 0, -2 };
    std::uint32_t buyer_tradeable_instrument_id_{};
    BuyerSide buyer_side_{};
    std::uint64_t buyer_order_id_{};
    std::uint64_t buyer_combination_trade_id_{};
    std::string buyer_participant_id_{};
    std::uint32_t seller_tradeable_instrument_id_{};
    SellerSide seller_side_{};
    std::uint64_t seller_order_id_{};
    std::uint64_t seller_combination_trade_id_{};
    std::string seller_participant_id_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
