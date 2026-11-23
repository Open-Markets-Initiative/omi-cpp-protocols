// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/HeartbeatBody.cpp
#include "HeartbeatBody.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Packet.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

HeartbeatBody::HeartbeatBody(const BodyHeader& body_header, std::uint8_t admin_id, std::uint16_t hb_interval, const std::vector<AdminBody>& admin_body)
  : body_header_(body_header), admin_id_(admin_id), hb_interval_(hb_interval), admin_body_(admin_body) {}

const BodyHeader& HeartbeatBody::body_header() const { return body_header_; }
BodyHeader& HeartbeatBody::body_header() { return body_header_; }
void HeartbeatBody::set_body_header(const BodyHeader& value) { body_header_ = value; }

std::uint8_t HeartbeatBody::admin_id() const { return admin_id_; }
void HeartbeatBody::set_admin_id(std::uint8_t value) { admin_id_ = value; }

std::uint16_t HeartbeatBody::hb_interval() const { return hb_interval_; }
void HeartbeatBody::set_hb_interval(std::uint16_t value) { hb_interval_ = value; }

const std::vector<AdminBody>& HeartbeatBody::admin_body() const { return admin_body_; }
std::vector<AdminBody>& HeartbeatBody::admin_body() { return admin_body_; }
void HeartbeatBody::set_admin_body(const std::vector<AdminBody>& value) { admin_body_ = value; }

std::size_t HeartbeatBody::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += body_header_.decode(data + offset, length - offset);

    wire::require("HeartbeatBody", offset + 1, length);
    admin_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("HeartbeatBody", offset + 2, length);
    hb_interval_ = wire::read_u16_le(data + offset);
    offset += 2;

    {
        const std::size_t count = wire::count(parent_->frame_header().num_body());
        admin_body_.clear();
        admin_body_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            AdminBody entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            admin_body_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t HeartbeatBody::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("HeartbeatBody", encoded_size(), capacity);

    offset += body_header_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(admin_id_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(hb_interval_));
    offset += 2;

    for (const auto& entry : admin_body_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t HeartbeatBody::encoded_size() const {
    return body_header_.encoded_size() + 1 + 2 + wire::encoded_size_of(admin_body_);
}

void HeartbeatBody::print(std::ostream& out) const {
    out << "HeartbeatBody{";
    out << "body_header=";
    body_header_.print(out);
    out << ", admin_id=";
    out << static_cast<int>(admin_id_);
    out << ", hb_interval=";
    out << hb_interval_;
    out << ", admin_body=";
    print::sequence(out, admin_body_);
    out << '}';
}

bool HeartbeatBody::operator==(const HeartbeatBody& other) const {
    return body_header_ == other.body_header_
        && admin_id_ == other.admin_id_
        && hb_interval_ == other.hb_interval_
        && admin_body_ == other.admin_body_;
}

bool HeartbeatBody::operator!=(const HeartbeatBody& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const HeartbeatBody& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
