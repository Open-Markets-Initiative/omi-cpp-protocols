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
#include "../enums/PotentialSecurityTradingEvent.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

class Visitor;

// Auction Bbo
class AuctionBbo : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::AuctionBbo;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 48;

    AuctionBbo() = default;
    AuctionBbo(std::optional<std::chrono::nanoseconds> transact_time, std::optional<std::int64_t> security_id, std::optional<Decimal> bid_px, std::optional<Decimal> offer_px, std::optional<std::int32_t> bid_size, std::optional<std::int32_t> offer_size, std::optional<PotentialSecurityTradingEvent> potential_security_trading_event, const std::array<std::byte, 7>& pad7);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

    // Security Id:
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Bid Px:
    std::optional<Decimal> bid_px() const;
    void set_bid_px(std::optional<Decimal> value);

    // Offer Px:
    std::optional<Decimal> offer_px() const;
    void set_offer_px(std::optional<Decimal> value);

    // Bid Size:
    std::optional<std::int32_t> bid_size() const;
    void set_bid_size(std::optional<std::int32_t> value);

    // Offer Size:
    std::optional<std::int32_t> offer_size() const;
    void set_offer_size(std::optional<std::int32_t> value);

    // Potential Security Trading Event:
    std::optional<PotentialSecurityTradingEvent> potential_security_trading_event() const;
    void set_potential_security_trading_event(std::optional<PotentialSecurityTradingEvent> value);

    // Pad7:
    const std::array<std::byte, 7>& pad7() const;
    std::array<std::byte, 7>& pad7();
    void set_pad7(const std::array<std::byte, 7>& value);

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

    bool operator==(const AuctionBbo& other) const;
    bool operator!=(const AuctionBbo& other) const;

  private:
    std::optional<std::chrono::nanoseconds> transact_time_{};
    std::optional<std::int64_t> security_id_{};
    std::optional<Decimal> bid_px_{};
    std::optional<Decimal> offer_px_{};
    std::optional<std::int32_t> bid_size_{};
    std::optional<std::int32_t> offer_size_{};
    std::optional<PotentialSecurityTradingEvent> potential_security_trading_event_{};
    std::array<std::byte, 7> pad7_{};
};

} // namespace eurex::t7::eobi::fbe::v6_0
