#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/PacketMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

class PacketMessageVisitor;

// Price Tick Size Messages define a set of price tick size tables.
class UdpPayloadPriceTickSizeMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::PriceTickSizeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    UdpPayloadPriceTickSizeMessage() = default;
    UdpPayloadPriceTickSizeMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t price_tick_size_table_id, Decimal price_tick_size, Decimal price_start);

    // Nanoseconds: Number of nanoseconds since last Timestamp Seconds Message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Price Tick Size Table Id: Price tick size table identifier.
    std::uint32_t price_tick_size_table_id() const;
    void set_price_tick_size_table_id(std::uint32_t value);

    // Price Tick Size: Price tick size.
    Decimal price_tick_size() const;
    void set_price_tick_size(Decimal value);

    // Price Start: Start of price range for this price tick size.
    Decimal price_start() const;
    void set_price_start(Decimal value);

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

    bool operator==(const UdpPayloadPriceTickSizeMessage& other) const;
    bool operator!=(const UdpPayloadPriceTickSizeMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t price_tick_size_table_id_{};
    Decimal price_tick_size_{ 0, -1 };
    Decimal price_start_{ 0, -1 };
};

} // namespace jnx::jnxequities::pts::itch::v1_7
