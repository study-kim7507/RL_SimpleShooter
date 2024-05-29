from Model import Qnet
import torch
from GameMaster import GameMaster
from Communication import networkInit

Receive_Buffer = []
Send_Buffer = []

networkInit(Send_Buffer, Receive_Buffer)
env = GameMaster(Send_Buffer, Receive_Buffer)

q = Qnet()

# 얼마나 학습한 network를 들고 올 것인가
trainNum = 500
# load 할 q_network를 Play.py 와 같은 directory에 위치 할 것
PATH = './params7/q_net' + str(trainNum) + '.pth'
q.load_state_dict(torch.load(PATH))

q_target = Qnet()
q_target.load_state_dict(q.state_dict())

score = 0.0

for n_epi in range(100):
    s = env.reset()
    done = False

    while not done:
        a = q.sample_action(torch.from_numpy(s).float(), 0)
        s_p, r, done, _ = env.step(a)
        s = s_p
        score += r
        if done:
            print(score)
            score = 0.0
            break
