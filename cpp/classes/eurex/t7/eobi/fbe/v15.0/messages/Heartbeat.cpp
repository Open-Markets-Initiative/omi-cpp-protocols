#include "Heartbeat.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

Heartbeat::Heartbeat(std::optional<std::uint32_t> last_msg_seq_num_processed, const std::array<std::byte, 4>& pad4)
  : last_msg_seq_num_processed_(last_msg_seq_num_processed), pad4_(pad4) {}

std::optional<std::uint32_t> Heartbeat::last_msg_seq_num_processed() const { return last_msg_seq_num_processed_; }
void Heartbeat::set_last_msg_seq_num_processed(std::optional<std::uint32_t> value) { last_msg_seq_num_processed_ = value; }

const std::array<std::byte, 4>& Heartbeat::pad4() const { return pad4_; }
std::array<std::byte, 4>& Heartbeat::pad4() { return pad4_; }
void Heartbeat::set_pad4(const std::array<std::byte, 4>& value) { pad4_ = value; }

MessageCode Heartbeat::type() const { return message_type; }

std::string_view Heartbeat::name() const { return "Heartbeat"; }

std::size_t Heartbeat::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("Heartbeat", wire_size, length);

    last_msg_seq_num_processed_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0xFFFFFFFFULL));
    offset += 4;

    wire::read_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t Heartbeat::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Heartbeat", wire_size, capacity);

    wire::write_u32_le(data + offset, last_msg_seq_num_processed_.value_or(static_cast<std::uint32_t>(0xFFFFFFFFULL)));
    offset += 4;

    wire::write_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t Heartbeat::encoded_size() const {
    return wire_size;
}

void Heartbeat::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> Heartbeat::clone() const {
    return std::make_unique<Heartbeat>(*this);
}

void Heartbeat::print(std::ostream& out) const {
    out << "Heartbeat{";
    out << "last_msg_seq_num_processed=";
    print::optional(out, last_msg_seq_num_processed_);
    out << ", pad4=";
    print::hex(out, pad4_.data(), pad4_.size());
    out << '}';
}

bool Heartbeat::equals(const Message& other) const {
    const auto* that = dynamic_cast<const Heartbeat*>(&other);
    return that != nullptr && *this == *that;
}

bool Heartbeat::operator==(const Heartbeat& other) const {
    return last_msg_seq_num_processed_ == other.last_msg_seq_num_processed_
        && pad4_ == other.pad4_;
}

bool Heartbeat::operator!=(const Heartbeat& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v15_0
