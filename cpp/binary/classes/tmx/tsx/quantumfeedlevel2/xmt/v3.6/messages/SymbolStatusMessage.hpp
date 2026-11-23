// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/SymbolStatusMessage.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Currency.hpp"
#include "../enums/ListingMarket.hpp"
#include "../enums/MocEligible.hpp"
#include "../enums/ProductType.hpp"
#include "../enums/StockState.hpp"
#include "../enums/TestSymbol.hpp"
#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class Visitor;

// Symbol Status Message
class SymbolStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::SymbolStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 66;

    SymbolStatusMessage() = default;
    SymbolStatusMessage(const std::string& symbol, std::optional<std::uint8_t> stock_group, const std::string& cusip, std::optional<std::uint16_t> board_lot, Currency currency, std::optional<Decimal> face_value, std::optional<Decimal> last_sale, ListingMarket listing_market, ProductType product_type, std::optional<std::uint32_t> buy_maximum_quantity, std::optional<std::uint32_t> buy_minimum_quantity, std::optional<std::uint32_t> sell_maximum_quantity, std::optional<std::uint32_t> sell_minimum_quantity, const std::string& stock_state, TestSymbol test_symbol, MocEligible moc_eligible);

    // Symbol: A Unique Alphanumeric Identifier For A Security
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Stock Group: An Identifier Of The Stock Group
    std::optional<std::uint8_t> stock_group() const;
    void set_stock_group(std::optional<std::uint8_t> value);

    // Cusip: Clearing And Settlement Registration Number
    const std::string& cusip() const;
    std::string& cusip();
    void set_cusip(const std::string& value);

    // Board Lot: Contains The Board Lot Size
    std::optional<std::uint16_t> board_lot() const;
    void set_board_lot(std::optional<std::uint16_t> value);

    // Currency: The Currency Associated With A Reported Price
    Currency currency() const;
    void set_currency(Currency value);

    // Face Value: The Face Value Of A Debenture
    std::optional<Decimal> face_value() const;
    void set_face_value(std::optional<Decimal> value);

    // Last Sale: Last Sale Price Of A Stock
    std::optional<Decimal> last_sale() const;
    void set_last_sale(std::optional<Decimal> value);

    // Listing Market: The Market On Which A Security Is Listed
    ListingMarket listing_market() const;
    void set_listing_market(ListingMarket value);

    // Product Type: The Product Type For A Symbol
    ProductType product_type() const;
    void set_product_type(ProductType value);

    // Buy Maximum Quantity: The Maximum Quantity Of A Mutual Fund Allowed To Purchase
    std::optional<std::uint32_t> buy_maximum_quantity() const;
    void set_buy_maximum_quantity(std::optional<std::uint32_t> value);

    // Buy Minimum Quantity: The Minimum Quantity Of A Mutual Fund Required To Purchase
    std::optional<std::uint32_t> buy_minimum_quantity() const;
    void set_buy_minimum_quantity(std::optional<std::uint32_t> value);

    // Sell Maximum Quantity: The Maximum Quantity Of A Mutual Fund Allowed To Sell
    std::optional<std::uint32_t> sell_maximum_quantity() const;
    void set_sell_maximum_quantity(std::optional<std::uint32_t> value);

    // Sell Minimum Quantity: The Minimum Quantity Of A Mutual Fund Required To Sell
    std::optional<std::uint32_t> sell_minimum_quantity() const;
    void set_sell_minimum_quantity(std::optional<std::uint32_t> value);

    // Stock State: The State Of The Stock
    const std::string& stock_state() const;
    std::string& stock_state();
    void set_stock_state(const std::string& value);

    // Test Symbol: Indicates The Symbol Is A Test Symbol
    TestSymbol test_symbol() const;
    void set_test_symbol(TestSymbol value);

    // Moc Eligible: Identifies Whether The Stock Is Eligible To Trade In The Market On Close
    // Session Each Trading Day
    MocEligible moc_eligible() const;
    void set_moc_eligible(MocEligible value);

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

    bool operator==(const SymbolStatusMessage& other) const;
    bool operator!=(const SymbolStatusMessage& other) const;

  private:
    std::string symbol_{};
    std::optional<std::uint8_t> stock_group_{};
    std::string cusip_{};
    std::optional<std::uint16_t> board_lot_{};
    Currency currency_{};
    std::optional<Decimal> face_value_{};
    std::optional<Decimal> last_sale_{};
    ListingMarket listing_market_{};
    ProductType product_type_{};
    std::optional<std::uint32_t> buy_maximum_quantity_{};
    std::optional<std::uint32_t> buy_minimum_quantity_{};
    std::optional<std::uint32_t> sell_maximum_quantity_{};
    std::optional<std::uint32_t> sell_minimum_quantity_{};
    std::string stock_state_{};
    TestSymbol test_symbol_{};
    MocEligible moc_eligible_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
