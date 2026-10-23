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

#include "../common/Decimal.hpp"
#include "../enums/ExerciseStyle.hpp"
#include "../enums/PutOrCall.hpp"
#include "../enums/SecurityType.hpp"
#include "../enums/SettlMethod.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class Visitor;

// Add Flexible Instrument
class AddFlexibleInstrument : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::AddFlexibleInstrument;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 88;

    AddFlexibleInstrument() = default;
    AddFlexibleInstrument(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time, const std::string& security_desc, std::optional<SecurityType> security_type, std::optional<PutOrCall> put_or_call, std::optional<ExerciseStyle> exercise_style, std::optional<SettlMethod> settl_method, std::optional<std::uint32_t> maturity_date, std::optional<Decimal> strike_price, std::optional<std::uint32_t> opt_attribute, std::optional<std::uint32_t> contract_date, std::optional<std::uint32_t> security_reference_data_supplement, const std::array<std::byte, 4>& pad4);

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

    // Put Or Call:
    std::optional<PutOrCall> put_or_call() const;
    void set_put_or_call(std::optional<PutOrCall> value);

    // Exercise Style:
    std::optional<ExerciseStyle> exercise_style() const;
    void set_exercise_style(std::optional<ExerciseStyle> value);

    // Settl Method:
    std::optional<SettlMethod> settl_method() const;
    void set_settl_method(std::optional<SettlMethod> value);

    // Maturity Date:
    std::optional<std::uint32_t> maturity_date() const;
    void set_maturity_date(std::optional<std::uint32_t> value);

    // Strike Price:
    std::optional<Decimal> strike_price() const;
    void set_strike_price(std::optional<Decimal> value);

    // Opt Attribute:
    std::optional<std::uint32_t> opt_attribute() const;
    void set_opt_attribute(std::optional<std::uint32_t> value);

    // Contract Date:
    std::optional<std::uint32_t> contract_date() const;
    void set_contract_date(std::optional<std::uint32_t> value);

    // Security Reference Data Supplement:
    std::optional<std::uint32_t> security_reference_data_supplement() const;
    void set_security_reference_data_supplement(std::optional<std::uint32_t> value);

    // Pad4:
    const std::array<std::byte, 4>& pad4() const;
    std::array<std::byte, 4>& pad4();
    void set_pad4(const std::array<std::byte, 4>& value);

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

    bool operator==(const AddFlexibleInstrument& other) const;
    bool operator!=(const AddFlexibleInstrument& other) const;

  private:
    std::optional<std::int64_t> security_id_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
    std::string security_desc_{};
    std::optional<SecurityType> security_type_{};
    std::optional<PutOrCall> put_or_call_{};
    std::optional<ExerciseStyle> exercise_style_{};
    std::optional<SettlMethod> settl_method_{};
    std::optional<std::uint32_t> maturity_date_{};
    std::optional<Decimal> strike_price_{};
    std::optional<std::uint32_t> opt_attribute_{};
    std::optional<std::uint32_t> contract_date_{};
    std::optional<std::uint32_t> security_reference_data_supplement_{};
    std::array<std::byte, 4> pad4_{};
};

} // namespace eurex::t7::eobi::fbe::v13_0
