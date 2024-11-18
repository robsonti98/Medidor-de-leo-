import serial
import time

ser = serial.Serial('COM6', 9600)  # Substitua 'COM3' pela porta correta
time.sleep(2)  # Aguarda a inicialização da conexão


while True:
    if ser.in_waiting > 0:  # Verifica se há dados na porta serial
        linha = ser.readline().decode('utf-8').strip()  # Lê a linha
        print(linha)  # Exibe os dados
        time.sleep(1)


