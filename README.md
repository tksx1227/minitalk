# minitalk
A programs that uses UNIX signals to perform small data exchange.

Place ft_printf in the root directory and use it.

[![tksx1227/ft_printf - GitHub](https://gh-card.dev/repos/tksx1227/ft_printf.svg?fullname=)](https://github.com/tksx1227/ft_printf)

## Description
It is a program that sends an arbitrary character string from the client to the server using a signal.

When the server receives the message, it signals the client side that the message was received successfully.

## Usage
Start the server and specify the process ID of the server and the message you want to send to the server as arguments to the client.

The client receives a response from the server depending on whether the message was sent successfully or unsuccessfully.

```bash
$ make
$ ./bin/server &
$ ./bin/client <SERVER_PROCESS_ID> <MESSAGES>
```

## Example

```
$ ./bin/server &
> PID: 42
$ ./bin/client 42 Hello
> Hello[ Successed to send message. ]
$ ./bin/client 42 "I'm sending message to process 42."
> I'm sending message to process 42.[ Successed to send message. ]
```
