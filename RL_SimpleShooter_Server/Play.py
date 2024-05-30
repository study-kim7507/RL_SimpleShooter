from Model import Qnet
import torch
from GameMaster import GameMaster
from Communication import networkInit
import matplotlib.pyplot as plt
import time

Receive_Buffer = []
Send_Buffer = []

networkInit(Send_Buffer, Receive_Buffer)
env = GameMaster(Send_Buffer, Receive_Buffer)

episodeNum = 1000
PATH = './result/q_net' + str(episodeNum) + '.pth'

q = Qnet()
q.load_state_dict(torch.load(PATH))

q_target = Qnet()
q_target.load_state_dict(q.state_dict())

score = 0.0
startTime = time.time()
saveResultTime = []
saveResultScore = []

s = env.reset()
while True:
    a = q.sample_action(torch.from_numpy(s).float(), 0)
    s_p, r, done = env.step(a)
    s = s_p

    score += r

    # 진행정도에 따른 점수를 시각화하기 위함.
    currentTime = time.time() - startTime
    saveResultTime.append(currentTime)
    saveResultScore.append(score)

    if done == 1:
        plt.plot(saveResultTime, saveResultScore)

        plt.title("Episode num : " + str(episodeNum))
        plt.xlabel("Time")
        plt.ylabel("Accumulated Rewards")

        plt.show()
        break


