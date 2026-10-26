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
#include "../enums/IpoQuotationReleaseQualifier.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

class Visitor;

// Indicates the anticipated IPO quotation release time of a security.
class IpoQuotingPeriodUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::IpoQuotingPeriodUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    IpoQuotingPeriodUpdateMessage() = default;
    IpoQuotingPeriodUpdateMessage(std::uint16_t tracking, std::chrono::nanoseconds time_stamp, const std::string& stock, std::uint32_t ipo_quotation_release_time, IpoQuotationReleaseQualifier ipo_quotation_release_qualifier, Decimal ipo_price);

    // Tracking: Nasdaq internal tracking number
    std::uint16_t tracking() const;
    void set_tracking(std::uint16_t value);

    // Time Stamp: Timestamp
    std::chrono::nanoseconds time_stamp() const;
    void set_time_stamp(std::chrono::nanoseconds value);
    std::int64_t time_stamp_utc(const calendar::Day& day) const;

    // Stock: Denotes the security symbol for the issue in the execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Ipo Quotation Release Time: Denotes the IPO release time, in seconds since midnight, for
    // quotation to the nearest second.
    std::uint32_t ipo_quotation_release_time() const;
    void set_ipo_quotation_release_time(std::uint32_t value);

    // Ipo Quotation Release Qualifier: Denotes the IPO release qualifier
    IpoQuotationReleaseQualifier ipo_quotation_release_qualifier() const;
    void set_ipo_quotation_release_qualifier(IpoQuotationReleaseQualifier value);

    // Ipo Price: Denotes the IPO price to be used for intraday net change calculations.
    Decimal ipo_price() const;
    void set_ipo_price(Decimal value);

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

    bool operator==(const IpoQuotingPeriodUpdateMessage& other) const;
    bool operator!=(const IpoQuotingPeriodUpdateMessage& other) const;

  private:
    std::uint16_t tracking_{};
    std::chrono::nanoseconds time_stamp_{};
    std::string stock_{};
    std::uint32_t ipo_quotation_release_time_{};
    IpoQuotationReleaseQualifier ipo_quotation_release_qualifier_{};
    Decimal ipo_price_{ 0, -4 };
};

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
