import socket
import threading
import random # For Test

STOP_FLAG = False
CNT = 0

Send_Buffer = None
Receive_Buffer = None

def networkInit(Send, Receive):
    global Send_Buffer
    global Receive_Buffer

    Send_Buffer = Send
    Receive_Buffer = Receive

    # 서버 설정
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

    sender = threading.Thread(target=send, args=(client_socket,))
    receiver = threading.Thread(target=receive, args=(client_socket,))

    sender.start()
    receiver.start()


def send(socket):
    global STOP_FLAG
    global Send_Buffer
    while True:
        if len(Send_Buffer) > 0:
            # ['step', 0], ['step', 1], ['step', 2] 혹은 ['reset'] 이라는 데이터가 언리얼로 전송될 것임.
            # [1, 0], [1, 1], [1, 2] 혹은 [0]이라는 값이 언리얼에서 확인 가능 -> URPacket = {'reset': 0, 'step': 1}
            socket.send(Send_Buffer[0])
            Send_Buffer.pop(0)
        if STOP_FLAG:
            break

def receive(socket):
    global STOP_FLAG
    global Receive_Buffer
    global CNT
    while True:
        recvData = socket.recv(1024)
        if recvData:
            CNT += 1
            Receive_Buffer.append(recvData)
        else:
            print('Disconeced')
            STOP_FLAG = True
            break
