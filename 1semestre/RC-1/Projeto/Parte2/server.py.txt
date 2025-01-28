import socket
import threading
import signal
import sys
import random

# Signal handler for graceful shutdown
def signal_handler(sig, frame):
    print('\nServer shutting down...')
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)
print('Press Ctrl+C to exit...')

# Globals
ip_addr = "0.0.0.0"
tcp_port = 5005
client_stats = {}  # Dictionary to track clients: {address: (random_number, tries, player_name)}

# Client handler function
def handle_client_connection(client_socket, address):
    print(f'Accepted connection from {address[0]}:{address[1]}')
    
    try:
        # Receive player name
        player_name = client_socket.recv(1024).decode().strip()
        if not player_name:
            player_name = "Anonymous"
        print(f"Player '{player_name}' connected from {address[0]}:{address[1]}")
        
       # Initialize client state
        client_stats[address] = {
            "random_number": random.randint(1, 100),
            "tries": 0,
            "player_name": player_name,
            "total_tries": 0
        }
        client_socket.send(f"Welcome, {player_name}! Guess a number between 1 and 100.".encode())
        
        
        while True:
            guess = client_socket.recv(1024).decode().strip()
            if not guess:
                break
            
            # Handle the guess
            try:
                guess = int(guess)
                client_state = client_stats[address]
                random_number = client_state["random_number"]
                client_state["tries"] += 1
                client_state["total_tries"] += 1

                if guess < random_number:
                    response = "Too low! Try again."
                elif guess > random_number:
                    response = "Too high! Try again."
                else:
                    response = f"Congratulations, {client_state['player_name']}! You guessed the number in {client_state['tries']} tries."
                    response += " Starting a new game!"
                    # Reset for a new game
                    client_state["random_number"] = random.randint(1, 100)
                    client_state["tries"] = 0
                
                client_socket.send(response.encode())
            except ValueError:
                client_socket.send("Invalid input. Please enter a valid number.".encode())
    
    except (socket.timeout, socket.error) as e:
        print(f"Client {address} error: {e}")
    finally:
        print(f"Client {address[0]}:{address[1]} disconnected.")
        client_socket.close()
        if address in client_stats:
            del client_stats[address]

# Main server setup
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((ip_addr, tcp_port))
server.listen(5)  # Max backlog of connections

print(f'Listening on {ip_addr}:{tcp_port}')

while True:
    client_sock, address = server.accept()
    client_handler = threading.Thread(
        target=handle_client_connection,
        args=(client_sock, address),
        daemon=True
    )
    client_handler.start()