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
#include "../enums/SecurityTradingStatus.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class Visitor;

// Auction Clearing Price
class AuctionClearingPrice : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::AuctionClearingPrice;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 48;

    AuctionClearingPrice() = default;
    AuctionClearingPrice(std::optional<std::chrono::nanoseconds> transact_time, std::optional<std::int64_t> security_id, std::optional<Decimal> last_px, std::optional<Decimal> last_qty, std::optional<Decimal> imbalance_qty, std::optional<SecurityTradingStatus> security_trading_status, std::optional<PotentialSecurityTradingEvent> potential_security_trading_event, const std::array<std::byte, 6>& pad6);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

    // Security Id: Unique instrument identifier
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Last Px:
    std::optional<Decimal> last_px() const;
    void set_last_px(std::optional<Decimal> value);

    // Last Qty: Total executed matched quantity of this match event
    std::optional<Decimal> last_qty() const;
    void set_last_qty(std::optional<Decimal> value);

    // Imbalance Qty:
    std::optional<Decimal> imbalance_qty() const;
    void set_imbalance_qty(std::optional<Decimal> value);

    // Security Trading Status:
    std::optional<SecurityTradingStatus> security_trading_status() const;
    void set_security_trading_status(std::optional<SecurityTradingStatus> value);

    // Potential Security Trading Event:
    std::optional<PotentialSecurityTradingEvent> potential_security_trading_event() const;
    void set_potential_security_trading_event(std::optional<PotentialSecurityTradingEvent> value);

    // Pad6:
    const std::array<std::byte, 6>& pad6() const;
    std::array<std::byte, 6>& pad6();
    void set_pad6(const std::array<std::byte, 6>& value);

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

    bool operator==(const AuctionClearingPrice& other) const;
    bool operator!=(const AuctionClearingPrice& other) const;

  private:
    std::optional<std::chrono::nanoseconds> transact_time_{};
    std::optional<std::int64_t> security_id_{};
    std::optional<Decimal> last_px_{};
    std::optional<Decimal> last_qty_{};
    std::optional<Decimal> imbalance_qty_{};
    std::optional<SecurityTradingStatus> security_trading_status_{};
    std::optional<PotentialSecurityTradingEvent> potential_security_trading_event_{};
    std::array<std::byte, 6> pad6_{};
};

} // namespace eurex::t7::eobi::fbe::v15_0
