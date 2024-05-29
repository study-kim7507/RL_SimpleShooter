'''
    학습을 위한 환경 구축.
    현재 구현에서는 우리의 환경은 클라이언트(언리얼)에 구현되어 있음.
    -> 환경과 상호작용을 위한 Environment 구현.
'''

import time
import numpy as np

# 한 에피소드 종료 시. 클라이언트에게 환경 초기화 지시를 위한 reset.
# 에피소드 진행하는 과정에서 클라이언트에게 특정 action을 취하라는 지시를 위한 step
URPacket = {'reset': 0, 'step': 1}

class GameMaster:
    def __init__(self, Send_Buffer, Receive_Buffer):
        self.Send_Buffer = Send_Buffer
        self.Receive_Buffer = Receive_Buffer

    def step(self, action):
        # 클라이언트(언리얼)로 'step'과 함께 action을 전송.
        # 클라이언트 측에서는 모델로부터 계산된 action을 취하게 된다.
        data = bytes([URPacket['step']])
        data += bytes([action])
        self.Send_Buffer.append(data)

        while len(self.Receive_Buffer) <= 0:
            time.sleep(0.1)

        # action을 취한 후, 클라이언트로부터 받은 데이터를 바탕으로 reward 계산.
        packet = BytesToPacket(self.Receive_Buffer[0])
        self.Receive_Buffer.pop(0)

        # [상대 무기 번호, 현재 방어구 번호 (에이전트)]
        state = np.array(packet[0:2])

        # 올바른 방어구를 취해 적은 피해를 받으면 1의 reward.
        # 그렇지 않다면 -1의 reward.
        reward = 1 if state[0] == state[1] else -1

        # 에피소드 종료 조건.
        done = False if packet[2] == 0 else True

        return state, reward, done

    # 새로운 에피소드 학습을 위한 환경을 초기화
    def reset(self):
        # 한 에피소드가 종료되어 클라이언트로 환경을 초기화하라는 지시를 내림.
        self.Send_Buffer.append(bytes([URPacket['reset']]))
        while len(self.Receive_Buffer) <= 0:
            time.sleep(0.1)
        state = eval(self.Receive_Buffer[0].decode('utf-8'))
        state = np.array(state[0:2])

        self.Receive_Buffer.pop()

        return state

def BytesToPacket(data):
    # 바이트 데이터를 문자열로 디코딩하여 쉼표로 분할
    decoded_data = data.decode('utf-8')
    parts = decoded_data.split(',')

    # 실수로 변환하여 반환
    info = [float(part) for part in parts]
    return info
