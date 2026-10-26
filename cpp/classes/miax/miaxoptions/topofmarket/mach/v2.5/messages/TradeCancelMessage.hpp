#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/TradeCondition.hpp"
#include "../messages/Data.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class DataVisitor;

// This is the message format that will be used to disseminate canceled Trades that are
// resulting from Trade cancellations or corrections on MIAX during the current trading
// session.
class TradeCancelMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::TradeCancelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 22;

    TradeCancelMessage() = default;
    TradeCancelMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t product_id, std::uint32_t trade_id, std::uint8_t correction_number, Decimal trade_price, std::uint32_t trade_size, TradeCondition trade_condition);

    // Nanoseconds: Time at which this product is added/updated on MIAX system today.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Product Id: MIAX Product ID mapped to a given option. It is assigned per trading session
    // and is valid for that session.
    std::uint32_t product_id() const;
    void set_product_id(std::uint32_t value);

    // Trade Id: Unique Trade ID assigned to every Trade.
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Correction Number: Trade correction number. 0 for New trades. Greater than or equal to 0
    // for trades resulting from corrections/adjustments.
    std::uint8_t correction_number() const;
    void set_correction_number(std::uint8_t value);

    // Trade Price: Price at which this product traded
    Decimal trade_price() const;
    void set_trade_price(Decimal value);

    // Trade Size: Number of contracts executed in this trade
    std::uint32_t trade_size() const;
    void set_trade_size(std::uint32_t value);

    // Trade Condition: Trade Condition Values. Please refer to Appendix A.
    TradeCondition trade_condition() const;
    void set_trade_condition(TradeCondition value);

    // Data
    DataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(DataVisitor& visitor) const override;
    std::unique_ptr<Data> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Data& other) const override;

    bool operator==(const TradeCancelMessage& other) const;
    bool operator!=(const TradeCancelMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t product_id_{};
    std::uint32_t trade_id_{};
    std::uint8_t correction_number_{};
    Decimal trade_price_{ 0, -4 };
    std::uint32_t trade_size_{};
    TradeCondition trade_condition_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
