#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Published whenever a visible order is partially executed at its displayed price.
class PartialOrderExecutionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::PartialOrderExecutionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 56;

    PartialOrderExecutionMessage() = default;
    PartialOrderExecutionMessage(Side side, const std::array<std::byte, 7>& pad_7, Decimal price, std::chrono::nanoseconds trd_reg_ts_time_priority, std::int64_t security_id, std::uint32_t trd_match_id, const std::array<std::byte, 4>& pad_4, std::int64_t last_qty, Decimal last_px);

    // Side: Side of the order.
    Side side() const;
    void set_side(Side value);

    // Pad 7: not used
    const std::array<std::byte, 7>& pad_7() const;
    std::array<std::byte, 7>& pad_7();
    void set_pad_7(const std::array<std::byte, 7>& value);

    // Price: Reserved for future use.
    Decimal price() const;
    void set_price(Decimal value);

    // Trd Reg Ts Time Priority: Priority timestamp.
    std::chrono::nanoseconds trd_reg_ts_time_priority() const;
    void set_trd_reg_ts_time_priority(std::chrono::nanoseconds value);

    // Security Id: Unique instrument identifier.
    std::int64_t security_id() const;
    void set_security_id(std::int64_t value);

    // Trd Match Id: Unique identifier for each price level of a match event.
    std::uint32_t trd_match_id() const;
    void set_trd_match_id(std::uint32_t value);

    // Pad 4: not used
    const std::array<std::byte, 4>& pad_4() const;
    std::array<std::byte, 4>& pad_4();
    void set_pad_4(const std::array<std::byte, 4>& value);

    // Last Qty: The potential matchable quantity for the auction.
    std::int64_t last_qty() const;
    void set_last_qty(std::int64_t value);

    // Last Px: Indicating the potential Auction price for a crossed order book.
    Decimal last_px() const;
    void set_last_px(Decimal value);

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

    bool operator==(const PartialOrderExecutionMessage& other) const;
    bool operator!=(const PartialOrderExecutionMessage& other) const;

  private:
    Side side_{};
    std::array<std::byte, 7> pad_7_{};
    Decimal price_{ 0, -6 };
    std::chrono::nanoseconds trd_reg_ts_time_priority_{};
    std::int64_t security_id_{};
    std::uint32_t trd_match_id_{};
    std::array<std::byte, 4> pad_4_{};
    std::int64_t last_qty_{};
    Decimal last_px_{ 0, -6 };
};

} // namespace bse::bseindia::eobi::fbe::v1_4
