#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Data.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

class DataVisitor;

// used to disseminate trades that are resulting from executions on MIAX Futures Onyx during
// the current trading session
class LastSaleMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::LastSaleMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    LastSaleMessage() = default;
    LastSaleMessage(std::chrono::nanoseconds timestamp, std::uint32_t instrument_id, std::uint64_t trade_id, Decimal price, std::uint32_t size);

    // Timestamp: Matching Engine time
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Instrument Id: Unique ID assigned by MIAX Futures Onyx
    std::uint32_t instrument_id() const;
    void set_instrument_id(std::uint32_t value);

    // Trade Id: Unique ID assigned by the Matching Engine
    std::uint64_t trade_id() const;
    void set_trade_id(std::uint64_t value);

    // Price: Execution price
    Decimal price() const;
    void set_price(Decimal value);

    // Size: Number of shares executed
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

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

    bool operator==(const LastSaleMessage& other) const;
    bool operator!=(const LastSaleMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t instrument_id_{};
    std::uint64_t trade_id_{};
    Decimal price_{ 0, -9 };
    std::uint32_t size_{};
};

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
