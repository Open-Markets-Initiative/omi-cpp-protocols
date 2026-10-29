#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/TradeCond1.hpp"
#include "../enums/TradeCond2.hpp"
#include "../enums/TradeCond3.hpp"
#include "../enums/TradeCond4.hpp"
#include "../messages/Message.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

class Visitor;

// In the event that an earlier trade has been reported with one or multiple fields in error, a
// Trade Correction message is sent.
class TradeCorrectionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeCorrectionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    TradeCorrectionMessage() = default;
    TradeCorrectionMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t original_trade_id, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume, TradeCond1 trade_cond_1, TradeCond2 trade_cond_2, TradeCond3 trade_cond_3, TradeCond4 trade_cond_4);

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

    // Original Trade Id: The original TradeID of the Trade being cancelled.
    std::uint32_t original_trade_id() const;
    void set_original_trade_id(std::uint32_t value);

    // Trade Id: Unique identifier for this trade.
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Price: The price of the Trade. Use the Price scale from the Symbol Index Mapping
    // message.
    std::int32_t price() const;
    void set_price(std::int32_t value);

    // Volume: The volume of the trade in shares.
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Trade Cond 1: Settlement related conditions.
    TradeCond1 trade_cond_1() const;
    void set_trade_cond_1(TradeCond1 value);

    // Trade Cond 2: The reason for Trade Through Exemptions.
    TradeCond2 trade_cond_2() const;
    void set_trade_cond_2(TradeCond2 value);

    // Trade Cond 3: Extended hours/sequencing related conditions.
    TradeCond3 trade_cond_3() const;
    void set_trade_cond_3(TradeCond3 value);

    // Trade Cond 4: SRO Required Detail.
    TradeCond4 trade_cond_4() const;
    void set_trade_cond_4(TradeCond4 value);

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

    bool operator==(const TradeCorrectionMessage& other) const;
    bool operator!=(const TradeCorrectionMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint32_t original_trade_id_{};
    std::uint32_t trade_id_{};
    std::int32_t price_{};
    std::uint32_t volume_{};
    TradeCond1 trade_cond_1_{};
    TradeCond2 trade_cond_2_{};
    TradeCond3 trade_cond_3_{};
    TradeCond4 trade_cond_4_{};
};

} // namespace nyse::nationalequities::trades::pillar::v2_6
