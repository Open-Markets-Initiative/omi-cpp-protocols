#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// This message disseminates price band information to the market advising the setting, zeroing
// or adjusting of the Extreme Trade Range price, the Anomalous Order Threshold price and the
// associated ranges for a contract that requires Market Integrity Rules enforcement
class AnomalousOrderThresholdPublishMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AnomalousOrderThresholdPublishMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 58;

    AnomalousOrderThresholdPublishMessage() = default;
    AnomalousOrderThresholdPublishMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Decimal aot_price, Decimal aot_upper_price, Decimal aot_lower_price, Decimal etr_price, Decimal etr_upper_price, Decimal etr_lower_price);

    // Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Trade Date: Trade Date. Represented as number of days since 1 January 1970.
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Tradeable Instrument Id: Identifier of the Order Book.
    std::uint32_t tradeable_instrument_id() const;
    void set_tradeable_instrument_id(std::uint32_t value);

    // Aot Price: Anomalous Order Threshold price (AOT).
    Decimal aot_price() const;
    void set_aot_price(Decimal value);

    // Aot Upper Price: Upper range of the AOT.
    Decimal aot_upper_price() const;
    void set_aot_upper_price(Decimal value);

    // Aot Lower Price: Lower range of the AOT.
    Decimal aot_lower_price() const;
    void set_aot_lower_price(Decimal value);

    // Etr Price: Extreme Trade Range price (ETR), if zero, then MIR is not enforced.
    Decimal etr_price() const;
    void set_etr_price(Decimal value);

    // Etr Upper Price: Upper range of the ETR.
    Decimal etr_upper_price() const;
    void set_etr_upper_price(Decimal value);

    // Etr Lower Price: Lower range of the ETR.
    Decimal etr_lower_price() const;
    void set_etr_lower_price(Decimal value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const AnomalousOrderThresholdPublishMessage& other) const;
    bool operator!=(const AnomalousOrderThresholdPublishMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::uint32_t tradeable_instrument_id_{};
    Decimal aot_price_{ 0, -2 };
    Decimal aot_upper_price_{ 0, -2 };
    Decimal aot_lower_price_{ 0, -2 };
    Decimal etr_price_{ 0, -2 };
    Decimal etr_upper_price_{ 0, -2 };
    Decimal etr_lower_price_{ 0, -2 };
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
