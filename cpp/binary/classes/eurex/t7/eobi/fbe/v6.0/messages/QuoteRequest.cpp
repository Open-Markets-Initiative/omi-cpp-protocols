#include "QuoteRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

QuoteRequest::QuoteRequest(std::optional<std::int64_t> security_id, std::optional<std::int32_t> last_qty, std::optional<Side> side, const std::array<std::byte, 3>& pad3, std::optional<std::chrono::nanoseconds> transact_time)
  : security_id_(security_id), last_qty_(last_qty), side_(side), pad3_(pad3), transact_time_(transact_time) {}

std::optional<std::int64_t> QuoteRequest::security_id() const { return security_id_; }
void QuoteRequest::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<std::int32_t> QuoteRequest::last_qty() const { return last_qty_; }
void QuoteRequest::set_last_qty(std::optional<std::int32_t> value) { last_qty_ = value; }

std::optional<Side> QuoteRequest::side() const { return side_; }
void QuoteRequest::set_side(std::optional<Side> value) { side_ = value; }

const std::array<std::byte, 3>& QuoteRequest::pad3() const { return pad3_; }
std::array<std::byte, 3>& QuoteRequest::pad3() { return pad3_; }
void QuoteRequest::set_pad3(const std::array<std::byte, 3>& value) { pad3_ = value; }

std::optional<std::chrono::nanoseconds> QuoteRequest::transact_time() const { return transact_time_; }
void QuoteRequest::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

MessageCode QuoteRequest::type() const { return message_type; }

std::string_view QuoteRequest::name() const { return "Quote Request"; }

std::size_t QuoteRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("QuoteRequest", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    last_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    side_ = wire::nullable_enum<Side>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad3_.data(), 3);
    offset += 3;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t QuoteRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteRequest", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_i32_le(data + offset, last_qty_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_u8(data + offset, side_ ? static_cast<std::uint8_t>(*side_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad3_.data(), 3);
    offset += 3;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t QuoteRequest::encoded_size() const {
    return wire_size;
}

void QuoteRequest::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> QuoteRequest::clone() const {
    return std::make_unique<QuoteRequest>(*this);
}

void QuoteRequest::print(std::ostream& out) const {
    out << "QuoteRequest{";
    out << "security_id=";
    print::optional(out, security_id_);
    out << ", last_qty=";
    print::optional(out, last_qty_);
    out << ", side=";
    print::optional(out, side_);
    out << ", pad3=";
    print::hex(out, pad3_.data(), pad3_.size());
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << '}';
}

bool QuoteRequest::equals(const Message& other) const {
    const auto* that = dynamic_cast<const QuoteRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteRequest::operator==(const QuoteRequest& other) const {
    return security_id_ == other.security_id_
        && last_qty_ == other.last_qty_
        && side_ == other.side_
        && pad3_ == other.pad3_
        && transact_time_ == other.transact_time_;
}

bool QuoteRequest::operator!=(const QuoteRequest& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v6_0
