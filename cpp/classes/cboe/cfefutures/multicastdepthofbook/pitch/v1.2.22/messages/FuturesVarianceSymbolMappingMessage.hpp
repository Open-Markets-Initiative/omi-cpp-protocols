#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

class Visitor;

// The Futures Variance Symbol Mapping message is used to disseminate symbol reference data for
// S&P 500 Variance Futures (VA Futures) symbols.
class FuturesVarianceSymbolMappingMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::FuturesVarianceSymbolMappingMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 38;

    FuturesVarianceSymbolMappingMessage() = default;
    FuturesVarianceSymbolMappingMessage(std::chrono::nanoseconds time_offset, std::uint32_t unit_timestamp, const std::string& feed_symbol, const std::string& futures_symbol, Decimal accrued_day_variance, std::uint16_t num_final_returns, std::uint16_t num_elapsed_returns);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Unit Timestamp: Unit timestamp expressed as number of whole seconds since the Epoch
    // (Midnight, January 1, 1970 UTC).
    std::uint32_t unit_timestamp() const;
    void set_unit_timestamp(std::uint32_t value);

    // Feed Symbol: Six character, base 62 symbol.
    const std::string& feed_symbol() const;
    std::string& feed_symbol();
    void set_feed_symbol(const std::string& value);

    // Futures Symbol: Twelve character textual definition of the symbol where the first six
    // characters contain the product symbol, left justified, and padded on the right with
    // spaces, and the right most six characters are the expiration date in YYMMDD format.
    const std::string& futures_symbol() const;
    std::string& futures_symbol();
    void set_futures_symbol(const std::string& value);

    // Accrued Day Variance: Accrued day variance as of the start of the trading day (signed
    // 64-bit decimal with twelve implied decimal places).
    Decimal accrued_day_variance() const;
    void set_accrued_day_variance(Decimal value);

    // Num Final Returns: Number of S&P 500 Index returns used in the Final Settlement Value
    // calculation.
    std::uint16_t num_final_returns() const;
    void set_num_final_returns(std::uint16_t value);

    // Num Elapsed Returns: Number of elapsed S&P 500 Index returns including the current day.
    std::uint16_t num_elapsed_returns() const;
    void set_num_elapsed_returns(std::uint16_t value);

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

    bool operator==(const FuturesVarianceSymbolMappingMessage& other) const;
    bool operator!=(const FuturesVarianceSymbolMappingMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint32_t unit_timestamp_{};
    std::string feed_symbol_{};
    std::string futures_symbol_{};
    Decimal accrued_day_variance_{ 0, -12 };
    std::uint16_t num_final_returns_{};
    std::uint16_t num_elapsed_returns_{};
};

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
