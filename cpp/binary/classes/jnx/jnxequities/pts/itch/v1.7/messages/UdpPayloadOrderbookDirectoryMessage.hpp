#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Group.hpp"
#include "../messages/PacketMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

class PacketMessageVisitor;

// Orderbook Directory Messages provide information about orderbooks available in the Japannext
// PTS execution system.
class UdpPayloadOrderbookDirectoryMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::OrderbookDirectoryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 44;

    UdpPayloadOrderbookDirectoryMessage() = default;
    UdpPayloadOrderbookDirectoryMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t orderbook_id, const std::string& orderbook_code, const std::string& group, std::uint32_t round_lot_size, std::uint32_t price_tick_size_table_id, std::uint32_t price_decimals, Decimal upper_price_limit, Decimal lower_price_limit);

    // Nanoseconds: Number of nanoseconds since last Timestamp Seconds Message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Orderbook Id: 4 digit Quick code.
    std::uint32_t orderbook_id() const;
    void set_orderbook_id(std::uint32_t value);

    // Orderbook Code: International Securities Identification Number (ISIN).
    const std::string& orderbook_code() const;
    std::string& orderbook_code();
    void set_orderbook_code(const std::string& value);

    // Group: Orderbook group identifier.
    const std::string& group() const;
    std::string& group();
    void set_group(const std::string& value);

    // Round Lot Size: Number of shares that represent a round lot.
    std::uint32_t round_lot_size() const;
    void set_round_lot_size(std::uint32_t value);

    // Price Tick Size Table Id: Price tick size table identifier.
    std::uint32_t price_tick_size_table_id() const;
    void set_price_tick_size_table_id(std::uint32_t value);

    // Price Decimals: Number of decimal places in price fields; value is 1.
    std::uint32_t price_decimals() const;
    void set_price_decimals(std::uint32_t value);

    // Upper Price Limit: Maximum tradable price.
    Decimal upper_price_limit() const;
    void set_upper_price_limit(Decimal value);

    // Lower Price Limit: Minimum tradable price.
    Decimal lower_price_limit() const;
    void set_lower_price_limit(Decimal value);

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

    bool operator==(const UdpPayloadOrderbookDirectoryMessage& other) const;
    bool operator!=(const UdpPayloadOrderbookDirectoryMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t orderbook_id_{};
    std::string orderbook_code_{};
    std::string group_{};
    std::uint32_t round_lot_size_{};
    std::uint32_t price_tick_size_table_id_{};
    std::uint32_t price_decimals_{};
    Decimal upper_price_limit_{ 0, -1 };
    Decimal lower_price_limit_{ 0, -1 };
};

} // namespace jnx::jnxequities::pts::itch::v1_7
