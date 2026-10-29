#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Carries the best bid and offer of an order book outside continuous trading.
class TopOfBookMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::TopOfBookMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    TopOfBookMessage() = default;
    TopOfBookMessage(std::chrono::nanoseconds transact_time, std::int64_t security_id, std::optional<Decimal> bid_px, std::optional<Decimal> offer_px);

    // Transact Time: Transaction timestamp.
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Security Id: Unique instrument identifier.
    std::int64_t security_id() const;
    void set_security_id(std::int64_t value);

    // Bid Px: Bid price/rate.
    std::optional<Decimal> bid_px() const;
    void set_bid_px(std::optional<Decimal> value);

    // Offer Px: Offer price/rate.
    std::optional<Decimal> offer_px() const;
    void set_offer_px(std::optional<Decimal> value);

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

    bool operator==(const TopOfBookMessage& other) const;
    bool operator!=(const TopOfBookMessage& other) const;

  private:
    std::chrono::nanoseconds transact_time_{};
    std::int64_t security_id_{};
    std::optional<Decimal> bid_px_{};
    std::optional<Decimal> offer_px_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
