#include "CrossRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

CrossRequest::CrossRequest(std::optional<std::int64_t> security_id, std::optional<std::int32_t> last_qty, const std::array<std::byte, 4>& pad4, std::optional<std::chrono::nanoseconds> transact_time)
  : security_id_(security_id), last_qty_(last_qty), pad4_(pad4), transact_time_(transact_time) {}

std::optional<std::int64_t> CrossRequest::security_id() const { return security_id_; }
void CrossRequest::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<std::int32_t> CrossRequest::last_qty() const { return last_qty_; }
void CrossRequest::set_last_qty(std::optional<std::int32_t> value) { last_qty_ = value; }

const std::array<std::byte, 4>& CrossRequest::pad4() const { return pad4_; }
std::array<std::byte, 4>& CrossRequest::pad4() { return pad4_; }
void CrossRequest::set_pad4(const std::array<std::byte, 4>& value) { pad4_ = value; }

std::optional<std::chrono::nanoseconds> CrossRequest::transact_time() const { return transact_time_; }
void CrossRequest::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

MessageCode CrossRequest::type() const { return message_type; }

std::string_view CrossRequest::name() const { return "Cross Request"; }

std::size_t CrossRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CrossRequest", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    last_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    wire::read_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t CrossRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CrossRequest", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_i32_le(data + offset, last_qty_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

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
    out << ", last_qty=";
    print::optional(out, last_qty_);
    out << ", pad4=";
    print::hex(out, pad4_.data(), pad4_.size());
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
        && last_qty_ == other.last_qty_
        && pad4_ == other.pad4_
        && transact_time_ == other.transact_time_;
}

bool CrossRequest::operator!=(const CrossRequest& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v6_0
