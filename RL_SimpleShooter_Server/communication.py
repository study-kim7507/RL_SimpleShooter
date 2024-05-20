import socket
import threading
import random # For Test

STOP_FLAG = False

Send_Buffer = None
Receive_Buffer = None

def Init(Send, Receive):
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
            socket.send(Send_Buffer[0])
            Send_Buffer.pop(0)
        if STOP_FLAG:
            break

def receive(socket):
    global STOP_FLAG
    global Receive_Buffer
    global Send_Buffer # For Test
    while True:
        # 처음 시작 시 최초 한 번은 초기 체력 0의 데미지를 받아옴
        # 모델로부터 계산된 액션을 취한 뒤, 타격이 일어나면 데이터를 받음.
        recvData = socket.recv(1024).decode()
        print(stringToArray(recvData))
        if recvData:
            randInt = str(random.randint(0, 2))
            Send_Buffer.append(randInt.encode()) # For Test
            Receive_Buffer.append(recvData)
        else:
            print('Disconeced')
            STOP_FLAG = True
            break


# 클라이언트로부터 수신한 데이터를 파싱.
# 현재 구현에서는 [현재 체력, 받은 피해]
def stringToArray(recvData):
    string_list = recvData.split(",")
    float_list = [float(item) for item in string_list]

    return float_list