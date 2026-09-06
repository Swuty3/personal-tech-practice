# Base64 Encoder & Decoder

Simple C implementation of Base64 encode and decode, written for learning bit‑manipulation.

## Overview

Two standalone C programs implementing the Base64 encoding algorithm from scratch.
No external libraries, only standard C library.

- `convert_to_base64.c`：Base64 encoder，convert plain text string to base64 string，append padding `=` automatically.
- `convert_base64.c`：Base64 decoder，convert base64 string back to original text，support illegal character detection.

> 
> This is a learning‑practice project, not for production environment.

## Compile

```
# build encoder
gcc convert_to_base64.c -o b64enc

# build decoder
gcc convert_base64.c -o b64dec
```

## Usage

### Encode

```
./b64enc
Input a string: hello world
aGVsbG8gd29ybGQ=
```

### Decode

```
./b64dec
Input base64 code: aGVsbG8gd29ybGQ=
hello world
```

## Implementation notes

1. Encoder uses bit‑mask to split original 8‑bit bytes into 6‑bit groups for Base64 alphabet.
2. Auto‑fill padding character `=` to make output length multiple of 4.
3. Decoder maps Base64 character back to 6‑bit value, merge four 6‑bit groups into three 8‑bit bytes.
4. Contains error handling for invalid base64 input characters.
5. There is a commented alternative bit‑struct implementation idea in decoder source code.

## Limitations

- Fixed buffer size (101 bytes), input string length limited.
- Only handle printable string input, not designed for arbitrary binary data.
- For study purpose only, do not use in production.
