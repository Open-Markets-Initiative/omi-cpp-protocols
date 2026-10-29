#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "../groups/SummaryMdEntry.hpp"
#include "../messages/Message.hpp"
#include "../structs/NetChgPrevDay.hpp"
#include "../structs/UnderlyingPx.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class Visitor;

// Summary messages contain the end of session market data for each product.
class SummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::SummaryMessage;

    SummaryMessage() = default;
    SummaryMessage(std::uint32_t class_key, std::uint32_t security_id, std::uint8_t price_type, std::uint32_t trade_volume, std::uint32_t open_interest, const NetChgPrevDay& net_chg_prev_day, const UnderlyingPx& underlying_px, std::uint8_t no_entries, const std::vector<SummaryMdEntry>& summary_md_entry);

    // Class Key: Class key
    std::uint32_t class_key() const;
    void set_class_key(std::uint32_t value);

    // Security Id: Product key
    std::uint32_t security_id() const;
    void set_security_id(std::uint32_t value);

    // Price Type: Specifies how to interpret the value in the StrikePrice field.
    std::uint8_t price_type() const;
    void set_price_type(std::uint8_t value);

    // Trade Volume: Total trade volume for security
    std::uint32_t trade_volume() const;
    void set_trade_volume(std::uint32_t value);

    // Open Interest: Open Interest
    std::uint32_t open_interest() const;
    void set_open_interest(std::uint32_t value);

    // Net Chg Prev Day:
    const NetChgPrevDay& net_chg_prev_day() const;
    NetChgPrevDay& net_chg_prev_day();
    void set_net_chg_prev_day(const NetChgPrevDay& value);

    // Underlying Px:
    const UnderlyingPx& underlying_px() const;
    UnderlyingPx& underlying_px();
    void set_underlying_px(const UnderlyingPx& value);

    // No Entries: Number of MDEntries in this message. Will not exceed 255
    std::uint8_t no_entries() const;
    void set_no_entries(std::uint8_t value);

    // Summary Md Entry: Summary market data
    const std::vector<SummaryMdEntry>& summary_md_entry() const;
    std::vector<SummaryMdEntry>& summary_md_entry();
    void set_summary_md_entry(const std::vector<SummaryMdEntry>& value);

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

    bool operator==(const SummaryMessage& other) const;
    bool operator!=(const SummaryMessage& other) const;

  private:
    std::uint32_t class_key_{};
    std::uint32_t security_id_{};
    std::uint8_t price_type_{};
    std::uint32_t trade_volume_{};
    std::uint32_t open_interest_{};
    NetChgPrevDay net_chg_prev_day_{};
    UnderlyingPx underlying_px_{};
    std::uint8_t no_entries_{};
    std::vector<SummaryMdEntry> summary_md_entry_{};
};

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
