# Omi C++ Protocols

Generated C++ binary-protocol parsers, one directory tree per generation format under
`cpp/`:

- `cpp/advanced/` — packed structs, types, messages and dispatch (the Advanced parser)
- `cpp/modern/` — the Modern parser
- `cpp/classes/` — the Classes library: owning classes that decode once and encode back
- `cpp/flyweight/` — the Flyweight library: views over the bytes, read in place without casts
- `cpp/tmp/` — the Tmp header: one per protocol, types and packed messages, each field asked for by its type

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
| Advanced | 46 | 385,121 |
| Modern | 46 | 217,884 |
| Classes | 44 | 493,547 |
| Flyweight | 44 | 222,485 |
| Tmp | 46 | 119,226 |

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

The pcap reader they all share is `executables/pcap/`.

```sh
./build/dump_<protocol> capture.pcap
./build/extractor_<protocol> capture.pcap output-directory
./build/statistics_<protocol> -i capture.pcap
./build/verify_<protocol> capture.pcap
```

## Tests

`tests/` holds a test per protocol and format (26 of them), each written against the
surface that format's program uses, plus one run of each program on its protocol's first
declared capture (45 of them):

- `tests/modern/` walks every payload with the Modern iterator and requires the declared
  message — what extractor reads through
- `tests/advanced/` walks every segment with the session layer's `process_segment` and
  requires the declared message to be dispatched — what statistics reads through
- `tests/classes/` decodes every datagram into the `Packet`, requires the declared message
  through the `Visitor`, and requires each datagram to encode back to its own bytes — what
  dump reads through
- the program runs require dump to print the message's class, statistics to count it,
  extractor to write a sample, and verify to pass the whole capture

Every build compiles them, so a test that does not build fails the build like anything under
`checks/`. Running them reads the captures each protocol declares, which takes a packet
corpus checkout:

```sh
cmake -S . -B build -DOMI_PACKETS_DIR=/path/to/packets
cmake --build build --parallel && ctest --test-dir build
```

A protocol a format's generator refuses is left out of that format, and out of the programs
and tests that read through it:

- Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d, Classes: no counted or sized frame found under the packet root 'Udp Packet'
- Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d, Flyweight: no counted or sized frame found under the packet root 'Udp Packet'
- Miax.MiaxOptions.TopOfMarket.Mach.v2.5, Classes: no counted or sized frame found under the packet root 'Udp Packet'
- Miax.MiaxOptions.TopOfMarket.Mach.v2.5, Flyweight: no counted or sized frame found under the packet root 'Udp Packet'

## Organizations

> [Asx][Asx.Directory] · [B3][B3.Directory] · [Cboe][Cboe.Directory] · [Cme][Cme.Directory] · [Eurex][Eurex.Directory] · [Iex][Iex.Directory] · [Jpx][Jpx.Directory] · [Lseg][Lseg.Directory] · [Memx][Memx.Directory] · [Miax][Miax.Directory] · [Nasdaq][Nasdaq.Directory] · [Nyse][Nyse.Directory] · [Siac][Siac.Directory]

## Exchanges

> [ArcaEquities][ArcaEquities.Exchange] · [ArcaOptions][ArcaOptions.Exchange] · [AsxDerivatives][AsxDerivatives.Exchange] · [B3Derivatives][B3Derivatives.Exchange] · [BzxEquities][BzxEquities.Exchange] · [CfeFutures][CfeFutures.Exchange] · [EdgxOptions][EdgxOptions.Exchange] · [IexEquities][IexEquities.Exchange] · [Lse][Lse.Exchange] · [MemxEquities][MemxEquities.Exchange] · [MiaxOptions][MiaxOptions.Exchange] · [NomOptions][NomOptions.Exchange] · [NordicEquities][NordicEquities.Exchange] · [NsmEquities][NsmEquities.Exchange] · [NyseEquities][NyseEquities.Exchange] · [OseDerivatives][OseDerivatives.Exchange] · [PearlEquities][PearlEquities.Exchange] · [PhlxOptions][PhlxOptions.Exchange] · [TseEquities][TseEquities.Exchange]

## Platforms

> [Cme Globex][Globex.Platform] · [Lseg Millennium][Millennium.Platform] · [Eurex T7][T7.Platform]

## Consolidators

> [Cqs][Cqs.Consolidator] · [Cts][Cts.Consolidator] · [Opra][Opra.Consolidator]

[Asx.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Asx "Australian Securities Exchange"
[B3.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/B3 "Brasil, Bolsa, Balcão"
[Cboe.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cboe "Chicago Board Options Exchange"
[Cme.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cme "CME Group"
[Eurex.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Eurex "Eurex Exchange"
[Iex.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Iex "Investors Exchange"
[Jpx.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Jpx "Japan Exchange Group"
[Lseg.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Lseg "London Stock Exchange"
[Memx.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Memx "The Members Exchange"
[Miax.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Miax "Miami International Holdings"
[Nasdaq.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq "National Association of Securities Dealers Automated Quotations (Nasdaq)"
[Nyse.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse "New York Stock Exchange"
[Siac.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Siac "The Securities Industry Automation Corporation"
[ArcaEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse/Protocols/ArcaEquities "Nyse Arca Equities"
[ArcaOptions.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse/Protocols/ArcaOptions "Nyse Arca Options"
[AsxDerivatives.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Asx/Protocols/AsxDerivatives "Asx Derivatives"
[B3Derivatives.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/B3/Protocols/B3Derivatives "B3 Derivatives"
[BzxEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cboe/Protocols/BzxEquities "Cboe Bzx Equities"
[CfeFutures.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cboe/Protocols/CfeFutures "Cboe Futures Exchange"
[Cqs.Consolidator]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Siac/Protocols/Cqs "Consolidated Quotation System"
[Cts.Consolidator]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Siac/Protocols/Cts "Consolidated Tape System"
[EdgxOptions.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cboe/Protocols/EdgxOptions "Cboe Edgx Options"
[Globex.Platform]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Cme/Protocols/Globex "CME Globex"
[IexEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Iex/Protocols/IexEquities "IEX Equities"
[Lse.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Lseg/Protocols/Lse "London Stock Exchange"
[MemxEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Memx/Protocols/MemxEquities "Memx Equities"
[MiaxOptions.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Miax/Protocols/MiaxOptions "MIAX Options"
[Millennium.Platform]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Lseg/Protocols/Millennium "Millennium Exchange"
[NomOptions.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq/Protocols/NomOptions "Nasdaq Options Market"
[NordicEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq/Protocols/NordicEquities "Nasdaq Nordic Equities"
[NsmEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq/Protocols/NsmEquities "Nasdaq Stock Market"
[NyseEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nyse/Protocols/NyseEquities "New York Stock Exchange Equities"
[Opra.Consolidator]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Siac/Protocols/Opra "Options Price Reporting Authority"
[OseDerivatives.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Jpx/Protocols/OseDerivatives "Osaka Securities Exchange"
[PearlEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Miax/Protocols/PearlEquities "MIAX Pearl Equities"
[PhlxOptions.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq/Protocols/PhlxOptions "Nasdaq PHLX"
[T7.Platform]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Eurex/Protocols/T7 "T7"
[TseEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Jpx/Protocols/TseEquities "Tokyo Stock Exchange Equities"
