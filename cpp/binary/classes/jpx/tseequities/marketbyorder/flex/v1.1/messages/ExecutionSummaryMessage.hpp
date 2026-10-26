#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/TriggeredSide.hpp"
#include "../messages/Message.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class Visitor;

// Provides summary information about execution. Delivered when an execution occurs.
class ExecutionSummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ExecutionSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 45;

    ExecutionSummaryMessage() = default;
    ExecutionSummaryMessage(std::chrono::microseconds time_microseconds, TriggeredSide triggered_side, std::uint64_t total_volume, std::uint64_t total_invalidation, Decimal last_price, std::uint32_t match_id, std::optional<Decimal> best_offer, std::optional<Decimal> best_bid);

    // Time Microseconds: Time to the nearest microsecond
    std::chrono::microseconds time_microseconds() const;
    void set_time_microseconds(std::chrono::microseconds value);

    // Triggered Side: Indicates the side whose order triggered the execution
    TriggeredSide triggered_side() const;
    void set_triggered_side(TriggeredSide value);

    // Total Volume: Total volume of executed orders in number of shares
    std::uint64_t total_volume() const;
    void set_total_volume(std::uint64_t value);

    // Total Invalidation: Total volume of invalidated orders in number of shares
    std::uint64_t total_invalidation() const;
    void set_total_invalidation(std::uint64_t value);

    // Last Price: Last price at the time the execution was processed
    Decimal last_price() const;
    void set_last_price(Decimal value);

    // Match Id: Identifier assigned per issue on an execution basis, unique and sequential
    // each business day
    std::uint32_t match_id() const;
    void set_match_id(std::uint32_t value);

    // Best Offer: Best offer at the time the execution processing finishes; set to 0 at market
    // close
    std::optional<Decimal> best_offer() const;
    void set_best_offer(std::optional<Decimal> value);

    // Best Bid: Best bid at the time the execution processing finishes; set to 0 at market
    // close
    std::optional<Decimal> best_bid() const;
    void set_best_bid(std::optional<Decimal> value);

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

    bool operator==(const ExecutionSummaryMessage& other) const;
    bool operator!=(const ExecutionSummaryMessage& other) const;

  private:
    std::chrono::microseconds time_microseconds_{};
    TriggeredSide triggered_side_{};
    std::uint64_t total_volume_{};
    std::uint64_t total_invalidation_{};
    Decimal last_price_{ 0, -4 };
    std::uint32_t match_id_{};
    std::optional<Decimal> best_offer_{};
    std::optional<Decimal> best_bid_{};
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
