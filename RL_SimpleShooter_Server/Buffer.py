'''
    DQN 알고리즘에서 사용되는 리플레이 메모리 구현.
    에이전트가 경험한 상태 전환(transition)을 저장.
    학습 시, 지정한 배치 사이즈만큼 무작위로 샘플링하여 사용
    -> 강화학습 에이전트는 환경과 상호작용하면서 상태, 행동, 보상, 다음 상태를 경험.
    -> 연속적인 경험들 사이에는 높은 상관성이 존재하는데 이는 학습에 부정적인 영향을 미침
    -> 리플레이 메모리를 통해 이러한 상관성을 줄이기 위함.
'''

import collections
import random
import torch
import numpy as np

class ReplayBuffer():
    # Deque 자료구조 활용. 지정한 버퍼 사이즈 이외의 데이터가 들어올 시, 가장 오래된 데이터부터 삭제.
    def __init__(self, buffer_limit=1000):
        self.buffer = collections.deque(maxlen=buffer_limit)

    def put(self, transition):
        self.buffer.append(transition)

    # 상관성을 줄이기 위해 리플레이 버퍼에서 지정한 배치 사이즈만큼 랜덤 샘플링.
    # 샘플링된 데이터를 바탕으로 학습을 진행.
    def sample(self, n):
        mini_batch = random.sample(self.buffer, n)
        s_lst, a_lst, r_lst, s_prime_lst, done_mask_lst = [], [], [], [], []

        for transition in mini_batch:
            s, a, r, s_prime, done_mask = transition
            s_lst.append(s)
            a_lst.append([a])
            r_lst.append([r])
            s_prime_lst.append(s_prime)
            done_mask_lst.append([done_mask])

        # Convert lists to numpy arrays
        s_array = np.array(s_lst)
        a_array = np.array(a_lst)
        r_array = np.array(r_lst)
        s_prime_array = np.array(s_prime_lst)
        done_mask_array = np.array(done_mask_lst)

        # Convert numpy arrays to PyTorch tensors
        return torch.tensor(s_array, dtype=torch.float), torch.tensor(a_array, dtype=torch.int64), \
               torch.tensor(r_array), torch.tensor(s_prime_array, dtype=torch.float), \
               torch.tensor(done_mask_array)

    def size(self):
        return len(self.buffer)
