// Databento.MarketData.Normalized.Dbn.v3: messages/RecordBodyOhlcvMsg.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/GatewayMessage.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

class GatewayMessageVisitor;

// Open, high, low, close, and volume; the record of the ohlcv schemas
class RecordBodyOhlcvMsg : public GatewayMessage {
  public:
    // The code that selects this message
    static constexpr GatewayMessageCode message_type = Rtype::OhlcvEndOfDay;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    RecordBodyOhlcvMsg() = default;
    RecordBodyOhlcvMsg(std::optional<Decimal> open, std::optional<Decimal> high, std::optional<Decimal> low, std::optional<Decimal> close, std::uint64_t volume);

    // Open: The open price for the bar
    std::optional<Decimal> open() const;
    void set_open(std::optional<Decimal> value);

    // High: The high price for the bar
    std::optional<Decimal> high() const;
    void set_high(std::optional<Decimal> value);

    // Low: The low price for the bar
    std::optional<Decimal> low() const;
    void set_low(std::optional<Decimal> value);

    // Close: The close price for the bar
    std::optional<Decimal> close() const;
    void set_close(std::optional<Decimal> value);

    // Volume: The total volume traded during the aggregation period
    std::uint64_t volume() const;
    void set_volume(std::uint64_t value);

    // GatewayMessage
    GatewayMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(GatewayMessageVisitor& visitor) const override;
    std::unique_ptr<GatewayMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const GatewayMessage& other) const override;

    bool operator==(const RecordBodyOhlcvMsg& other) const;
    bool operator!=(const RecordBodyOhlcvMsg& other) const;

  private:
    std::optional<Decimal> open_{};
    std::optional<Decimal> high_{};
    std::optional<Decimal> low_{};
    std::optional<Decimal> close_{};
    std::uint64_t volume_{};
};

} // namespace databento::marketdata::normalized::dbn::v3
