#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/SecurityClass.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

class Visitor;

// BBO products will broadcast a real-time update every time that the exchange's best bid and
// offer quote is updated during the trading day.
class BboQuotationMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::BboQuotationMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 33;

    BboQuotationMessage() = default;
    BboQuotationMessage(std::uint16_t tracking_number, std::chrono::nanoseconds time_stamp, const std::string& stock, SecurityClass security_class, Decimal best_bid_price, std::uint32_t best_bid_size, Decimal best_offer_price, std::uint32_t best_offer_size);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Time Stamp: Timestamp
    std::chrono::nanoseconds time_stamp() const;
    void set_time_stamp(std::chrono::nanoseconds value);
    std::int64_t time_stamp_utc(const calendar::Day& day) const;

    // Stock: Denotes the security symbol for the issue in the execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Security Class: Indicates the primary listing market for the issue.
    SecurityClass security_class() const;
    void set_security_class(SecurityClass value);

    // Best Bid Price: Denotes the best bid price, or the highest price for market buy order(s)
    // in the execution system.
    Decimal best_bid_price() const;
    void set_best_bid_price(Decimal value);

    // Best Bid Size: Denotes the aggregated number of shares available for display within the
    // execution system at the best bid price.
    std::uint32_t best_bid_size() const;
    void set_best_bid_size(std::uint32_t value);

    // Best Offer Price: Denotes the Nasdaq exchange's best offer price, or the lowest price
    // for market sell order(s) in the execution system.
    Decimal best_offer_price() const;
    void set_best_offer_price(Decimal value);

    // Best Offer Size: Denotes the aggregated number of shares available for display within
    // the execution system at the best offer price.
    std::uint32_t best_offer_size() const;
    void set_best_offer_size(std::uint32_t value);

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

    bool operator==(const BboQuotationMessage& other) const;
    bool operator!=(const BboQuotationMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds time_stamp_{};
    std::string stock_{};
    SecurityClass security_class_{};
    Decimal best_bid_price_{ 0, -4 };
    std::uint32_t best_bid_size_{};
    Decimal best_offer_price_{ 0, -4 };
    std::uint32_t best_offer_size_{};
};

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
