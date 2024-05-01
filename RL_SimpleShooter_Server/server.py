import time
import socket
import random

# 서버 설정
host = ""
port =

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host, port))
server_socket.listen(5)

print(f"서버가 {host}:{port}에서 대기 중입니다..")

while True:
    # 클라이언트 연결 대기
    client_socket, client_address = server_socket.accept()
    print(f"클라이언트 {client_address}가 연결되었습니다.")

    try:
        # 클라이언트로부터 요청 받기
        data = client_socket.recv(1024).decode("utf-8")
        if not data:
          continue

        # 요청 파싱
        response = data
        print(response)

        while True:
            # TODO: 클라이언트로부터 받은 데이터를 모델로 전송.
            randInt = str(random.randint(0, 2))
            client_socket.send(randInt.encode("utf-8"))
            time.sleep(5)
            # TODO: 모델로부터 계산된 액션을 클라이언트로 전송.

    except Exception as e:
        print(f"오류 발생: {e}")

    finally:
        # 클라이언트 소켓 닫기
        print("연결종료")
        client_socket.close()