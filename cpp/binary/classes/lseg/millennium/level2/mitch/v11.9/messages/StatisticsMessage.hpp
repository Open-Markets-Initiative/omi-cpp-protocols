// Lseg.Millennium.Level2.Mitch.v11.9: messages/StatisticsMessage.hpp
#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/StatisticsReserved.hpp"
#include "../common/Decimal.hpp"
#include "../enums/OpenClosePriceIndicator.hpp"
#include "../enums/StatisticType.hpp"
#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// Used to disseminate official Opening and Closing prices
class StatisticsMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StatisticsMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 21;

    StatisticsMessage() = default;
    StatisticsMessage(std::chrono::nanoseconds nanosecond, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, StatisticType statistic_type, Decimal price, OpenClosePriceIndicator open_close_price_indicator, const StatisticsReserved& statistics_reserved);

    // Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
    std::chrono::nanoseconds nanosecond() const;
    void set_nanosecond(std::chrono::nanoseconds value);

    // Instrument Id: Instrument's symbol.
    std::uint32_t instrument_id() const;
    void set_instrument_id(std::uint32_t value);

    // Reserved A: Reserved field
    const std::array<std::byte, 1>& reserved_a() const;
    std::array<std::byte, 1>& reserved_a();
    void set_reserved_a(const std::array<std::byte, 1>& value);

    // Reserved B: Reserved field
    const std::array<std::byte, 1>& reserved_b() const;
    std::array<std::byte, 1>& reserved_b();
    void set_reserved_b(const std::array<std::byte, 1>& value);

    // Statistic Type: Statistic Type
    StatisticType statistic_type() const;
    void set_statistic_type(StatisticType value);

    // Price: Limit price of the order.
    Decimal price() const;
    void set_price(Decimal value);

    // Open Close Price Indicator:
    OpenClosePriceIndicator open_close_price_indicator() const;
    void set_open_close_price_indicator(OpenClosePriceIndicator value);

    // Statistics Reserved: Reserved for future use
    const StatisticsReserved& statistics_reserved() const;
    StatisticsReserved& statistics_reserved();
    void set_statistics_reserved(const StatisticsReserved& value);

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

    bool operator==(const StatisticsMessage& other) const;
    bool operator!=(const StatisticsMessage& other) const;

  private:
    std::chrono::nanoseconds nanosecond_{};
    std::uint32_t instrument_id_{};
    std::array<std::byte, 1> reserved_a_{};
    std::array<std::byte, 1> reserved_b_{};
    StatisticType statistic_type_{};
    Decimal price_{ 0, -8 };
    OpenClosePriceIndicator open_close_price_indicator_{};
    StatisticsReserved statistics_reserved_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
