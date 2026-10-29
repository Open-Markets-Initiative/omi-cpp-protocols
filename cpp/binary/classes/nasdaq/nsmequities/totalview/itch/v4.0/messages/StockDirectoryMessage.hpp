#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/MarketCategory.hpp"
#include "../enums/RoundLotsOnly.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class SequencedMessageVisitor;

// Market data redistributors should process this message to populate the Financial Status
// Indicator (required display field) and the Market Category (recommended display field) for
// NASDAQ-listed issues.
class StockDirectoryMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = 'R';
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    StockDirectoryMessage() = default;
    StockDirectoryMessage(std::chrono::nanoseconds nanoseconds, const std::string& stock, MarketCategory market_category, FinancialStatusIndicator financial_status_indicator, std::uint32_t round_lot_size, RoundLotsOnly round_lots_only);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Stock: Denotes the security symbol for the issue in NASDAQ Single Book. Refer to
    // Appendix NASDAQ Single Book stock symbol convention information.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Market Category: Indicates Listing market or listing market tier for the issue
    MarketCategory market_category() const;
    void set_market_category(MarketCategory value);

    // Financial Status Indicator: For NASDAQ-listed issues, this field indicates when a firm
    // is not in compliance with NASDAQ continued listing requirements. For CQS issues, this
    // field will also be space-filled. Redistributors should refer to SIAC feeds for code if
    // needed.
    FinancialStatusIndicator financial_status_indicator() const;
    void set_financial_status_indicator(FinancialStatusIndicator value);

    // Round Lot Size: Indicates the number of shares that represent a round lot for the issue
    std::uint32_t round_lot_size() const;
    void set_round_lot_size(std::uint32_t value);

    // Round Lots Only: Indicates if NASDAQ system limits order entry for issue
    RoundLotsOnly round_lots_only() const;
    void set_round_lots_only(RoundLotsOnly value);

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

    bool operator==(const StockDirectoryMessage& other) const;
    bool operator!=(const StockDirectoryMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::string stock_{};
    MarketCategory market_category_{};
    FinancialStatusIndicator financial_status_indicator_{};
    std::uint32_t round_lot_size_{};
    RoundLotsOnly round_lots_only_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
