#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/FinancialProduct.hpp"
#include "../enums/PutOrCall.hpp"
#include "../messages/Message.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

class Visitor;

// Disseminated for all active securities at start of day or intra-day.
class OrderBookDirectory : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderBookDirectory;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 128;

    OrderBookDirectory() = default;
    OrderBookDirectory(std::chrono::nanoseconds nanoseconds, std::uint32_t order_book_id, const std::string& symbol, const std::string& long_name, const std::string& isin, FinancialProduct financial_product, const std::string& trading_currency, std::uint16_t decimals_in_price, std::uint16_t decimals_in_nominal_value, std::uint32_t odd_lot_size, std::uint32_t round_lot_size, std::uint32_t block_lot_size, std::uint64_t nominal_value, std::uint8_t number_of_legs, std::uint32_t underlying_orderbook_id, std::int32_t strike_price, std::uint32_t expiration_date, std::uint16_t decimals_in_strike_price, PutOrCall put_or_call);

    // Nanoseconds: Nanoseconds portion
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Order Book Id: Primary identifier of an order book
    std::uint32_t order_book_id() const;
    void set_order_book_id(std::uint32_t value);

    // Symbol: Security short name
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Long Name: Human-readable long name
    const std::string& long_name() const;
    std::string& long_name();
    void set_long_name(const std::string& value);

    // Isin: ISIN code
    const std::string& isin() const;
    std::string& isin();
    void set_isin(const std::string& value);

    // Financial Product: Product type
    FinancialProduct financial_product() const;
    void set_financial_product(FinancialProduct value);

    // Trading Currency: Trading currency
    const std::string& trading_currency() const;
    std::string& trading_currency();
    void set_trading_currency(const std::string& value);

    // Decimals In Price: Number of decimals in price (256=fractions)
    std::uint16_t decimals_in_price() const;
    void set_decimals_in_price(std::uint16_t value);

    // Decimals In Nominal Value: Number of decimals in Nominal Value
    std::uint16_t decimals_in_nominal_value() const;
    void set_decimals_in_nominal_value(std::uint16_t value);

    // Odd Lot Size: Odd lot size
    std::uint32_t odd_lot_size() const;
    void set_odd_lot_size(std::uint32_t value);

    // Round Lot Size: Round lot size
    std::uint32_t round_lot_size() const;
    void set_round_lot_size(std::uint32_t value);

    // Block Lot Size: Block lot size
    std::uint32_t block_lot_size() const;
    void set_block_lot_size(std::uint32_t value);

    // Nominal Value: Nominal value
    std::uint64_t nominal_value() const;
    void set_nominal_value(std::uint64_t value);

    // Number Of Legs: Only for combination instruments
    std::uint8_t number_of_legs() const;
    void set_number_of_legs(std::uint8_t value);

    // Underlying Orderbook Id: Underlying instrument ID
    std::uint32_t underlying_orderbook_id() const;
    void set_underlying_orderbook_id(std::uint32_t value);

    // Strike Price: Derivative strike price
    std::int32_t strike_price() const;
    void set_strike_price(std::int32_t value);

    // Expiration Date: Date of expiration
    std::uint32_t expiration_date() const;
    void set_expiration_date(std::uint32_t value);

    // Decimals In Strike Price: Decimals in Strike Price
    std::uint16_t decimals_in_strike_price() const;
    void set_decimals_in_strike_price(std::uint16_t value);

    // Put Or Call: 1=Call, 2=Put
    PutOrCall put_or_call() const;
    void set_put_or_call(PutOrCall value);

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

    bool operator==(const OrderBookDirectory& other) const;
    bool operator!=(const OrderBookDirectory& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t order_book_id_{};
    std::string symbol_{};
    std::string long_name_{};
    std::string isin_{};
    FinancialProduct financial_product_{};
    std::string trading_currency_{};
    std::uint16_t decimals_in_price_{};
    std::uint16_t decimals_in_nominal_value_{};
    std::uint32_t odd_lot_size_{};
    std::uint32_t round_lot_size_{};
    std::uint32_t block_lot_size_{};
    std::uint64_t nominal_value_{};
    std::uint8_t number_of_legs_{};
    std::uint32_t underlying_orderbook_id_{};
    std::int32_t strike_price_{};
    std::uint32_t expiration_date_{};
    std::uint16_t decimals_in_strike_price_{};
    PutOrCall put_or_call_{};
};

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
