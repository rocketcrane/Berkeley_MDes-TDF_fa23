import serial
from pythonosc.udp_client import SimpleUDPClient
from pythonosc import osc_bundle_builder
from pythonosc import osc_message_builder

# Configuration
SERIAL_PORT = '/dev/ttys014'  # Adjust this to your serial port
SERIAL_BAUDRATE = 9600
UDP_IP = '127.0.0.1'  # Localhost (adjust if needed)
UDP_PORT = 12345

# Set up serial connection
ser = serial.Serial(SERIAL_PORT, SERIAL_BAUDRATE, timeout=1)  # 1 second timeout
# print(f"Connected to {SERIAL_PORT} at {SERIAL_BAUDRATE} baud")

# Set up OSC client
client = SimpleUDPClient(UDP_IP, UDP_PORT)

# variables for accelerometer values
x = 0
y = 0
z = 0
r = 0
p = 0
t = 0
# indices for string split
xIndex = 4
yIndex = 6
zIndex = 8
rIndex = 10
pIndex = 12
tIndex = 14

try:
	while True:
		data = ser.readline()  # Read a line from the serial port
		if data:
			splitData = str.split(str(data))
			# split all the numbers out of the string
			if len(splitData) > xIndex:
				x = splitData[xIndex].split(',')[0]
			if len(splitData) > yIndex:
				y = splitData[yIndex].split(',')[0]
			if len(splitData) > zIndex:
				z = splitData[zIndex].split(',')[0]
			if len(splitData) > rIndex:
				r = splitData[rIndex].split(',')[0]
			if len(splitData) > pIndex:
				p = splitData[pIndex].split(',')[0]
			if len(splitData) > tIndex:
				t = splitData[tIndex].split('\\')[0]
			# Initialize the bundle builder
			bundle = osc_bundle_builder.OscBundleBuilder(osc_bundle_builder.IMMEDIATELY)
			# Create the OSC message and add arguments
			msg = osc_message_builder.OscMessageBuilder(address="/x")
			msg.add_arg(x)
			bundle.add_content(msg.build())
			msg = osc_message_builder.OscMessageBuilder(address="/y")
			msg.add_arg(y)
			bundle.add_content(msg.build())
			msg = osc_message_builder.OscMessageBuilder(address="/z")
			msg.add_arg(z)
			bundle.add_content(msg.build())
			msg = osc_message_builder.OscMessageBuilder(address="/r")
			msg.add_arg(r)
			bundle.add_content(msg.build())
			msg = osc_message_builder.OscMessageBuilder(address="/p")
			msg.add_arg(p)
			bundle.add_content(msg.build())
			msg = osc_message_builder.OscMessageBuilder(address="/t")
			msg.add_arg(t)
			# Add the message to the bundle
			bundle.add_content(msg.build())
			# Build the bundle
			final_bundle = bundle.build()
			client.send(final_bundle)
		else:
			print("No data received from serial port")

except KeyboardInterrupt:
	print("\nStopping...")
finally:
	ser.close()