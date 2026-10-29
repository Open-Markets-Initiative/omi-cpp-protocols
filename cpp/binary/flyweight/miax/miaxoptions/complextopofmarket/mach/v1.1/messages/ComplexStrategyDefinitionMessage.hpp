#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ActiveOnMiax.hpp"
#include "../enums/UpdateReason.hpp"
#include "../groups/LegDefinition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// This is the message format that will be used to disseminate stock option strategies traded
// on MIAX for the current session.
class ComplexStrategyDefinitionMessage {
  public:
    static constexpr const char* name = "ComplexStrategyDefinitionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexStrategyDefinitionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexStrategyDefinitionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 33;
    std::size_t encoded_size() const { return leg_definition_end(); }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t strategy_id() const { return wire::read_u32_le(at(4)); }

    std::string_view underlying_symbol() const { return view::text(at(8), 11, ' '); }

    ActiveOnMiax active_on_miax() const { return static_cast<ActiveOnMiax>(wire::read_char(at(19))); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(20).template first<1>(); }

    UpdateReason update_reason() const { return static_cast<UpdateReason>(wire::read_char(at(21))); }

    std::span<const std::byte, 10> reserved_10() const { return bytes_.subspan(22).template first<10>(); }

    std::uint8_t number_of_legs() const { return wire::read_u8(at(32)); }

    view::entries<LegDefinition> leg_definition() const { return view::entries<LegDefinition>{ bytes_.subspan(33), wire::count(number_of_legs()) }; }

    void print(std::ostream& out) const {
        out << "ComplexStrategyDefinitionMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", strategy_id=";
        out << strategy_id();
        out << ", underlying_symbol=";
        print::text(out, underlying_symbol());
        out << ", active_on_miax=";
        out << active_on_miax();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", update_reason=";
        out << update_reason();
        out << ", reserved_10=";
        print::hex(out, reserved_10().data(), reserved_10().size());
        out << ", number_of_legs=";
        out << static_cast<int>(number_of_legs());
        out << ", leg_definition=";
        print::sequence(out, leg_definition());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t leg_definition_end() const { return 33 + leg_definition().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexStrategyDefinitionMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
