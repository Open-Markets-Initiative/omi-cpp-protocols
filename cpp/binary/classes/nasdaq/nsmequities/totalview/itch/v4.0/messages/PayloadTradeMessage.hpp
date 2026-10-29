#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Side.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class PacketMessageVisitor;

// The Trade Message is designed to provide execution details for normal match events involving
// non-displayable order types.
class PayloadTradeMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::TradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 35;

    PayloadTradeMessage() = default;
    PayloadTradeMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_reference_number, Side side, std::uint32_t shares, const std::string& stock, Decimal price, std::uint64_t match_number);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Order Reference Number: The unique reference number assigned to the new order at the
    // time of receipt.
    std::uint64_t order_reference_number() const;
    void set_order_reference_number(std::uint64_t value);

    // Side: The type of order being added.
    Side side() const;
    void set_side(Side value);

    // Shares: The total number of shares associated with the order being added to the book.
    std::uint32_t shares() const;
    void set_shares(std::uint32_t value);

    // Stock: Denotes the security symbol for the issue in NASDAQ Single Book. Refer to
    // Appendix NASDAQ Single Book stock symbol convention information.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Price: The display price of the new order. Refer to Data Types for field processing
    // notes.
    Decimal price() const;
    void set_price(Decimal value);

    // Match Number: The NASDAQ generated day-unique Match Number of this execution. The match
    // number is also referenced in the Trade Break Message.
    std::uint64_t match_number() const;
    void set_match_number(std::uint64_t value);

    // PacketMessage
    PacketMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PacketMessageVisitor& visitor) const override;
    std::unique_ptr<PacketMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const PacketMessage& other) const override;

    bool operator==(const PayloadTradeMessage& other) const;
    bool operator!=(const PayloadTradeMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t order_reference_number_{};
    Side side_{};
    std::uint32_t shares_{};
    std::string stock_{};
    Decimal price_{ 0, -4 };
    std::uint64_t match_number_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
