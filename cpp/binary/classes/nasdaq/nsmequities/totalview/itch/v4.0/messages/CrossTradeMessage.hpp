#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/CrossType.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class SequencedMessageVisitor;

// Cross Trade message indicates that NASDAQ has completed its cross process for a specific
// security.
class CrossTradeMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = 'Q';
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 31;

    CrossTradeMessage() = default;
    CrossTradeMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t cross_shares, const std::string& stock, Decimal cross_price, std::uint64_t match_number, CrossType cross_type);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Cross Shares: The number of shares matched in the NASDAQ Cross.
    std::uint64_t cross_shares() const;
    void set_cross_shares(std::uint64_t value);

    // Stock: Denotes the security symbol for the issue in NASDAQ Single Book. Refer to
    // Appendix NASDAQ Single Book stock symbol convention information.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Cross Price: The price at which the cross occurred. Refer to Data Types for field
    // processing notes.
    Decimal cross_price() const;
    void set_cross_price(Decimal value);

    // Match Number: The NASDAQ generated day-unique Match Number of this execution. The match
    // number is also referenced in the Trade Break Message.
    std::uint64_t match_number() const;
    void set_match_number(std::uint64_t value);

    // Cross Type: The NASDAQ cross session for which the message is being generated.
    CrossType cross_type() const;
    void set_cross_type(CrossType value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const CrossTradeMessage& other) const;
    bool operator!=(const CrossTradeMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t cross_shares_{};
    std::string stock_{};
    Decimal cross_price_{ 0, -4 };
    std::uint64_t match_number_{};
    CrossType cross_type_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
