#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Reason.hpp"
#include "../enums/TradingState.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class PacketMessageVisitor;

// NASDAQ uses this administrative message to indicate the current trading status of a security
// to the trading community.
class PayloadStockTradingActionMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::StockTradingActionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    PayloadStockTradingActionMessage() = default;
    PayloadStockTradingActionMessage(std::chrono::nanoseconds nanoseconds, const std::string& stock, TradingState trading_state, char reserved, const std::string& reason);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Stock: Denotes the security symbol for the issue in NASDAQ Single Book. Refer to
    // Appendix NASDAQ Single Book stock symbol convention information.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Trading State: Indicates the current trading state for the stock.
    TradingState trading_state() const;
    void set_trading_state(TradingState value);

    // Reserved: Reserved.
    char reserved() const;
    void set_reserved(char value);

    // Reason: Trading Action reason.
    const std::string& reason() const;
    std::string& reason();
    void set_reason(const std::string& value);

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

    bool operator==(const PayloadStockTradingActionMessage& other) const;
    bool operator!=(const PayloadStockTradingActionMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::string stock_{};
    TradingState trading_state_{};
    char reserved_{};
    std::string reason_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
