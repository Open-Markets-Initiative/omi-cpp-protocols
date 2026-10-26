#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class Visitor;

// Top Of Book
class TopOfBook : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::TopOfBook;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 56;

    TopOfBook() = default;
    TopOfBook(std::optional<std::chrono::nanoseconds> transact_time, std::optional<std::int64_t> security_id, std::optional<Decimal> bid_px, std::optional<Decimal> offer_px, std::optional<Decimal> bid_size, std::optional<Decimal> offer_size, std::optional<std::uint16_t> number_of_buy_orders, std::optional<std::uint16_t> number_of_sell_orders, const std::array<std::byte, 4>& pad4);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

    // Security Id: Unique instrument identifier
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Bid Px:
    std::optional<Decimal> bid_px() const;
    void set_bid_px(std::optional<Decimal> value);

    // Offer Px:
    std::optional<Decimal> offer_px() const;
    void set_offer_px(std::optional<Decimal> value);

    // Bid Size:
    std::optional<Decimal> bid_size() const;
    void set_bid_size(std::optional<Decimal> value);

    // Offer Size:
    std::optional<Decimal> offer_size() const;
    void set_offer_size(std::optional<Decimal> value);

    // Number Of Buy Orders:
    std::optional<std::uint16_t> number_of_buy_orders() const;
    void set_number_of_buy_orders(std::optional<std::uint16_t> value);

    // Number Of Sell Orders:
    std::optional<std::uint16_t> number_of_sell_orders() const;
    void set_number_of_sell_orders(std::optional<std::uint16_t> value);

    // Pad4:
    const std::array<std::byte, 4>& pad4() const;
    std::array<std::byte, 4>& pad4();
    void set_pad4(const std::array<std::byte, 4>& value);

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

    bool operator==(const TopOfBook& other) const;
    bool operator!=(const TopOfBook& other) const;

  private:
    std::optional<std::chrono::nanoseconds> transact_time_{};
    std::optional<std::int64_t> security_id_{};
    std::optional<Decimal> bid_px_{};
    std::optional<Decimal> offer_px_{};
    std::optional<Decimal> bid_size_{};
    std::optional<Decimal> offer_size_{};
    std::optional<std::uint16_t> number_of_buy_orders_{};
    std::optional<std::uint16_t> number_of_sell_orders_{};
    std::array<std::byte, 4> pad4_{};
};

} // namespace eurex::t7::eobi::fbe::v15_0
