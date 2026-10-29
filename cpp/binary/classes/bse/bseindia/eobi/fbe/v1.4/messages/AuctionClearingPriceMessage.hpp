#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Published for a crossed order book in an auction, indicating the potential auction price.
class AuctionClearingPriceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::AuctionClearingPriceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    AuctionClearingPriceMessage() = default;
    AuctionClearingPriceMessage(std::chrono::nanoseconds transact_time, std::int64_t security_id, Decimal last_px, std::int64_t last_qty);

    // Transact Time: Transaction timestamp.
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Security Id: Unique instrument identifier.
    std::int64_t security_id() const;
    void set_security_id(std::int64_t value);

    // Last Px: Indicating the potential Auction price for a crossed order book.
    Decimal last_px() const;
    void set_last_px(Decimal value);

    // Last Qty: The potential matchable quantity for the auction.
    std::int64_t last_qty() const;
    void set_last_qty(std::int64_t value);

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

    bool operator==(const AuctionClearingPriceMessage& other) const;
    bool operator!=(const AuctionClearingPriceMessage& other) const;

  private:
    std::chrono::nanoseconds transact_time_{};
    std::int64_t security_id_{};
    Decimal last_px_{ 0, -6 };
    std::int64_t last_qty_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
