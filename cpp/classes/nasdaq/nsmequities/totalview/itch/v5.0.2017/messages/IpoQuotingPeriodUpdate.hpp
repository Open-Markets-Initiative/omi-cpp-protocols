#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/IpoQuotationReleaseQualifier.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

class SequencedMessageVisitor;

// Indicates the anticipated IPO quotation release time of a security.
class IpoQuotingPeriodUpdate : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = 'K';
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 27;

    IpoQuotingPeriodUpdate() = default;
    IpoQuotingPeriodUpdate(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, std::chrono::seconds ipo_quotation_release_time, IpoQuotationReleaseQualifier ipo_quotation_release_qualifier, Decimal ipo_price);

    // Stock Locate: Always 0
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: NASDAQ OMX internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Stock: Denotes the security symbol for the issue in the NASDAQ execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Ipo Quotation Release Time: Denotes the IPO release time, in seconds since midnight, for
    // quotation to the nearest second.
    std::chrono::seconds ipo_quotation_release_time() const;
    void set_ipo_quotation_release_time(std::chrono::seconds value);

    // Ipo Quotation Release Qualifier: Anticipated quotation release time. This value would be
    // used when NASDAQ Market Operations initially enters the IPO instrument for release.IPO
    // release canceled/postponed.This value would be used when NASDAQ Market Operations
    // cancels or postpones the release of the IPO instrument.
    IpoQuotationReleaseQualifier ipo_quotation_release_qualifier() const;
    void set_ipo_quotation_release_qualifier(IpoQuotationReleaseQualifier value);

    // Ipo Price: Denotes the IPO price to be used for intraday net change calculations. Prices
    // are given in decimal format with 6 whole number places followed by 4 decimal digits.
    Decimal ipo_price() const;
    void set_ipo_price(Decimal value);

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

    bool operator==(const IpoQuotingPeriodUpdate& other) const;
    bool operator!=(const IpoQuotingPeriodUpdate& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::string stock_{};
    std::chrono::seconds ipo_quotation_release_time_{};
    IpoQuotationReleaseQualifier ipo_quotation_release_qualifier_{};
    Decimal ipo_price_{ 0, -4 };
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
