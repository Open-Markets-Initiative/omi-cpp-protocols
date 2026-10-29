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
#include "../enums/MatchSubType.hpp"
#include "../enums/MatchType.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

class Visitor;

// Trade Report
class TradeReport : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::TradeReport;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    TradeReport() = default;
    TradeReport(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time, std::optional<std::uint32_t> trd_match_id, std::optional<std::int32_t> last_qty, std::optional<Decimal> last_px, std::optional<MatchType> match_type, std::optional<MatchSubType> match_sub_type, const std::array<std::byte, 6>& pad6);

    // Security Id:
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

    // Trd Match Id:
    std::optional<std::uint32_t> trd_match_id() const;
    void set_trd_match_id(std::optional<std::uint32_t> value);

    // Last Qty:
    std::optional<std::int32_t> last_qty() const;
    void set_last_qty(std::optional<std::int32_t> value);

    // Last Px:
    std::optional<Decimal> last_px() const;
    void set_last_px(std::optional<Decimal> value);

    // Match Type:
    std::optional<MatchType> match_type() const;
    void set_match_type(std::optional<MatchType> value);

    // Match Sub Type:
    std::optional<MatchSubType> match_sub_type() const;
    void set_match_sub_type(std::optional<MatchSubType> value);

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

    bool operator==(const TradeReport& other) const;
    bool operator!=(const TradeReport& other) const;

  private:
    std::optional<std::int64_t> security_id_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
    std::optional<std::uint32_t> trd_match_id_{};
    std::optional<std::int32_t> last_qty_{};
    std::optional<Decimal> last_px_{};
    std::optional<MatchType> match_type_{};
    std::optional<MatchSubType> match_sub_type_{};
    std::array<std::byte, 6> pad6_{};
};

} // namespace eurex::t7::eobi::fbe::v3_0
