#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/TradeFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Data.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class DataVisitor;

// This message format is used to publish trade executions for orders not displayed on the
// book. Executions for orders routed and executed in another trading center and trade
// corrections are also published using this message.
class TradeMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::TradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 30;

    TradeMessage() = default;
    TradeMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, std::uint64_t trade_id, std::uint8_t correction_number, Decimal price, std::uint32_t size, const TradeFlags& trade_flags);

    // Nanoseconds: Nanosecond part of Matching Engine time.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Symbol Id: Symbol ID mapped to a given symbol. It is assigned per trading session and is
    // valid for that session.
    std::uint32_t symbol_id() const;
    void set_symbol_id(std::uint32_t value);

    // Trade Id: Unique ID assigned by the Matching Engine.
    std::uint64_t trade_id() const;
    void set_trade_id(std::uint64_t value);

    // Correction Number: Trade correction number. Set to zero for new trades. Increments by 1
    // for each subsequent correction.
    std::uint8_t correction_number() const;
    void set_correction_number(std::uint8_t value);

    // Price: Displayed price.
    Decimal price() const;
    void set_price(Decimal value);

    // Size: Number of displayed shares of the order.
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Trade Flags: Trade flags. Bit 0 indicates SIP reportability; bit 1 indicates Retail
    // Trade participation; bits 2-7 are reserved.
    const TradeFlags& trade_flags() const;
    TradeFlags& trade_flags();
    void set_trade_flags(const TradeFlags& value);

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

    bool operator==(const TradeMessage& other) const;
    bool operator!=(const TradeMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t symbol_id_{};
    std::uint64_t trade_id_{};
    std::uint8_t correction_number_{};
    Decimal price_{ 0, -6 };
    std::uint32_t size_{};
    TradeFlags trade_flags_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
