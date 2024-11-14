import bluetooth
from datetime import datetime


# ---------------------------------------------------------------------
# configurando funções

def save_log(value):
	with open('logs.txt', 'a') as file:
		file.write(f"\n{datetime.now()} - {value}")


# ---------------------------------------------------------------------


target_name = "ESP32_BT"
target_address = None

print("Search for: ", target_name)

while 1:
	print('.')
	nearby_devices = bluetooth.discover_devices()

	for addr in nearby_devices:
		if target_name == bluetooth.lookup_name(addr):
			target_address = addr
			break
	break

if target_address is None:
	print("dispositivo nao encontrado")
	exit

print("conectando a esp32 com o endereco: ", target_address)
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((target_address, 1))

buffer = ""

while 1:

	data = sock.recv(1024).decode('utf-8')

	buffer += data

	if '\n' in buffer:

		lines = buffer.split('\n')

		for line in lines[:-1]:
			print("Dados recebidos: ", line)
			save_log(line)
		buffer = lines[-1]


