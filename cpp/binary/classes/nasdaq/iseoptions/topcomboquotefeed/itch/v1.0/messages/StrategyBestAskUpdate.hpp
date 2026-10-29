#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/QuoteCondition.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

class Visitor;

// The options system will continuously calculate its best offer position for active strategies
// on the options market during the trading day. Whenever the best ask position changes on one
// side but not the other side, the options system will send its best ask update via this feed
// for the affected security
class StrategyBestAskUpdate : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StrategyBestAskUpdate;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 39;

    StrategyBestAskUpdate() = default;
    StrategyBestAskUpdate(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, QuoteCondition quote_condition, Decimal price, std::uint32_t size, std::uint32_t cust_size, std::uint32_t pro_cust_size, std::uint32_t ntt_size, std::uint32_t market_size, std::uint32_t ntt_market_size);

    // Timestamp: The time, expressed as the number of nanoseconds after midnight.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Strategy Id: ISE’s Strategy ID assigned daily, valid while there are any open complex
    // orders for the day
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

    // Quote Condition: <space> = regular quote/autox eligible “X” = Pre-Open/Halted
    QuoteCondition quote_condition() const;
    void set_quote_condition(QuoteCondition value);

    // Price: Best bid or ask price in fixed point format with 6 whole number places followed
    // by 4 decimal digits, the side determined by Message Type.
    Decimal price() const;
    void set_price(Decimal value);

    // Size: Aggregated number of contracts on the bid or ask side being displayed in the
    // options market at the current time.
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Cust Size: Customer Quantity on the bid or ask side.
    std::uint32_t cust_size() const;
    void set_cust_size(std::uint32_t value);

    // Pro Cust Size: Customer professional quantity on the bid or ask side.
    std::uint32_t pro_cust_size() const;
    void set_pro_cust_size(std::uint32_t value);

    // Ntt Size: Limit size that can’t be traded through
    std::uint32_t ntt_size() const;
    void set_ntt_size(std::uint32_t value);

    // Market Size: The aggregate market size.
    std::uint32_t market_size() const;
    void set_market_size(std::uint32_t value);

    // Ntt Market Size: The aggregated NTT Market Size.
    std::uint32_t ntt_market_size() const;
    void set_ntt_market_size(std::uint32_t value);

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

    bool operator==(const StrategyBestAskUpdate& other) const;
    bool operator!=(const StrategyBestAskUpdate& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t strategy_id_{};
    QuoteCondition quote_condition_{};
    Decimal price_{ 0, -4 };
    std::uint32_t size_{};
    std::uint32_t cust_size_{};
    std::uint32_t pro_cust_size_{};
    std::uint32_t ntt_size_{};
    std::uint32_t market_size_{};
    std::uint32_t ntt_market_size_{};
};

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
