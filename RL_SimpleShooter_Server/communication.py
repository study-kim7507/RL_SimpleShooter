'''
    클라이언트와 데이터 송수신을 위한 함수 구현.
    서버 -> 클라이언트 : Send_Buffer에 존재하는 데이터를 전송
    클라이언트 -> 서버 : 클라이언트로부터 받은 데이터를 Receive_Buffer에 저장.
'''

import socket
import threading

STOP_FLAG = False

# 송수신하는 데이터 저장을 위함.
Send_Buffer = None
Receive_Buffer = None

# 서버 소켓을 설정하고, 클라이언트의 연결을 기다린 후, 데이터를 송수신하는 스레드 생성.
def networkInit(Send, Receive):
    global Send_Buffer
    global Receive_Buffer

    Send_Buffer = Send
    Receive_Buffer = Receive

    # 서버 설정
    # Local 기준, host = "127.0.0.1", port = "8888"
    host = "127.0.0.1"
    port = 8888

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))

    # 해당 소켓이 몇 개의 동시 접속을 허용하는지.
    # 서버 소켓은 상대방의 접속이 올 때까지 계속 대기 하는 상태
    server_socket.listen(1)
    print(f"서버가 {host}:{port}에서 대기 중입니다..")

    client_socket, client_address = server_socket.accept()
    print(f"클라이언트 {client_address}가 연결되었습니다.")

    # 송신을 위한 스레드, 수신을 위한 스레드 생성.
    sender = threading.Thread(target=send, args=(client_socket,))
    receiver = threading.Thread(target=receive, args=(client_socket,))

    sender.start()
    receiver.start()


def send(socket):
    global STOP_FLAG
    global Send_Buffer

    # Send_Buffer에 데이터가 있는 경우.
    # 즉, 클라이언트로 보낼 데이터가 존재하는 경우 클라이언트로 데이터를 전송
    while True:
        if len(Send_Buffer) > 0:
            socket.send(Send_Buffer[0])
            Send_Buffer.pop(0)
        if STOP_FLAG:
            break

def receive(socket):
    global STOP_FLAG
    global Receive_Buffer

    while True:
        # 클라이언트로부터 데이터가 수신되면 해당 데이터를 Receive_Buffer에 저장.
        recvData = socket.recv(1024)
        if recvData:
            Receive_Buffer.append(recvData)
        else:
            print('Disconeced')
            STOP_FLAG = True
            break
