#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/SecurityType.hpp"
#include "../messages/Message.hpp"
#include "../structs/RelatedInstrumentGrpComp.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class Visitor;

// Add Scaled Simple Instrument
class AddScaledSimpleInstrument : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::AddScaledSimpleInstrument;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 72;

    AddScaledSimpleInstrument() = default;
    AddScaledSimpleInstrument(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time, const std::string& security_desc, std::optional<SecurityType> security_type, const std::array<std::byte, 1>& pad1, std::optional<std::uint16_t> quantity_scaling_factor, const std::array<std::byte, 4>& pad4, const RelatedInstrumentGrpComp& related_instrument_grp_comp);

    // Security Id:
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

    // Security Desc:
    const std::string& security_desc() const;
    std::string& security_desc();
    void set_security_desc(const std::string& value);

    // Security Type:
    std::optional<SecurityType> security_type() const;
    void set_security_type(std::optional<SecurityType> value);

    // Pad1:
    const std::array<std::byte, 1>& pad1() const;
    std::array<std::byte, 1>& pad1();
    void set_pad1(const std::array<std::byte, 1>& value);

    // Quantity Scaling Factor:
    std::optional<std::uint16_t> quantity_scaling_factor() const;
    void set_quantity_scaling_factor(std::optional<std::uint16_t> value);

    // Pad4:
    const std::array<std::byte, 4>& pad4() const;
    std::array<std::byte, 4>& pad4();
    void set_pad4(const std::array<std::byte, 4>& value);

    // Related Instrument Grp Comp:
    const RelatedInstrumentGrpComp& related_instrument_grp_comp() const;
    RelatedInstrumentGrpComp& related_instrument_grp_comp();
    void set_related_instrument_grp_comp(const RelatedInstrumentGrpComp& value);

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

    bool operator==(const AddScaledSimpleInstrument& other) const;
    bool operator!=(const AddScaledSimpleInstrument& other) const;

  private:
    std::optional<std::int64_t> security_id_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
    std::string security_desc_{};
    std::optional<SecurityType> security_type_{};
    std::array<std::byte, 1> pad1_{};
    std::optional<std::uint16_t> quantity_scaling_factor_{};
    std::array<std::byte, 4> pad4_{};
    RelatedInstrumentGrpComp related_instrument_grp_comp_{};
};

} // namespace eurex::t7::eobi::fbe::v13_0
