# simple-dns-resolver
Simple DNS Resolver

### Overview
This project is a simple DNS response parser written in C.
It sends a DNS query and parses the server’s response, extracting useful information from the **Resource Records (RRs)**.

Currently, my code only supports:
- **A (Type 1)** : IPv4 address records
- **CNAME (Type 5)** : – Canonical name (alias) records

These are probably enough to resolve most common domain names into IP addresses.

### Usage
Compile it:
```
make
```
or
```
make re
```

Then run with a domain name:

```
./dns-resolve <domain-name>
```

### Improvements
- Support for additional record types:
  - AAAA (IPv6)
  - MX (Mail Exchange)
  - NS (Name Server)
  - PTR (Reverse DNS)
- Error handling and timeouts.
- More robust query building.
- ...

### Useful links
- https://datatracker.ietf.org/doc/html/rfc1035#autoid-44
- http://www.tcpipguide.com/free/t_DNSNameNotationandMessageCompressionTechnique-2.htm
