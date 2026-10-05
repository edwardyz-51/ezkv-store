# KV Protocol — Version 1

## Framing

Each request and response ends with LF (`\n`).
A connection can carry multiple requests.
The client waits for a response before sending its next request.

## Commands

SET <key> <value>\n
GET <key>\n
DELETE <key>\n

Commands are case-sensitive.

## Keys and values

Keys contain 1–128 bytes and cannot contain whitespace.

SET uses one space between the command and key, and one space
between the key and value. Everything after the second separator
is the value, including additional spaces.

Values must be nonempty and cannot contain CR or LF.

GET and DELETE use one space before the key and allow no extra
arguments or trailing spaces.

Request lines cannot exceed 4,096 bytes, excluding the final LF.

## Responses

SET:
- OK\n

GET:
- VALUE <value>\n
- NOT_FOUND\n

DELETE:
- OK\n if the key existed and was removed
- NOT_FOUND\n if the key did not exist

Invalid request:
- ERROR BAD_REQUEST\n
- Keep the connection open.

Oversized request:
- ERROR LINE_TOO_LONG\n
- Close the connection.

## Behavior

SET overwrites an existing value.
GET never inserts a missing key.
An unfinished request is discarded when the connection closes.