#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Payload.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

class PayloadVisitor;

// BrokenTradeMessage
class BrokenTradeMessage : public Payload {
  public:
    // The code that selects this message
    static constexpr PayloadCode message_type = TemplateId::BrokenTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 30;

    BrokenTradeMessage() = default;
    BrokenTradeMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, std::uint64_t trade_id, std::uint32_t original_quantity, Decimal original_price);

    // Timestamp: Timestamp
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Security Id: SecurityID
    std::uint16_t security_id() const;
    void set_security_id(std::uint16_t value);

    // Trade Id: TradeId
    std::uint64_t trade_id() const;
    void set_trade_id(std::uint64_t value);

    // Original Quantity: OriginalQuantity
    std::uint32_t original_quantity() const;
    void set_original_quantity(std::uint32_t value);

    // Original Price: OriginalPrice
    Decimal original_price() const;
    void set_original_price(Decimal value);

    // Payload
    PayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PayloadVisitor& visitor) const override;
    std::unique_ptr<Payload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Payload& other) const override;

    bool operator==(const BrokenTradeMessage& other) const;
    bool operator!=(const BrokenTradeMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t security_id_{};
    std::uint64_t trade_id_{};
    std::uint32_t original_quantity_{};
    Decimal original_price_{ 0, -6 };
};

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
