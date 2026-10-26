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
#include "../enums/CrossRequestType.hpp"
#include "../enums/InputSource.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class Visitor;

// Cross Request
class CrossRequest : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::CrossRequest;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    CrossRequest() = default;
    CrossRequest(std::optional<std::int64_t> security_id, std::optional<Decimal> last_px, std::optional<Decimal> last_qty, std::optional<Side> side, std::optional<CrossRequestType> cross_request_type, std::optional<InputSource> input_source, const std::array<std::byte, 5>& pad5, std::optional<std::chrono::nanoseconds> transact_time);

    // Security Id: Unique instrument identifier
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Last Px:
    std::optional<Decimal> last_px() const;
    void set_last_px(std::optional<Decimal> value);

    // Last Qty: Total executed matched quantity of this match event
    std::optional<Decimal> last_qty() const;
    void set_last_qty(std::optional<Decimal> value);

    // Side:
    std::optional<Side> side() const;
    void set_side(std::optional<Side> value);

    // Cross Request Type:
    std::optional<CrossRequestType> cross_request_type() const;
    void set_cross_request_type(std::optional<CrossRequestType> value);

    // Input Source:
    std::optional<InputSource> input_source() const;
    void set_input_source(std::optional<InputSource> value);

    // Pad5:
    const std::array<std::byte, 5>& pad5() const;
    std::array<std::byte, 5>& pad5();
    void set_pad5(const std::array<std::byte, 5>& value);

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

    bool operator==(const CrossRequest& other) const;
    bool operator!=(const CrossRequest& other) const;

  private:
    std::optional<std::int64_t> security_id_{};
    std::optional<Decimal> last_px_{};
    std::optional<Decimal> last_qty_{};
    std::optional<Side> side_{};
    std::optional<CrossRequestType> cross_request_type_{};
    std::optional<InputSource> input_source_{};
    std::array<std::byte, 5> pad5_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
};

} // namespace eurex::t7::eobi::fbe::v15_0
