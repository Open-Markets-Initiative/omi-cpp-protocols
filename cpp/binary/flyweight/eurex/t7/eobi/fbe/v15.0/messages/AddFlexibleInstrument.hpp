#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityType.hpp"
#include "../enums/PutOrCall.hpp"
#include "../enums/ExerciseStyle.hpp"
#include "../enums/SettlMethod.hpp"
#include "../common/Decimal.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class AddFlexibleInstrument {
  public:
    static constexpr const char* name = "AddFlexibleInstrument";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddFlexibleInstrument(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddFlexibleInstrument has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 88;
    static constexpr std::size_t fixed_size = 88;
    std::size_t encoded_size() const { return 88; }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::string_view security_desc() const { return view::text(at(16), 40, ' '); }

    std::optional<SecurityType> security_type() const { return wire::nullable_enum<SecurityType>(wire::read_u8(at(56)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<PutOrCall> put_or_call() const { return wire::nullable_enum<PutOrCall>(wire::read_u8(at(57)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<ExerciseStyle> exercise_style() const { return wire::nullable_enum<ExerciseStyle>(wire::read_u8(at(58)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<SettlMethod> settl_method() const { return wire::nullable_enum<SettlMethod>(wire::read_u8(at(59)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<std::uint32_t> maturity_date() const { return wire::nullable(wire::read_u32_le(at(60)), static_cast<std::uint32_t>(0xFFFFFFFFULL)); }

    std::optional<Decimal> strike_price() const { return wire::nullable_decimal(wire::read_i64_le(at(64)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<std::uint32_t> opt_attribute() const { return wire::nullable(wire::read_u32_le(at(72)), static_cast<std::uint32_t>(0xFFFFFFFFULL)); }

    std::optional<std::uint32_t> contract_date() const { return wire::nullable(wire::read_u32_le(at(76)), static_cast<std::uint32_t>(0xFFFFFFFFULL)); }

    std::optional<std::uint32_t> security_reference_data_supplement() const { return wire::nullable(wire::read_u32_le(at(80)), static_cast<std::uint32_t>(0xFFFFFFFFULL)); }

    std::span<const std::byte, 4> pad4() const { return bytes_.subspan(84).template first<4>(); }

    void print(std::ostream& out) const {
        out << "AddFlexibleInstrument{";
        out << "security_id=";
        print::optional(out, security_id());
        out << ", transact_time=";
        print::optional_duration(out, transact_time());
        out << ", security_desc=";
        print::text(out, security_desc());
        out << ", security_type=";
        print::optional(out, security_type());
        out << ", put_or_call=";
        print::optional(out, put_or_call());
        out << ", exercise_style=";
        print::optional(out, exercise_style());
        out << ", settl_method=";
        print::optional(out, settl_method());
        out << ", maturity_date=";
        print::optional(out, maturity_date());
        out << ", strike_price=";
        print::optional(out, strike_price());
        out << ", opt_attribute=";
        print::optional(out, opt_attribute());
        out << ", contract_date=";
        print::optional(out, contract_date());
        out << ", security_reference_data_supplement=";
        print::optional(out, security_reference_data_supplement());
        out << ", pad4=";
        print::hex(out, pad4().data(), pad4().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddFlexibleInstrument& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v15_0
