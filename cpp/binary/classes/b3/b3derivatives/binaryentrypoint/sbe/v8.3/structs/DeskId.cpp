#include "DeskId.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

DeskId::DeskId(std::uint8_t desk_id_length, const std::string& desk_id_data)
  : desk_id_length_(desk_id_length), desk_id_data_(desk_id_data) {}

std::uint8_t DeskId::desk_id_length() const { return desk_id_length_; }
void DeskId::set_desk_id_length(std::uint8_t value) { desk_id_length_ = value; }

const std::string& DeskId::desk_id_data() const { return desk_id_data_; }
std::string& DeskId::desk_id_data() { return desk_id_data_; }
void DeskId::set_desk_id_data(const std::string& value) { desk_id_data_ = value; }

std::size_t DeskId::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("DeskId", offset + 1, length);
    desk_id_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(desk_id_length_);
        wire::require("DeskId", offset + count, length);
        desk_id_data_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t DeskId::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("DeskId", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto desk_id_length = desk_id_length_;
    desk_id_length = static_cast<std::uint8_t>(desk_id_data_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(desk_id_length));
    offset += 1;

    wire::require_capacity("encode", offset + desk_id_data_.size(), capacity);
    wire::write_text(data + offset, desk_id_data_.size(), ' ', desk_id_data_);
    offset += desk_id_data_.size();

    return offset;
}

std::size_t DeskId::encoded_size() const {
    return 1 + desk_id_data_.size();
}

void DeskId::print(std::ostream& out) const {
    out << "DeskId{";
    out << "desk_id_length=";
    out << static_cast<int>(desk_id_length_);
    out << ", desk_id_data=";
    print::text(out, desk_id_data_);
    out << '}';
}

bool DeskId::operator==(const DeskId& other) const {
    return desk_id_length_ == other.desk_id_length_
        && desk_id_data_ == other.desk_id_data_;
}

bool DeskId::operator!=(const DeskId& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const DeskId& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
