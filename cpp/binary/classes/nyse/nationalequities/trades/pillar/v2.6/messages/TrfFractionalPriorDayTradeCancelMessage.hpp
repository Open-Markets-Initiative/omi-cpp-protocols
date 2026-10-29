#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

class Visitor;

// If a TRF participant firm discovers that it has reported a trade with an inaccurate price or
// volume on a previous day, the firm may correct the trade on a subsequent day by publishing a
// Prior Day Trade Cancel message, followed by a Prior Day Trade. New message effective
// 1/12/26.
class TrfFractionalPriorDayTradeCancelMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TrfFractionalPriorDayTradeCancelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    TrfFractionalPriorDayTradeCancelMessage() = default;
    TrfFractionalPriorDayTradeCancelMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t trade_id, std::int32_t price, std::uint64_t fractional_volume, std::uint32_t prior_day_time, std::uint32_t prior_day_time_ns);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Time Ns: The nanosecond offset from the Source Time
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Symbol Index: The ID of the symbol in the Symbol Index message
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Symbol Seq Num: The symbol sequence number.
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Trade Id: Unique identifier for this trade.
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Price: The price of the Trade. Use the Price scale from the Symbol Index Mapping
    // message.
    std::int32_t price() const;
    void set_price(std::int32_t value);

    // Fractional Volume: The volume of the trade in shares, inclusive of any fractional
    // quantity. Implied scale is 6.
    std::uint64_t fractional_volume() const;
    void set_fractional_volume(std::uint64_t value);

    // Prior Day Time: The date and time when this Trade occurred at the participant firm, in
    // seconds since Jan 1, 1970 00:00:00 UTC.
    std::uint32_t prior_day_time() const;
    void set_prior_day_time(std::uint32_t value);

    // Prior Day Time Ns: The nanosecond offset from the Prior Day Time
    std::uint32_t prior_day_time_ns() const;
    void set_prior_day_time_ns(std::uint32_t value);

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

    bool operator==(const TrfFractionalPriorDayTradeCancelMessage& other) const;
    bool operator!=(const TrfFractionalPriorDayTradeCancelMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint32_t trade_id_{};
    std::int32_t price_{};
    std::uint64_t fractional_volume_{};
    std::uint32_t prior_day_time_{};
    std::uint32_t prior_day_time_ns_{};
};

} // namespace nyse::nationalequities::trades::pillar::v2_6
