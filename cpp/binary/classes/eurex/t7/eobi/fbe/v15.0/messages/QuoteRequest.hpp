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
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class Visitor;

// Quote Request
class QuoteRequest : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::QuoteRequest;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    QuoteRequest() = default;
    QuoteRequest(std::optional<std::int64_t> security_id, std::optional<Decimal> last_qty, std::optional<Side> side, const std::array<std::byte, 7>& pad7, std::optional<std::chrono::nanoseconds> transact_time);

    // Security Id: Unique instrument identifier
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Last Qty: Total executed matched quantity of this match event
    std::optional<Decimal> last_qty() const;
    void set_last_qty(std::optional<Decimal> value);

    // Side:
    std::optional<Side> side() const;
    void set_side(std::optional<Side> value);

    // Pad7:
    const std::array<std::byte, 7>& pad7() const;
    std::array<std::byte, 7>& pad7();
    void set_pad7(const std::array<std::byte, 7>& value);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

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

    bool operator==(const QuoteRequest& other) const;
    bool operator!=(const QuoteRequest& other) const;

  private:
    std::optional<std::int64_t> security_id_{};
    std::optional<Decimal> last_qty_{};
    std::optional<Side> side_{};
    std::array<std::byte, 7> pad7_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
};

} // namespace eurex::t7::eobi::fbe::v15_0
