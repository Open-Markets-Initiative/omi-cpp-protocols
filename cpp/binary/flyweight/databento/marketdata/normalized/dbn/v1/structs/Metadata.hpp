// Databento.MarketData.Normalized.Dbn.v1: structs/Metadata.hpp
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
#include "../enums/Schema.hpp"
#include "../enums/StypeIn.hpp"
#include "../enums/StypeOut.hpp"
#include "../enums/TsOut.hpp"
#include "../groups/SymbolMapping.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// DBN metadata header, once at the start of a file or stream
class Metadata {
  public:
    static constexpr const char* name = "Metadata";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Metadata(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Metadata has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 194;
    std::size_t encoded_size() const { return symbol_mapping_end(); }

    std::string_view magic() const { return view::text(at(0), 3, '\0'); }

    std::uint8_t version() const { return wire::read_u8(at(3)); }

    std::uint32_t metadata_length() const { return wire::read_u32_le(at(4)); }

    std::string_view dataset() const { return view::text(at(8), 16, '\0'); }

    std::optional<Schema> schema() const { return wire::nullable_enum<Schema>(wire::read_u16_le(at(24)), static_cast<std::uint16_t>(65535ULL)); }

    std::chrono::nanoseconds start() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(26)))); }

    std::optional<std::chrono::nanoseconds> end() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(34)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<std::uint64_t> limit() const { return wire::nullable(wire::read_u64_le(at(42)), static_cast<std::uint64_t>(0ULL)); }

    std::span<const std::byte, 8> metadata_reserved_8() const { return bytes_.subspan(50).template first<8>(); }

    std::optional<StypeIn> stype_in() const { return wire::nullable_enum<StypeIn>(wire::read_u8(at(58)), static_cast<std::uint8_t>(255ULL)); }

    StypeOut stype_out() const { return static_cast<StypeOut>(wire::read_u8(at(59))); }

    TsOut ts_out() const { return static_cast<TsOut>(wire::read_u8(at(60))); }

    std::span<const std::byte, 47> metadata_reserved() const { return bytes_.subspan(61).template first<47>(); }

    std::uint32_t schema_definition_length() const { return wire::read_u32_le(at(108)); }

    std::size_t schema_definition_size() const { return wire::count(schema_definition_length()); }
    std::span<const std::byte> schema_definition() const {
        wire::require("Metadata", 112 + schema_definition_size(), bytes_.size());
        return bytes_.subspan(112, schema_definition_size());
    }

    std::uint32_t symbols_count() const {
        wire::require("Metadata", schema_definition_end() + 4, bytes_.size());
        return wire::read_u32_le(at(schema_definition_end()));
    }

    std::string_view symbol() const {
        wire::require("Metadata", symbols_count_end() + 22, bytes_.size());
        return view::text(at(symbols_count_end()), 22, '\0');
    }

    std::uint32_t partial_count() const {
        wire::require("Metadata", symbol_end() + 4, bytes_.size());
        return wire::read_u32_le(at(symbol_end()));
    }

    std::string_view partial_symbol() const {
        wire::require("Metadata", partial_count_end() + 22, bytes_.size());
        return view::text(at(partial_count_end()), 22, '\0');
    }

    std::uint32_t not_found_count() const {
        wire::require("Metadata", partial_symbol_end() + 4, bytes_.size());
        return wire::read_u32_le(at(partial_symbol_end()));
    }

    std::string_view not_found_symbol() const {
        wire::require("Metadata", not_found_count_end() + 22, bytes_.size());
        return view::text(at(not_found_count_end()), 22, '\0');
    }

    std::uint32_t mappings_count() const {
        wire::require("Metadata", not_found_symbol_end() + 4, bytes_.size());
        return wire::read_u32_le(at(not_found_symbol_end()));
    }

    view::entries<SymbolMapping> symbol_mapping() const { return view::entries<SymbolMapping>{ bytes_.subspan(mappings_count_end()), wire::count(mappings_count()) }; }

    void print(std::ostream& out) const {
        out << "Metadata{";
        out << "magic=";
        print::text(out, magic());
        out << ", version=";
        out << static_cast<int>(version());
        out << ", metadata_length=";
        out << metadata_length();
        out << ", dataset=";
        print::text(out, dataset());
        out << ", schema=";
        print::optional(out, schema());
        out << ", start=";
        out << start().count();
        out << ", end=";
        print::optional_duration(out, end());
        out << ", limit=";
        print::optional(out, limit());
        out << ", metadata_reserved_8=";
        print::hex(out, metadata_reserved_8().data(), metadata_reserved_8().size());
        out << ", stype_in=";
        print::optional(out, stype_in());
        out << ", stype_out=";
        out << stype_out();
        out << ", ts_out=";
        out << ts_out();
        out << ", metadata_reserved=";
        print::hex(out, metadata_reserved().data(), metadata_reserved().size());
        out << ", schema_definition_length=";
        out << schema_definition_length();
        out << ", schema_definition=";
        print::hex(out, schema_definition().data(), schema_definition().size());
        out << ", symbols_count=";
        out << symbols_count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", partial_count=";
        out << partial_count();
        out << ", partial_symbol=";
        print::text(out, partial_symbol());
        out << ", not_found_count=";
        out << not_found_count();
        out << ", not_found_symbol=";
        print::text(out, not_found_symbol());
        out << ", mappings_count=";
        out << mappings_count();
        out << ", symbol_mapping=";
        print::sequence(out, symbol_mapping());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t schema_definition_end() const { return 112 + schema_definition_size(); }
    std::size_t symbols_count_end() const { return schema_definition_end() + 4; }
    std::size_t symbol_end() const { return symbols_count_end() + 22; }
    std::size_t partial_count_end() const { return symbol_end() + 4; }
    std::size_t partial_symbol_end() const { return partial_count_end() + 22; }
    std::size_t not_found_count_end() const { return partial_symbol_end() + 4; }
    std::size_t not_found_symbol_end() const { return not_found_count_end() + 22; }
    std::size_t mappings_count_end() const { return not_found_symbol_end() + 4; }
    std::size_t symbol_mapping_end() const { return mappings_count_end() + symbol_mapping().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Metadata& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v1
