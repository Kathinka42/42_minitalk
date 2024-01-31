# 42 Minitalk

## Introduction
Minitalk is a project that focuses on interprocess communication using signals in Unix-based systems. The goal is to implement a simple client-server architecture where the client sends messages to the server using signals, and the server processes and displays the received messages. The project is part of the core curriculum at 42Heilbronn.
## Features
- **Signal-Based Communication**: Using signals (SIGUSR1 and SIGUSR2) for communication between the client and server.
- **Binary Message Transmission**: Converting ASCII messages into binary and transmitting them bit by bit.
- **Acknowledgment Mechanism**: Implementing an acknowledgment mechanism to ensure reliable message delivery.

## Requirements
- Unix-based system (Linux or macOS)

## Technologies Used
- C Programming Language
- Unix Signals (SIGUSR1 and SIGUSR2)

## Installation and Usage

```bash
# Navigate to the project directory
cd minitalk

# Compile the server and client
make

# Start the server
./server

# In a separate terminal, start the client with the server's PID and the message to be sent
./client [server_pid] [message]
