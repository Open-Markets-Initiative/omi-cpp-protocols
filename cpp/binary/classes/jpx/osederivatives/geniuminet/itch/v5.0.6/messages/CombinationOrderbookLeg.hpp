#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/LegSide.hpp"
#include "../messages/Message.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

class Visitor;

// Mapping between a combination orderbook and its leg orderbooks.
class CombinationOrderbookLeg : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::CombinationOrderbookLeg;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    CombinationOrderbookLeg() = default;
    CombinationOrderbookLeg(std::chrono::nanoseconds nanoseconds, std::uint32_t combination_orderbook_id, std::uint32_t leg_orderbook_id, LegSide leg_side, std::uint32_t leg_ratio);

    // Nanoseconds: Nanoseconds portion
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Combination Orderbook Id: Identifier of combo orderbook
    std::uint32_t combination_orderbook_id() const;
    void set_combination_orderbook_id(std::uint32_t value);

    // Leg Orderbook Id: Orderbook ID of Leg instrument
    std::uint32_t leg_orderbook_id() const;
    void set_leg_orderbook_id(std::uint32_t value);

    // Leg Side: Leg Side
    LegSide leg_side() const;
    void set_leg_side(LegSide value);

    // Leg Ratio: Leg Ratio
    std::uint32_t leg_ratio() const;
    void set_leg_ratio(std::uint32_t value);

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

    bool operator==(const CombinationOrderbookLeg& other) const;
    bool operator!=(const CombinationOrderbookLeg& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t combination_orderbook_id_{};
    std::uint32_t leg_orderbook_id_{};
    LegSide leg_side_{};
    std::uint32_t leg_ratio_{};
};

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
