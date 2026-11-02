#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

#include "../enums/Schema.hpp"
#include "../enums/StypeIn.hpp"
#include "../enums/StypeOut.hpp"
#include "../enums/TsOut.hpp"
#include "../groups/SymbolMapping.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// DBN metadata header, once at the start of a file or stream
class Metadata {
  public:

    Metadata() = default;
    Metadata(const std::string& magic, std::uint8_t version, std::uint32_t metadata_length, const std::string& dataset, std::optional<Schema> schema, std::chrono::nanoseconds start, std::optional<std::chrono::nanoseconds> end, std::optional<std::uint64_t> limit, std::optional<StypeIn> stype_in, StypeOut stype_out, TsOut ts_out, std::uint16_t symbol_cstr_len, const std::array<std::byte, 53>& metadata_reserved, std::uint32_t schema_definition_length, const std::vector<std::byte>& schema_definition, std::uint32_t symbols_count, const std::string& symbol, std::uint32_t partial_count, const std::string& partial_symbol, std::uint32_t not_found_count, const std::string& not_found_symbol, std::uint32_t mappings_count, const std::vector<SymbolMapping>& symbol_mapping, const std::array<std::byte, 0>& metadata_padding);

    // Magic: The DBN magic string
    const std::string& magic() const;
    std::string& magic();
    void set_magic(const std::string& value);

    // Version: The DBN schema version number
    std::uint8_t version() const;
    void set_version(std::uint8_t value);

    // Metadata Length: The length of the metadata after this field, in bytes
    std::uint32_t metadata_length() const;
    void set_metadata_length(std::uint32_t value);

    // Dataset: The dataset code
    const std::string& dataset() const;
    std::string& dataset();
    void set_dataset(const std::string& value);

    // Schema: The data record schema; no value for a file of mixed schemas
    std::optional<Schema> schema() const;
    void set_schema(std::optional<Schema> value);

    // Start: The start time of query range in UNIX epoch nanoseconds
    std::chrono::nanoseconds start() const;
    void set_start(std::chrono::nanoseconds value);

    // End: The end time of query range in UNIX epoch nanoseconds; no value when unbounded
    std::optional<std::chrono::nanoseconds> end() const;
    void set_end(std::optional<std::chrono::nanoseconds> value);

    // Limit: The maximum number of records to return; no value when unlimited
    std::optional<std::uint64_t> limit() const;
    void set_limit(std::optional<std::uint64_t> value);

    // Stype In: The input symbology type
    std::optional<StypeIn> stype_in() const;
    void set_stype_in(std::optional<StypeIn> value);

    // Stype Out: The output symbology type
    StypeOut stype_out() const;
    void set_stype_out(StypeOut value);

    // Ts Out: Whether every record carries a ts_out trailer, the live gateway send timestamp
    TsOut ts_out() const;
    void set_ts_out(TsOut value);

    // Symbol Cstr Len: The number of bytes in fixed-length symbol strings, including a null
    // terminator byte; 71 in version 3
    std::uint16_t symbol_cstr_len() const;
    void set_symbol_cstr_len(std::uint16_t value);

    // Metadata Reserved: Reserved, 53 bytes
    const std::array<std::byte, 53>& metadata_reserved() const;
    std::array<std::byte, 53>& metadata_reserved();
    void set_metadata_reserved(const std::array<std::byte, 53>& value);

    // Schema Definition Length: The length of the schema definition; always 0
    std::uint32_t schema_definition_length() const;
    void set_schema_definition_length(std::uint32_t value);

    // Schema Definition: The schema definition; always empty
    const std::vector<std::byte>& schema_definition() const;
    std::vector<std::byte>& schema_definition();
    void set_schema_definition(const std::vector<std::byte>& value);

    // Symbols Count: The number of query input symbols
    std::uint32_t symbols_count() const;
    void set_symbols_count(std::uint32_t value);

    // Symbol: One of the query input symbols
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Partial Count: The number of symbols that did not resolve for at least one day in the
    // query time range
    std::uint32_t partial_count() const;
    void set_partial_count(std::uint32_t value);

    // Partial Symbol: One of the symbols that did not resolve for at least one day in the
    // query time range
    const std::string& partial_symbol() const;
    std::string& partial_symbol();
    void set_partial_symbol(const std::string& value);

    // Not Found Count: The number of symbols that did not resolve for any day in the query
    // time range
    std::uint32_t not_found_count() const;
    void set_not_found_count(std::uint32_t value);

    // Not Found Symbol: One of the symbols that did not resolve for any day in the query time
    // range
    const std::string& not_found_symbol() const;
    std::string& not_found_symbol();
    void set_not_found_symbol(const std::string& value);

    // Mappings Count: The number of symbol mappings
    std::uint32_t mappings_count() const;
    void set_mappings_count(std::uint32_t value);

    // Symbol Mapping: The mappings of one raw symbol
    const std::vector<SymbolMapping>& symbol_mapping() const;
    std::vector<SymbolMapping>& symbol_mapping();
    void set_symbol_mapping(const std::vector<SymbolMapping>& value);

    // Metadata Padding: Padding to an 8 byte boundary
    const std::array<std::byte, 0>& metadata_padding() const;
    std::array<std::byte, 0>& metadata_padding();
    void set_metadata_padding(const std::array<std::byte, 0>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const Metadata& other) const;
    bool operator!=(const Metadata& other) const;

  private:
    std::string magic_{};
    std::uint8_t version_{};
    std::uint32_t metadata_length_{};
    std::string dataset_{};
    std::optional<Schema> schema_{};
    std::chrono::nanoseconds start_{};
    std::optional<std::chrono::nanoseconds> end_{};
    std::optional<std::uint64_t> limit_{};
    std::optional<StypeIn> stype_in_{};
    StypeOut stype_out_{};
    TsOut ts_out_{};
    std::uint16_t symbol_cstr_len_{};
    std::array<std::byte, 53> metadata_reserved_{};
    std::uint32_t schema_definition_length_{};
    std::vector<std::byte> schema_definition_{};
    std::uint32_t symbols_count_{};
    std::string symbol_{};
    std::uint32_t partial_count_{};
    std::string partial_symbol_{};
    std::uint32_t not_found_count_{};
    std::string not_found_symbol_{};
    std::uint32_t mappings_count_{};
    std::vector<SymbolMapping> symbol_mapping_{};
    std::array<std::byte, 0> metadata_padding_{};
};

std::ostream& operator<<(std::ostream& out, const Metadata& value);

} // namespace databento::marketdata::normalized::dbn::v2
