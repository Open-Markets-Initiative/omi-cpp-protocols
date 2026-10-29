#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include "../enums/ActiveOnMiax.hpp"
#include "../enums/UpdateReason.hpp"
#include "../groups/LegDefinition.hpp"
#include "../messages/Data.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

class DataVisitor;

// This is the message format that will be used to disseminate stock option strategies traded
// on MIAX for the current session.
class ComplexStrategyDefinitionMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::ComplexStrategyDefinitionMessage;

    ComplexStrategyDefinitionMessage() = default;
    ComplexStrategyDefinitionMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t strategy_id, const std::string& underlying_symbol, ActiveOnMiax active_on_miax, const std::array<std::byte, 1>& reserved_1, UpdateReason update_reason, const std::array<std::byte, 10>& reserved_10, std::uint8_t number_of_legs, const std::vector<LegDefinition>& leg_definition);

    // Nanoseconds: Time at which this product is added/updated on MIAX system today.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Strategy Id: MIAX Strategy ID is assigned per trading day and is valid only for that
    // day.
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

    // Underlying Symbol: Stock Symbol for the option.
    const std::string& underlying_symbol() const;
    std::string& underlying_symbol();
    void set_underlying_symbol(const std::string& value);

    // Active On Miax: Indicates if this symbol is tradable on MIAX in the current session: “A”
    // = Active (tradable) on MIAX “I” = Inactive (not tradable) on MIAX
    ActiveOnMiax active_on_miax() const;
    void set_active_on_miax(ActiveOnMiax value);

    // Reserved 1: Reserved for future use
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Update Reason: “N” – New strategy created
    UpdateReason update_reason() const;
    void set_update_reason(UpdateReason value);

    // Reserved 10: Reserved for future use **
    const std::array<std::byte, 10>& reserved_10() const;
    std::array<std::byte, 10>& reserved_10();
    void set_reserved_10(const std::array<std::byte, 10>& value);

    // Number Of Legs: Number of Legs. Variable from 2 to 8
    std::uint8_t number_of_legs() const;
    void set_number_of_legs(std::uint8_t value);

    // Leg Definition: Complex Strategy Number of Legs
    const std::vector<LegDefinition>& leg_definition() const;
    std::vector<LegDefinition>& leg_definition();
    void set_leg_definition(const std::vector<LegDefinition>& value);

    // Data
    DataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(DataVisitor& visitor) const override;
    std::unique_ptr<Data> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Data& other) const override;

    bool operator==(const ComplexStrategyDefinitionMessage& other) const;
    bool operator!=(const ComplexStrategyDefinitionMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t strategy_id_{};
    std::string underlying_symbol_{};
    ActiveOnMiax active_on_miax_{};
    std::array<std::byte, 1> reserved_1_{};
    UpdateReason update_reason_{};
    std::array<std::byte, 10> reserved_10_{};
    std::uint8_t number_of_legs_{};
    std::vector<LegDefinition> leg_definition_{};
};

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
