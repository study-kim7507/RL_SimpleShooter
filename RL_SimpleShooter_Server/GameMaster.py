import struct
import time
import numpy as np
import collections

URPacket = {'reset': 0, 'step': 1}


class GameMaster:
    def __init__(self, Send_Buffer, Receive_Buffer):
        self.Send_Buffer = Send_Buffer
        self.Receive_Buffer = Receive_Buffer

    def step(self, a):
        # 언리얼로 'step'과 함께 action을 전송. 액션 값을 언리얼에서 받아 방어구 변경.
        data = bytes([URPacket['step']])
        data += bytes([a])
        self.Send_Buffer.append(data)

        while len(self.Receive_Buffer) <= 0:
            time.sleep(0.1)
		# 클라이언트(언리얼)에서 [CurrentHealth, Damage, Done] 형태로 데이터를 받음 -> 잘못 생각했음 -> [현재 방어구, Damage] 가 전달되어야함.
        packet = BytesToPacket(self.Receive_Buffer[0])
        self.Receive_Buffer.pop(0)

        info = 0
        state = np.array(packet[0:2]) # [현재 방어구, Damage]

        reward = 100 if int(packet[1]) == 5 else -100
        done = False if packet[2] == 0 else True

        return state, reward, done, info

    # 새로운 에피소드 학습을 위한 환경을 초기화
    def reset(self):
        # 언리얼로 reset을 전송. 환경을 초기화 -> 현재 체력 초기화 (언리얼 내에서)
        self.Send_Buffer.append(bytes([URPacket['reset']]))
        while len(self.Receive_Buffer) <= 0:
            time.sleep(0.1)
        state = eval(self.Receive_Buffer[0].decode('utf-8'))
        state = np.array(state[0:2]) # TODO: state = np.array(state[0:2]) done을 제외한 현재 체력과 데미지 만을 추출.

        self.Receive_Buffer.pop()

        return state

def BytesToPacket(data):
    # 바이트 데이터를 문자열로 디코딩하여 쉼표로 분할
    decoded_data = data.decode('utf-8')
    parts = decoded_data.split(',')

    # 실수로 변환하여 반환
    info = [float(part) for part in parts]
    return info
