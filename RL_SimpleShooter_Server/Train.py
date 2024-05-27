import time
from Model import Qnet
import torch
from GameMaster import GameMaster
from Communication import networkInit
from Buffer import ReplayBuffer
import torch.optim as optim
import torch.nn.functional as F
# import matplotlib.pyplot as plt

# 연산을 CPU가 아닌 GPU에서 진행하겠다.(빠른 연산을 위해) 여러 개의 그래픽카드가 존재한다면, 0번째 그래픽 카드를 사용하겠다.
device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
print(device)

learning_rate = 0.0005
gamma = 0.98
batch_size = 20

Receive_Buffer = []
Send_Buffer = []

q = Qnet()
q.to(device)
# q.load_state_dict(torch.load('./params7/q_net50.pth'))
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
    for i in range(1):
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

        # 옵티마이저의 그라디언트를 초기화
        optimizer.zero_grad()
        # 손실함수에 대한 그라디언트 역전파
        loss.backward()
        # 옵티마이저를 통해 모델의 가중치를 업데이트
        optimizer.step()

# 에피소드를 1000번 실행
for n_epi in range(1000):
    # 감가율이 0.01보다 크면 계산된 감가율을, 그렇지 않다면 0.01을
    epsilon = max(0.01, 0.08 - 0.01 * (n_epi / 200))  # Linear annealing from 8% to 1%

    # 매 에피소드마다 환경을 초기화
    s = env.reset()

    # 해당 구문으로 인해 언리얼에서 보내는 Done이 1이어도 한번은 학습과정을 거침.
    # 즉, 언리얼에서 보내는 done이 계속 1이면 한번 step이후, 한번 reset 과정 -> 한 에피소드에 한 step 과정 거침
    # 언리얼에서 done 값을 상황에 따라 맞게 변경하는 구현을 진행해야함 -> 캐릭터가 죽으면 done을 1로 한다던가..
    done = False

    # 한번의 에피소드가 끝나는 조건 중 하나 cnt > 2000
    cnt = 0
    reward = 0


    while not done:
        # action
        a = q.sample_action(torch.from_numpy(s).float().to(device), epsilon)
        # 행동 a 에 따른 state_prime, reward, done
        s_p, r, done, _ = env.step(a)
        done_mask = 0.0 if done else 1.0
        # replay memory에 MDP, transition을 추가
        memory.put([s, a, r, s_p, done_mask])

        # 이제 state는 state'
        s = s_p

        reward += r
        cnt += 1



        if done or cnt > 50:
            break

    # TODO: 언리얼: 100초에 한번씩 무기 교체
    if memory.size() > 50:
         print("Train!")
         train(q, q_target, memory, optimizer)
    if n_epi % 5 == 0:
        q_target.load_state_dict(q.state_dict())

    if n_epi % 50 == 0:
        PATH = './params7/q_net' + str(n_epi) + '.pth'
        torch.save(q.state_dict(), PATH)

PATH = './q_net7.pth'
torch.save(q.state_dict(), PATH)

