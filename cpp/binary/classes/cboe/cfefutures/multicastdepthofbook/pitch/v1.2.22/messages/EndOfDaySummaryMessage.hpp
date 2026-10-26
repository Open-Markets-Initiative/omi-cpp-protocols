#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/SummaryFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

class Visitor;

// The End of Day Summary message is sent immediately after trading ends for a symbol. No more
// Market Update messages will follow an End of Day Summary message for a particular symbol.
class EndOfDaySummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::EndOfDaySummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 63;

    EndOfDaySummaryMessage() = default;
    EndOfDaySummaryMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, std::uint32_t trade_date, std::uint32_t open_interest, Decimal high_price, Decimal low_price, Decimal open_price, Decimal close_price, std::uint32_t total_volume, std::uint32_t block_volume, std::uint32_t ecrp_volume, const SummaryFlags& summary_flags);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Symbol: Six character, base 62 symbol.
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Trade Date: Current Trade Date
    std::uint32_t trade_date() const;
    void set_trade_date(std::uint32_t value);

    // Open Interest: Open Interest for this symbol.
    std::uint32_t open_interest() const;
    void set_open_interest(std::uint32_t value);

    // High Price: The higher of highest bid price and highest trade price for the day. Block
    // and ECRP trades (Trade Condition=B or E) do not update High Price.
    Decimal high_price() const;
    void set_high_price(Decimal value);

    // Low Price: The lower of lowest offer price and lowest trade price for the day. Block and
    // ECRP trades (Trade Condition=B or E) do not update Low Price.
    Decimal low_price() const;
    void set_low_price(Decimal value);

    // Open Price: The first trade on the day (in any session) will set the Open Price for the
    // day (valid only if Total Volume > 0). Block and ECRP trades (Trade Condition=B or E) do
    // not update Open Price.
    Decimal open_price() const;
    void set_open_price(Decimal value);

    // Close Price: The last trade on the day (in any session) will set the Close Price for the
    // day (valid only if Total Volume > 0). Block and ECRP trades (Trade Condition=B or E) do
    // not update Close Price.
    Decimal close_price() const;
    void set_close_price(Decimal value);

    // Total Volume: Total number of contracts traded for the day, including block and ECRP
    // trades.
    std::uint32_t total_volume() const;
    void set_total_volume(std::uint32_t value);

    // Block Volume: Total number of block and derived contracts traded for the day.
    std::uint32_t block_volume() const;
    void set_block_volume(std::uint32_t value);

    // Ecrp Volume: Total number of contracts traded for the day.
    std::uint32_t ecrp_volume() const;
    void set_ecrp_volume(std::uint32_t value);

    // Summary Flags: Summary Flags bitfields
    const SummaryFlags& summary_flags() const;
    SummaryFlags& summary_flags();
    void set_summary_flags(const SummaryFlags& value);

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

    bool operator==(const EndOfDaySummaryMessage& other) const;
    bool operator!=(const EndOfDaySummaryMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string symbol_{};
    std::uint32_t trade_date_{};
    std::uint32_t open_interest_{};
    Decimal high_price_{ 0, -4 };
    Decimal low_price_{ 0, -4 };
    Decimal open_price_{ 0, -4 };
    Decimal close_price_{ 0, -4 };
    std::uint32_t total_volume_{};
    std::uint32_t block_volume_{};
    std::uint32_t ecrp_volume_{};
    SummaryFlags summary_flags_{};
};

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
