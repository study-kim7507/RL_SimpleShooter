'''
    클라이언트와 상호작용하면서 받은 데이터를 바탕으로 학습을 진행.
    데이터를 바탕으로 가장 가능성이 높은 action을 추출하여 클라이언트로 다시 전송.
'''

from Model import Qnet
import torch
from GameMaster import GameMaster
from Communication import networkInit
from Buffer import ReplayBuffer
import torch.optim as optim
import torch.nn.functional as F

# 연산을 CPU가 아닌 GPU에서 진행하겠다.(빠른 연산을 위해) 여러 개의 그래픽카드가 존재한다면, 0번째 그래픽 카드를 사용하겠다.
device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
print(device)

learning_rate = 0.0005
gamma = 0.98
batch_size = 32

Receive_Buffer = []
Send_Buffer = []

q = Qnet()
q.to(device)

q_target = Qnet()
q_target.load_state_dict(q.state_dict())

try:
    optimizer = optim.Adam(q.parameters(), lr=learning_rate)
    print("Optimizer created successfully")
except Exception as e:
    print(f"Error creating optimizer: {e}")

memory = ReplayBuffer(buffer_limit=1000)

networkInit(Send_Buffer, Receive_Buffer)
env = GameMaster(Send_Buffer, Receive_Buffer)

# 모델 훈련
def train(q, q_target, memory, optimizer):
    # 훈련 반복 횟수
    for i in range(10):
        # Replay memory에서 배치 사이즈만큼 샘플을 추출
        s, a, r, s_prime, done_mask = memory.sample(batch_size)

        # 현재 상태 s를 입력으로 하여 q 네트워크 출력을 계산
        q_out = q(s.to(device))
        # 선택된 행동 a에 대한 q값 추출
        q_a = q_out.gather(1, a.to(device))
        # 다음 상태 s_prime에 대한 target 네트워크의 최대 Q 값을 계산
        max_q_prime = q_target(s_prime).max(1)[0].unsqueeze(1)
        # 종료 여부를 고려한 감가율이 적용된 타겟 Q값 계산
        target = r + gamma * max_q_prime * done_mask
        # 예측된 Q값과 타겟 Q값 간의 손실 계산
        loss = F.smooth_l1_loss(q_a, target.to(device))

        # 옵티마이저의 그래디언트를 초기화
        optimizer.zero_grad()
        # 손실함수에 대한 그래디언트 역전파
        loss.backward()
        # 옵티마이저를 통해 모델의 가중치를 업데이트
        optimizer.step()

# 지정된 수만큼 에피소드 수행
for n_epi in range(1000):
    # 감가율이 0.01보다 크면 계산된 감가율을, 그렇지 않다면 0.01을
    epsilon = max(0.01, 0.08 - 0.01 * (n_epi / 200))  # Linear annealing from 8% to 1%

    # 매 에피소드마다 환경을 초기화
    s = env.reset()

    done = False

    cnt = 0
    reward = 0

    while not done:
        # action
        a = q.sample_action(torch.from_numpy(s).float().to(device), epsilon)
        # 행동 a에 따른 state_prime, reward, done

        s_p, r, done = env.step(a)

        done_mask = 0.0 if done else 1.0
        memory.put([s, a, r, s_p, done_mask])

        s = s_p

        reward += r
        cnt += 1

        if done or cnt > 20:
            break

    if memory.size() > 100:
         train(q, q_target, memory, optimizer)
    if n_epi % 5 == 0:
        q_target.load_state_dict(q.state_dict())

    # 50번의 에피소드마다 모델을 저장.
    # 학습 이후, 저장된 모델을 불러와 플레이에 적용을 위함.
    if n_epi % 50 == 0:
        PATH = './params7/q_net' + str(n_epi) + '.pth'
        torch.save(q.state_dict(), PATH)

