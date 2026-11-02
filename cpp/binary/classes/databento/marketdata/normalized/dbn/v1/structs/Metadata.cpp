#include "Metadata.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

Metadata::Metadata(const std::string& magic, std::uint8_t version, std::uint32_t metadata_length, const std::string& dataset, std::optional<Schema> schema, std::chrono::nanoseconds start, std::optional<std::chrono::nanoseconds> end, std::optional<std::uint64_t> limit, const std::array<std::byte, 8>& metadata_reserved_8, std::optional<StypeIn> stype_in, StypeOut stype_out, TsOut ts_out, const std::array<std::byte, 47>& metadata_reserved, std::uint32_t schema_definition_length, const std::vector<std::byte>& schema_definition, std::uint32_t symbols_count, const std::string& symbol, std::uint32_t partial_count, const std::string& partial_symbol, std::uint32_t not_found_count, const std::string& not_found_symbol, std::uint32_t mappings_count, const std::vector<SymbolMapping>& symbol_mapping)
  : magic_(magic), version_(version), metadata_length_(metadata_length), dataset_(dataset), schema_(schema), start_(start), end_(end), limit_(limit), metadata_reserved_8_(metadata_reserved_8), stype_in_(stype_in), stype_out_(stype_out), ts_out_(ts_out), metadata_reserved_(metadata_reserved), schema_definition_length_(schema_definition_length), schema_definition_(schema_definition), symbols_count_(symbols_count), symbol_(symbol), partial_count_(partial_count), partial_symbol_(partial_symbol), not_found_count_(not_found_count), not_found_symbol_(not_found_symbol), mappings_count_(mappings_count), symbol_mapping_(symbol_mapping) {}

const std::string& Metadata::magic() const { return magic_; }
std::string& Metadata::magic() { return magic_; }
void Metadata::set_magic(const std::string& value) { magic_ = value; }

std::uint8_t Metadata::version() const { return version_; }
void Metadata::set_version(std::uint8_t value) { version_ = value; }

std::uint32_t Metadata::metadata_length() const { return metadata_length_; }
void Metadata::set_metadata_length(std::uint32_t value) { metadata_length_ = value; }

const std::string& Metadata::dataset() const { return dataset_; }
std::string& Metadata::dataset() { return dataset_; }
void Metadata::set_dataset(const std::string& value) { dataset_ = value; }

std::optional<Schema> Metadata::schema() const { return schema_; }
void Metadata::set_schema(std::optional<Schema> value) { schema_ = value; }

std::chrono::nanoseconds Metadata::start() const { return start_; }
void Metadata::set_start(std::chrono::nanoseconds value) { start_ = value; }

std::optional<std::chrono::nanoseconds> Metadata::end() const { return end_; }
void Metadata::set_end(std::optional<std::chrono::nanoseconds> value) { end_ = value; }

std::optional<std::uint64_t> Metadata::limit() const { return limit_; }
void Metadata::set_limit(std::optional<std::uint64_t> value) { limit_ = value; }

const std::array<std::byte, 8>& Metadata::metadata_reserved_8() const { return metadata_reserved_8_; }
std::array<std::byte, 8>& Metadata::metadata_reserved_8() { return metadata_reserved_8_; }
void Metadata::set_metadata_reserved_8(const std::array<std::byte, 8>& value) { metadata_reserved_8_ = value; }

std::optional<StypeIn> Metadata::stype_in() const { return stype_in_; }
void Metadata::set_stype_in(std::optional<StypeIn> value) { stype_in_ = value; }

StypeOut Metadata::stype_out() const { return stype_out_; }
void Metadata::set_stype_out(StypeOut value) { stype_out_ = value; }

TsOut Metadata::ts_out() const { return ts_out_; }
void Metadata::set_ts_out(TsOut value) { ts_out_ = value; }

const std::array<std::byte, 47>& Metadata::metadata_reserved() const { return metadata_reserved_; }
std::array<std::byte, 47>& Metadata::metadata_reserved() { return metadata_reserved_; }
void Metadata::set_metadata_reserved(const std::array<std::byte, 47>& value) { metadata_reserved_ = value; }

std::uint32_t Metadata::schema_definition_length() const { return schema_definition_length_; }
void Metadata::set_schema_definition_length(std::uint32_t value) { schema_definition_length_ = value; }

const std::vector<std::byte>& Metadata::schema_definition() const { return schema_definition_; }
std::vector<std::byte>& Metadata::schema_definition() { return schema_definition_; }
void Metadata::set_schema_definition(const std::vector<std::byte>& value) { schema_definition_ = value; }

std::uint32_t Metadata::symbols_count() const { return symbols_count_; }
void Metadata::set_symbols_count(std::uint32_t value) { symbols_count_ = value; }

const std::string& Metadata::symbol() const { return symbol_; }
std::string& Metadata::symbol() { return symbol_; }
void Metadata::set_symbol(const std::string& value) { symbol_ = value; }

std::uint32_t Metadata::partial_count() const { return partial_count_; }
void Metadata::set_partial_count(std::uint32_t value) { partial_count_ = value; }

const std::string& Metadata::partial_symbol() const { return partial_symbol_; }
std::string& Metadata::partial_symbol() { return partial_symbol_; }
void Metadata::set_partial_symbol(const std::string& value) { partial_symbol_ = value; }

std::uint32_t Metadata::not_found_count() const { return not_found_count_; }
void Metadata::set_not_found_count(std::uint32_t value) { not_found_count_ = value; }

const std::string& Metadata::not_found_symbol() const { return not_found_symbol_; }
std::string& Metadata::not_found_symbol() { return not_found_symbol_; }
void Metadata::set_not_found_symbol(const std::string& value) { not_found_symbol_ = value; }

std::uint32_t Metadata::mappings_count() const { return mappings_count_; }
void Metadata::set_mappings_count(std::uint32_t value) { mappings_count_ = value; }

const std::vector<SymbolMapping>& Metadata::symbol_mapping() const { return symbol_mapping_; }
std::vector<SymbolMapping>& Metadata::symbol_mapping() { return symbol_mapping_; }
void Metadata::set_symbol_mapping(const std::vector<SymbolMapping>& value) { symbol_mapping_ = value; }

std::size_t Metadata::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("Metadata", offset + 3, length);
    magic_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("Metadata", offset + 1, length);
    version_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("Metadata", offset + 4, length);
    metadata_length_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("Metadata", offset + 16, length);
    dataset_ = wire::read_text(data + offset, 16, '\0');
    offset += 16;

    wire::require("Metadata", offset + 2, length);
    schema_ = wire::nullable_enum<Schema>(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("Metadata", offset + 8, length);
    start_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("Metadata", offset + 8, length);
    end_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::require("Metadata", offset + 8, length);
    limit_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("Metadata", offset + 8, length);
    wire::read_bytes(data + offset, metadata_reserved_8_.data(), 8);
    offset += 8;

    wire::require("Metadata", offset + 1, length);
    stype_in_ = wire::nullable_enum<StypeIn>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("Metadata", offset + 1, length);
    stype_out_ = static_cast<StypeOut>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("Metadata", offset + 1, length);
    ts_out_ = static_cast<TsOut>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("Metadata", offset + 47, length);
    wire::read_bytes(data + offset, metadata_reserved_.data(), 47);
    offset += 47;

    wire::require("Metadata", offset + 4, length);
    schema_definition_length_ = wire::read_u32_le(data + offset);
    offset += 4;

    {
        const std::size_t count = wire::count(schema_definition_length_);
        wire::require("Metadata", offset + count, length);
        schema_definition_.assign(data + offset, data + offset + count);
        offset += count;
    }

    wire::require("Metadata", offset + 4, length);
    symbols_count_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("Metadata", offset + 22, length);
    symbol_ = wire::read_text(data + offset, 22, '\0');
    offset += 22;

    wire::require("Metadata", offset + 4, length);
    partial_count_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("Metadata", offset + 22, length);
    partial_symbol_ = wire::read_text(data + offset, 22, '\0');
    offset += 22;

    wire::require("Metadata", offset + 4, length);
    not_found_count_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("Metadata", offset + 22, length);
    not_found_symbol_ = wire::read_text(data + offset, 22, '\0');
    offset += 22;

    wire::require("Metadata", offset + 4, length);
    mappings_count_ = wire::read_u32_le(data + offset);
    offset += 4;

    {
        const std::size_t count = wire::count(mappings_count_);
        symbol_mapping_.clear();
        symbol_mapping_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SymbolMapping entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            symbol_mapping_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t Metadata::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Metadata", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto schema_definition_length = schema_definition_length_;
    schema_definition_length = static_cast<std::uint32_t>(schema_definition_.size());
    auto mappings_count = mappings_count_;
    mappings_count = static_cast<std::uint32_t>(symbol_mapping_.size());

    wire::write_text(data + offset, 3, '\0', magic_);
    offset += 3;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(version_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(metadata_length_));
    offset += 4;

    wire::write_text(data + offset, 16, '\0', dataset_);
    offset += 16;

    wire::write_u16_le(data + offset, schema_ ? static_cast<std::uint16_t>(*schema_) : static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(start_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, end_ ? static_cast<std::uint64_t>(end_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_u64_le(data + offset, limit_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_bytes(data + offset, metadata_reserved_8_.data(), 8);
    offset += 8;

    wire::write_u8(data + offset, stype_in_ ? static_cast<std::uint8_t>(*stype_in_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(stype_out_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(ts_out_));
    offset += 1;

    wire::write_bytes(data + offset, metadata_reserved_.data(), 47);
    offset += 47;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(schema_definition_length));
    offset += 4;

    wire::require_capacity("encode", offset + schema_definition_.size(), capacity);
    wire::write_bytes(data + offset, schema_definition_.data(), schema_definition_.size());
    offset += schema_definition_.size();

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbols_count_));
    offset += 4;

    wire::write_text(data + offset, 22, '\0', symbol_);
    offset += 22;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(partial_count_));
    offset += 4;

    wire::write_text(data + offset, 22, '\0', partial_symbol_);
    offset += 22;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(not_found_count_));
    offset += 4;

    wire::write_text(data + offset, 22, '\0', not_found_symbol_);
    offset += 22;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(mappings_count));
    offset += 4;

    for (const auto& entry : symbol_mapping_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t Metadata::encoded_size() const {
    return 3 + 1 + 4 + 16 + 2 + 8 + 8 + 8 + 8 + 1 + 1 + 1 + 47 + 4 + schema_definition_.size() + 4 + 22 + 4 + 22 + 4 + 22 + 4 + wire::encoded_size_of(symbol_mapping_);
}

void Metadata::print(std::ostream& out) const {
    out << "Metadata{";
    out << "magic=";
    print::text(out, magic_);
    out << ", version=";
    out << static_cast<int>(version_);
    out << ", metadata_length=";
    out << metadata_length_;
    out << ", dataset=";
    print::text(out, dataset_);
    out << ", schema=";
    print::optional(out, schema_);
    out << ", start=";
    out << start_.count();
    out << ", end=";
    print::optional_duration(out, end_);
    out << ", limit=";
    print::optional(out, limit_);
    out << ", metadata_reserved_8=";
    print::hex(out, metadata_reserved_8_.data(), metadata_reserved_8_.size());
    out << ", stype_in=";
    print::optional(out, stype_in_);
    out << ", stype_out=";
    out << stype_out_;
    out << ", ts_out=";
    out << ts_out_;
    out << ", metadata_reserved=";
    print::hex(out, metadata_reserved_.data(), metadata_reserved_.size());
    out << ", schema_definition_length=";
    out << schema_definition_length_;
    out << ", schema_definition=";
    print::hex(out, schema_definition_.data(), schema_definition_.size());
    out << ", symbols_count=";
    out << symbols_count_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", partial_count=";
    out << partial_count_;
    out << ", partial_symbol=";
    print::text(out, partial_symbol_);
    out << ", not_found_count=";
    out << not_found_count_;
    out << ", not_found_symbol=";
    print::text(out, not_found_symbol_);
    out << ", mappings_count=";
    out << mappings_count_;
    out << ", symbol_mapping=";
    print::sequence(out, symbol_mapping_);
    out << '}';
}

bool Metadata::operator==(const Metadata& other) const {
    return magic_ == other.magic_
        && version_ == other.version_
        && metadata_length_ == other.metadata_length_
        && dataset_ == other.dataset_
        && schema_ == other.schema_
        && start_ == other.start_
        && end_ == other.end_
        && limit_ == other.limit_
        && metadata_reserved_8_ == other.metadata_reserved_8_
        && stype_in_ == other.stype_in_
        && stype_out_ == other.stype_out_
        && ts_out_ == other.ts_out_
        && metadata_reserved_ == other.metadata_reserved_
        && schema_definition_length_ == other.schema_definition_length_
        && schema_definition_ == other.schema_definition_
        && symbols_count_ == other.symbols_count_
        && symbol_ == other.symbol_
        && partial_count_ == other.partial_count_
        && partial_symbol_ == other.partial_symbol_
        && not_found_count_ == other.not_found_count_
        && not_found_symbol_ == other.not_found_symbol_
        && mappings_count_ == other.mappings_count_
        && symbol_mapping_ == other.symbol_mapping_;
}

bool Metadata::operator!=(const Metadata& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Metadata& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v1
