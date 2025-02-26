import socket
from pynput.mouse import Controller

# Initialize mouse controller
mouse = Controller()

# Server details
HOST = "0.0.0.0"  # Listen on all interfaces
PORT = 80         # Port to listen on

# Create a socket
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Listening on {HOST}:{PORT}")

    while True:
        conn, addr = s.accept()
        with conn:
            print(f"Connected by {addr}")
            while True:
                data = conn.recv(1024).decode().strip()
                if not data:
                    break

                # Parse the data (ax, ay)
                try:
                    ax, ay = map(float, data.split(","))
                    print(f"ax: {ax}, ay: {ay}")

                    # Map accelerometer data to mouse movement
                    move_x = int(ax * 10)  # Adjust scaling as needed
                    move_y = int(ay * 10)  # Adjust scaling as needed

                    # Move the mouse
                    mouse.move(move_x, move_y)
                except ValueError:
                    print("Invalid data received")