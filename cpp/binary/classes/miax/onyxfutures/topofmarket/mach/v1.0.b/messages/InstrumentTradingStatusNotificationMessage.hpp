#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/MarketState.hpp"
#include "../enums/TradingStatus.hpp"
#include "../messages/Data.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

class DataVisitor;

// Used to notify firms of changes to the trading status of a particular Simple or Complex
// instrument
class InstrumentTradingStatusNotificationMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::InstrumentTradingStatusNotificationMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 14;

    InstrumentTradingStatusNotificationMessage() = default;
    InstrumentTradingStatusNotificationMessage(std::chrono::nanoseconds timestamp, std::uint32_t instrument_id, TradingStatus trading_status, MarketState market_state);

    // Timestamp: Matching Engine time
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Instrument Id: Unique ID assigned by MIAX Futures Onyx
    std::uint32_t instrument_id() const;
    void set_instrument_id(std::uint32_t value);

    // Trading Status: Trading Status
    TradingStatus trading_status() const;
    void set_trading_status(TradingStatus value);

    // Market State: Market State
    MarketState market_state() const;
    void set_market_state(MarketState value);

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

    bool operator==(const InstrumentTradingStatusNotificationMessage& other) const;
    bool operator!=(const InstrumentTradingStatusNotificationMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t instrument_id_{};
    TradingStatus trading_status_{};
    MarketState market_state_{};
};

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
