#include "CrossRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

CrossRequest::CrossRequest(std::optional<std::int64_t> security_id, std::optional<Decimal> last_px, std::optional<Decimal> last_qty, std::optional<Side> side, std::optional<CrossRequestType> cross_request_type, std::optional<InputSource> input_source, const std::array<std::byte, 5>& pad5, std::optional<std::chrono::nanoseconds> transact_time)
  : security_id_(security_id), last_px_(last_px), last_qty_(last_qty), side_(side), cross_request_type_(cross_request_type), input_source_(input_source), pad5_(pad5), transact_time_(transact_time) {}

std::optional<std::int64_t> CrossRequest::security_id() const { return security_id_; }
void CrossRequest::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<Decimal> CrossRequest::last_px() const { return last_px_; }
void CrossRequest::set_last_px(std::optional<Decimal> value) { last_px_ = value; }

std::optional<Decimal> CrossRequest::last_qty() const { return last_qty_; }
void CrossRequest::set_last_qty(std::optional<Decimal> value) { last_qty_ = value; }

std::optional<Side> CrossRequest::side() const { return side_; }
void CrossRequest::set_side(std::optional<Side> value) { side_ = value; }

std::optional<CrossRequestType> CrossRequest::cross_request_type() const { return cross_request_type_; }
void CrossRequest::set_cross_request_type(std::optional<CrossRequestType> value) { cross_request_type_ = value; }

std::optional<InputSource> CrossRequest::input_source() const { return input_source_; }
void CrossRequest::set_input_source(std::optional<InputSource> value) { input_source_ = value; }

const std::array<std::byte, 5>& CrossRequest::pad5() const { return pad5_; }
std::array<std::byte, 5>& CrossRequest::pad5() { return pad5_; }
void CrossRequest::set_pad5(const std::array<std::byte, 5>& value) { pad5_ = value; }

std::optional<std::chrono::nanoseconds> CrossRequest::transact_time() const { return transact_time_; }
void CrossRequest::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

MessageCode CrossRequest::type() const { return message_type; }

std::string_view CrossRequest::name() const { return "Cross Request"; }

std::size_t CrossRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CrossRequest", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    last_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    last_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    side_ = wire::nullable_enum<Side>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    cross_request_type_ = wire::nullable_enum<CrossRequestType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    input_source_ = wire::nullable_enum<InputSource>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad5_.data(), 5);
    offset += 5;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t CrossRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CrossRequest", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_i64_le(data + offset, last_px_ ? static_cast<std::int64_t>(last_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, last_qty_ ? static_cast<std::int64_t>(last_qty_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u8(data + offset, side_ ? static_cast<std::uint8_t>(*side_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, cross_request_type_ ? static_cast<std::uint8_t>(*cross_request_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, input_source_ ? static_cast<std::uint8_t>(*input_source_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad5_.data(), 5);
    offset += 5;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t CrossRequest::encoded_size() const {
    return wire_size;
}

void CrossRequest::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> CrossRequest::clone() const {
    return std::make_unique<CrossRequest>(*this);
}

void CrossRequest::print(std::ostream& out) const {
    out << "CrossRequest{";
    out << "security_id=";
    print::optional(out, security_id_);
    out << ", last_px=";
    print::optional(out, last_px_);
    out << ", last_qty=";
    print::optional(out, last_qty_);
    out << ", side=";
    print::optional(out, side_);
    out << ", cross_request_type=";
    print::optional(out, cross_request_type_);
    out << ", input_source=";
    print::optional(out, input_source_);
    out << ", pad5=";
    print::hex(out, pad5_.data(), pad5_.size());
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << '}';
}

bool CrossRequest::equals(const Message& other) const {
    const auto* that = dynamic_cast<const CrossRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool CrossRequest::operator==(const CrossRequest& other) const {
    return security_id_ == other.security_id_
        && last_px_ == other.last_px_
        && last_qty_ == other.last_qty_
        && side_ == other.side_
        && cross_request_type_ == other.cross_request_type_
        && input_source_ == other.input_source_
        && pad5_ == other.pad5_
        && transact_time_ == other.transact_time_;
}

bool CrossRequest::operator!=(const CrossRequest& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v15_0
