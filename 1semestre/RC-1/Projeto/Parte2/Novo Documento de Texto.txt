import socket
import signal
import sys

# Signal handler for graceful shutdown
def signal_handler(sig, frame):
    print('\nExiting...')
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)
print('Press Ctrl+C to exit...')

# Globals
ip_addr = "203.4.11.114"
tcp_port = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((ip_addr, tcp_port))

# Get player name
player_name = input("Enter your player name: ").strip()
if not player_name:
    player_name = "Anonymous"

# Send player name to server
sock.send(player_name.encode())

# Game loop
try:
    while True:
        response = sock.recv(4096).decode()
        print(f'Server: {response}')
        
           
        if "Starting a new game!" in response:
            print("A new game has started!")
        
        guess = input("Your guess: ").strip()
        sock.send(guess.encode())
except (socket.timeout, socket.error) as e:
    print(f"Error: {e}")
finally:
    print("Goodbye!")
    sock.close()