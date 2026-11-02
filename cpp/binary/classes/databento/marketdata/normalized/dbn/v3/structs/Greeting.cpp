#include "Greeting.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

Greeting::Greeting(const std::string& control_fields)
  : control_fields_(control_fields) {}

const std::string& Greeting::control_fields() const { return control_fields_; }
std::string& Greeting::control_fields() { return control_fields_; }
void Greeting::set_control_fields(const std::string& value) { control_fields_ = value; }

std::size_t Greeting::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    {
        const std::size_t count = wire::terminated_length(data + offset, length - offset, 0);
        control_fields_ = wire::read_text(data + offset, count, '\0');
        offset += count + 1;
    }

    return offset;
}

std::size_t Greeting::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Greeting", encoded_size(), capacity);

    wire::require_capacity("encode", offset + control_fields_.size() + 1, capacity);
    wire::write_text(data + offset, control_fields_.size(), '\0', control_fields_);
    offset += control_fields_.size();
    wire::write_u8(data + offset, 0);
    offset += 1;

    return offset;
}

std::size_t Greeting::encoded_size() const {
    return (control_fields_.size() + 1);
}

void Greeting::print(std::ostream& out) const {
    out << "Greeting{";
    out << "control_fields=";
    print::text(out, control_fields_);
    out << '}';
}

bool Greeting::operator==(const Greeting& other) const {
    return control_fields_ == other.control_fields_;
}

bool Greeting::operator!=(const Greeting& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Greeting& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v3
