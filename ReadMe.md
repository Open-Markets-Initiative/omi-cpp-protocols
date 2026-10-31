# Omi C++ Protocols

Generated C++ protocol parsers, one directory per model family under `cpp/` and, within a
family, one directory tree per generation format. The binary protocols are under `cpp/binary/`:

- `cpp/binary/advanced/` — packed structs, types, messages and dispatch (the Advanced parser)
- `cpp/binary/modern/` — the Modern parser
- `cpp/binary/classes/` — the Classes library: owning classes that decode once and encode back
- `cpp/binary/flyweight/` — the Flyweight library: views over the bytes, read in place without casts
- `cpp/binary/tmp/` — the Tmp header: one per protocol, types and packed messages, each field asked for by its type

The delimited files are read under `cpp/delimited/`: a reader per protocol, which reads each line
of a file straight into typed C++ values (see Delimited, below).

Every parser is compile-verified: `checks/` holds one translation unit per protocol and
format that includes the aggregating headers, and `CMakeLists.txt` compiles them all —
so a clean build fires the generated layout `static_assert`s across every protocol.

```sh
cmake -S . -B build && cmake --build build
```

## Development

Updates are greatly appreciated; however, this entire repository is source generated. If you wish to suggest updates, the recommended process is to create an issue with changes and explanation.

| Parser | Protocol Count | Generated Lines |
| --- | --- | --- |
| Advanced | 92 | 710,762 |
| Modern | 96 | 412,351 |
| Classes | 97 | 964,881 |
| Flyweight | 96 | 451,861 |
| Tmp | 98 | 239,702 |
| Delimited | 10 | 3,577 |

| Organization | Protocol Count | Generated Lines |
| --- | --- | --- |
| Asx | 1 | 29,009 |
| B3 | 10 | 548,324 |
| Bse | 1 | 21,537 |
| Cboe | 10 | 192,150 |
| CixAts | 1 | 11,313 |
| Cme | 4 | 358,284 |
| Eurex | 4 | 124,643 |
| Iex | 10 | 145,006 |
| Jnx | 3 | 54,785 |
| Jpx | 2 | 32,541 |
| Lseg | 2 | 37,138 |
| Memx | 1 | 12,787 |
| Miax | 4 | 55,372 |
| Nasdaq | 13 | 387,545 |
| Nyse | 33 | 478,075 |
| OtcMarkets | 1 | 13,619 |
| Siac | 7 | 275,057 |
| Tmx | 1 | 4,917 |

## Programs

`executables/` holds the programs, one directory per protocol under each. They read the
parsers published under `cpp/` by a repository-root-relative include, so a protocol's parser
exists in exactly one place. Each program reads through one format:

- `executables/dump/` — prints every message as its class and fields, through Classes
- `executables/extractor/` — samples a capture down to one packet per message type, through Modern
- `executables/statistics/` — counts packets and messages by type, through Advanced where the
  protocol has a transport sequence and Modern where it does not
- `executables/verify/` — holds every packet to the rules it was framed by and requires it to
  encode back to its own bytes, through Classes; exits non-zero on any failure
- `executables/roundtrip/` — builds every message with each field set, writes them into a
  capture of its own and reads it back, through Classes; each field must read as it was written

The pcap reader they all share is `executables/pcap/`.

```sh
./build/dump_<protocol> capture.pcap
./build/extractor_<protocol> capture.pcap output-directory
./build/statistics_<protocol> -i capture.pcap
./build/verify_<protocol> capture.pcap
./build/roundtrip_<protocol> written.pcap
```

## Delimited

`cpp/delimited/` holds a reader per delimited protocol (10 of them, the NYSE Daily
TAQ files): a csv's header row, which selects the layout variant the file is read by, then each
data line read straight into typed C++ values, with no binary record between. A protocol's reader
is two headers in its directory: `Rows.hpp`, the reading of a line onto a row, and `Row.hpp`, its
data record as a plain C++ row - text as a `std::string_view` of the line, an integer, a decimal as
the integer of its stated places, a date as days since 1970-01-01, a time of day as its count since
midnight, a field a line may leave empty as optional. A time of day counted from midnight in a zone
the model states has `<field>_utc(day)`, the instant on a day, UTC Unix nanoseconds; a row prints
it so on a stream's print day (`out << calendar::on(day)`), ISO 8601 UTC.

The headers every reader shares are emitted once, in `cpp/delimited/delimited/`: the line scanner
(`Scanner.hpp`), the values a row holds (`Values.hpp`) and the calendar (`Day.hpp`). A reader
includes them as `../delimited/`, which resolves with `cpp/delimited/delimited` on the include path,
as `checks/` compiles each reader. Nothing here needs Arrow: a Parquet program is the formats
repository's.

`executables/rows/` holds a program per protocol reading a file of its lines, gzip or plain, through
its reader, printing the first rows and counting the rest. It reads gzip through zlib, so the build
makes it where zlib is found.

```sh
./build/rows_<protocol> lines.csv.gz [--rows count] [--day yyyymmdd]
```

## Tests

`tests/` holds a test per protocol and format (480 of them), each written against the
surface that format's program uses, plus one run of each program on its protocol's first
declared capture (306 of them):

- `tests/binary/modern/` walks every payload with the Modern iterator and requires the declared
  message — what extractor reads through
- `tests/binary/advanced/` walks every segment with the session layer's `process_segment` and
  requires the declared message to be dispatched — what statistics reads through
- `tests/binary/classes/` decodes every datagram into the `Packet`, requires the declared message
  through the `Visitor`, and requires each datagram to encode back to its own bytes — what
  dump reads through
- the program runs require dump to print the message's class, statistics to count it,
  extractor to write a sample, and verify to pass the whole capture
- roundtrip runs without a capture (416 of them): each must read back every
  message it wrote as it was written

Every build compiles them, so a test that does not build fails the build like anything under
`checks/`. Running them reads the captures each protocol declares, which takes a packet
corpus checkout:

```sh
cmake -S . -B build -DOMI_PACKETS_DIR=/path/to/packets
cmake --build build --parallel && ctest --test-dir build
```

A protocol a format's generator refuses is left out of that format, and out of the programs
and tests that read through it:

- Cboe.C1Options.MarketDataFeed.Csm.v1.4.2, Modern: 'packet.message.payload.securitydefinitionmessage' has no size known before it is read, nor a Size rule stating one
- Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d, Advanced: 'Heartbeat' is an action the model neither calls a message nor sets in a packet, so it has no place among the messages or the packets
- Miax.MiaxOptions.TopOfMarket.Mach.v2.5, Advanced: 'Heartbeat' is an action the model neither calls a message nor sets in a packet, so it has no place among the messages or the packets
- Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1, Advanced: 'Heartbeat' is an action the model neither calls a message nor sets in a packet, so it has no place among the messages or the packets
- Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b, Advanced: 'Heartbeat' is an action the model neither calls a message nor sets in a packet, so it has no place among the messages or the packets
- Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b, Flyweight: 'packet.machmessage.payload.applicationmessage.data.simpleinstrumentdefinitionmessage.minimumsize' is named minimum_size, which its view declares for itself
- OtcMarkets.LinkAts.Multicast.Link.v4.3, Advanced: Unrecognized C++ type for element 'Heartbeat' (size=1, addr=packet.packetheader.packetflag.heartbeat). Traits: [Size=1, Memory=Bits]. Add a kind in TypeKind.For(), or a branch in TypeKind.CppType.
- OtcMarkets.LinkAts.Multicast.Link.v4.3, Modern: Unsupported C++ integer: 'Heartbeat' (1 bytes, signed=False, unsigned=False, isBytes=False)
- Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10, Advanced: 'packet.frameheader.numbody' counts a group of 'packet.packetbody.heartbeatbody' but lies outside it
- Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10, Classes: the payload branch selecting 'Business Bodies' has no dependency and data; default and composite dispatch keys are not yet supported by the Classes generator
- Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10, Flyweight: the payload branch selecting 'Business Bodies' has no dependency and data; default and composite dispatch keys are not yet supported by the Flyweight generator

## Organizations

> [Asx][Asx.Directory] · [B3][B3.Directory] · [Bse][Bse.Directory] · [Cboe][Cboe.Directory] · [CixAts][CixAts.Directory] · [Cme][Cme.Directory] · [Eurex][Eurex.Directory] · [Iex][Iex.Directory] · [Jnx][Jnx.Directory] · [Jpx][Jpx.Directory] · [Lseg][Lseg.Directory] · [Memx][Memx.Directory] · [Miax][Miax.Directory] · [Nasdaq][Nasdaq.Directory] · [Nyse][Nyse.Directory] · [OtcMarkets][OtcMarkets.Directory] · [Siac][Siac.Directory] · [Tmx][Tmx.Directory]

## Exchanges

> [AmexEquities][AmexEquities.Exchange] · [AmexOptions][AmexOptions.Exchange] · [ArcaEquities][ArcaEquities.Exchange] · [ArcaOptions][ArcaOptions.Exchange] · [AsxDerivatives][AsxDerivatives.Exchange] · [B3Derivatives][B3Derivatives.Exchange] · [BseIndia][BseIndia.Exchange] · [ByxEquities][ByxEquities.Exchange] · [BzxEquities][BzxEquities.Exchange] · [C1Options][C1Options.Exchange] · [CfeFutures][CfeFutures.Exchange] · [EdgaEquities][EdgaEquities.Exchange] · [EdgxEquities][EdgxEquities.Exchange] · [EdgxOptions][EdgxOptions.Exchange] · [IexEquities][IexEquities.Exchange] · [IseOptions][IseOptions.Exchange] · [JnxEquities][JnxEquities.Exchange] · [LinkAts][LinkAts.Ats] · [Lse][Lse.Exchange] · [MemxEquities][MemxEquities.Exchange] · [MiaxOptions][MiaxOptions.Exchange] · [NationalEquities][NationalEquities.Exchange] · [NomOptions][NomOptions.Exchange] · [NordicEquities][NordicEquities.Exchange] · [NsmEquities][NsmEquities.Exchange] · [NtxEquities][NtxEquities.Exchange] · [NyseEquities][NyseEquities.Exchange] · [OnyxFutures][OnyxFutures.Exchange] · [OseDerivatives][OseDerivatives.Exchange] · [PearlEquities][PearlEquities.Exchange] · [PhlxOptions][PhlxOptions.Exchange] · [PsxEquities][PsxEquities.Exchange] · [TexasEquities][TexasEquities.Exchange] · [TseEquities][TseEquities.Exchange] · [Tsx][Tsx.Exchange]

## Platforms

> [CixAts CixAspen][CixAspen.Platform] · [Cme Globex][Globex.Platform] · [Lseg Millennium][Millennium.Platform] · [Eurex T7][T7.Platform]

## Consolidators

> [Cqs][Cqs.Consolidator] · [Cts][Cts.Consolidator] · [NyseConsolidated][NyseConsolidated.Consolidator] · [Opra][Opra.Consolidator]

[Asx.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Asx "Australian Securities Exchange"
[B3.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/B3 "Brasil, Bolsa, Balcão"
[Bse.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Bse "BSE Limited"
[Cboe.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cboe "Chicago Board Options Exchange"
[CixAts.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/CixAts "CIX Trading Inc."
[Cme.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cme "CME Group"
[Eurex.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Eurex "Eurex Exchange"
[Iex.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Iex "Investors Exchange"
[Jnx.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Jnx "Japannext Securities"
[Jpx.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Jpx "Japan Exchange Group"
[Lseg.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Lseg "London Stock Exchange"
[Memx.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Memx "The Members Exchange"
[Miax.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Miax "Miami International Holdings"
[Nasdaq.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq "National Association of Securities Dealers Automated Quotations (Nasdaq)"
[Nyse.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse "New York Stock Exchange"
[OtcMarkets.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/OtcMarkets "OTC Markets Group"
[Siac.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Siac "The Securities Industry Automation Corporation"
[Tmx.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Tmx "TMX Group"
[AmexEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse/Protocols/AmexEquities "Nyse Amex Equities"
[AmexOptions.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse/Protocols/AmexOptions "Nyse Amex Options"
[ArcaEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse/Protocols/ArcaEquities "Nyse Arca Equities"
[ArcaOptions.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse/Protocols/ArcaOptions "Nyse Arca Options"
[AsxDerivatives.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Asx/Protocols/AsxDerivatives "Asx Derivatives"
[B3Derivatives.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/B3/Protocols/B3Derivatives "B3 Derivatives"
[BseIndia.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Bse/Protocols/BseIndia "BSE India"
[ByxEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cboe/Protocols/ByxEquities "Cboe Byx Equities"
[BzxEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cboe/Protocols/BzxEquities "Cboe Bzx Equities"
[C1Options.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cboe/Protocols/C1Options "Cboe C1 Options"
[CfeFutures.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cboe/Protocols/CfeFutures "Cboe Futures Exchange"
[CixAspen.Platform]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/CixAts/Protocols/CixAspen "CIX Aspen"
[Cqs.Consolidator]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Siac/Protocols/Cqs "Consolidated Quotation System"
[Cts.Consolidator]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Siac/Protocols/Cts "Consolidated Tape System"
[EdgaEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cboe/Protocols/EdgaEquities "Cboe Edga Equities"
[EdgxEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cboe/Protocols/EdgxEquities "Cboe Edgx Equities"
[EdgxOptions.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cboe/Protocols/EdgxOptions "Cboe Edgx Options"
[Globex.Platform]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cme/Protocols/Globex "CME Globex"
[IexEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Iex/Protocols/IexEquities "IEX Equities"
[IseOptions.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq/Protocols/IseOptions "Nasdaq ISE"
[JnxEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Jnx/Protocols/JnxEquities "Japannext Equities"
[LinkAts.Ats]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/OtcMarkets/Protocols/LinkAts "OTC Link ATS"
[Lse.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Lseg/Protocols/Lse "London Stock Exchange"
[MemxEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Memx/Protocols/MemxEquities "Memx Equities"
[MiaxOptions.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Miax/Protocols/MiaxOptions "MIAX Options"
[Millennium.Platform]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Lseg/Protocols/Millennium "Millennium Exchange"
[NationalEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse/Protocols/NationalEquities "Nyse National Equities"
[NomOptions.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq/Protocols/NomOptions "Nasdaq Options Market"
[NordicEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq/Protocols/NordicEquities "Nasdaq Nordic Equities"
[NsmEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq/Protocols/NsmEquities "Nasdaq Stock Market"
[NtxEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq/Protocols/NtxEquities "Nasdaq Texas"
[NyseConsolidated.Consolidator]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse/Protocols/NyseConsolidated "NYSE Consolidated"
[NyseEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse/Protocols/NyseEquities "New York Stock Exchange Equities"
[OnyxFutures.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Miax/Protocols/OnyxFutures "MIAX Futures Onyx"
[Opra.Consolidator]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Siac/Protocols/Opra "Options Price Reporting Authority"
[OseDerivatives.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Jpx/Protocols/OseDerivatives "Osaka Securities Exchange"
[PearlEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Miax/Protocols/PearlEquities "MIAX Pearl Equities"
[PhlxOptions.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq/Protocols/PhlxOptions "Nasdaq PHLX"
[PsxEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq/Protocols/PsxEquities "Nasdaq PSX"
[T7.Platform]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Eurex/Protocols/T7 "T7"
[TexasEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse/Protocols/TexasEquities "Nyse Texas Equities"
[TseEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Jpx/Protocols/TseEquities "Tokyo Stock Exchange Equities"
[Tsx.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Tmx/Protocols/Tsx "Toronto Stock Exchange"
